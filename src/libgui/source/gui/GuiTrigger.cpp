#include "gui/GuiController.h"
#include "gui/GuiElement.h"
#include "gui/GuiTrigger.h"

/**
 * Constructor for the GuiTrigger class.
 */
GuiTrigger::GuiTrigger()
    : chan(CHANNEL_ALL), btns(BUTTON_NONE), bClickEverywhere(false), bHoldEverywhere(false), bSelectionClickEverywhere(false), bLastTouched(false) {
}

GuiTrigger::GuiTrigger(uint32_t ch, uint32_t btn, bool clickEverywhere, bool holdEverywhere, bool selectionClickEverywhere)
    : chan(ch), btns(btn), bClickEverywhere(clickEverywhere), bHoldEverywhere(holdEverywhere), bSelectionClickEverywhere(selectionClickEverywhere), bLastTouched(false) {
}

/**
 * Destructor for the GuiTrigger class.
 */
GuiTrigger::~GuiTrigger() {
}

/**
 * Sets a simple trigger. Requires:
 * - Element is selected
 * - Trigger button is pressed
 */
void GuiTrigger::setTrigger(uint32_t ch, uint32_t btn) {
    chan = ch;
    btns = btn;
}

bool GuiTrigger::left(const GuiController *controller) const {
    if ((controller->chan & chan) == 0) {
        return false;
    }
    if ((controller->data.buttons_h | controller->data.buttons_d) & (BUTTON_LEFT | STICK_L_LEFT)) {
        return true;
    }
    return false;
}

bool GuiTrigger::right(const GuiController *controller) const {
    if ((controller->chan & chan) == 0) {
        return false;
    }
    if ((controller->data.buttons_h | controller->data.buttons_d) & (BUTTON_RIGHT | STICK_L_RIGHT)) {
        return true;
    }
    return false;
}

bool GuiTrigger::up(const GuiController *controller) const {
    if ((controller->chan & chan) == 0) {
        return false;
    }
    if ((controller->data.buttons_h | controller->data.buttons_d) & (BUTTON_UP | STICK_L_UP)) {
        return true;
    }
    return false;
}

bool GuiTrigger::down(const GuiController *controller) const {
    if ((controller->chan & chan) == 0) {
        return false;
    }
    if ((controller->data.buttons_h | controller->data.buttons_d) & (BUTTON_DOWN | STICK_L_DOWN)) {
        return true;
    }
    return false;
}

int32_t GuiTrigger::clicked(const GuiController *controller) const {
    if ((controller->chan & chan) == 0) {
        return CLICKED_NONE;
    }

    int32_t bResult = CLICKED_NONE;

    if (controller->data.touched && controller->data.validPointer && (btns & VPAD_TOUCH) && !controller->lastData.touched) {
        bResult = CLICKED_TOUCH;
    }

    if (controller->data.buttons_d & btns) {
        bResult = CLICKED_BUTTON;
    }
    return bResult;
}

bool GuiTrigger::held(const GuiController *controller) const {
    if ((controller->chan & chan) == 0) {
        return false;
    }

    bool bResult = false;

    if (controller->data.touched && (btns & VPAD_TOUCH) && controller->data.validPointer && controller->lastData.touched && controller->lastData.validPointer) {
        bResult = true;
    }

    if (controller->data.buttons_h & btns) {
        bResult = true;
    }

    return bResult;
}

bool GuiTrigger::released(const GuiController *controller) const {
    if ((controller->chan & chan) == 0) {
        return false;
    }

    if (clicked(controller) || held(controller)) {
        return false;
    }

    bool bResult = false;

    if (!controller->data.touched && (btns & VPAD_TOUCH) && controller->lastData.touched && controller->lastData.validPointer) {
        bResult = true;
    }

    if (controller->data.buttons_r & btns) {
        bResult = true;
    }

    return bResult;
}
