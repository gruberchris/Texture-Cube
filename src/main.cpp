#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include "Camera.hpp"

void processUserInput(GLFWwindow *window, Camera *camera) {
    float cameraSpeed = 0.05f;

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera->rotateAroundYAxis(cameraSpeed);
    else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera->rotateAroundYAxis(-cameraSpeed);
    else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera->rotateAroundXAxis(cameraSpeed);
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera->rotateAroundXAxis(-cameraSpeed);
    else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera->zoomIn(1.0f);
    else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera->zoomOut(1.0f);
    else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->moveForward(cameraSpeed);
    else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->moveBackward(cameraSpeed);
}

struct WindowData {
    Camera* camera{};
    bool wireframeMode = false;
};

void key_callback(GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods) {
    auto *windowData = static_cast<WindowData *>(glfwGetWindowUserPointer(window));
    auto camera = windowData->camera;

    if (key == GLFW_KEY_HOME && action == GLFW_PRESS) {
        camera->reset();
    } else if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
        windowData->wireframeMode = !windowData->wireframeMode;
        if(windowData->wireframeMode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main() {
    // Initialise GLFW
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int WINDOW_WIDTH = 1024;
    const int WINDOW_HEIGHT = 768;

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL MacOS Project Template", nullptr, nullptr);

    if( window == nullptr ) {
        std::cerr << "Failed to open GLFW window. Check your drivers opengl support." << std::endl;
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        getchar();
        glfwTerminate();
        return -1;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Set background color
    glClearColor(0.0f, 0.0f, 0.6f, 0.0f);

    Shader shader("shaders/vertex/default.glsl", "shaders/fragment/default.glsl");

    Camera camera;
    bool wireframeMode = false;

    glfwSetWindowUserPointer(window, new WindowData{&camera, wireframeMode});

    // Check if the ESC key was pressed or the window was closed
    while(!glfwWindowShouldClose(window)) {
        processUserInput(window, &camera);
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );

        // Use our shader
        shader.use();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Close OpenGL window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
