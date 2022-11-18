#include "stdafx.h"
#include "Global.h"
#include "StopWaitRdtSender.h"


StopWaitRdtSender::StopWaitRdtSender() :base(0),expectSequenceNumberSend(0), waitingState(false),lastack(-1),ackcnt(0)
{
	for (int i = 0; i < SeqLength; i++) {
		packetWaitingAck[i].seqnum = -1;
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
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].acknum = -1; //���Ը��ֶ�
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].seqnum = this->expectSequenceNumberSend;
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].checksum = 0;
		memcpy(this->packetWaitingAck[expectSequenceNumberSend % SeqLength].payload, message.data, sizeof(message.data));
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[expectSequenceNumberSend % SeqLength]);
		pUtils->printPacket("���ͷ����ͱ���", this->packetWaitingAck[expectSequenceNumberSend % SeqLength]);
		if (base == expectSequenceNumberSend) {
			cout << "���ͷ�������ʱ��" << endl;
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[expectSequenceNumberSend % SeqLength].seqnum);
		}
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

	if (checkSum == ackPkt.checksum && ackPkt.acknum >= base) {
		int tmpbase = base;
		base = ackPkt.acknum + 1;
		//this->expectSequenceNumberSend = 1 - this->expectSequenceNumberSend;			//��һ�����������0-1֮���л�
		//this->waitingState = false;
		pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
		for (int i = base + N; i < base + 8; i++) {
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
		if (base == expectSequenceNumberSend) {
			cout << "��ǰ������ȫ�����գ��رռ�ʱ��" << endl;
			waitingState = false;
			pns->stopTimer(SENDER, tmpbase);		//�رն�ʱ��
		}
		else {
			cout << "��ǰ���黹û�����꣬�����ȴ�" << endl;
			pns->stopTimer(SENDER, tmpbase);
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
		}
	}
	else {
		if (checkSum != ackPkt.checksum) {
			cout << "���ͷ��յ���ACK��" << endl;
		}
		else {
			//cout << "���ͷ�û���յ���ȷ����ţ������ȴ�" << endl;
			if (lastack == ackPkt.acknum) {
				ackcnt++;
				if (ackcnt == 4) {
					cout << "�յ���3������ack����ʼ�����ش�������ack���Ϊ" << lastack + 1 << endl;
					pns->stopTimer(SENDER, lastack + 1);
					pns->startTimer(SENDER, Configuration::TIME_OUT, lastack + 1);
					pns->sendToNetworkLayer(RECEIVER, packetWaitingAck[(lastack+1) % SeqLength]);
				}
			}
			else {
				lastack = ackPkt.acknum;
				ackcnt = 1;
			}
		}
	}
}

void StopWaitRdtSender::timeoutHandler(int seqNum) {
	//Ψһһ����ʱ��,���迼��seqNum
	cout << "��ʱ�ˣ�����Back N" << endl;
	pns->stopTimer(SENDER, seqNum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
//	for (int i = base; i < expectSequenceNumberSend; i++) {
		cout << "�ط���" << seqNum << "������" << endl;
		pUtils->printPacket("���ͷ���ʱ��ʱ�䵽���ط�����", this->packetWaitingAck[seqNum % SeqLength]);
		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[seqNum % SeqLength]);
	//}
}
