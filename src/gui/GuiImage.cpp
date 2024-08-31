#include "GuiImage.h"
#include <glm/mat4x4.hpp>

void GuiImage::draw(CVideo *pVideo) {
    glm::mat4 identityMatrix(1.0f);
    draw(pVideo, identityMatrix);
}

void GuiImage::setSize(float width, float height) {
    this->width = width;
    this->height = height;
}
void GuiImage::draw(CVideo *pVideo, const glm::mat4 &modelView) {
    if (this->isVisible()) {
        // Apply modelView transformation
        glm::mat4 finalMatrix = modelView * glm::translate(glm::mat4(1.0f), glm::vec3(this->getCenterX(), this->getCenterY(), this->getDepth()));
        finalMatrix = glm::scale(finalMatrix, glm::vec3(this->getScaleX(), this->getScaleY(), 1.0f));
        finalMatrix = glm::rotate(finalMatrix, glm::radians(this->getAngle()), glm::vec3(0.0f, 0.0f, 1.0f));

        // Set up shader and uniforms
        // Draw the image using the finalMatrix

        // If it's a texture
        if (imgType == IMAGE_TEXTURE && imageData) {
            // Bind texture, set up vertices, etc.
            // Draw textured quad
        }
        // If it's a color
        else if (imgType == IMAGE_COLOR) {
            // Set up color vertices
            // Draw colored quad
        }

        // Apply tiling if necessary
        for (int32_t y = 0; y < tileVertical; y++) {
            for (int32_t x = 0; x < tileHorizontal; x++) {
                // Draw tiled image
            }
        }
    }
}
