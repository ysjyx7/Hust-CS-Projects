#include "stdafx.h"
#include "Global.h"
#include "StopWaitRdtReceiver.h"


StopWaitRdtReceiver::StopWaitRdtReceiver() :expectSequenceNumberRcvd(N), base(0)
{
	lastAckPkt.acknum = -1; //��ʼ״̬�£��ϴη��͵�ȷ�ϰ���ȷ�����Ϊ-1��ʹ�õ���һ�����ܵ����ݰ�����ʱ��ȷ�ϱ��ĵ�ȷ�Ϻ�Ϊ-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//���Ը��ֶ�
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
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(packet);

	//���У�����ȷ��ͬʱ�յ����ĵ���ŵ��ڽ��շ��ڴ��յ��ı������һ��
	if (checkSum == packet.checksum) {
		//pUtils->printPacket("���շ���ȷ�յ����ͷ��ı���", packet);
		cout << "���շ�������������Ϊ��[ ";
		for (int i = base; i < base + N; i++) {
			cout << i << ' ';
		}
		cout << ']' << endl;
		if (base == packet.seqnum) {
			cout << "���շ��յ��ı������Ϊ�����" << base << endl;
			lastAckPkt.acknum = packet.seqnum;
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
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
			cout << "���շ��յ��ı������Ϊ" << packet.seqnum << endl;
			pUtils->printPacket("���շ��ѻ��淢�ͷ��ı���", packet);
			CachePacket[packet.seqnum % SeqLength] = packet;
			CachePacket[packet.seqnum % SeqLength].ACK = true;
			lastAckPkt.acknum = packet.seqnum;
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
		}
		else if (packet.seqnum >= base - N && packet.seqnum <= base - 1) {
			pUtils->printPacket("���շ���ȷ�յ���ȷ�ϵĹ�ʱ����", packet);
			lastAckPkt.acknum = packet.seqnum;
			lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
			pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
			pns->sendToNetworkLayer(SENDER, lastAckPkt);
		}
		else {
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,������Ų���", packet);
			cout << "��ʱ���շ��ڴ��������" << this->base << "��" << this->expectSequenceNumberRcvd << "֮��" << endl;
		}
	}
	else {
		//if (checkSum != packet.checksum) {
		pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,����У�����", packet);
		//}
		//else {
			//pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,������Ų���", packet);
		//}
		//pUtils->printPacket("���շ����·����ϴε�ȷ�ϱ���", lastAckPkt);
		//pns->sendToNetworkLayer(SENDER, lastAckPkt);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢���ϴε�ȷ�ϱ���

	}
}