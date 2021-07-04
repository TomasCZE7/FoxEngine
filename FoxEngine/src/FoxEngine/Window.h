#pragma once
#include "fepch.h"
#include "FoxEngine/Core.h"
#include "FoxEngine/Event/Event.h"
#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

namespace FoxEngine {

    struct WindowProperties {
            std::string Title;
            unsigned int Width;
            unsigned int Height;

            public:
            WindowProperties(std::string title = "Fox Engine", unsigned int width = 1280, unsigned int height = 720)
            : Title(title), Width(width), Height(height){

            }

    };

    class FOX_API Window {
            public:
            virtual ~Window(){}

            virtual void OnUpdate() = 0;
            virtual void OnRender() = 0;

            virtual unsigned int GetHeight() const = 0;
            virtual unsigned int GetWidth() const = 0;

            virtual void SetVSync(bool enabled) = 0;
            virtual bool IsVSync() const = 0;

            virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;
                
            static Window* Create(const WindowProperties& properties = WindowProperties());

            virtual void* GetNativeWindow() const = 0;

    };

}