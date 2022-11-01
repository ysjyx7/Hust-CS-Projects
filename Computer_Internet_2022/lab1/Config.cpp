//
// Created by yx7 on 2022/10/16.
//

#include "Config.h"
Config::Config() {

}
Config::~Config() {

}
const int Config::BUFFERLENGTH = 4096;
std::string Config::PATH = "";
std::string Config::SERVERADDRESS = "";
const u_long Config::BLOCKMODE = 1;
int Config::PORT = 5050;

