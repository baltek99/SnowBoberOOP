#include "Life.h"
#include "ConstValues.h"

Life::Life(const Position& position_) : EntityWithTexture(position_, Visual("", ConstValues::HEART_WIDTH, ConstValues::HEART_HEIGHT)) {}
