#include "StdAfx.h"
#include "String.h"

String::String(void)
{
}

String::~String(void)
{
}

bool String::IsEquals(const char * s1, const char * s2)
{
	return strcmp(s1, s2) == 0;
}

const char* String::concat(std::string s1, std::string s2)
{

	int n = s1.length() + s2.length();
	char* s3 = new char[n+1];
	/*
	for(int i = 0; i < s1.length(); i++)
		s3[i] = s1[i];
	for(int i = s1.length(); i < n; i++)
		s3[i] = s2[i - s1.length()];
	*/
	sprintf(s3,"%s%s",s1.c_str(),s2.c_str());
	return s3;
}