#include <array>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.hpp"
#include "Camera.hpp"

static GLuint loadCubeObject() {
    // Create a cube object
    std::array<float, 192> vertices = {
            // positions       // colors         // texture coordinates
            // Front face
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

            // Back face
            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

            // Left face
            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

            // Right face
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

            // Top face
            -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

            // Bottom face
            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    std::array<unsigned int, 36> indices = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            4, 5, 6,
            6, 7, 4,
            // back
            8, 9, 10,
            10, 11, 8,
            // left
            12, 13, 14,
            14, 15, 12,
            // bottom
            16, 17, 18,
            18, 19, 16,
            // top
            20, 21, 22,
            22, 23, 20
    };

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind the VAO
    glBindVertexArray(0);

    return VAO;
}

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
    GLFWwindow* window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "Texture Cube", nullptr, nullptr);

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
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    // Enable depth test. This ensures that fragments are rendered based on their depth values, making sure that closer objects obscure farther objects.
    glEnable(GL_DEPTH_TEST);

    Shader shader("shaders/vertex/default.glsl", "shaders/fragment/default.glsl");
    Camera camera;
    bool wireframeMode = false;

    glfwSetWindowUserPointer(window, new WindowData{&camera, wireframeMode});

    // Load a 3D cube object
    GLuint VAO = loadCubeObject();

    int textureWidth;
    int textureHeight;
    int textureColorChannels;

    // OpenGL expects the 0.0 coordinate on the y-axis to be on the bottom-left side of the image,
    // but STB expects it to be on the top-left side of the image, so we need to flip the image vertically.
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load("assets/textures/wall.jpg", &textureWidth, &textureHeight, &textureColorChannels, 0);

    if (!data) {
        std::cerr << "Failed to load texture" << std::endl;
        return -1;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint textureLocation = glGetUniformLocation(shader.getProgramID(), "texture0");
    glUniform1i(textureLocation, 0);

    // Check if the ESC key was pressed or the window was closed
    while(!glfwWindowShouldClose(window)) {
        processUserInput(window, &camera);
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        shader.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Create the model identity matrix
        auto model = glm::mat4(1.0f);

        // Apply transformations to the model matrix to rotate it around the y-axis at a rate of 50 degrees per second
        model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        // Set the view and projection matrices in the shader
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // update the uniform color
        double timeValue = glfwGetTime();
        // Dividing by 2.0f scales the result of the sine function to range between -0.5 and 0.5.
        // Adding 0.5f shifts the range of values to be between 0 and 1.
        float redValue = ((float)sin(timeValue) / 2.0f) + 0.5f;
        float greenValue = ((float)sin(timeValue + 10) / 2.0f) + 0.5f;
        float blueValue = 0;
        int vertexColorLocation = glGetUniformLocation(shader.getProgramID(), "cubeColor");
        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

        glBindVertexArray(VAO); // Bind the VAO
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0); // Unbind the VAO

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete the texture
    glDeleteTextures(1, &texture);

    // Close OpenGL window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
