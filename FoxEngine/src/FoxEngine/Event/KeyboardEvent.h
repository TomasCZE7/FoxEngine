#pragma once
#include "fepch.h"
#include "FoxEngine/Core.h"
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

        unsigned GetKey() const
        {
	        return key;
        }
    };

    class FOX_API KeyboardKeyPressedEvent : public KeyboardEvent{
    private:
        unsigned int repeatCount;
    public:
        KeyboardKeyPressedEvent(unsigned int key, unsigned int repeatCount)
                : KeyboardEvent(key), repeatCount(repeatCount){
        }

        DEFINE_EVENT_CLASS_TYPE(KEYBOARD_KEY_PRESSED);

        virtual std::string ToString() const override {
            return "KeyboardKeyPressedEvent (key: " + std::to_string(key) + ", repeatCount: " + std::to_string(repeatCount) + ")";
        }
    };

    class FOX_API KeyboardTypedEvent : public KeyboardEvent {
    private:
    public:
        KeyboardTypedEvent(unsigned int key)
            : KeyboardEvent(key) {
        }

        DEFINE_EVENT_CLASS_TYPE(KEYBOARD_TYPED);

        virtual std::string ToString() const override {
            return "KeyboardTypedEvent (key: " + std::to_string(key) + ")";
        }

    };

    class FOX_API KeyboardKeyReleasedEvent : public KeyboardEvent{
    public:
        KeyboardKeyReleasedEvent(unsigned int key)
                : KeyboardEvent(key){

        }
        DEFINE_EVENT_CLASS_TYPE(KEYBOARD_KEY_RELEASED);

        virtual std::string ToString() const override {
            return "KeyboardKeyReleasedEvent (key: " + std::to_string(key) + ")";
        }
    };

}