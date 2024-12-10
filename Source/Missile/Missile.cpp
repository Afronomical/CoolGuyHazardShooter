#include "Missile.h"


Missile::Missile(Player* player1Ref, Player* player2Ref) : player1(player1Ref), player2(player2Ref)
{
	missileTexture = AssetHandler::LoadTexture("Assets/Animations/catgun.png");
	transform.lock()->position = Vector2(200, 0);
	transform.lock()->size = Vector2(30, 30);

	startPos = transform.lock()->position;
}

Missile::~Missile()
{

}

void Missile::Update(float deltaTime)
{
	delta = deltaTime;
	RandDir();
	distanceToPlayer1 = Vector2::Distance(transform.lock()->position, player1->transform.lock()->position);
	distanceToPlayer2 = Vector2::Distance(transform.lock()->position, player2->transform.lock()->position);
	if (distanceToPlayer1 < distanceToPlayer2)
	{
		transform.lock()->position += DirectionToPlayer(player1) * missileSpeed;
	}
	else
	{
		transform.lock()->position += DirectionToPlayer(player2) * missileSpeed;
	}
	if (distanceToPlayer1 <= didtanceToDestroy || distanceToPlayer2 <= didtanceToDestroy)
	{
		MissileHit();
	}
}

void Missile::Draw()
{
	AssetHandler::DrawStatic(missileTexture, transform.lock()->position, transform.lock()->size.X, transform.lock()->size.Y, 1);
}

void Missile::MissileMove()
{

}

Vector2 Missile::DirectionToPlayer(Player* playerObj)
{
	Vector2 dir = (playerObj->transform.lock()->position - transform.lock()->position).Normalized();
	forward = Vector2::Lerp(forward, dir + randRot, delta * accel);
	return forward;
}

void Missile::RandDir()
{
	randDirTime += delta;
	//Debug::Log(std::to_string(delta));
	//Debug::Log(std::to_string(randDirTime));
	if (randDirTime >= randDirDuration)
	{
		randDirTime = 0;

		randRot = Vector2(Maths::RandomRange(-randDirRange, randDirRange), Maths::RandomRange(-randDirRange, randDirRange));
	}
}

void Missile::MissileHit()
{
	transform.lock()->position = startPos;
}


