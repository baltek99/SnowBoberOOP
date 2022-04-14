#pragma once

#include "IRenderable.h"
#include "Visual.h"
#include "Entity.h"

class EntityWithTexture : public Entity, public IRenderable {
protected:
    Visual visual;
    int zIndex;

public:
    EntityWithTexture(const Position &position_, const Visual &visual_);

    Visual getVisual() const;

    void setVisual(const Visual &visual_);

    int getZIndex() const;

    virtual void render(/*SpriteBatch batch*/) override;
};


