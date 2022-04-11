#pragma once
#ifndef VISUAL_H
#define VISUAL_H
class Visual
{
public:
    Visual(Texture texture_, int imgWidth_, int imgHeight_);

    Visual(TextureRegion texture_, int imgWidth_, int imgHeight_, float rotation_);

    TextureRegion getTexture();

    void setTexture(TextureRegion texture_);

    int getImgWidth();

    int getImgHeight();

    float getRotation();

    void setRotation(float rotation_);
};
#endif // !VISUAL_H

