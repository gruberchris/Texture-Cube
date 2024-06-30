//
// Created by Christopher Gruber on 6/26/24.
//

#ifndef OPENGL_MACOS_PROJECT_TEMPLATE_SHADER_HPP
#define OPENGL_MACOS_PROJECT_TEMPLATE_SHADER_HPP

#include <string>
#include <glad/glad.h>
#include <glm/fwd.hpp>

class Shader {
public:
    // Constructor that builds the shader from a vertex and fragment shader file
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    // Use the current shader
    void use() const;

    // Utility functions
    [[nodiscard]] GLuint getProgramID() const;

    [[maybe_unused]] [[nodiscard]] bool isCompiled() const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    GLuint programID;
    GLuint vertexID;
    GLuint fragmentID;

    // Utility function for checking shader compilation/linking errors.
    static void checkCompileErrors(GLuint shader, const std::string& type);
};

#endif //OPENGL_MACOS_PROJECT_TEMPLATE_SHADER_HPP
