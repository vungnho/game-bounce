#include "StdAfx.h"
#include "ObjectType.h"

	int ObjectType::GetType(const char* object_type)
	{
		for(int i = Begin; i <= End; i++)
		{
			if(String::IsEquals(object_type, GetList()[i - Begin]))
			{
				return i;
			}
		}
		return OBJECT;
	}

	const char* ObjectType::GetType(int object_type)
	{

		if(object_type < Begin || object_type > End)
			return "object";
		return GetList()[object_type - Begin];

	}