#pragma once

#include "FoxEngine/Core/Window.h"
#include "FoxEngine/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace FoxEngine{

    class WindowsWindow : public Window {
    private:
        GLFWwindow* window;
        GraphicsContext* graphicsContext;

        struct WindowData{
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            std::function<void(Event&)> Callback;
        };

        WindowData windowData;

        virtual void init(const WindowProperties& windowProperties);
        virtual void shutdown();

    public:
        virtual ~WindowsWindow();
        WindowsWindow(const WindowProperties& windowProperties);

        void onUpdate() override;
        void onRender() override;

        inline unsigned int getHeight() const override { return windowData.Height; };
        inline unsigned int getWidth() const override { return windowData.Width; };
        inline std::string getWindowTitle() const override { return windowData.Title; };

        inline void setEventCallback(const std::function<void(Event&)>& callback) override { windowData.Callback = callback; }

        void setVSync(bool enabled) override;
        bool isVSync() const override;
        inline virtual void* getNativeWindow() const { return window; };
    };

}