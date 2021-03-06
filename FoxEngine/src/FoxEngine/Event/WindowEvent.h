#pragma once
#include "../Core.h"
#include "Event.h"

namespace FoxEngine {

    class FOX_API WindowClosedEvent : Event{
    public:
        WindowClosedEvent(){

        }
        DEFINE_EVENT_CLASS_TYPE(WINDOW_CLOSED);
        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
    };

    class FOX_API WindowResizedEvent : Event{
    private:
        float height, width;
    public:
        WindowResizedEvent(float height, float width)
        : height(height), width(width){

        }
        DEFINE_EVENT_CLASS_TYPE(WINDOW_RESIZED);
        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
    };

    class FOX_API WindowMovedEvent : Event{
    private:
        float positionX, positionY;
    public:
        WindowMovedEvent(float positionX, float positionY)
                : positionX(positionX), positionY(positionY){

        }
        DEFINE_EVENT_CLASS_TYPE(WINDOW_MOVED);
        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
    };

    class FOX_API WindowFocusEvent : Event{
    private:
        bool isWindowFocused;
    public:
        WindowFocusEvent(bool isWindowFocused)
                : isWindowFocused(isWindowFocused){

        }
        DEFINE_EVENT_CLASS_TYPE(WINDOW_FOCUS);
        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_WINDOW);
    };

}