#pragma once

#include "FoxEngine/Window.h"

#include <GLFW/glfw3.h>

namespace FoxEngine{

    class WindowsWindow : public Window {
    private:
        GLFWwindow* WindowRef;

        struct WindowData{
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            std::function<void(Event&)> Callback;
        };

        WindowData m_WindowData;

        virtual void Init(const WindowProperties& windowProperties);
        virtual void Shutdown();

    public:
        virtual ~WindowsWindow();
        WindowsWindow(const WindowProperties& windowProperties);

        void OnUpdate() override;
        void OnRender() override;

        inline unsigned int GetHeight() const override { return m_WindowData.Height; };
        inline unsigned int GetWidth() const override { return m_WindowData.Width; };

        inline void SetEventCallback(const std::function<void(Event&)>& callback) override { m_WindowData.Callback = callback; }

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;
        inline virtual void* GetNativeWindow() const { return WindowRef; };
    };

}