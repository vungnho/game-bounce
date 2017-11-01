
/* 
 * File:   Singleton.h
 * Author: giappi
 *
 * Created on March 28, 2017, 8:18 PM
 */

#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton
{
	//friend T;
public:
	static T* GetInstance(void)
	{
		if (!instance)
		{
			instance = new T;
		}
		return instance;
	}
	static void DestroyInstance()
	{
		if (instance != NULL)
		{
			delete instance;
			instance = NULL;
		}
	};
	Singleton& operator=(Singleton const&){};


protected:
    Singleton();
    static T* instance;
	virtual ~Singleton(){};
};

template <class T>
T* Singleton<T>::instance = NULL;



#endif /* SINGLETON_H */

