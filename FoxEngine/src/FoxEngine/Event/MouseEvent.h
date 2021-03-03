#pragma once
#include "../Core.h"
#include "Event.h"

namespace FoxEngine{

    class FOX_API MouseEvent : public Event{
    protected:
        float positionX, positionY;
    public:

        MouseEvent(float positionX, float positionY)
        : positionX(positionX), positionY(positionY) {
        }

    };
    class FOX_API MouseButtonPressedEvent : public MouseEvent{
    protected:
        int buttonType;
    public:

        MouseButtonPressedEvent(float positionX, float positionY, int buttonType)
                : MouseEvent(positionX, positionY), buttonType(buttonType) {
        }

        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE_BUTTON);
        DEFINE_EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED);

    };

    class FOX_API MouseButtonReleasedEvent : public MouseEvent{
    protected:
        int buttonType;
    public:

        MouseButtonReleasedEvent(float positionX, float positionY, int buttonType)
                : MouseEvent(positionX, positionY), buttonType(buttonType) {
        }

        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE_BUTTON);
        DEFINE_EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED);

    };

    class FOX_API MouseSteppedEvent : public MouseEvent{
    protected:
    public:
        MouseSteppedEvent(unsigned int positionX, unsigned int positionY)
                : MouseEvent(positionX, positionY) {
        }

        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE);
        DEFINE_EVENT_CLASS_TYPE(MOUSE_STEPPED);

    };

    class FOX_API MouseScrolledEvent : public MouseEvent{
    protected:
        float offsetX, offsetY;
    public:
        MouseScrolledEvent(float positionX, float positionY, float offsetX, float offsetY)
                : MouseEvent(positionX, positionY), offsetX(offsetX), offsetY(offsetY) {
        }

        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE_BUTTON);
        DEFINE_EVENT_CLASS_TYPE(MOUSE_SCROLLED);

    };

}