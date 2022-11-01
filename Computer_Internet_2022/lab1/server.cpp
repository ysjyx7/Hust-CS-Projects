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
//当chrome浏览器打开一个网页时，除了请求网页本身外，还会发出另外一个请求 /favicon.ico，请求谷歌浏览器的图标
//因此Server实际上打开了多个会话Socket，需要一个List来保存这些会话Socket
//保存打开的当前的会话socket

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
		select()机制中提供的fd_set的数据结构，实际上是long类型的数组，
		每一个数组元素都能与一打开的文件句柄（不管是socket句柄，还是其他文件或命名管道或设备句柄）建立联系，建立联系的工作由程序员完成.
		当调用select()时，由内核根据IO状态修改fd_set的内容，由此来通知执行了select()的进程哪个socket或文件句柄发生了可读或可写事件。
	*/
	fd_set rfds;				//用于检查socket是否有数据到来的的文件描述符，用于socket非阻塞模式下等待网络事件通知（有数据到来）
	fd_set wfds;				//用于检查socket是否可以发送的文件描述符，用于socket非阻塞模式下等待网络事件通知（可以发送数据）
	//bool first_connetion = true;

	int nRc = WSAStartup(0x0202, &wsaData);

	if (nRc) {
		printf("Winsock  startup failed with error!\n");
	}

	if (wsaData.wVersion != 0x0202) {
		printf("Winsock version is not correct!\n");
	}

	printf("Winsock  startup Ok!\n");


	//监听socket
	SOCKET srvSocket;

	//服务器地址和客户端地址
	sockaddr_in addr, clientAddr;

	//会话socket，负责和client进程通信
	SOCKET sessionSocket;

	//ip地址长度
	int addrLen;

	//创建监听socket
	srvSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (srvSocket != INVALID_SOCKET)
		printf("Socket create Ok!\n");


	//设置服务器的端口和地址
	//addr.sin_family = AF_INET;
	//addr.sin_port = htons(5050);
	//addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //主机上任意一块网卡的IP地址
	addr.sin_family = AF_INET;
	addr.sin_port = htons(Config::PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(Config::SERVERADDRESS.c_str());

	//binding
	int rtn = bind(srvSocket, (LPSOCKADDR)&addr, sizeof(addr));
	if (rtn != SOCKET_ERROR)
		printf("Socket bind Ok!\n");

	//监听
	rtn = listen(srvSocket, 5);
	if (rtn != SOCKET_ERROR)
		printf("Socket listen Ok!\n");

	clientAddr.sin_family = AF_INET;
	addrLen = sizeof(clientAddr);

	//设置接收缓冲区
	char recvBuf[4096];

	u_long blockMode = 1;//将srvSock设为非阻塞模式以监听客户连接请求

	//调用ioctlsocket，将srvSocket改为非阻塞模式，改成反复检查fd_set元素的状态，看每个元素对应的句柄是否可读或可写
	if ((rtn = ioctlsocket(srvSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO：允许或禁止套接口s的非阻塞模式。
		cout << "ioctlsocket() failed with error!\n";
		return;
	}
	cout << "ioctlsocket() for server socket ok!	Waiting for client connection\n";

	while (true) {
		//清空rfds和wfds数组
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);

		//将srvSocket加入rfds数组
		//即：当客户端连接请求到来时，rfds数组里srvSocket对应的的状态为可读
		//因此这条语句的作用就是：设置等待客户连接请求
		FD_SET(srvSocket, &rfds);

		for (list<SOCKET>::iterator itor = sessionSockets.begin(); itor != sessionSockets.end(); itor++) {
			//将sessionSockets里的每个会话socket加入rfds数组和wfds数组
			//即：当客户端发送数据过来时，rfds数组里sessionSocket的对应的状态为可读；当可以发送数据到客户端时，wfds数组里sessionSocket的对应的状态为可写
			//因此下面二条语句的作用就是：
			//设置等待所有会话SOKCET可接受数据或可发送数据
			FD_SET(*itor, &rfds);
			FD_SET(*itor, &wfds);
		}

		/*
			select工作原理：传入要监听的文件描述符集合（可读、可写，有异常）开始监听，select处于阻塞状态。
			当有可读写事件发生或设置的等待时间timeout到了就会返回，返回之前自动去除集合中无事件发生的文件描述符，返回时传出有事件发生的文件描述符集合。
			但select传出的集合并没有告诉用户集合中包括哪几个就绪的文件描述符，需要用户后续进行遍历操作(通过FD_ISSET检查每个句柄的状态)。
		*/
		//开始等待，等待rfds里是否有输入事件，wfds里是否有可写事件
		//The select function returns the total number of socket handles that are ready and contained in the fd_set structure
		//返回总共可以读或写的句柄个数
		int nTotal = select(0, &rfds, &wfds, NULL, NULL);

		//如果srvSock收到连接请求，接受客户连接请求
		if (FD_ISSET(srvSocket, &rfds)) {
			nTotal--;   //因为客户端请求到来也算可读事件，因此-1，剩下的就是真正有可读事件的句柄个数（即有多少个socket收到了数据）

			//产生新的会话SOCKET
			sessionSocket = accept(srvSocket, (LPSOCKADDR)&clientAddr, &addrLen);
			if (sessionSocket != INVALID_SOCKET)
				printf("Socket listen one client request!\n");

			//把会话SOCKET设为非阻塞模式
			if ((rtn = ioctlsocket(sessionSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO：允许或禁止套接口s的非阻塞模式。
				cout << "ioctlsocket() failed with error!\n";
				return;
			}
			cout << "ioctlsocket() for session socket ok!	Waiting for client data\n";

			//设置等待会话SOKCET可接受数据或可发送数据
			FD_SET(sessionSocket, &rfds);
			FD_SET(sessionSocket, &wfds);

			//把新的会话socket加入会话socket列表
			sessionSockets.push_back(sessionSocket);
		}

		//检查会话SOCKET是否有数据到来
		if (nTotal > 0) { //如果还有可读事件，说明是会话socket有数据到来
			//遍历所有会话socket，如果会话socket有数据到来，则接受客户的数据
			for (list<SOCKET>::iterator itor = sessionSockets.begin(); itor != sessionSockets.end(); itor++) {
				if (FD_ISSET(*itor, &rfds)) { //如果遍历到的当前socket有数据到来
					//receiving data from client
					memset(recvBuf, '\0', Config::BUFFERLENGTH);
					rtn = recv(*itor, recvBuf, Config::BUFFERLENGTH, 0);
					//printf("请求IP为");
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