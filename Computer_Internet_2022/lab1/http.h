#pragma once
#include<string>
#include<unordered_map>
#include<sstream>
using namespace std;

enum class Method { GET=1,POST=2};

const unordered_map<string, Method> MethodMap = { {"GET",Method::GET},{"POST",Method::POST}};

const unordered_map<int, string> StatusMap = { {200,"OK"},{404,"Not Found"}};

const unordered_map<string, string> FileTypeMap = { {"html","test"},{},{},{}};

//string GetResponseStr(Request req,int Status);
const std::unordered_map<std::string, std::string> FileType = { {"html", "text/html"},

															   {"txt", "text/plain"},
															   {"gif", "image/gif"},
															   {"jpeg", "image/jpeg"},
															   {"jpg", "image/jpeg"},
															   {"png", "image/png"},
															   {"ico", "image/x-icon"},
};

class Request {
	Method method;
	string version;
	string url;
	string ext;
	string methodstring;
	size_t str_size = 0;
	string body;
public:
	Request DecodeReqFromStr(stringstream& ss);
	Request UpdateBody(string s);
	string GetUrl();
	string GetBody();
	friend string GetResponseStr(Request req, int Statues);

};