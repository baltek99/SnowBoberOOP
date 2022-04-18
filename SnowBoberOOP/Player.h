#pragma once

#include <queue>
#include "EntityWithTexture.h"
#include "ICollidable.h"
#include "IMovable.h"
#include "IPlayerActions.h"
#include "CollisionInfo.h"
#include "PlayerState.h"
#include "Life.h"

class Player : public EntityWithTexture, public IPlayerActions, public ICollidable, public IMovable {
private :
    int score;
    std::string name;
    std::queue<Life> lives;
    bool immortal = false;
    PlayerState playerState;
    CollisionInfo collisionInfo;
    int jumpFrom;
    long startJumpFrame;
    int jumpHeight;
    float jumpDuration;
    float flipRotationSpeed;
    float ollieUpRotationSpeed;
    float ollieDownRotationSpeed;
    int initialImmortalDurationVal;
    int immortalDuration;
    int speedCount;

public :
    Player(const Position &position_, const Visual &visual_, std::string name_);

    CollisionInfo getCollisionInfo() const;

    bool isImmortal() const;

    void setImmortal(bool immortal_);

    void setPlayerState(const PlayerState playerState_);

    PlayerState getPlayerState() const;

    std::queue<Life> getLives() const;
    
    int getNumberOfLives() const;

    int getScore() const;

    std::string getName() const;

    void setName(std::string name_);

    void moveRight();

    void moveLeft();
        
    void jump(long gameFrame) override;
    
    void crouch() override;

    void move(long gameFrame) override;
   
    void speedUp(long gameFrame) override;

    void collide(ICollidable * collidable) override;

    void render(/*SpriteBatch batch*/) override;
};

