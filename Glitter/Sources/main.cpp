// Local Headers
#include "glitter.hpp"
#include "shader_s.h"

// System Headers
#include <GL/gl.h>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "LearnOpenGPL", nullptr, nullptr);

    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    Shader ourShader("../Glitter/Shaders/shader.vs", "../Glitter/Shaders/shader.fs");

    // Set vertex data and buffers
    // Set z to 0 so appears as 2d
    float vertices[] = {
        // positions        // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top 
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the array buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Wireframe mode (Default is GL_FILL not GL_LINE)
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

    // Each iteration of this loop is a frame
    while (!glfwWindowShouldClose(mWindow)) {
        // input
        processInput(mWindow);

        // rendering commands here
        // Background fill color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
       
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // check and call events and swap buffers 
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
   
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

