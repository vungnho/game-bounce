//#include "StdAfx.h"
#include "ContactListener.h"
#include "Bounce.h"
#include <Box2D/Box2D.h>

ContactListener * ContactListener::ms_pInstance = NULL;
ContactListener::ContactListener(void)
{
}

ContactListener::~ContactListener(void)
{
}

void ContactListener::BeginContact(b2Contact* contact)
{

	Object *objectA, *objectB;
  //check if fixture A was a ball

  void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  if ( bodyUserData )
  {
     objectA = static_cast<Bounce*>( bodyUserData );
	 objectA->startContact();
  }

  //check if fixture B was a ball
  bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  if ( bodyUserData )
  {
     objectB = static_cast<Bounce*>( bodyUserData );
	 objectB->startContact();
  }


   objectA->ContactWith(objectB);


}
  
void ContactListener::EndContact(b2Contact* contact)
{
Object *objectA, *objectB;
  //check if fixture A was a ball
  void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
  if ( bodyUserData )
  {
     objectA = static_cast<Bounce*>( bodyUserData );
    static_cast<Bounce*>( bodyUserData )->endContact();
  }

  //check if fixture B was a ball
  bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
  if ( bodyUserData )
  {
     objectB = static_cast<Bounce*>( bodyUserData );
    static_cast<Bounce*>( bodyUserData )->endContact();
  }

  //objectA->ContactWith(objectB);
}

