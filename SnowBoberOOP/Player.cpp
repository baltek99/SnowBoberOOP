#include "Player.h"
#include "ConstValues.h"
#include "Util.h"
#include "Obstacle.h"
#include "Rail.h"

Player::Player(const Position& position_, const Visual& visual_, std::string name_) : EntityWithTexture(position_, visual_) {
    name = name_;
    jumpHeight = 120;
    jumpDuration = 110;
    flipRotationSpeed = 3.4f;
    ollieUpRotationSpeed = 1.3f;
    ollieDownRotationSpeed = 0.5f;
    initialImmortalDurationVal = 150;
    immortalDuration = 150;
    speedCount = 5;
    zIndex = 0;
    score = 0;
    lives = std::queue<Life>();
    lives.push(Life(Position(ConstValues::HEART_POSITION_X_1, ConstValues::HEART_POSITION_Y)));
    lives.push(Life(Position(ConstValues::HEART_POSITION_X_2, ConstValues::HEART_POSITION_Y)));
    lives.push(Life(Position(ConstValues::HEART_POSITION_X_3, ConstValues::HEART_POSITION_Y)));
    playerState = PlayerState::IDLE;
    collisionInfo = CollisionInfo(visual.getImgWidth(), visual.getImgHeight());
}

CollisionInfo Player::getCollisionInfo() const {
    return collisionInfo;
}

bool Player::isImmortal() const {
    return immortal;
}

void Player::setImmortal(bool immortal_) {
    immortal = immortal_;
}

void Player::setPlayerState(const PlayerState playerState_) {
    playerState = playerState_;
}

PlayerState Player::getPlayerState() const {
    return playerState;
}

std::queue<Life> Player::getLives() const {
    return lives;
}

int Player::getNumberOfLives() const {
    return lives.size();
}

int Player::getScore() const {
    return score;
}

std::string Player::getName() const {
    return name;
}

void Player::setName(std::string name_) {
    name = name_;
}

void Player::moveRight() {
    if (playerState == PlayerState::IDLE) {
        position.setX(position.getX() + 5);
        if (position.getX() > ConstValues::BOBER_MAX_X) position.setX(ConstValues::BOBER_MAX_X);
    }
}

void Player::moveLeft() {
    if (playerState == PlayerState::IDLE) {
        position.setX(position.getX() - 5);
        if (position.getX() < ConstValues::BOBER_MIN_X) position.setX(ConstValues::BOBER_MIN_X);
    }
}

void Player::jump(long gameFrame) {
    sf::Texture texture;
    if (playerState == PlayerState::SLIDING) {
        playerState = PlayerState::JUMPING_ON_RAIL;
        jumpFrom = ConstValues::JUMP_FROM_RAIL_Y;
        startJumpFrame = gameFrame;
        texture.loadFromFile("bober-flip.png");
        setVisual(Visual(texture, ConstValues::BOBER_IN_JUMP_WIDTH, ConstValues::BOBER_IN_JUMP_HEIGHT));
    }
    else if (playerState != PlayerState::JUMPING && playerState != PlayerState::JUMPING_ON_RAIL
        && playerState != PlayerState::JUMPING_FROM_CROUCH) {
        if (playerState == PlayerState::CROUCH) {
            texture.loadFromFile("bober-flip.png");
            playerState = PlayerState::JUMPING_FROM_CROUCH;
        }
        else {
            texture.loadFromFile("bober-jump.png");
            playerState = PlayerState::JUMPING;
        }
        jumpFrom = ConstValues::JUMP_FROM_GROUND_Y;
        startJumpFrame = gameFrame;
        setVisual(Visual(texture, ConstValues::BOBER_IN_JUMP_WIDTH, ConstValues::BOBER_IN_JUMP_HEIGHT));
    }
}

void Player::crouch() {
    if (playerState == PlayerState::IDLE) {
        playerState = PlayerState::CROUCH;

        position.setY(100);
        sf::Texture texture;
        texture.loadFromFile("bober-luzny.png");
        setVisual(Visual(texture, ConstValues::BOBER_CROUCH_WIDTH, ConstValues::BOBER_CROUCH_HEIGHT));
    }
    else if (playerState == PlayerState::CROUCH) {
        playerState = PlayerState::IDLE;

        position.setY(ConstValues::IDLE_RIDE_Y);
        sf::Texture texture;
        texture.loadFromFile("bober-stand.png");
        setVisual(Visual(texture, ConstValues::BOBER_DEFAULT_WIDTH, ConstValues::BOBER_DEFAULT_HEIGHT));
    }
}

