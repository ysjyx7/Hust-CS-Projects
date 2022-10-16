//
// Created by yx7 on 2022/10/16.
//

#ifndef NET_CONFIG_H
#define NET_CONFIG_H
#include<string>
#include<iostream>

#include "winsock2.h"
class Config {
    Config();
    ~Config();
public:
    static const int BUFFERLENGTH;
    static std::string SERVERADDRESS;
    static int PORT;
    static const u_long BLOCKMODE;
    static std::string PATH;
};
#endif //NET_CONFIG_H