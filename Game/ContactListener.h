#pragma once
#include <box2d/dynamics/b2worldcallbacks.h>

class ContactListener :
	public b2ContactListener
{
public:
	ContactListener(void);
	~ContactListener(void);

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	static void CreateInstance()
    {
        ms_pInstance = new ContactListener();
    }


public:
	/*implicit methods exist for the copy constructor and operator= and we want to forbid calling them.*/
	ContactListener(const ContactListener &){};
	ContactListener& operator =(const ContactListener &){};
	static ContactListener * GetInstance() 
    {
		if(!ms_pInstance) CreateInstance();
		return ms_pInstance;
    }
	static void DestroyInstance() 
    {
	   if ( ms_pInstance )
	   {
		  delete ms_pInstance;
		  ms_pInstance = NULL;
	   }
    }

protected:
	static ContactListener * ms_pInstance;

};
