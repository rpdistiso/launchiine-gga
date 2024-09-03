#include "gui/GuiCheckBox.h"
#include "gui/GuiImage.h"
#include "gui/GuiImageData.h"

/**
 * Constructor for the GuiCheckBox class.
 */

GuiCheckBox::GuiCheckBox(GuiImage *background, bool checked, float width, float height)
    : GuiToggle(checked, width, height) {
    setImageBackground(background);
}

/**
 * Destructor for the GuiCheckBox class.
 */
GuiCheckBox::~GuiCheckBox() {
}

void GuiCheckBox::setImageBackground(GuiImage *img) {
    backgroundImg = img;
    if (img) {
        img->setParent(this);
    }
}

void GuiCheckBox::setImageSelected(GuiImage *img) {
    selectedImg = img;
    if (img) {
        img->setParent(this);
    }
}

void GuiCheckBox::setImageHighlighted(GuiImage *img) {
    highlightedImg = img;
    if (img) {
        img->setParent(this);
    }
    setIconOver(img);
}

void GuiCheckBox::update(GuiController *c) {
    if (bChanged) {
        if (selected) {
            GuiButton::setImage(selectedImg);
        } else {
            GuiButton::setImage(backgroundImg);
        }
        bChanged = false;
    }
    GuiToggle::update(c);
}
