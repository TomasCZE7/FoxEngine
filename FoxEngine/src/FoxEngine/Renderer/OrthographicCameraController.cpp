#include "fepch.h"
#include "FoxEngine/Renderer/OrthographicCameraController.h"

#include "FoxEngine/Core/Input.h"
#include "FoxEngine/Core/KeyCodes.h"
#include "FoxEngine/Core/MouseButtonCodes.h"
#include "FoxEngine/Core/TimeStep.h"

namespace FoxEngine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: aspectRatio(aspectRatio), camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel), rotation(rotation)
	{
		
	}

	void OrthographicCameraController::onUpdate(TimeStep ts)
	{

		/*if (Input::IsKeyPressed(FOX_KEY_A))
		{
			cameraPosition.x -= cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
			cameraPosition.y -= sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(FOX_KEY_D))
		{
			cameraPosition.x += cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
			cameraPosition.y += sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(FOX_KEY_W))
		{
			cameraPosition.x += -sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
			cameraPosition.y += cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(FOX_KEY_S))
		{
			cameraPosition.x -= -sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
			cameraPosition.y -= cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
		}

		if (rotation)
		{
			if (Input::IsKeyPressed(FOX_KEY_Q))
				cameraRotation += cameraRotationSpeed * ts;
			if (Input::isKeyPressed(FOX_KEY_E))
				cameraRotation -= cameraRotationSpeed * ts;

			if (cameraRotation > 180.0f)
				cameraRotation -= 360.0f;
			else if (cameraRotation <= -180.0f)
				cameraRotation += 360.0f;

			camera.setRotation(cameraRotation);
		}*/

		if(Input::isMouseButtonPressed(FOX_MOUSE_BUTTON_MIDDLE))
		{
			if(lastMousePosition.first != -1 && lastMousePosition.second != -1)
			{
				std::pair<float, float> newPos = Input::getMousePosition();

				float xDiff = (cameraTranslationSpeed / 4.0) * (newPos.first - lastMousePosition.first) / 100.0;
				float yDiff = (cameraTranslationSpeed / 4.0) * (newPos.second - lastMousePosition.second) / 100.0;

                cameraPosition.x -= xDiff;
                cameraPosition.y += yDiff;
			}
            mouseState = MouseState::MOVING_CAMERA;
            lastMousePosition = Input::getMousePosition();
		} else if(lastMousePosition.first != -1 && lastMousePosition.second != -1)
		{
            lastMousePosition.first = -1;
            lastMousePosition.first = -1;
            mouseState = MouseState::IDLE;
		}

        camera.setPosition(cameraPosition);

        cameraTranslationSpeed = zoomLevel;
	}

	void OrthographicCameraController::onEvent(Event& e)
	{
		EventCaster eventCaster(e);
        eventCaster.cast<MouseScrolledEvent>(FOX_BIND_EVENT_FUNCTION(OrthographicCameraController::onMouseScrolled));
        eventCaster.cast<WindowResizedEvent>(FOX_BIND_EVENT_FUNCTION(OrthographicCameraController::onWindowResized));
	}

	void OrthographicCameraController::onResize(float width, float height)
	{
        aspectRatio = width / height;
        camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
	}

	void OrthographicCameraController::calculateView()
	{
        bounds = {-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel };
        camera.setProjection(bounds.left, bounds.right, bounds.bottom, bounds.top);
	}

	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e)
	{
        zoomLevel -= e.getOffsetY() * 0.25f;
        zoomLevel = std::clamp(zoomLevel, zoomLevelMin, zoomLevelMax);
        camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizedEvent& e)
	{
        onResize((float) e.getWidth(), (float) e.getHeight());
		return false;
	}
}
