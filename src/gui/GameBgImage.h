#ifndef GAME_BG_IMAGE_H
#define GAME_BG_IMAGE_H

#include <gui/GuiImageAsync.h>
#include <gui/video/shaders/Shader3D.h>
#include "GuiImage.h"

class GameBgImage : public GuiImageAsync {
public:
    GameBgImage(const std::string &filename, GuiImageData *preloadImage);

    virtual ~GameBgImage();

    void setAlphaFadeOut(const glm::vec4 &a) {
        alphaFadeOut = a;
    }
class GameBgImage : public GuiImage {
public:
    void draw(CVideo *pVideo) override;
    void draw(CVideo *pVideo, const glm::mat4 &modelView) override;
};

private:
    glm::mat4 identity;
    glm::vec4 alphaFadeOut;
};

#endif // _GAME_BG_IMAGE_H_
