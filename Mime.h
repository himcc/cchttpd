#ifndef _MIME_H
#define _MIME_H
#include<unordered_map>
#include<string>
using namespace std;
class Mime
{
public:
	unordered_map<string,string> mime;
	Mime();
	const char * gettype(string key);
};
#endif
