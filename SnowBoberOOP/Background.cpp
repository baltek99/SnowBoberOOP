#include "Background.h"
#include "ConstValues.h"

Background::Background(const Position &position_, const Visual &visual_, int speed_) : EntityWithTexture(position_, visual_), speed(speed_) {}

void Background::fixPosition() {
    int pos = getPosition().getX();
    int width = ConstValues::V_WIDTH;
    if (pos <= -width) {
        getPosition().setX(width + pos % width);
    }
}

void Background::move(long gameFrame) {
    getPosition().setX(getPosition().getX() + speed);
}

void Background::speedUp(long gameFrame) {
    if (gameFrame % ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT == 0) {
        speed--;
    }
}