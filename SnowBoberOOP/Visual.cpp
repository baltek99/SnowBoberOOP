#include "Visual.h"

class Visual {
    private TextureRegion texture;
private:
    int imgWidth;
    int imgHeight;
    float rotation;

public :
    Visual(Texture texture_, int imgWidth_, int imgHeight_) {
        texture = new TextureRegion(texture_);
        imgWidth = imgWidth_;
        imgHeight = imgHeight_;
        rotation = 0;
    }

    Visual(TextureRegion texture_, int imgWidth_, int imgHeight_, float rotation_) {
        texture = texture_;
        imgWidth = imgWidth_;
        imgHeight = imgHeight_;
        rotation = rotation_;
    }

    TextureRegion getTexture() {
        return texture;
    }

    void setTexture(TextureRegion texture_) {
        texture = texture_;
    }

    int getImgWidth() {
        return imgWidth;
    }

    int getImgHeight() {
        return imgHeight;
    }

    float getRotation() {
        return rotation;
    }

    void setRotation(float rotation_) {
        rotation = rotation_;
    }
};