#pragma once

#include "EntityWithTexture.h"
#include "IMovable.h"

class Background : public EntityWithTexture, public IMovable {
protected:
    int speed;

public:
    Background(const Position &position, const Visual &visual, int speed);

    void fixPosition();
    
    void move(long gameFrame) override;

    void speedUp(long gameFrame) override;
};

