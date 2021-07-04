#pragma once
#include "FoxEngine/Core.h"
#include "Event.h"
#include "FoxEngine/Application.h"

namespace FoxEngine {

    class FOX_API ApplicationEvent : public Event {
    protected:
        FoxEngine::Application& application;
    public:
        ApplicationEvent(FoxEngine::Application &application)
                : application(application) {
        }
        DEFINE_EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION);

        virtual std::string ToString() const override {
            return GetName();
        };
    };

    class FOX_API ApplicationDisconnectedEvent : public ApplicationEvent {
    public:
        ApplicationDisconnectedEvent(FoxEngine::Application& application)
                : ApplicationEvent(application) {}

    };

    class FOX_API ApplicationConnectedEvent : public ApplicationEvent {
    public:
        ApplicationConnectedEvent(FoxEngine::Application& application)
                : ApplicationEvent(application) {
        }
        DEFINE_EVENT_CLASS_TYPE(APPLICATION_CONNECTED)

        virtual std::string ToString() const override {
            return GetName();
        }
    };

    class FOX_API ApplicationTickedEvent : public ApplicationEvent {
    public:
        ApplicationTickedEvent(FoxEngine::Application& application)
                : ApplicationEvent(application) {
        }

        DEFINE_EVENT_CLASS_TYPE(APPLICATION_TICKED);

        virtual std::string ToString() const override {
            return GetName();
        }
    };

    class FOX_API ApplicationUpdatedEvent : public ApplicationEvent {
    public:
        ApplicationUpdatedEvent(FoxEngine::Application& application)
                : ApplicationEvent(application) {
        }

        DEFINE_EVENT_CLASS_TYPE(APPLICATION_UPDATED);

        virtual std::string ToString() const override {
            return GetName();
        }
    };

    class FOX_API ApplicationRenderedEvent : public ApplicationEvent {
    public:
        ApplicationRenderedEvent(FoxEngine::Application& application)
                : ApplicationEvent(application) {
        }

        DEFINE_EVENT_CLASS_TYPE(APPLICATION_RENDERED);

        virtual std::string ToString() const override {
            return GetName();
        }
    };

}