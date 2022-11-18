#include "stdafx.h"
#include "Global.h"
#include "StopWaitRdtReceiver.h"


StopWaitRdtReceiver::StopWaitRdtReceiver() :expectSequenceNumberRcvd(N), base(0)
{
	lastAckPkt.acknum = -1; //初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//忽略该字段
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastAckPkt.payload[i] = '.';
	}
	for (int i = 0; i < SeqLength; i++) {
		CachePacket[i].ACK = false;
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}


StopWaitRdtReceiver::~StopWaitRdtReceiver()
{
}

void StopWaitRdtReceiver::receive(const Packet& packet) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(packet);

	//如果校验和正确，同时收到报文的序号等于接收方期待收到的报文序号一致
	if (checkSum == packet.checksum) {
		//pUtils->printPacket("接收方正确收到发送方的报文", packet);
		cout << "接收方滑动窗口内容为：[ ";
		for (int i = base; i < base + N; i++) {
			cout << i << ' ';
		}
		cout << ']' << endl;
		if (base == packet.seqnum) {
			cout << "接收方收到的报文序号为基序号" << base << endl;
			lastAckPkt.acknum = packet.seqnum;
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("接收方发送确认报文", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
			CachePacket[base % SeqLength] = packet;
			CachePacket[base % SeqLength].ACK = true;
			//CachePacket[base % SeqLength].acknum = 0;
			while (CachePacket[base % SeqLength].ACK) {
				Message msg;
				memcpy(msg.data, CachePacket[base % SeqLength].payload, sizeof(packet.payload));
				pns->delivertoAppLayer(RECEIVER, msg);
				CachePacket[base++ % SeqLength].ACK = false;
				CachePacket[packet.seqnum % SeqLength].acknum = -1;
				CachePacket[expectSequenceNumberRcvd++ % SeqLength].ACK = false;
			}
		}
		else if (packet.seqnum > base && packet.seqnum < expectSequenceNumberRcvd) {
			cout << "接收方收到的报文序号为" << packet.seqnum << endl;
			pUtils->printPacket("接收方已缓存发送方的报文", packet);
			CachePacket[packet.seqnum % SeqLength] = packet;
			CachePacket[packet.seqnum % SeqLength].ACK = true;
			lastAckPkt.acknum = packet.seqnum;
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("接收方发送确认报文", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
		}
		else if (packet.seqnum >= base - N && packet.seqnum <= base - 1) {
			pUtils->printPacket("接收方正确收到已确认的过时报文", packet);
			lastAckPkt.acknum = packet.seqnum;
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("接收方发送确认报文", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
		}
		else {
			pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
			cout << "此时接收方期待的序号在" << this->base << "和" << this->expectSequenceNumberRcvd << "之间" << endl;
		}
	}
	else {
		//if (checkSum != packet.checksum) {
		pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
		//}
		//else {
			//pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
		//}
		//pUtils->printPacket("接收方重新发送上次的确认报文", lastAckPkt);
		//pns->sendToNetworkLayer(SENDER, lastAckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送上次的确认报文

	}
}