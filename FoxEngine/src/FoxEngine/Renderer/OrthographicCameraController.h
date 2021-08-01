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
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	
	class OrthographicCameraController
	{
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCameraBounds m_Bounds;
		OrthographicCamera m_Camera;
		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		
		float m_CameraRotationSpeed = 120.0f;
		float m_CameraTranslationSpeed = 1.0f;
		float m_ZoomSpeed = 0.25f;
		float m_ZoomLevelMax = 6.0f, m_ZoomLevelMin = 0.25f;

		std::pair<float, float> m_LastMousePosition;

		MouseState m_MouseState = MouseState::IDLE;
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }
		const MouseState& GetMouseState() const { return m_MouseState; }

		//Setters
		void SetCameraRotationSpeed(float cameraRotationSpeed) { m_CameraRotationSpeed = cameraRotationSpeed; }
		void SetCameraTranslationSpeed(float cameraTranslationSpeed) { m_CameraTranslationSpeed = cameraTranslationSpeed; }
		void SetZoomSpeed(float zoomSpeed) { m_ZoomSpeed = zoomSpeed; }
		void SetZoomLevelMax(float zoomLevelMax) { m_ZoomLevelMax = zoomLevelMax; }
		void SetZoomLevelMin(float zoomLevelMin) { m_ZoomLevelMin = zoomLevelMin; }
		void SetZoomLevel(float zoomLevel) {
			m_ZoomLevel = zoomLevel;
			CalculateView();
		}

		void OnResize(float width, float height);

		void CalculateView();
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);
	};
}
