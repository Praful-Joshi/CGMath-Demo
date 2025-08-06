#include <render.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Global static state
static GLFWwindow* window = nullptr;
static GLuint shaderProgram = 0;
static GLuint vao = 0, vbo = 0;

//camera setup
static float yaw = -90.0f;   // left-right
static float pitch = 0.0f;   // up-down
static float radius = 20.0f; // distance from origin
static double lastX = 960.0, lastY = 540.0;
static bool firstMouse = true;
static bool mouseDown = false;


// Shader sources
const char* vertexShaderSrc = R"glsl(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
out vec3 fragColor;
uniform mat4 MVP;
void main() {
    gl_Position = MVP * vec4(aPos, 1.0);
    fragColor = aColor;
}
)glsl";

const char* fragmentShaderSrc = R"glsl(
#version 330 core
in vec3 fragColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(fragColor, 1.0);
}
)glsl";

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        mouseDown = (action == GLFW_PRESS);
        firstMouse = true; // reset on click
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (!mouseDown) return;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        return;
    }

    float sensitivity = 0.2f;
    float dx = xpos - lastX;
    float dy = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    yaw += dx * sensitivity;
    pitch += dy * sensitivity;

    // clamp pitch
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}


GLuint compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::cerr << "Shader Compile Error:\n" << info << "\n";
    }
    return shader;
}

void ensureOpenGLInitialized(const char* title) {
    if (window) return; // Already initialized

    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(1920, 1080, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Window creation failed\n";
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW init failed\n";
        exit(1);
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f); 


    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    glDeleteShader(vs);
    glDeleteShader(fs);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

}


void drawLine(const glm::vec3& to, const glm::vec3& color, const glm::mat4& mvp) {
    float vertices[] = {
        0.f, 0.f, 0.f,  color.x, color.y, color.z,
        to.x, to.y, to.z,  color.x, color.y, color.z
    };

    GLuint tmpVBO;
    glGenBuffers(1, &tmpVBO);
    glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_LINES, 0, 2);

    glDeleteBuffers(1, &tmpVBO);
}

void showAndBlockUntilClosed(float* vertices, glm::mat4 mvp) {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertices, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_LINES, 0, 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    window = nullptr; // Reset state so next call can reinit
}

void renderVec2(Vec2* vec2Array, int count)
{
    ensureOpenGLInitialized("2D Vector Scene");

    glm::mat4 proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f);

    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw XYZ axes
        drawLine(glm::vec3(3,0,0), glm::vec3(1,0,0), proj); // X - red
        drawLine(glm::vec3(0,3,0), glm::vec3(0,1,0), proj); // Y - green
        for (int i = 0; i < count; ++i) {
            glm::vec3 to(vec2Array[i].getX(), vec2Array[i].getY(), 0.0f);
            drawLine(to, glm::vec3(1,1,0), proj);

            glm::vec4 clipPos = proj * glm::vec4(to, 1.0f);
            float screenX = (clipPos.x * 0.5f + 0.5f) * 800;
            float screenY = (1.0f - (clipPos.y * 0.5f + 0.5f)) * 600;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    window = nullptr;
}

void renderVec3(Vec3* vec3Array, int count)
{
    ensureOpenGLInitialized("3D Vector Scene");

    glm::vec3 cameraPos = glm::vec3(10.0f, 10.0f, 10.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float yawRad = glm::radians(yaw);
        float pitchRad = glm::radians(pitch);

        cameraPos.x = radius * cos(pitchRad) * cos(yawRad);
        cameraPos.y = radius * sin(pitchRad);
        cameraPos.z = radius * cos(pitchRad) * sin(yawRad);

        glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, glm::vec3(0,1,0));
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.f/3.f, 0.1f, 100.f);
        glm::mat4 mvp = proj * view;

        // Draw XYZ axes
        drawLine(glm::vec3(1000,0,0), glm::vec3(1,0,0), mvp); // X - red
        drawLine(glm::vec3(0,1000,0), glm::vec3(0,1,0), mvp); // Y - green
        drawLine(glm::vec3(0,0,1000), glm::vec3(0,0,1), mvp); // Z - blue

        // Draw vectors (yellow)
        for (int i = 0; i < count; i++) {

            glm::vec3 to(vec3Array[i].getX(), vec3Array[i].getY(), vec3Array[i].getZ());
            drawLine(to, glm::vec3(1,1,0), mvp);

            // Project 3D to 2D screen space
            glm::vec4 clipPos = mvp * glm::vec4(to, 1.0);
            clipPos /= clipPos.w;
            float screenX = (clipPos.x * 0.5f + 0.5f) * 800; // assuming 800x600
            float screenY = (1.0f - (clipPos.y * 0.5f + 0.5f)) * 600;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    window = nullptr;
}



