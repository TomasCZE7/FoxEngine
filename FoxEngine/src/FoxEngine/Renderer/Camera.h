#pragma once
#include <glm/glm.hpp>

namespace FoxEngine{

    class Camera {
    protected:
        glm::mat4 projection = glm::mat4(1.0f);
    public:
        Camera() = default;
        Camera(const glm::mat4& projection)
        : projection(projection) {}

        virtual ~Camera() = default;

        const glm::mat4& getProjection() const {
            return projection;
        }
    };

}