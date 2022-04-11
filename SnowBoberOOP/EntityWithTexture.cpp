#include "EntityWithTexture.h"
#include "Position.h"
#include "Entity.h"
#include "Visual.h"

class EntityWithTexture : Entity {
private:
    Visual visual;
protected:
    int zIndex = 0;

    public EntityWithTexture(Position position, Visual visual) : Entity(position) {
        this.visual = visual;
    }

    public Visual getVisual() {
        return visual;
    }

    public void setVisual(Visual visual) {
        this.visual = visual;
    }

    public int getZIndex() {
        return zIndex;
    }

    @Override
    public void render(SpriteBatch batch) {
        batch.draw(
            visual.getTexture(),
            this.getPosition().getX(),
            this.getPosition().getY(),
            visual.getImgWidth() / 2f,
            visual.getImgHeight() / 2f,
            visual.getImgWidth(),
            visual.getImgHeight(),
            1,
            1,
            visual.getRotation()
        );
    }
};
