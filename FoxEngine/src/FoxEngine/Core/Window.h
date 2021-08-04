#pragma once
#include "fepch.h"
#include "FoxEngine/Core/Core.h"
#include "FoxEngine/Event/Event.h"
#define FOX_BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

namespace FoxEngine {

    struct WindowProperties {
            std::string title;
            unsigned int width;
            unsigned int height;

            public:
            WindowProperties(std::string title = "Fox Engine", unsigned int width = 1280, unsigned int height = 720)
            : title(title), width(width), height(height){

            }

    };

    class FOX_API Window {
            public:
            virtual ~Window(){}

            virtual void onUpdate() = 0;
            virtual void onRender() = 0;

            virtual unsigned int getHeight() const = 0;
            virtual unsigned int getWidth() const = 0;

            virtual void setVSync(bool enabled) = 0;
            virtual bool isVSync() const = 0;

            virtual void setEventCallback(const std::function<void(Event &)>& callback) = 0;
                
            static Window* create(const WindowProperties& properties = WindowProperties());

            virtual void* getNativeWindow() const = 0;
            virtual inline std::string getWindowTitle() const = 0;

    };

}