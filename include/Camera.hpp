//
// Created by Christopher Gruber on 6/25/24.
//

#ifndef OPENGL_MACOS_PROJECT_TEMPLATE_CAMERA_HPP
#define OPENGL_MACOS_PROJECT_TEMPLATE_CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/fwd.hpp>

class Camera {
public:
    Camera() = default;

    [[nodiscard]] glm::mat4 getViewMatrix() const;
    void moveForward(float delta);
    void moveBackward(float delta);
    void zoomIn(float delta);
    void zoomOut(float delta);
    void reset();
    void rotateAroundYAxis(float angle);
    void rotateAroundXAxis(float angle);
    [[nodiscard]] float getZoom() const;
    [[nodiscard]] const glm::vec3 &getPosition() const;

private:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    float zoom = 45.0f;
};

#endif //OPENGL_MACOS_PROJECT_TEMPLATE_CAMERA_HPP
