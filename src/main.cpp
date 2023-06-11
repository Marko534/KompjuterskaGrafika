#define _USE_MATH_DEFINES

#include <OpenGLPrj.hpp>

#include <GLFW/glfw3.h>

#include <Shader.hpp>

#include <iostream>
#include <string>
#include <vector>

const std::string program_name = ("Transformation basics");

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
    glfwWindowHint(
        GLFW_OPENGL_FORWARD_COMPAT,
        GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                          program_name.c_str(), nullptr, nullptr);
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

    std::string shader_location("../res/shaders/");

    std::string used_shaders("shader");

    Shader ourShader(shader_location + used_shaders + std::string(".vert"),
                     shader_location + used_shaders + std::string(".frag"));

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    std::vector<float> vertices;
    //RECTANGLE first bit
    vertices.push_back(-0.55); vertices.push_back(0.5); vertices.push_back(0.0);
    vertices.push_back(-0.8); vertices.push_back(0.5); vertices.push_back(0.0);
    vertices.push_back(-0.8); vertices.push_back(-0.5); vertices.push_back(0.0);
    vertices.push_back(-0.55); vertices.push_back(-0.5); vertices.push_back(0.0);

    vertices.push_back(-0.55); vertices.push_back(-0.5); vertices.push_back(0.3);
    vertices.push_back(-0.55); vertices.push_back(0.5); vertices.push_back(0.3);
    vertices.push_back(-0.8); vertices.push_back(0.5); vertices.push_back(0.3);
    vertices.push_back(-0.8); vertices.push_back(0.5); vertices.push_back(0.0);

    //RECTANGLE second bit
    vertices.push_back(-0.8); vertices.push_back(-0.5); vertices.push_back(0.3);
    vertices.push_back(-0.8); vertices.push_back(-0.5); vertices.push_back(0.0);
    vertices.push_back(-0.8); vertices.push_back(0.5); vertices.push_back(0.0);
    vertices.push_back(-0.8); vertices.push_back(0.5); vertices.push_back(0.3);

    vertices.push_back(-0.55); vertices.push_back(0.5); vertices.push_back(0.3);
    vertices.push_back(-0.55); vertices.push_back(-0.5); vertices.push_back(0.3);
    vertices.push_back(-0.55); vertices.push_back(-0.5); vertices.push_back(0.0);
    vertices.push_back(-0.8); vertices.push_back(-0.5); vertices.push_back(0.0);

    int numberOfVertices = 1000;
    float radiusSmall = 0.40;
    float radiusBig = 0.61;
    float angle = 0;
    float angle_ofset = 2.0* M_PI / numberOfVertices;

    for (int i = 0; i <= numberOfVertices ; i++) {
    //7
        vertices.push_back(cos(angle) * radiusSmall+0.8-radiusBig);
        vertices.push_back(sin(angle) * radiusSmall);
        vertices.push_back(0.3);
    //6
        vertices.push_back(cos(angle+angle_ofset) * radiusSmall+0.8-radiusBig);
        vertices.push_back(sin(angle+angle_ofset) * radiusSmall);
        vertices.push_back(0.3);
    //5
        vertices.push_back(cos(angle) * radiusBig +0.8-radiusBig);
        vertices.push_back(sin(angle) * radiusBig);
        vertices.push_back(0.3);

    //4
        vertices.push_back(cos(angle+angle_ofset) * radiusBig+0.8-radiusBig);
        vertices.push_back(sin(angle+angle_ofset) * radiusBig);
        vertices.push_back(0.3);

    //3
        vertices.push_back(cos(angle) * radiusBig +0.8-radiusBig);
        vertices.push_back(sin(angle) * radiusBig);
        vertices.push_back(0.0);

    //2
        vertices.push_back(cos(angle+angle_ofset) * radiusBig+0.8-radiusBig);
        vertices.push_back(sin(angle+angle_ofset) * radiusBig);
        vertices.push_back(0.0);
    //1
        vertices.push_back(cos(angle) * radiusSmall+0.8-radiusBig);
        vertices.push_back(sin(angle) * radiusSmall);
        vertices.push_back(0.0);
    //0
        vertices.push_back(cos(angle+angle_ofset) * radiusSmall+0.8-radiusBig);
        vertices.push_back(sin(angle+angle_ofset) * radiusSmall);
        vertices.push_back(0.0);

    //-1
        vertices.push_back(cos(angle) * radiusSmall+0.8-radiusBig);
        vertices.push_back(sin(angle) * radiusSmall);
        vertices.push_back(0.3);
        //-2
        vertices.push_back(cos(angle+angle_ofset) * radiusSmall+0.8-radiusBig);
        vertices.push_back(sin(angle+angle_ofset) * radiusSmall);
        vertices.push_back(0.3);
        angle += 2.0* M_PI / numberOfVertices;
    }

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // bind the VAO (it was already bound, but just to demonstrate): seeing as we only have a single VAO we can
    // just bind it beforehand before rendering the respective triangle; this is another approach.
    glBindVertexArray(VAO);

    // load and create a texture
    // -------------------------

    glEnable(GL_DEPTH_TEST);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        ourShader.use();

        // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = model =
                glm::rotate(model, (float) glfwGetTime() * glm::radians(22.5f),
                            glm::vec3(0.0f, 1.0f, 0.0f));
//        model = model =
//                glm::rotate(model, glm::radians(22.5f),
//                            glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection =
                glm::perspective(glm::radians(45.0f),
                                 (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the
        // projection matrix rarely changes it's often best practice to set it
        // outside the main loop only once.
        ourShader.setMat4("projection", projection);
        // render container
        glBindVertexArray(VAO);
        ourShader.passColor3("COLOR", new float[] {0.192,0.192,0.514});
        glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
        glDrawArrays(GL_TRIANGLE_FAN, 8, 8);

        ourShader.passColor3("COLOR", new float[] {0.165, 0.576, 0.82});
//        glDrawArrays(GL_TRIANGLE_STRIP, 16, 10);
//
//        float col_int = 1.0/numberOfVertices;
//        float col = 0;
        for (int i =0; i < numberOfVertices;i++) {
//            ourShader.passColor3("COLOR", new float[] {0.0, 1.0, col});
//            col+=col_int;
            glDrawArrays(GL_TRIANGLE_STRIP, 16+i*10, 10);
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
        // etc.)
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

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
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

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
