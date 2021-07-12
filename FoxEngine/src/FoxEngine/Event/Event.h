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
    protected:
        bool Handled = false;
    public:
        virtual ~Event() = default;
        virtual EventType GetEventType() const = 0;
        virtual int GetEventCategoryFlags() const = 0;
        virtual const char* GetName() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category){
            return GetEventCategoryFlags() & category;
        }

        bool IsHandled() const { return Handled; }

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
        bool Cast(EventFunction<T> function){
            if(event.GetEventType() == T::GetStaticType()){
                event.Handled = function(*(T*)&event);
                return true;
            }
            return false;
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Event& event) {
        return os << event.ToString();
    }

}


#define DEFINE_EVENT_CLASS_TYPE(type) static EventType GetStaticType(){ return EventType::type; } \
                                        virtual EventType GetEventType() const override { return GetStaticType(); } \
                                        virtual const char* GetName() const override { return #type; }

#define DEFINE_EVENT_CLASS_CATEGORY(category) virtual int GetEventCategoryFlags() const override { return category; }