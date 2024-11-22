#pragma once
#include "../Players/Players.h"
class Player : public GameObject
{
public:
    Player(bool isPlayer1);      
    ~Player() override;     

    void Update(float deltaTime) override;
    void Draw() override;

    
    void MoveLeft();
    void MoveRight();
    void Jump();
    void Kill();

    Asset texture;
    float health = 3;
    float playerMoveSpeed = 25.0f;
    float deltaTimeRef;
    bool isPlayerDead = false;
};

