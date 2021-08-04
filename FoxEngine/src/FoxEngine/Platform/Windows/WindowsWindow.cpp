#include "fepch.h"
#include "WindowsWindow.h"
#include "FoxEngine/Event/WindowEvent.h"
#include "FoxEngine/Event/KeyboardEvent.h"
#include "FoxEngine/Event/MouseEvent.h"

#include "FoxEngine/Platform/OpenGL/OpenGLContext.h"

namespace FoxEngine{
    static bool s_glfwInitialized = false;

    static void GLFWErrorCallback(int errorCode, const char* message) {
        FOX_CORE_ERROR("GLFW Error ({0}): {1}", errorCode, message);
    }

    Window* Window::create(const WindowProperties& properties){
        return new WindowsWindow(properties);
    }

    WindowsWindow::~WindowsWindow() {
    }

    WindowsWindow::WindowsWindow(const WindowProperties& windowProperties) {
        init(windowProperties);
    }

    void WindowsWindow::init(const WindowProperties& windowProperties) {
        windowData.Title = windowProperties.title;
        windowData.Width = windowProperties.width;
        windowData.Height = windowProperties.height;


        FOX_CORE_DEBUG("Creating window {0} ({1} x {2})", windowData.Title, windowData.Width, windowData.Height);

        if(!s_glfwInitialized){
            int success = glfwInit();
            FOX_CORE_ASSERT(success, "Could not initialize GLFW!")
            glfwSetErrorCallback(GLFWErrorCallback);
            s_glfwInitialized = true;
        }

        window = glfwCreateWindow((int)windowData.Width, (int)windowData.Height, windowData.Title.c_str(), nullptr, nullptr);
        graphicsContext = new OpenGLContext(window);
        graphicsContext->init();


        glfwSetWindowUserPointer(window, &windowData);

        setVSync(true);

        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
            {
                WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
                data.Height = height;
                data.Width = width;

                WindowResizedEvent event((float)width, (float)height);
                data.Callback(event);
            });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                WindowClosedEvent event;
                data.Callback(event);
            });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int modes)
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
        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int modes) {
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
    	
            glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int character)
                {
                    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                    KeyboardTypedEvent event(character);
                    data.Callback(event);
                });
    	
        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffest, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event(0, 0, (float)xOffest, (float)yOffset);
            data.Callback(event);
            });


        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float) xPos, (float)yPos);
            data.Callback(event);
            });
    }

    void WindowsWindow::shutdown() {
        glfwDestroyWindow(window);
    }

    void WindowsWindow::onUpdate() {
        glfwPollEvents();
        graphicsContext->swapBuffers();
    }

    void WindowsWindow::onRender() {}

    void WindowsWindow::setVSync(bool enabled) {
        glfwSwapInterval(enabled ? 1 : 0);
        windowData.VSync = enabled;
    }

    bool WindowsWindow::isVSync() const {
        return windowData.VSync;
    }

}