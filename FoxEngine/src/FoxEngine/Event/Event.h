#pragma once
#include "fepch.h"
#include "FoxEngine/Core/Core.h"

namespace FoxEngine {

    enum class EventType {
        NONE = 0,
        WINDOW_CLOSED, WINDOW_RESIZED, WINDOW_FOCUS, WINDOW_MOVED,
        KEYBOARD_KEY_PRESSED, KEYBOARD_KEY_RELEASED, KEYBOARD_TYPED,
        APPLICATION_CONNECTED, APPLICATION_DISCONNECTED, APPLICATION_TICKED, APPLICATION_UPDATED, APPLICATION_RENDERED,
        MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_STEPPED, MOUSE_SCROLLED,
    };

    enum EventCategory {
        NONE = 0,
        EVENT_CATEGORY_APPLICATION = BIT(0),
        EVENT_CATEGORY_INPUT = BIT(1),
        EVENT_CATEGORY_KEYBOARD = BIT(2),
        EVENT_CATEGORY_WINDOW = BIT(3),
        EVENT_CATEGORY_MOUSE = BIT(4),
        EVENT_CATEGORY_MOUSE_BUTTON = BIT(5),
    };

    class FOX_API Event {
        friend class EventCaster;
    public:
        bool handled = false;
    public:
        virtual ~Event() = default;
        virtual EventType getEventType() const = 0;
        virtual int getEventCategoryFlags() const = 0;
        virtual const char* getName() const = 0;
        virtual std::string toString() const { return getName(); }

        inline bool isInCategory(EventCategory category){
            return getEventCategoryFlags() & category;
        }

        bool isHandled() const { return handled; }

    };

    class EventCaster {
        template<typename T>
        using EventFunction = std::function<bool(T&)>;
    private:
        Event& event;
    public:
        EventCaster(Event& event)
        : event(event){
        }

        template<typename T>
        bool cast(EventFunction<T> function){
            if(event.getEventType() == T::getStaticType()){
                event.handled = function(*(T*)&event);
                return true;
            }
            return false;
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Event& event) {
        return os << event.toString();
    }

}


#define DEFINE_EVENT_CLASS_TYPE(type) static EventType getStaticType(){ return EventType::type; } \
                                        virtual EventType getEventType() const override { return getStaticType(); } \
                                        virtual const char* getName() const override { return #type; }

#define DEFINE_EVENT_CLASS_CATEGORY(category) virtual int getEventCategoryFlags() const override { return category; }