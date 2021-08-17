#include "SceneCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace FoxEngine{

    SceneCamera::SceneCamera() {
        recalculateProjection();
    }

    SceneCamera::~SceneCamera() {

    }

    void SceneCamera::setOrthographic(float size, float nearClip, float farClip) {
        orthographicSize = size;
        orthographicNear = nearClip;
        orthographicFar = farClip;
    }

    void SceneCamera::setViewportSize(uint32_t width, uint32_t height) {
        aspectRatio = (float) width / (float) height;
        recalculateProjection();
    }

    void SceneCamera::recalculateProjection() {
        float orthoLeft = -orthographicSize * aspectRatio * 0.5f;
        float orthoRight = orthographicSize * aspectRatio * 0.5f;
        float orthoBottom = -orthographicSize * 0.5f;
        float orthoTop = orthographicSize * 0.5f;

        projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthographicNear, orthographicFar);
    }

}