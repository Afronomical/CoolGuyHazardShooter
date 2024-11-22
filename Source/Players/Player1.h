#pragma once
#include "../Players/Players.h"
class Player1 : public GameObject
{
public:
    Player1();      
    ~Player1();     

    void Update(float deltaTime) override;
    void Draw() override;

    
    void MoveLeft();
    void MoveRight();
    void Jump();

    Asset texture;
    float health = 3;
    float playerMoveSpeed = 25.0f;
    float deltaTimeRef;
    bool isPlayerDead = false;
};

