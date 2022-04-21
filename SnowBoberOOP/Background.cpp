#include "Background.h"
#include "ConstValues.h"

Background::Background(const Position &position_, const Visual &visual_, int speed_) : EntityWithTexture(position_, visual_), speed(speed_) {}

void Background::fixPosition() {
    int pos = position.getX();
    int width = ConstValues::V_WIDTH;
    if (pos <= -width) {
        position.setX(width + pos % width);
    }
}

void Background::move(long gameFrame) {
    position.setX(position.getX() + speed);
}

void Background::speedUp(long gameFrame) {
    if (gameFrame % ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT == 0) {
        speed--;
    }
}