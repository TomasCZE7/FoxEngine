#pragma once
#include "fepch.h"
#include "FoxEngine/Core/Core.h"
#include "Event.h"

namespace FoxEngine{

    class FOX_API MouseEvent : public Event{
    protected:
        float positionX, positionY;
    public:

        MouseEvent(float positionX, float positionY)
        : positionX(positionX), positionY(positionY) {
        }

        float getPositionX() const
        {
	        return positionX;
        }

        float getPositionY() const
        {
	        return positionY;
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

        inline int getButtonType() const { return buttonType; }

        virtual std::string toString() const override {
            return "MouseButtonPressedEvent (posX: " + std::to_string(positionX) + ", posY: " + std::to_string(positionY) + ", buttonType: " + std::to_string(buttonType) + ")";
        }
    };

    class FOX_API MouseButtonReleasedEvent : public MouseEvent{
    protected:
        int buttonType;
    public:

        MouseButtonReleasedEvent(float positionX, float positionY, int buttonType)
                : MouseEvent(positionX, positionY), buttonType(buttonType) {
        }

        DEFINE_EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED);
        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE_BUTTON);
    	
        inline int getButtonType() const { return buttonType; }

        virtual std::string toString() const override {
            return "MouseButtonReleasedEvent (posX: " + std::to_string(positionX) + ", posY: " + std::to_string(positionY) + ", buttonType: " + std::to_string(buttonType) + ")";
        }

    };

    class FOX_API MouseMovedEvent : public MouseEvent{
    protected:
    public:
        MouseMovedEvent(float positionX, float positionY)
                : MouseEvent(positionX, positionY) {
        }

        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE);
        DEFINE_EVENT_CLASS_TYPE(MOUSE_STEPPED);

        virtual std::string toString() const override {
            return "MouseMovedEvent (positionX: "+ std::to_string(positionX) +", positionY: " + std::to_string(positionY) + ")";
        }
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

        float getOffsetX() const
        {
	        return offsetX;
        }

        float getOffsetY() const
        {
	        return offsetY;
        }
        virtual std::string toString() const override {
            return "MouseScrolledEvent (posX: " + std::to_string(positionX) + ", posY: "+ std::to_string(positionY) +", offsetX: " + std::to_string(offsetX)
        		+   ", offsetY: " + std::to_string(offsetY) + ")";
        }
    };

}