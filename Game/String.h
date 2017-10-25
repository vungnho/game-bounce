#pragma once
#include <string>
class String
{
public:
	String(void);
	~String(void);

	static bool IsEquals(const char *  s1, const char * s2);
	static const char* concat(std::string s1, std::string s2);
};
