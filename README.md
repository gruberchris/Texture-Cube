# OpenGL macOS Project Template

This is a template project for macOS that uses OpenGL. It is a simple project that renders a triangle to the screen. The project uses CMake to build the project and uses the GLFW library to create an OpenGL context.

## Building the Project

To build the project, you will need to have CMake installed. You can download CMake from the [official website](https://cmake.org/download/).

Once you have CMake installed, you can build the project by running the following commands in the terminal:

```shell
mkdir build
cd build
cmake ..
make
```

This will generate an Xcode project in the `build` directory that you can open and run.

## Dependencies

The project uses the following dependencies:

- [GLFW](https://www.glfw.org/download.html)
- [GLAD](https://glad.dav1d.de)
- [GLM](https://github.com/g-truc/glm)