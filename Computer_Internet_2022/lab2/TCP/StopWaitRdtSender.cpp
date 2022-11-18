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
	if (this->waitingState) { //发送方处于等待确认状态
		return false;
	}
	if (expectSequenceNumberSend < base + N) {
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].acknum = -1; //忽略该字段
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].seqnum = this->expectSequenceNumberSend;
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].checksum = 0;
		memcpy(this->packetWaitingAck[expectSequenceNumberSend % SeqLength].payload, message.data, sizeof(message.data));
		this->packetWaitingAck[expectSequenceNumberSend % SeqLength].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[expectSequenceNumberSend % SeqLength]);
		pUtils->printPacket("发送方发送报文", this->packetWaitingAck[expectSequenceNumberSend % SeqLength]);
		if (base == expectSequenceNumberSend) {
			cout << "发送方启动计时器" << endl;
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[expectSequenceNumberSend % SeqLength].seqnum);
		}
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

	if (checkSum == ackPkt.checksum && ackPkt.acknum >= base) {
		int tmpbase = base;
		base = ackPkt.acknum + 1;
		//this->expectSequenceNumberSend = 1 - this->expectSequenceNumberSend;			//下一个发送序号在0-1之间切换
		//this->waitingState = false;
		pUtils->printPacket("发送方正确收到确认", ackPkt);
		for (int i = base + N; i < base + 8; i++) {
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
		if (base == expectSequenceNumberSend) {
			cout << "当前分组以全部接收，关闭计时器" << endl;
			waitingState = false;
			pns->stopTimer(SENDER, tmpbase);		//关闭定时器
		}
		else {
			cout << "当前分组还没接受完，继续等待" << endl;
			pns->stopTimer(SENDER, tmpbase);
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
		}
	}
	else {
		if (checkSum != ackPkt.checksum) {
			cout << "发送方收到的ACK损坏" << endl;
		}
		else {
			//cout << "发送方没有收到正确的序号，继续等待" << endl;
			if (lastack == ackPkt.acknum) {
				ackcnt++;
				if (ackcnt == 4) {
					cout << "收到了3个冗余ack，开始快速重传，冗余ack序号为" << lastack + 1 << endl;
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
	//唯一一个定时器,无需考虑seqNum
	cout << "超时了，进行Back N" << endl;
	pns->stopTimer(SENDER, seqNum);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
//	for (int i = base; i < expectSequenceNumberSend; i++) {
		cout << "重发第" << seqNum << "个报文" << endl;
		pUtils->printPacket("发送方定时器时间到，重发报文", this->packetWaitingAck[seqNum % SeqLength]);
		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[seqNum % SeqLength]);
	//}
}
