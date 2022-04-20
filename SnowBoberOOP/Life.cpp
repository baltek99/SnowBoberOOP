#include "Life.h"
#include "ConstValues.h"

Life::Life(const Position& position_) : EntityWithTexture(position_, Visual(TexturesManager::heart, ConstValues::HEART_WIDTH, ConstValues::HEART_HEIGHT)) {}
