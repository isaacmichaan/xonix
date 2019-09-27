#include "CollisionHandling.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "User.h"
#include "ConquerBall.h"
#include "SimpleBall.h"
#include "ChaserBall.h"
#include "TrigoBall.h"
#include "DestroyerBall.h"
#include "DisturbBall.h"
#include "Wall.h"

namespace { // anonymous namespace — the standard way to make function "static"

void userSBall(GameObject& U,
                  GameObject& SB)
{
	User& user = dynamic_cast<User&>(U);
	user.setLife(true);
}

void userDBall(GameObject& U,
	GameObject& DB)
{
	User& user = dynamic_cast<User&>(U);
	user.setLife(true);
}

void userDsBall(GameObject& U,
	GameObject& DsB)
{
	User& user = dynamic_cast<User&>(U);
	user.setLife(true);
}

void userWall(GameObject& U,
	GameObject& W)
{
	Wall& wall = dynamic_cast<Wall&>(W);
	User& user = dynamic_cast<User&>(U);

	/*if (wall.getChar() == '2')
		user.stopUser();*/

	if (wall.getChar() == 'g')
		user.setLife(true);
}

void sBallUser(GameObject& SB,
	GameObject& U)
{
	SimpleBall& ball = dynamic_cast<SimpleBall&>(SB);
	ball.setLife(true);
}

void chBallWall(GameObject& CB,
              GameObject& W)
{
	Wall& wall = dynamic_cast<Wall&>(W);
	ChaserBall& ball = dynamic_cast<ChaserBall&>(CB);

	if (wall.getChar() != 't' && wall.getChar() != 'o' )
		ball.setPos(ball.getSprite().getPosition().x, ball.getSprite().getPosition().y);
	
	if (wall.getChar() == 'g')
		ball.setLife(true);
}
void tBallWall(GameObject& TB,
	GameObject& W)
{
	Wall& wall = dynamic_cast<Wall&>(W);
	TrigoBall& ball = dynamic_cast<TrigoBall&>(TB);

	if (wall.getChar() != 't' && wall.getChar() != 'o')
	{
	
	ball.setDiraction((ball.getDiraction() + 1) % 4);
	ball.setPos(ball.getSprite().getPosition().x, ball.getSprite().getPosition().y);
	}
	if (wall.getChar() == 'g')
		ball.setLife(true);
}

void dBallUser(GameObject& DB,
	GameObject& U)
{
	DestroyerBall& ball = dynamic_cast<DestroyerBall&>(DB);
	ball.setLife(true);
}

void dBallWall(GameObject& DB,
	GameObject& W)
{
	Wall& wall = dynamic_cast<Wall&>(W);
	DestroyerBall& ball = dynamic_cast<DestroyerBall&>(DB);

	if (wall.getChar() == '2')
		ball.setPos(ball.getSprite().getPosition().x, ball.getSprite().getPosition().y);
	
	if (wall.getChar() == 'b')
		ball.setDestroyTile(true);
	
	if (wall.getChar() == 'g')
		ball.setLife(true);
}

void cBallWall(GameObject& CB,
	GameObject& W)
{
	Wall& wall = dynamic_cast<Wall&>(W);
	ConquerBall& ball = dynamic_cast<ConquerBall&>(CB);
	
	if (wall.getChar() == '2')
		ball.setPos(ball.getSprite().getPosition().x, ball.getSprite().getPosition().y);
	
	if (wall.getChar() == 't')
		ball.setBuildTile(true);
}

void dsBallUser(GameObject& DsB,
	GameObject& U)
{
	DisturbBall& ball = dynamic_cast<DisturbBall&>(DsB);
	ball.setLife(true);
}

void dsBallWall(GameObject& DsB,
	GameObject& W)
{
	Wall& wall = dynamic_cast<Wall&>(W);
	DisturbBall& ball = dynamic_cast<DisturbBall&>(DsB);
	
	if (wall.getChar() != '0')
		ball.setPos(ball.getSprite().getPosition().x, ball.getSprite().getPosition().y);
}

using HitFunctionPtr = void (*)(GameObject&, GameObject&);
using Key = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<Key, HitFunctionPtr>;

HitMap initializeCollisionMap()
{
    HitMap phm;
    phm[Key(typeid(User   ), typeid(SimpleBall    ))] = &userSBall;
	phm[Key(typeid(User), typeid(DestroyerBall))] = &userDBall;
	phm[Key(typeid(User), typeid(DisturbBall))] = &userDsBall;
	phm[Key(typeid(User), typeid(Wall))] = &userWall;
    phm[Key(typeid(SimpleBall), typeid(User))] = &sBallUser;
	phm[Key(typeid(ChaserBall), typeid(Wall))] = &chBallWall;
	phm[Key(typeid(TrigoBall), typeid(Wall))] = &tBallWall;
	phm[Key(typeid(DestroyerBall), typeid(User))] = &dBallUser;
	phm[Key(typeid(DestroyerBall), typeid(Wall))] = &dBallWall;
	phm[Key(typeid(ConquerBall), typeid(Wall))] = &cBallWall;
	phm[Key(typeid(DisturbBall), typeid(User))] = &dsBallUser;
	phm[Key(typeid(DisturbBall), typeid(Wall))] = &dsBallWall;
    return phm;
}

HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();
    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
	if (mapEntry == collisionMap.end())
	{
		return nullptr;
	}
    return mapEntry->second;
}

} // end namespace

void processCollision(GameObject& object1, GameObject& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
	if (phf)
	    phf(object1, object2);
}