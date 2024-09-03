#ifndef GUI_DRAG_LISTENER_H_
#define GUI_DRAG_LISTENER_H_

#include "gui/GuiButton.h"
#include "gui/GuiController.h"
#include "gui/GuiElement.h"
#include "gui/GuiTrigger.h"

class GuiDragListener : public GuiElement {
public:
    //!Constructor
    //!\param w Width
    //!\param h Height
    GuiDragListener(float w, float h);

    //!Destructor
    virtual ~GuiDragListener();

    void setState(int32_t i, int32_t c);

    //!Set a new GuiTrigger for the element
    //!\param i Index of trigger array to set
    //!\param t Pointer to GuiTrigger
    void setTrigger(GuiTrigger *t, int32_t idx = -1);

    //!Constantly called to allow the GuiDragListener to respond to updated input data
    //!\param t Pointer to a GuiTrigger, containing the current input data from PAD/WPAD
    void update(GuiController *c);

    sigslot::signal5<GuiDragListener *, const GuiController *, GuiTrigger *, int32_t, int32_t> dragged;

protected:
    static const int32_t iMaxGuiTriggers = 10;

    GuiTrigger *trigger[iMaxGuiTriggers]; //!< GuiTriggers (input actions) that this element responds to
};

#endif
