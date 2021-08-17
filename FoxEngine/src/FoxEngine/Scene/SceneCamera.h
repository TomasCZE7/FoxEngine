#pragma once
#include "FoxEngine/Renderer/Camera.h"

namespace FoxEngine{
    class SceneCamera : public Camera {
    private:
        float orthographicSize = 10.0f;
        float orthographicNear = -1.0f;
        float orthographicFar = 1.0f;
        float aspectRatio = 0.0f;

        void recalculateProjection();

        float getOrthographicSize() const { return orthographicSize; }
        void setOrthographicSize(float size){ orthographicSize = size; recalculateProjection(); }
    public:
        SceneCamera();
        virtual ~SceneCamera();

        void setOrthographic(float size, float nearClip, float farClip);
        void setViewportSize(uint32_t width, uint32_t height);

    };

}

