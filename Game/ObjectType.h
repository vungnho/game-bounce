#pragma once
#include "String.h"
class ObjectType
{
public:

	static const int OBJECT			= 10000;
	static const int BOX			= 10001;
	static const int BOUNCE			= 10002;
	static const int FOOD			= 10003;
	static const int THORN			= 10004;
	static const int TRIANGLE		= 10005;
	static const int HANDLER		= 10006;
	static const int BUTTON			= 10007;
	static const int CLOUD			= 10008;
	static const int TARGET			= 10009;
	static const int BACKGROUND		= 10010;
	static const int LEVELGAME		= 10011;
	static const int LABEL			= 10012;


    static const char** GetList();

	static int GetType(const char* object_type);

	static const char* GetType(int object_type);

private:
		static const int Begin = OBJECT;
		static const int End = LABEL;
        static const char* type[];
};
