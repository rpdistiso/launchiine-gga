#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gui/video/CursorDrawer.h"
#include "gui/video/shaders/ColorShader.h"
#include "gui/video/shaders/FXAAShader.h"
#include "gui/video/shaders/Shader3D.h"
#include "gui/video/shaders/ShaderFractalColor.h"
#include "gui/video/shaders/Texture2DShader.h"

CursorDrawer *CursorDrawer::instance = NULL;

CursorDrawer::CursorDrawer() {
    init_colorVtxs();
}

CursorDrawer::~CursorDrawer() {
    //! destroy shaders
    ColorShader::destroyInstance();
    FXAAShader::destroyInstance();
    Shader3D::destroyInstance();
    ShaderFractalColor::destroyInstance();
    Texture2DShader::destroyInstance();
    if (this->colorVtxs) {
        free(this->colorVtxs);
        this->colorVtxs = NULL;
    }
}

void CursorDrawer::init_colorVtxs() {
    if (!this->colorVtxs) {
        this->colorVtxs = (uint8_t *) memalign(0x40, sizeof(uint8_t) * 16);
        if (this->colorVtxs == NULL) { return; }
    }
    memset(this->colorVtxs, 0xFF, 16 * sizeof(uint8_t));

    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_ATTRIBUTE_BUFFER, this->colorVtxs, 16 * sizeof(uint8_t));
}

// Could be improved. It be more generic.
void CursorDrawer::draw_Cursor(float x, float y) {
    if (this->colorVtxs == NULL) {
        init_colorVtxs();
        return;
    }

    float widthScaleFactor  = 1.0f / (float) 1280;
    float heightScaleFactor = 1.0f / (float) 720;

    int32_t width = 20;

    glm::vec3 positionOffsets = glm::vec3(0.0f);

    positionOffsets[0] = (x - ((1280) / 2) + (width / 2)) * widthScaleFactor * 2.0f;
    positionOffsets[1] = -(y - ((720) / 2) + (width / 2)) * heightScaleFactor * 2.0f;

    glm::vec3 scale(width * widthScaleFactor, width * heightScaleFactor, 1.0f);

    ColorShader::instance()->setShaders();
    ColorShader::instance()->setAttributeBuffer(this->colorVtxs, NULL, 4);
    ColorShader::instance()->setAngle(0);
    ColorShader::instance()->setOffset(positionOffsets);
    ColorShader::instance()->setScale(scale);
    ColorShader::instance()->setColorIntensity(glm::vec4(1.0f));
    ColorShader::instance()->draw(GX2_PRIMITIVE_MODE_QUADS, 4);
}
