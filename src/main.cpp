#define _USE_MATH_DEFINES

#include <OpenGLPrj.hpp>

#include <GLFW/glfw3.h>

#include <Shader.hpp>

#include <iostream>
#include <cstring>
#include <vector>


const std::string program_name = ("GLSL Shader class example");

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, program_name.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("../res/shaders/shader.vert",
                     "../res/shaders/shader.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    std::vector<float> vertices;
    int numberOfRectangles = 10;
    float halfSize = 1.0/numberOfRectangles;
    float currentX = 1.0;
    float currentY = 3*halfSize;

    for(int i = 0 ; i<3;i++) {
        for (int j = 0; j <= numberOfRectangles; j++) {
            vertices.push_back(currentX);
            vertices.push_back(currentY);
            vertices.push_back(0.0);

            vertices.push_back(currentX);
            vertices.push_back(currentY+2*halfSize);
            vertices.push_back(0.0);
            currentX -= 2 * halfSize;
        }
        currentX = 1.0;
        currentY -=4*halfSize;
    }

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // bind the VAO (it was already bound, but just to demonstrate): seeing as we only have a single VAO we can
    // just bind it beforehand before rendering the respective triangle; this is another approach.
    glBindVertexArray(VAO);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {

        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ourShader.use();

        // Setting the colors for the RED part
        ourShader.setFloat("RED", 1.0f);
        ourShader.setFloat("GREEN", 0.0f);
        ourShader.setFloat("BLUE", 0.0f);
        float red = 1.0;
        glBindVertexArray(VAO);
        for (int i = 0; i<numberOfRectangles;i++){
            glDrawArrays(GL_TRIANGLE_STRIP, 2*i, 4);
            red-=1.0/numberOfRectangles;
            ourShader.setFloat("RED", red);
        }

        // Setting the colors for the GREEN part
        ourShader.setFloat("RED", 0.0f);
        ourShader.setFloat("GREEN", 1.0f);
        ourShader.setFloat("BLUE", 0.0f);
        float green = 1.0;
        glBindVertexArray(VAO);
        for (int i = numberOfRectangles+1; i<2*numberOfRectangles+1;i++){
            glDrawArrays(GL_TRIANGLE_STRIP, 2*i, 4);
            green-=1.0/numberOfRectangles;
            ourShader.setFloat("GREEN", green);
        }

        // Setting the colors for the BLUE part
        ourShader.setFloat("RED", 0.0f);
        ourShader.setFloat("GREEN", 0.0f);
        ourShader.setFloat("BLUE", 1.0f);
        float blue = 1.0;
        glBindVertexArray(VAO);
        for (int i = 2*numberOfRectangles+2; i<3*numberOfRectangles+2;i++){
            glDrawArrays(GL_TRIANGLE_STRIP, 2*i, 4);
            blue-=1.0/numberOfRectangles;
            ourShader.setFloat("BLUE", blue);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

