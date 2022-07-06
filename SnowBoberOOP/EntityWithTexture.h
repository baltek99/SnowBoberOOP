#pragma once

#include "IRenderable.h"
#include "Visual.h"
#include "Entity.h"
#include "TexturesManager.h"

class EntityWithTexture : public Entity, public IRenderable {
protected:
    Visual visual;
    int zIndex;

public:
    EntityWithTexture(const Position &position_, const Visual &visual_);

    Visual getVisual() const;

    Visual & getVisual();

    void setVisual(const Visual &visual_);

    int getZIndex() const;

    virtual void render(sf::RenderWindow &window) override;
};
