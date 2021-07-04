#include "fepch.h"
#include "WindowsWindow.h"
#include "FoxEngine/Event/WindowEvent.h"
#include "FoxEngine/Event/KeyboardEvent.h"
#include "FoxEngine/Event/MouseEvent.h"
#include "FoxEngine/Event/ApplicationEvent.h"

#include <glad/glad.h>

namespace FoxEngine{
    static bool s_glfwInitialized = false;

    static void GLFWErrorCallback(int errorCode, const char* message) {
        FOX_CORE_ERROR("GLFW Error ({0}): {1}", errorCode, message);
    }

    Window* Window::Create(const WindowProperties& windowProperties){
        return new WindowsWindow(windowProperties);
    }

    WindowsWindow::~WindowsWindow() {
    }

    WindowsWindow::WindowsWindow(const WindowProperties& windowProperties) {
        Init(windowProperties);
    }

    void WindowsWindow::Init(const WindowProperties& windowProperties) {
        m_WindowData.Title = windowProperties.Title;
        m_WindowData.Width = windowProperties.Width;
        m_WindowData.Height = windowProperties.Height;

        FOX_CORE_DEBUG("Creating window {0} ({1} x {2})", m_WindowData.Title, m_WindowData.Width, m_WindowData.Height);

        if(!s_glfwInitialized){
            int success = glfwInit();
            FOX_CORE_ASSERT(success, "Could not initialize GLFW!")
            glfwSetErrorCallback(GLFWErrorCallback);
            s_glfwInitialized = true;
        }

        WindowRef = glfwCreateWindow((int)m_WindowData.Width, (int)m_WindowData.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
        
        glfwMakeContextCurrent(WindowRef);
        int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        FOX_CORE_ASSERT(gladStatus, "Failed to initialize GLAD!")

        glfwSetWindowUserPointer(WindowRef, &m_WindowData);

        SetVSync(true);

        glfwSetWindowSizeCallback(WindowRef, [](GLFWwindow* window, int width, int height)
            {
                WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
                data.Height = height;
                data.Width = width;

                WindowResizedEvent event(width, height);
                data.Callback(event);
            });

        glfwSetWindowCloseCallback(WindowRef, [](GLFWwindow* window)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                WindowClosedEvent event;
                data.Callback(event);
            });

        glfwSetKeyCallback(WindowRef, [](GLFWwindow* window, int key, int scancode, int action, int modes)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                switch (action) {
                    case GLFW_PRESS:
                    {
                        KeyboardKeyPressedEvent event(key, 0);
                        data.Callback(event);
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        KeyboardKeyReleasedEvent event(key);
                        data.Callback(event);
                        break;
                    }
                    case GLFW_REPEAT:
                    {
                        KeyboardKeyPressedEvent event(key, 1);
                        data.Callback(event);
                        break;
                    }
                }
            });
        glfwSetMouseButtonCallback(WindowRef, [](GLFWwindow* window, int button, int action, int modes) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(0, 0, button);
                    data.Callback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(0, 0, button);
                    data.Callback(event);
                    break;
                }
            }
            });
    	
            glfwSetCharCallback(WindowRef, [](GLFWwindow* window, unsigned int character)
                {
                    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                    KeyboardTypedEvent event(character);
                    data.Callback(event);
                });
    	
        glfwSetScrollCallback(WindowRef, [](GLFWwindow* window, double xOffest, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event(0, 0, xOffest, yOffset);
            data.Callback(event);
            });


        glfwSetCursorPosCallback(WindowRef, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event(xPos, yPos);
            data.Callback(event);
            });
    }

    void WindowsWindow::Shutdown() {
        glfwDestroyWindow(WindowRef);
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(WindowRef);
    }

    void WindowsWindow::OnRender() {}

    void WindowsWindow::SetVSync(bool enabled) {
        glfwSwapInterval(enabled ? 1 : 0);
        m_WindowData.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const {
        return m_WindowData.VSync;
    }

}