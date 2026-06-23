#include "exercise.h"
#include "common.h"
#include <iostream>

static const char* vertSrc =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main(){\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

static const char* fragSrc =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "   FragColor = vec4(0.2f, 0.6f, 0.8f, 1.0f);\n"
    "}\0";


//blue fragment shader
static const char* fragSrc_blue =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "   FragColor = vec4(0.0f, 0.3f, 1.0f, 1.0f);\n"
    "}\0";

void exercise1a(){
    GLFWwindow* window = createWindow(800, 600, "Exercise 1a");
    if (!window) return;

    float vertices[] = {
        //first triangle
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,

        //second triangle
        -0.9f, 0.7f, 0.0f,
        -0.8f, 0.7f, 0.0f,
        -0.85f, 0.6f, 0.0f
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int shader = createShaderProgram(vertSrc, fragSrc);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader);
    glfwTerminate();
}

void exercise1a_1(){
    GLFWwindow* window = createWindow(800, 600, "Exercise 1a part 2");
    if (!window) return;

    float vertices_1[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    float vertices_2[] = {
        -0.9f, 0.7f, 0.0f,
        -0.8f, 0.7f, 0.0f,
        -0.85f, 0.6f, 0.0f
    };

    unsigned int VAO_1, VBO_1, VAO_2, VBO_2;
    glGenVertexArrays(1, &VAO_1);
    glGenBuffers(1, &VBO_1);
    glGenVertexArrays(1, &VAO_2);
    glGenBuffers(1, &VBO_2);

    glBindVertexArray(VAO_1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO_2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int shader = createShaderProgram(vertSrc, fragSrc);
    unsigned int shader2 = createShaderProgram(vertSrc, fragSrc_blue);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;    
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO_1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glUseProgram(shader2);
        glBindVertexArray(VAO_2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO_1);
    glDeleteBuffers(1, &VBO_1);
    glDeleteVertexArrays(1, &VAO_2);
    glDeleteBuffers(1, &VBO_2);
    glDeleteProgram(shader);
    glfwTerminate();
}
