#include "exercise.h"
#include "common.h"
#include "shader.h"
#include <glm/glm.hpp>

namespace {
struct TextureScene {
    unsigned int VAO, VBO, EBO;
    Shader shader;
    unsigned int texture;
};

TextureScene scene_3(){
    float vertices[] = {
        //position           //color            //texture coords
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Shader shader("assets/shaders/vert_src2.vert", "assets/shaders/frag_src2.frag");
    unsigned int texture = loadTexture("assets/textures/container.jpg");
    return {VAO, VBO, EBO, shader, texture};
}
}

void exercise3() {
    GLFWwindow* window = createWindow(800, 600, "Exercise 3");
    if(!window) return;

    TextureScene scene = scene_3();

    while(!glfwWindowShouldClose(window)){
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        scene.shader.use();
        scene.shader.setMat4("transform", glm::mat4(1.0f));
        glBindTexture(GL_TEXTURE_2D, scene.texture);
        glBindVertexArray(scene.VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene.EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &scene.VAO);
    glDeleteBuffers(1, &scene.VBO);
    glDeleteBuffers(1, &scene.EBO);
    glDeleteTextures(1, &scene.texture);
    glfwTerminate();
}
