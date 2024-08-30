#ifndef GUI_IMAGE_DATA_H
#define GUI_IMAGE_DATA_H

#include <malloc.h>
#include <gd.h>
#include <gui/GuiElement.h>
#include <gui/gx2_ext.h>
#include <gx2/texture.h>

class GuiElement;

class GuiImageData : public GuiElement {
public:
    //!Constructor
    GuiImageData();

    //!\param img Image data
    //!\param imgSize The image size
    GuiImageData(const uint8_t *img, int32_t imgSize, GX2TexClampMode textureClamp = GX2_TEX_CLAMP_MODE_CLAMP, GX2SurfaceFormat textureFormat = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8);

    //!\param path Image path
    GuiImageData(const char *path, GX2TexClampMode textureClamp, GX2SurfaceFormat textureFormat);

    //!Destructor
    virtual ~GuiImageData();

    //!Load image from buffer
    //!\param img Image data
    //!\param imgSize The image size
    void loadImage(const uint8_t *img, int32_t imgSize, GX2TexClampMode textureClamp = GX2_TEX_CLAMP_MODE_CLAMP, GX2SurfaceFormat textureFormat = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8);

    //!Load image from file
    //!\param path Image path
    void loadImageFromFile(const char *path, GX2TexClampMode textureClamp, GX2SurfaceFormat textureFormat);

    //! getter functions
    virtual const GX2Texture *getTexture() const {
        return texture;
    };

    virtual const GX2Sampler *getSampler() const {
        return sampler;
    };

    //!Gets the image width
    //!\return image width
    int32_t getWidth() const {
        if (texture) {
            return texture->surface.width;
        } else {
            return 0;
        }
    };

    //!Gets the image height
    //!\return image height
    int32_t getHeight() const {
        if (texture) {
            return texture->surface.height;
        } else {
            return 0;
        }
    };

    //! release memory of the image data
    void releaseData(void);

private:
    void gdImageToUnormR8G8B8A8(gdImagePtr gdImg, uint32_t *imgBuffer, uint32_t width, uint32_t height, uint32_t pitch);

    void gdImageToUnormR5G6B5(gdImagePtr gdImg, uint16_t *imgBuffer, uint32_t width, uint32_t height, uint32_t pitch);

    GX2Texture *texture;
    GX2Sampler *sampler;

    enum eMemoryTypes {
        eMemTypeMEM2,
        eMemTypeMEM1,
        eMemTypeMEMBucket
    };

    uint8_t memoryType;
};

#endif
