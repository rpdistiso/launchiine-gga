#include "gui/GuiImage.h"
#include "gui/GuiImageData.h"
#include "gui/GuiSwitch.h"

/**
 * Constructor for the GuiSwitch class.
 */

GuiSwitch::GuiSwitch(GuiImage *background, bool checked, float w, float h)
    : GuiToggle(checked, w, h) {
    setImageBackground(background);
}

/**
 * Destructor for the GuiSwitch class.
 */
GuiSwitch::~GuiSwitch() {
}

void GuiSwitch::setImageBackground(GuiImage *img) {
    backgroundImg = img;
    if (img) {
        img->setParent(this);
    }
    setImage(img);
}

void GuiSwitch::setImageOn(GuiImage *img) {
    onImg = img;
    if (img) {
        img->setParent(this);
        img->setAlignment(ALIGN_RIGHT);
    }
}

void GuiSwitch::setImageOff(GuiImage *img) {
    offImg = img;
    if (img) {
        img->setParent(this);
        img->setAlignment(ALIGN_LEFT);
    }
}

void GuiSwitch::setImageHighlighted(GuiImage *img) {
    highlightedImg = img;
    setIconOver(img);
}

void GuiSwitch::draw(CVideo *v) {
    if (!this->isVisible()) {
        return;
    }

    GuiToggle::draw(v);
    if (getValue()) {
        if (onImg != NULL) {
            onImg->draw(v);
        }
    } else {
        if (offImg != NULL) {
            offImg->draw(v);
        }
    }
}
