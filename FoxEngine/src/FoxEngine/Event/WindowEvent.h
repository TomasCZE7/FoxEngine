#pragma once
#include "fepch.h"
#include "FoxEngine/Core.h"
#include "Event.h"
#include "FoxEngine/Window.h"

namespace FoxEngine {

    class FOX_API WindowClosedEvent : public Event{
    public:
        WindowClosedEvent(){

        }
        DEFINE_EVENT_CLASS_TYPE(WINDOW_CLOSED);
        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);

        virtual std::string ToString() const override {
            return "WindowClosedEvent ()";
        }
    };

    class FOX_API WindowResizedEvent : public Event{
    private:
        float height, width;
    public:
        WindowResizedEvent(float height, float width)
        : height(height), width(width){

        }
        DEFINE_EVENT_CLASS_TYPE(WINDOW_RESIZED);
        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);

        float GetHeight() const
        {
	        return height;
        }

        float GetWidth() const
        {
	        return width;
        }
        virtual std::string ToString() const override {
            return "WindowResizedEvent (width: " + std::to_string(width) + ", height: " + std::to_string(height) + ")";
        }
    };

    class FOX_API WindowMovedEvent : public Event{
    private:
        float positionX, positionY;
    public:
        WindowMovedEvent(float positionX, float positionY)
                : positionX(positionX), positionY(positionY){

        }
        DEFINE_EVENT_CLASS_TYPE(WINDOW_MOVED);
        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);

        virtual std::string ToString() const override {
            return "WindowMovedEvent (positionY: " + std::to_string(positionX) + ", positionY: " + std::to_string(positionY) + ")";
        }
    };

    class FOX_API WindowFocusEvent : public Event{
    private:
        bool IsWindowFocused;
        Window& WindowRef;
    public:
        WindowFocusEvent(bool isWindowFocused, Window& window)
                : IsWindowFocused(isWindowFocused), WindowRef(window){

        }
        DEFINE_EVENT_CLASS_TYPE(WINDOW_FOCUS);
        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);

        virtual std::string ToString() const override {
            return "WindowFocusEvent (isWindowFocused: " + std::to_string(IsWindowFocused) + ", window: " + WindowRef.GetWindowTitle() + ")";
        }
    };

}