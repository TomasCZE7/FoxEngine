#pragma once
#include "../Core.h"
#include "Event.h"

namespace FoxEngine {

    class FOX_API KeyboardEvent : public Event {
    protected:
        unsigned int key;
    public:
        KeyboardEvent(unsigned int key)
        : key(key){

        }
        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_INPUT | EVENT_CATEGORY_KEYBOARD);
    };

    class FOX_API KeyboardKeyPressedEvent : public KeyboardEvent{
    private:
        unsigned int repeatCount;
    public:
        KeyboardKeyPressedEvent(unsigned int key, unsigned int repeatCount)
                : KeyboardEvent(key), repeatCount(repeatCount){
        }

        DEFINE_EVENT_CLASS_TYPE(KEYBOARD_KEY_PRESSED);
    };

    class FOX_API KeyboardKeyReleasedEvent : public KeyboardEvent{
    public:
        KeyboardKeyReleasedEvent(unsigned int key)
                : KeyboardEvent(key){

        }
        DEFINE_EVENT_CLASS_TYPE(KEYBOARD_KEY_RELEASED);
    };

}