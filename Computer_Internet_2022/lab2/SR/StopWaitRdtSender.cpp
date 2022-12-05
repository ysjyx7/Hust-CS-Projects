#include "stdafx.h"
#include "Global.h"
#include "StopWaitRdtSender.h"


StopWaitRdtSender::StopWaitRdtSender() :base(0),expectSequenceNumberSend(0), waitingState(false)
{
	for (int i = 0; i < SeqLength; i++) {
		packetWaitingAck[i].seqnum = -1;
		packetWaitingAck[i].ACK = false;
	}
}


StopWaitRdtSender::~StopWaitRdtSender()
{
}



bool StopWaitRdtSender::getWaitingState() {
	return waitingState;
}




bool StopWaitRdtSender::send(const Message& message) {
	if (this->waitingState) { //���ͷ����ڵȴ�ȷ��״̬
		return false;
	}
	if (expectSequenceNumberSend < base + N) {
		packetWaitingAck[expectSequenceNumberSend % SeqLength].ACK = false;
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].acknum = -1; //���Ը��ֶ�
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].seqnum = this->expectSequenceNumberSend;
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].checksum = 0;
		memcpy(this->packetWaitingAck[expectSequenceNumberSend % SeqLength].payload, message.data, sizeof(message.data));
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[expectSequenceNumberSend % SeqLength]);
		pUtils->printPacket("���ͷ����ͱ���", this->packetWaitingAck[expectSequenceNumberSend % SeqLength]);
		cout << "���ͷ�������ʱ��" << expectSequenceNumberSend << endl;
		pns->startTimer(SENDER, Configuration::TIME_OUT, expectSequenceNumberSend);
		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[expectSequenceNumberSend % SeqLength]);			//�������ͷ���ʱ��
		expectSequenceNumberSend++;
		cout << "��ǰ���ķ��ͺ�nextseqnumΪ" << expectSequenceNumberSend << endl;
		if (expectSequenceNumberSend == base + N) {
			waitingState = true;
		}
	}																				//����ȴ�״̬
	return true;
}

void StopWaitRdtSender::receive(const Packet& ackPkt) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ������ȷ�����=���ͷ��ѷ��Ͳ��ȴ�ȷ�ϵ����ݰ����
	if (checkSum == ackPkt.checksum) {
		//this->expectSequenceNumberSend = 1 - this->expectSequenceNumberSend;			//��һ�����������0-1֮���л�
		//this->waitingState = false;
		pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
		for (int i = base + N; i < base + SeqLength; i++) {
			packetWaitingAck[i % SeqLength].seqnum = -1;
		}
		cout << "���ͷ�������������Ϊ " << '[' << ' ';
		for (int i = base; i < base + N; i++) {
			if (packetWaitingAck[i % SeqLength].seqnum == -1) {
				cout << '*' << ' ';
			}
			else {
				cout << packetWaitingAck[i % SeqLength].seqnum << ' ';
			}
		}
		cout << ']' << endl;
		if (base == ackPkt.acknum) {
			cout << "�յ��ĸñ��ĵ�ack���Ϊ" << base << endl;
			pns->stopTimer(SENDER, base);
			packetWaitingAck[base % SeqLength].ACK = true;
			while (packetWaitingAck[base % SeqLength].ACK) {
				packetWaitingAck[(base++) % SeqLength].ACK = false;
			}
			waitingState = false;
		}else if(ackPkt.acknum>base&&packetWaitingAck[ackPkt.acknum%SeqLength].ACK==false){
			packetWaitingAck[ackPkt.acknum % SeqLength].ACK = true;
			cout << "�յ��˴����е�δȷ��ack" << ackPkt.acknum << endl;
			pns->stopTimer(SENDER, ackPkt.acknum);
		}
		else {
			cout << "�յ�������ack" << endl;
		}
	}
	else {
		//if (checkSum != ackPkt.checksum) {
			cout << "���ͷ��յ���ACK��" << endl;
		//}
		//e/lse {
		//	cout << "���ͷ�û���յ���ȷ����ţ������ȴ�" << endl;
		//}
	}
}

void StopWaitRdtSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	cout << "��ʱ��" << endl;
	pns->stopTimer(SENDER, seqNum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	//for (int i = base; i < expectSequenceNumberSend; i++) {
		cout << "�ط���" << seqNum << "������" << endl;
		pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط�����", this->packetWaitingAck[seqNum % SeqLength]);
		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[seqNum % SeqLength]);
	//}
}
