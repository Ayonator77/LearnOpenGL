#include "exercise2.h"
#include "common.h"
#include "shader.h"


SceneData scene_1(){
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader shader("assets/shaders/vert_src.vert", "assets/shaders/frag_src.frag");
    return {VAO, VBO, shader};
}


SceneData scene_2(){
    float vertices[] = {
        //position         //color
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //bind the vertex array object first, then bind and set vertex buffers, and then configure vertex attributes
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader shader("assets/shaders/vert_src.vert", "assets/shaders/frag_src.frag");
    return {VAO, VBO, shader};
}

void exercise2() {
    GLFWwindow* window = createWindow(800, 600, "Exercise 2");
    if(!window) return;

    SceneData scene = scene_2();
    //scene.shader.use();

    while(!glfwWindowShouldClose(window)){
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // double timeValue = glfwGetTime();
        // double greenValue = (sin(timeValue) / 2.0) + 0.5;
        // glGetUniformLocation(scene.shader.ID, "vertexColor");
        // scene.shader.setVec4("vertexColor", 0.0f, (float)greenValue, 0.0f, 1.0f);
        //glUniform4f(vertexColorLocation, 0.0f, (float)greenValue, 0.0f, 1.0f);

        scene.shader.use();
        scene.shader.setVec4("transVec", -0.5f, 0.0f, 0.0f, 0.0f);



        glBindVertexArray(scene.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &scene.VAO);
    glDeleteBuffers(1, &scene.VBO);
    glfwTerminate();
}