#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once
#include "winsock2.h"
#include"http.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include<fstream>
#include <list>
#include"Config.h"
using namespace std;

#pragma comment(lib,"ws2_32.lib")
bool GetFile(string filepath, Request& req);
//��chrome�������һ����ҳʱ������������ҳ�����⣬���ᷢ������һ������ /favicon.ico������ȸ��������ͼ��
//���Serverʵ���ϴ��˶���ỰSocket����Ҫһ��List��������Щ�ỰSocket
//����򿪵ĵ�ǰ�ĻỰsocket

list<SOCKET> sessionSockets;

void main() {
	cout << "Please input the filepath:";
	cin >> Config::PATH;
	cout << "Please input the Server Address:";
	cin >> Config::SERVERADDRESS;
	cout << "Please input the Port:";
	cin >> Config::PORT;
	WSADATA wsaData;
	/*
		select()�������ṩ��fd_set�����ݽṹ��ʵ������long���͵����飬
		ÿһ������Ԫ�ض�����һ�򿪵��ļ������������socket��������������ļ��������ܵ����豸�����������ϵ��������ϵ�Ĺ����ɳ���Ա���.
		������select()ʱ�����ں˸���IO״̬�޸�fd_set�����ݣ��ɴ���ִ֪ͨ����select()�Ľ����ĸ�socket���ļ���������˿ɶ����д�¼���
	*/
	fd_set rfds;				//���ڼ��socket�Ƿ������ݵ����ĵ��ļ�������������socket������ģʽ�µȴ������¼�֪ͨ�������ݵ�����
	fd_set wfds;				//���ڼ��socket�Ƿ���Է��͵��ļ�������������socket������ģʽ�µȴ������¼�֪ͨ�����Է������ݣ�
	//bool first_connetion = true;

	int nRc = WSAStartup(0x0202, &wsaData);

	if (nRc) {
		printf("Winsock  startup failed with error!\n");
	}

	if (wsaData.wVersion != 0x0202) {
		printf("Winsock version is not correct!\n");
	}

	printf("Winsock  startup Ok!\n");


	//����socket
	SOCKET srvSocket;

	//��������ַ�Ϳͻ��˵�ַ
	sockaddr_in addr, clientAddr;

	//�Ựsocket�������client����ͨ��
	SOCKET sessionSocket;

	//ip��ַ����
	int addrLen;

	//��������socket
	srvSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (srvSocket != INVALID_SOCKET)
		printf("Socket create Ok!\n");


	//���÷������Ķ˿ں͵�ַ
	//addr.sin_family = AF_INET;
	//addr.sin_port = htons(5050);
	//addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //����������һ��������IP��ַ
	addr.sin_family = AF_INET;
	addr.sin_port = htons(Config::PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(Config::SERVERADDRESS.c_str());

	//binding
	int rtn = bind(srvSocket, (LPSOCKADDR)&addr, sizeof(addr));
	if (rtn != SOCKET_ERROR)
		printf("Socket bind Ok!\n");

	//����
	rtn = listen(srvSocket, 5);
	if (rtn != SOCKET_ERROR)
		printf("Socket listen Ok!\n");

	clientAddr.sin_family = AF_INET;
	addrLen = sizeof(clientAddr);

	//���ý��ջ�����
	char recvBuf[4096];

	u_long blockMode = 1;//��srvSock��Ϊ������ģʽ�Լ����ͻ���������

	//����ioctlsocket����srvSocket��Ϊ������ģʽ���ĳɷ������fd_setԪ�ص�״̬����ÿ��Ԫ�ض�Ӧ�ľ���Ƿ�ɶ����д
	if ((rtn = ioctlsocket(srvSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO��������ֹ�׽ӿ�s�ķ�����ģʽ��
		cout << "ioctlsocket() failed with error!\n";
		return;
	}
	cout << "ioctlsocket() for server socket ok!	Waiting for client connection\n";

	while (true) {
		//���rfds��wfds����
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);

		//��srvSocket����rfds����
		//�������ͻ�������������ʱ��rfds������srvSocket��Ӧ�ĵ�״̬Ϊ�ɶ�
		//��������������þ��ǣ����õȴ��ͻ���������
		FD_SET(srvSocket, &rfds);

		for (list<SOCKET>::iterator itor = sessionSockets.begin(); itor != sessionSockets.end(); itor++) {
			//��sessionSockets���ÿ���Ựsocket����rfds�����wfds����
			//�������ͻ��˷������ݹ���ʱ��rfds������sessionSocket�Ķ�Ӧ��״̬Ϊ�ɶ��������Է������ݵ��ͻ���ʱ��wfds������sessionSocket�Ķ�Ӧ��״̬Ϊ��д
			//�����������������þ��ǣ�
			//���õȴ����лỰSOKCET�ɽ������ݻ�ɷ�������
			FD_SET(*itor, &rfds);
			FD_SET(*itor, &wfds);
		}

		/*
			select����ԭ������Ҫ�������ļ����������ϣ��ɶ�����д�����쳣����ʼ������select��������״̬��
			���пɶ�д�¼����������õĵȴ�ʱ��timeout���˾ͻ᷵�أ�����֮ǰ�Զ�ȥ�����������¼��������ļ�������������ʱ�������¼��������ļ����������ϡ�
			��select�����ļ��ϲ�û�и����û������а����ļ����������ļ�����������Ҫ�û��������б�������(ͨ��FD_ISSET���ÿ�������״̬)��
		*/
		//��ʼ�ȴ����ȴ�rfds���Ƿ��������¼���wfds���Ƿ��п�д�¼�
		//The select function returns the total number of socket handles that are ready and contained in the fd_set structure
		//�����ܹ����Զ���д�ľ������
		int nTotal = select(0, &rfds, &wfds, NULL, NULL);

		//���srvSock�յ��������󣬽��ܿͻ���������
		if (FD_ISSET(srvSocket, &rfds)) {
			nTotal--;   //��Ϊ�ͻ���������Ҳ��ɶ��¼������-1��ʣ�µľ��������пɶ��¼��ľ�����������ж��ٸ�socket�յ������ݣ�

			//�����µĻỰSOCKET
			sessionSocket = accept(srvSocket, (LPSOCKADDR)&clientAddr, &addrLen);
			if (sessionSocket != INVALID_SOCKET)
				printf("Socket listen one client request!\n");

			//�ѻỰSOCKET��Ϊ������ģʽ
			if ((rtn = ioctlsocket(sessionSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO��������ֹ�׽ӿ�s�ķ�����ģʽ��
				cout << "ioctlsocket() failed with error!\n";
				return;
			}
			cout << "ioctlsocket() for session socket ok!	Waiting for client data\n";

			//���õȴ��ỰSOKCET�ɽ������ݻ�ɷ�������
			FD_SET(sessionSocket, &rfds);
			FD_SET(sessionSocket, &wfds);

			//���µĻỰsocket����Ựsocket�б�
			sessionSockets.push_back(sessionSocket);
		}

		//���ỰSOCKET�Ƿ������ݵ���
		if (nTotal > 0) { //������пɶ��¼���˵���ǻỰsocket�����ݵ���
			//�������лỰsocket������Ựsocket�����ݵ���������ܿͻ�������
			for (list<SOCKET>::iterator itor = sessionSockets.begin(); itor != sessionSockets.end(); itor++) {
				if (FD_ISSET(*itor, &rfds)) { //����������ĵ�ǰsocket�����ݵ���
					//receiving data from client
					memset(recvBuf, '\0', Config::BUFFERLENGTH);
					rtn = recv(*itor, recvBuf, Config::BUFFERLENGTH, 0);
					//printf("����IPΪ");
					cout << "IP: " << inet_addr(Config::SERVERADDRESS.c_str()) << ", Port:" << addr.sin_port<<endl;
					if (rtn > 0) {
						printf("Received %d bytes from client: %s\n", rtn, recvBuf);
						stringstream ss(recvBuf);
						Request req = req.DecodeReqFromStr(ss);
						if (GetFile(Config::PATH + req.GetUrl(), req)) {
							string resp = GetResponseStr(req, 200);
							int sendrsp = send(*itor, resp.c_str(), resp.size(), 0);
							if (sendrsp == SOCKET_ERROR) {
								cout << "Send Error" << endl;
								continue;
							}
							sendrsp = send(*itor, req.GetBody().c_str(), req.GetBody().size(), 0);
							if (sendrsp == SOCKET_ERROR) {
								cout << "Send Failed!!" << endl;
							}
							cout << "Send success!" << endl;
						}
						else {
							GetFile(Config::PATH + "NotFound.html", req);
							string resp = GetResponseStr(req, 404);
							int sendrsp = send(*itor, resp.c_str(), resp.size(), 0);
							if (sendrsp == SOCKET_ERROR) {
								cout << "Send Error" << endl;
								continue;
							}
							sendrsp = send(*itor, req.GetBody().c_str(), req.GetBody().size(), 0);
							if (sendrsp == SOCKET_ERROR) {
								cout << "Send Failed!!" << endl;
							}
							cout << "Send success!" << endl;
						}
					}
				}
			}
		}
	}
}


bool GetFile(string filepath, Request& req) {
	ifstream file(filepath, ios::binary);
	if (!file) {
	//	cout << "Open Error!" << endl;
		return false;
	}
	file.seekg(0, ios::end);
	size_t filesize = file.tellg();
	//string buffer(0, filesize + 1);
	char* buffer = new char[filesize + 1];
	memset(buffer, 0, filesize + 1);
	file.seekg(0, ios::beg);
	file.read(buffer, filesize);
	file.close();
	string s(buffer, buffer + filesize);
	req.UpdateBody(s);
	return true;
}