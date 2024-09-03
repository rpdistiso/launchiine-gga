#include "gui/GuiToggle.h"

/**
 * Constructor for the GuiToggle class.
 */

GuiToggle::GuiToggle(bool checked, float width, float height)
    : GuiButton(width, height) {
    bChanged = false;
    selected = checked;
    clicked.connect(this, &GuiToggle::OnToggleClick);
}

/**
 * Destructor for the GuiButton class.
 */
GuiToggle::~GuiToggle() {
    bChanged = false;
    selected = false;
}

void GuiToggle::OnToggleClick(GuiButton *button, const GuiController *controller, GuiTrigger *trigger) {
    if (!isStateSet(STATE_DISABLED | STATE_HIDDEN | STATE_DISABLE_INPUT)) {
        if (selected) {
            setUnchecked();
        } else {
            setChecked();
        }
    }
}

void GuiToggle::update(GuiController *c) {
    GuiButton::update(c);
}
