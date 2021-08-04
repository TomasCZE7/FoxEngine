#pragma once
#include "FoxEngine/Core/TimeStep.h"
#include "FoxEngine/Renderer/OrthographicCamera.h"
#include "FoxEngine/Event/Event.h"
#include "FoxEngine/Event/WindowEvent.h"
#include "FoxEngine/Event/MouseEvent.h"

namespace FoxEngine
{
	enum class MouseState
	{
		IDLE, MOVING_CAMERA
	};
	
	struct OrthographicCameraBounds
	{
		float left, right;
		float bottom, top;

		float GetWidth() { return right - left; }
		float GetHeight() { return top - bottom; }
	};

	
	class OrthographicCameraController
	{
	private:
		float aspectRatio;
		float zoomLevel = 1.0f;
		OrthographicCameraBounds bounds;
		OrthographicCamera camera;
		bool rotation;

		glm::vec3 cameraPosition = {0.0f, 0.0f, 0.0f };
		float cameraRotation = 0.0f;
		
		float cameraRotationSpeed = 120.0f;
		float cameraTranslationSpeed = 1.0f;
		float zoomSpeed = 0.25f;
		float zoomLevelMax = 6.0f, zoomLevelMin = 0.25f;

		std::pair<float, float> lastMousePosition;

		MouseState mouseState = MouseState::IDLE;
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		void onUpdate(TimeStep ts);
		void onEvent(Event& e);
		OrthographicCamera& getCamera() { return camera; }
		const OrthographicCamera& getCamera() const { return camera; }
		const OrthographicCameraBounds& getBounds() const { return bounds; }
		const MouseState& getMouseState() const { return mouseState; }

		//Setters
		void setCameraRotationSpeed(float cameraRotationSpeed) { cameraRotationSpeed = cameraRotationSpeed; }
		void setCameraTranslationSpeed(float cameraTranslationSpeed) { cameraTranslationSpeed = cameraTranslationSpeed; }
		void setZoomSpeed(float zoomSpeed) { zoomSpeed = zoomSpeed; }
		void setZoomLevelMax(float zoomLevelMax) { zoomLevelMax = zoomLevelMax; }
		void setZoomLevelMin(float zoomLevelMin) { zoomLevelMin = zoomLevelMin; }
		void setZoomLevel(float zoomLevel) {
            zoomLevel = zoomLevel;
            calculateView();
		}

		void onResize(float width, float height);

		void calculateView();
	private:
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResized(WindowResizedEvent& e);
	};
}
