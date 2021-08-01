#include "fepch.h"
#include "FoxEngine/Renderer/OrthographicCameraController.h"

#include "FoxEngine/Core/Input.h"
#include "FoxEngine/Core/KeyCodes.h"
#include "FoxEngine/Core/MouseButtonCodes.h"
#include "FoxEngine/Core/TimeStep.h"

namespace FoxEngine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
		
	}

	void OrthographicCameraController::OnUpdate(TimeStep ts)
	{

		/*if (Input::IsKeyPressed(FOX_KEY_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(FOX_KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(FOX_KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(FOX_KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(FOX_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(FOX_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}*/

		if(Input::IsMouseButtonPressed(FOX_MOUSE_BUTTON_MIDDLE))
		{
			if(m_LastMousePosition.first != -1 && m_LastMousePosition.second != -1)
			{
				std::pair<float, float> newPos = Input::GetMousePosition();

				float xDiff = (newPos.first - m_LastMousePosition.first) / 100.0;
				float yDiff = (newPos.second - m_LastMousePosition.second) / 100.0;
				
				m_CameraPosition.x -= xDiff;
				m_CameraPosition.y += yDiff;
			}
			m_MouseState = MouseState::MOVING_CAMERA;
			m_LastMousePosition = Input::GetMousePosition();
		} else if(m_LastMousePosition.first != -1 && m_LastMousePosition.second != -1)
		{
			m_LastMousePosition.first = -1;
			m_LastMousePosition.first = -1;
			m_MouseState = MouseState::IDLE;
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventCaster eventCaster(e);
		eventCaster.Cast<MouseScrolledEvent>(FOX_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
		eventCaster.Cast<WindowResizedEvent>(FOX_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	void OrthographicCameraController::CalculateView()
	{
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{

		m_ZoomLevel -= e.GetOffsetY() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizedEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
}
