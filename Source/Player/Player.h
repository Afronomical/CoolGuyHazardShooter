#pragma once

#include "../GameObject/GameObject.h"
#include "../Physics/Rigidbody.h"
#include "../Collision/Collider.h"
#include "../Enemies/BaseEnemy.h"

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
    void SlowDown();
    //void OnCollisionEnter(Collider* other);
    // INFO: Temporary variable delete whenever
    bool isPlayer1 = false;

    Asset texture;
    std::weak_ptr<Rigidbody> playerRigidBody;
    std::weak_ptr<BoxCollider> playerCollider;

    float health = 3;
    float playerMoveSpeed = 100.0f;
    //float playerJumpForce = 5000.0f;
    float playerJumpTimer = 0.5f;
    float playerMass = 50.0f;
    bool isPlayerDead = false;

private:
    float deltaTimeRef = 0.0f;
    float slowedAmount = 25.0f;
    float fallSpeed = 100.0f;
    float playerJumpTimerSaved;
    bool isJumping = false;
    bool isGrounded = true;
};

