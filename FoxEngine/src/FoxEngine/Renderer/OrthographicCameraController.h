#pragma once
#include "FoxEngine/Core/TimeStep.h"
#include "FoxEngine/Renderer/OrthographicCamera.h"
#include "FoxEngine/Event/Event.h"
#include "FoxEngine/Event/WindowEvent.h"
#include "FoxEngine/Event/MouseEvent.h"

namespace FoxEngine
{
	class OrthographicCameraController
	{
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		
		float m_CameraRotationSpeed = 120.0f;
		float m_CameraTranslationSpeed = 1.0f;
		float m_ZoomSpeed = 0.25f;
		float m_ZoomLevelMax = 6.0f, m_ZoomLevelMin = 0.25f;
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		//Setters
		void SetCameraRotationSpeed(float cameraRotationSpeed) { m_CameraRotationSpeed = cameraRotationSpeed; }
		void SetCameraTranslationSpeed(float cameraTranslationSpeed) { m_CameraTranslationSpeed = cameraTranslationSpeed; }
		void SetZoomSpeed(float zoomSpeed) { m_ZoomSpeed = zoomSpeed; }
		void SetZoomLevelMax(float zoomLevelMax) { m_ZoomLevelMax = zoomLevelMax; }
		void SetZoomLevelMin(float zoomLevelMin) { m_ZoomLevelMin = zoomLevelMin; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);
	};
}
