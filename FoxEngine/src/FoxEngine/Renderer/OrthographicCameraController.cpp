#include "fepch.h"
#include "FoxEngine/Renderer/OrthographicCameraController.h"

#include "FoxEngine/Core/Input.h"
#include "FoxEngine/Core/KeyCodes.h"
#include "FoxEngine/Core/TimeStep.h"

namespace FoxEngine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
		m_AspectRatio(aspectRatio), m_Rotation(rotation),
		m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel })
	{
		
	}

	void OrthographicCameraController::OnUpdate(TimeStep ts)
	{

		if (Input::IsKeyPressed(FOX_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(FOX_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(FOX_KEY_UP))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(FOX_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}
		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;

		if (m_Rotation){
			if (Input::IsKeyPressed(FOX_KEY_E))
			{
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}

			if (FoxEngine::Input::IsKeyPressed(FOX_KEY_Q))
			{
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}
			m_Camera.SetRotation(m_CameraRotation);
		}
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventCaster eventCaster(e);
		eventCaster.Cast<MouseScrolledEvent>(FOX_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
		eventCaster.Cast<WindowResizedEvent>(FOX_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::CalculateView()
	{
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetOffsetY() * m_ZoomSpeed;
		m_ZoomLevel = std::clamp(m_ZoomLevel, m_ZoomLevelMin, m_ZoomLevelMax);
		CalculateView();
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizedEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		CalculateView();
		return false;
	}
}
