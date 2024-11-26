#pragma once

#include "../GameObject/GameObject.h"

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

    // INFO: Temporary variable delete whenever
    bool isPlayer1 = false;

    Asset texture;
    float health = 3;
    float playerMoveSpeed = 25.0f;
    float deltaTimeRef = 0.0f;
    bool isPlayerDead = false;
};

