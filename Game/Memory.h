#pragma once
#include <vector>

class Memory
{
public:
	Memory(void)
	{
	}

	~Memory(void)
	{
	}

	#define undefined  ((void*)0xcdcdcdcd)

	template<class T>
	static void Delete(T* &pointer)
	{
		if(pointer != NULL || pointer != undefined)
		{
			delete pointer;
			pointer = NULL;
		}
	}
	template<class T>
	static void Delete(T** &pointer, int n)
	{
		if(pointer != NULL || pointer != undefined)
		{
			for(int i = 0; i < n; i++)
			{
				Delete(pointer[i]);
			}
			delete[] pointer;
			pointer = NULL;
		}
	}
	template<class T>
	static void Delete(std::vector<T*> vector)
	{
		while(vector.size())
		{
			Memory::Delete(vector.back());
			vector.pop_back();
		}
	}
};
