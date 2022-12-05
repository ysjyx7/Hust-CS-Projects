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
	if (this->waitingState) { //发送方处于等待确认状态
		return false;
	}
	if (expectSequenceNumberSend < base + N) {
		packetWaitingAck[expectSequenceNumberSend % SeqLength].ACK = false;
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].acknum = -1; //忽略该字段
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].seqnum = this->expectSequenceNumberSend;
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].checksum = 0;
		memcpy(this->packetWaitingAck[expectSequenceNumberSend % SeqLength].payload, message.data, sizeof(message.data));
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[expectSequenceNumberSend % SeqLength]);
		pUtils->printPacket("发送方发送报文", this->packetWaitingAck[expectSequenceNumberSend % SeqLength]);
		cout << "发送方启动计时器" << expectSequenceNumberSend << endl;
		pns->startTimer(SENDER, Configuration::TIME_OUT, expectSequenceNumberSend);
		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[expectSequenceNumberSend % SeqLength]);			//启动发送方定时器
		expectSequenceNumberSend++;
		cout << "当前报文发送后nextseqnum为" << expectSequenceNumberSend << endl;
		if (expectSequenceNumberSend == base + N) {
			waitingState = true;
		}
	}																				//进入等待状态
	return true;
}

void StopWaitRdtSender::receive(const Packet& ackPkt) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//如果校验和正确，并且确认序号=发送方已发送并等待确认的数据包序号
	if (checkSum == ackPkt.checksum) {
		//this->expectSequenceNumberSend = 1 - this->expectSequenceNumberSend;			//下一个发送序号在0-1之间切换
		//this->waitingState = false;
		pUtils->printPacket("发送方正确收到确认", ackPkt);
		for (int i = base + N; i < base + SeqLength; i++) {
			packetWaitingAck[i % SeqLength].seqnum = -1;
		}
		cout << "发送方滑动窗口内容为 " << '[' << ' ';
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
			cout << "收到的该报文的ack序号为" << base << endl;
			pns->stopTimer(SENDER, base);
			packetWaitingAck[base % SeqLength].ACK = true;
			while (packetWaitingAck[base % SeqLength].ACK) {
				packetWaitingAck[(base++) % SeqLength].ACK = false;
			}
			waitingState = false;
		}else if(ackPkt.acknum>base&&packetWaitingAck[ackPkt.acknum%SeqLength].ACK==false){
			packetWaitingAck[ackPkt.acknum % SeqLength].ACK = true;
			cout << "收到了窗口中的未确认ack" << ackPkt.acknum << endl;
			pns->stopTimer(SENDER, ackPkt.acknum);
		}
		else {
			cout << "收到了无用ack" << endl;
		}
	}
	else {
		//if (checkSum != ackPkt.checksum) {
			cout << "发送方收到的ACK损坏" << endl;
		//}
		//e/lse {
		//	cout << "发送方没有收到正确的序号，继续等待" << endl;
		//}
	}
}

void StopWaitRdtSender::timeoutHandler(int seqNum) {
	//唯一一个定时器,无需考虑seqNum
	cout << "超时了" << endl;
	pns->stopTimer(SENDER, seqNum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	//for (int i = base; i < expectSequenceNumberSend; i++) {
		cout << "重发第" << seqNum << "个报文" << endl;
		pUtils->printPacket("发送方定时器时间到，重发报文", this->packetWaitingAck[seqNum % SeqLength]);
		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[seqNum % SeqLength]);
	//}
}
