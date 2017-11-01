
#include "CantactManager.h"


CantactManager::CantactManager(void)
{
}

CantactManager::~CantactManager(void)
{
}


std::vector<Vector2> CantactManager::CheckContacting(Object* o1, Object* o2)
{
	b2ContactEdge* contact_edge = ((b2Body*)(o1->GetUserData()))->GetContactList();
	b2Body* b2 = (b2Body*)(o2->GetUserData());
	while(contact_edge)
	{
		if(contact_edge->other == b2 && contact_edge->contact->IsTouching())
		{
			//return true;
		}
		contact_edge = contact_edge->next;
	}
	//return false;
	return std::vector<Vector2>();
}