#pragma once

#include "EntityWithTexture.h"
#include "ICollidable.h"
#include "IMovable.h"
#include "IPlayerActions.h"
#include "CollisionInfo.h"
#include "PlayerState.h"
#include "Life.h"
#include <deque>

class Player : public EntityWithTexture, public IPlayerActions, public ICollidable, public IMovable {
private :
    int score;
    std::string name;
    std::deque<Life> lives;
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
    Player();

    Player(const Position &position_, const Visual &visual_, std::string name_);

    void initVariables();

    CollisionInfo getCollisionInfo() const;

    CollisionInfo &getCollisionInfo();

    bool isImmortal() const;

    void setImmortal(bool immortal_);

    void setPlayerState(const PlayerState playerState_);

    PlayerState getPlayerState() const;

    std::deque<Life> getLives() const;
    
    size_t getNumberOfLives() const;

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

    void render(sf::RenderWindow& window) override;

    void updateImmortal();
};
