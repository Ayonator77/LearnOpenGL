#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Returns a window with a current OpenGL 3.3 core context and GLAD loaded.
// Returns nullptr on failure (GLFW is terminated before returning).
GLFWwindow* createWindow(int width, int height, const char* title);

// Compiles vertSrc + fragSrc and links them into a shader program.
// Prints errors to stdout. Caller owns the returned program ID.
unsigned int createShaderProgram(const char* vertSrc, const char* fragSrc);

// Loads an image file into an OpenGL 2D texture. Caller owns the returned texture ID.
unsigned int loadTexture(const char* path);

void processInput(GLFWwindow* window);