void Player::move(long gameFrame) {
    if (playerState == PlayerState::JUMPING || playerState == PlayerState::JUMPING_ON_RAIL || playerState == PlayerState::JUMPING_FROM_CROUCH) {
        if (gameFrame >= startJumpFrame + jumpDuration) {
            playerState = PlayerState::IDLE;
            position.setY(ConstValues::IDLE_RIDE_Y);
            getVisual().setRotation(0);
            sf::Texture texture;
            texture.loadFromFile("bober-stand.png");
            setVisual(Visual(texture, ConstValues::BOBER_DEFAULT_WIDTH, ConstValues::BOBER_DEFAULT_HEIGHT));
        }
        else {
            position.setY((int)Util::lerp(
                jumpFrom,
                jumpFrom + jumpHeight,
                Util::spike((gameFrame - startJumpFrame) / jumpDuration)
            ));

            if (playerState == PlayerState::JUMPING_ON_RAIL) {
                getVisual().setRotation(getVisual().getRotation() + flipRotationSpeed);
            }
            else if (playerState == PlayerState::JUMPING_FROM_CROUCH) {
                getVisual().setRotation(getVisual().getRotation() - flipRotationSpeed);
            }
            else {
                if ((gameFrame - startJumpFrame) / jumpDuration < 0.15f) {
                    getVisual().setRotation(getVisual().getRotation() + ollieUpRotationSpeed);
                }
                else if (getVisual().getRotation() > -10) {
                    getVisual().setRotation(getVisual().getRotation() - ollieDownRotationSpeed);
                }
            }
        }
    }
}

void Player::speedUp(long gameFrame) {
    if (gameFrame == ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT) {
        jumpHeight = 110;
        jumpDuration = 80;
        flipRotationSpeed = 4.5f;
    }
    else if (gameFrame == 3 * ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT) {
        jumpDuration = 65;
        flipRotationSpeed = 5.5f;
    }
    else if (gameFrame == 6 * ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT) {
        jumpDuration = 55;
        flipRotationSpeed = 6.0f;
    }
    else if (gameFrame == 8 * ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT) {
        jumpDuration = jumpDuration - jumpDuration / speedCount;
        flipRotationSpeed = flipRotationSpeed + flipRotationSpeed / speedCount;
        speedCount++;
    }
}

void Player::collide(ICollidable* collidable) {
    Obstacle* obstacle = (Obstacle*) collidable;
    if (obstacle->getObstacleType() == ObstacleType::SCORE_POINT) {
        score++;
    }
    else if (obstacle->getObstacleType() == ObstacleType::BOX || (obstacle->getObstacleType() == ObstacleType::RAIL &&
        (playerState == PlayerState::IDLE || playerState == PlayerState::CROUCH))) {
        lives.pop();
        immortal = true;
    }
    else if (obstacle->getObstacleType() == ObstacleType::RAIL && (playerState == PlayerState::JUMPING ||
        playerState == PlayerState::JUMPING_FROM_CROUCH || playerState == PlayerState::JUMPING_ON_RAIL)) {
        getPosition().setY(ConstValues::SLIDING_ON_RAIL_Y);
        playerState = PlayerState::SLIDING;
        sf::Texture texture;
        texture.loadFromFile("bober-rail.png");
        setVisual(Visual(texture, ConstValues::BOBER_ON_RAIL_WIDTH, ConstValues::BOBER_ON_RAIL_HEIGHT));
        Rail* rail = (Rail*)obstacle;
        rail->setRailCollisionHeight(1);
    }
    else if (obstacle->getObstacleType() == ObstacleType::GRID && playerState != PlayerState::CROUCH) {
        lives.pop();
        immortal = true;
    }
}

void Player::render(/*SpriteBatch batch*/) {
    if (immortal && immortalDuration > 0) {
        if (immortalDuration % 40 < 20) {
            EntityWithTexture::render();
        }
        immortalDuration--;
    }
    else if (immortal) {
        immortal = false;
        immortalDuration = initialImmortalDurationVal;
    }
    else {
        EntityWithTexture::render();
    }
}