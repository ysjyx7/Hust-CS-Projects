#include"http.h"
Request Request::DecodeReqFromStr(stringstream& ss) {
	Request req;
	ss >> req.methodstring>>req.url>>req.version;
	if (req.url == "/") {
		req.url = "index.html";
		req.ext = "html";
	}
	else {
		int index = req.url.find_last_of('/');
		req.url = req.url.substr(index + 1);
		index = req.url.find_last_of('.');
		req.ext = req.url.substr(index + 1);
	}
	auto mf = MethodMap.find(req.methodstring);
	if (mf != MethodMap.end()) {
		req.method = mf->second;
	}
	return req;
}

string GetResponseStr(Request req,int Status) {
	stringstream ss;
	auto Sf = StatusMap.find(Status);
	string StatusStr;
	if (Sf != StatusMap.end()) {
		StatusStr = Sf->second;
	}
	else {
		StatusStr = "";
	}
	ss << req.version << ' ' << Status << ' '<<StatusStr<<"\r\n";

	string FT;
	auto Ff = FileType.find(req.ext);
	if (Ff != FileType.end()) {
		FT = Ff->second;
	}
	else {
		FT = "text/html";
	}
	ss << "Content-Type : " << FT << ";charset=UTF-8\r\n";
	ss << "Connection: keep-alive\r\n";
	
	ss << "Content-Length:" << req.body.size() << "\r\n\r\n";

	return ss.str();
}

Request Request::UpdateBody(string s) {
	body = s;
	return *this;
}

string Request::GetUrl() {
	return url;
}

string Request::GetBody() {
	return body;
}