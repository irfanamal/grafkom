#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float camX = 0;
float camZ = 10;
float camY = 0;
float angleXZ = 0;
float angleYZ = 0;
glm::vec3 norm = glm::vec3(0.0f, 1.0f, 0.0f);

int main()
{
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("7.1.camera.vs", "7.1.camera.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.500f,  0.250f,  0.1875f,  0.0f, 0.0f,
         0.250f,  0.250f,  0.1875f,  1.0f, 0.0f,
        -0.500f, -0.375f,  0.1875f,  1.0f, 1.0f,
         0.250f,  0.250f,  0.1875f,  1.0f, 1.0f,
        -0.500f, -0.375f,  0.1875f,  0.0f, 1.0f,
         0.375f,  0.000f,  0.1875f,  0.0f, 0.0f,

        -0.500f, -0.375f,  0.1875f,  0.0f, 0.0f,
         0.375f,  0.000f,  0.1875f,  1.0f, 0.0f,
         0.750f, -0.125f,  0.1875f,  1.0f, 1.0f,
        -0.500f, -0.375f,  0.1875f,  1.0f, 1.0f,
         0.750f, -0.125f,  0.1875f,  0.0f, 1.0f,
         0.750f, -0.375f,  0.1875f,  0.0f, 0.0f,

        -0.500f,  0.250f, -0.1875f,  0.0f, 0.0f,
         0.250f,  0.250f, -0.1875f,  1.0f, 0.0f,
        -0.500f, -0.375f, -0.1875f,  1.0f, 1.0f,
         0.250f,  0.250f, -0.1875f,  1.0f, 1.0f,
        -0.500f, -0.375f, -0.1875f,  0.0f, 1.0f,
         0.375f,  0.000f, -0.1875f,  0.0f, 0.0f,

        -0.500f, -0.375f, -0.1875f,  0.0f, 0.0f,
         0.375f,  0.000f, -0.1875f,  1.0f, 0.0f,
         0.750f, -0.125f, -0.1875f,  1.0f, 1.0f,
        -0.500f, -0.375f, -0.1875f,  1.0f, 1.0f,
         0.750f, -0.125f, -0.1875f,  0.0f, 1.0f,
         0.750f, -0.375f, -0.1875f,  0.0f, 0.0f,

        -0.500f,  0.250f,  0.1875f,  0.0f, 1.0f,
         0.250f,  0.250f,  0.1875f,  1.0f, 1.0f,
        -0.500f,  0.250f, -0.1875f,  1.0f, 0.0f,
        -0.500f,  0.250f, -0.1875f,  1.0f, 0.0f,
         0.250f,  0.250f, -0.1875f,  0.0f, 0.0f,
         0.250f,  0.250f,  0.1875f,  0.0f, 1.0f,

         0.250f,  0.250f,  0.1875f,  0.0f, 1.0f,
         0.375f,  0.000f,  0.1875f,  1.0f, 1.0f,
         0.250f,  0.250f, -0.1875f,  1.0f, 0.0f,
         0.250f,  0.250f, -0.1875f,  1.0f, 0.0f,
         0.375f,  0.000f, -0.1875f,  0.0f, 0.0f,
         0.375f,  0.000f,  0.1875f,  0.0f, 1.0f,

         0.375f,  0.000f,  0.1875f,  0.0f, 1.0f,
         0.750f, -0.125f,  0.1875f,  1.0f, 1.0f,
         0.375f,  0.000f, -0.1875f,  1.0f, 0.0f,
         0.375f,  0.000f, -0.1875f,  1.0f, 0.0f,
         0.750f, -0.125f, -0.1875f,  0.0f, 0.0f,
         0.750f, -0.125f,  0.1875f,  0.0f, 1.0f,

        -0.500f, -0.375f,  0.1875f,  0.0f, 1.0f,
         0.750f, -0.375f,  0.1875f,  1.0f, 1.0f,
        -0.500f, -0.375f, -0.1875f,  1.0f, 0.0f,
        -0.500f, -0.375f, -0.1875f,  1.0f, 0.0f,
         0.750f, -0.375f, -0.1875f,  0.0f, 0.0f,
         0.750f, -0.375f,  0.1875f,  0.0f, 1.0f,

         0.750f, -0.125f,  0.1875f,  0.0f, 1.0f,
         0.750f, -0.375f,  0.1875f,  1.0f, 1.0f,
         0.750f, -0.125f, -0.1875f,  1.0f, 0.0f,
         0.750f, -0.125f, -0.1875f,  1.0f, 0.0f,
         0.750f, -0.375f, -0.1875f,  0.0f, 0.0f,
         0.750f, -0.375f,  0.1875f,  0.0f, 1.0f,

        -0.500f,  0.250f,  0.1875f,  0.0f, 1.0f,
        -0.500f, -0.375f,  0.1875f,  1.0f, 1.0f,
        -0.500f,  0.250f, -0.1875f,  1.0f, 0.0f,
        -0.500f,  0.250f, -0.1875f,  1.0f, 0.0f,
        -0.500f, -0.375f, -0.1875f,  0.0f, 0.0f,
        -0.500f, -0.375f,  0.1875f,  0.0f, 1.0f,
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        // glm::vec3( 2.0f,  5.0f, -15.0f),
        // glm::vec3(-1.5f, -2.2f, -2.5f),
        // glm::vec3(-3.8f, -2.0f, -12.3f),
        // glm::vec3 (2.4f, -0.4f, -3.5f),
        // glm::vec3(-1.7f,  3.0f, -7.5f),
        // glm::vec3( 1.3f, -2.0f, -2.5f),
        // glm::vec3( 1.5f,  2.0f, -2.5f),
        // glm::vec3( 1.5f,  0.2f, -1.5f),
        // glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/putih.jpg").c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load(FileSystem::getPath("resources/textures/putih.jpg").c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
    // -----------------------------------------------------------------------------------------------------------
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection); 


    // render loop
    // -----------
    // float camX = 0;
    // float camZ = 10;
    // float camY = 0;
    // float angleXZ = 0;
    // float angleYZ = 0;
    float before = 0;
    // float val = 0.0f;
    // glm::vec3 norm = glm::vec3(0.0f, 1.0f, 0.0f);
    // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    // glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    // glm::vec3 right;

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        ourShader.use();

        // camera/view transformation
        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        float radius = 10.0f;
        before = camZ;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            angleYZ += 0.01;
            camY   = sin(angleYZ) * radius;
            camZ   = cos(angleYZ) * radius;
            if (before >= 0 && camZ < 0) {
                norm *= -1;
            } else if (before < 0 && camZ >= 0) {
                norm = glm::vec3(0.0f, 1.0f, 0.0f);
            }
            view = glm::lookAt(glm::vec3(0.0f, camY, camZ), glm::vec3(0.0f, 0.0f, 0.0f), norm);
        } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            angleYZ -= 0.01;
            camY   = sin(angleYZ) * radius;
            camZ   = cos(angleYZ) * radius;
            if (before >= 0 && camZ < 0) {
                norm *= -1;
            } else if (before < 0 && camZ >= 0) {
                norm = glm::vec3(0.0f, 1.0f, 0.0f);
            }
            view = glm::lookAt(glm::vec3(0.0f, camY, camZ), glm::vec3(0.0f, 0.0f, 0.0f), norm);
        } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            angleXZ += 0.01;
            camX   = sin(angleXZ) * radius;
            camZ   = cos(angleXZ) * radius;
            view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            angleXZ -= 0.01;
            camX   = sin(angleXZ) * radius;
            camZ   = cos(angleXZ) * radius;
            view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        } else {
            view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0f, 0.0f, 0.0f), norm);
        }
        
        // glm::vec3 depan;
        // depan.x = cos(angleXZ) * cos(angleYZ);
        // depan.y = sin(angleYZ);
        // depan.z = sin(angleXZ) * cos(angleYZ);
        // front = glm::normalize(depan);
        // right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
        // up = glm::normalize(glm::cross(right, front));
        // view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0f, 0.0f, 0.0f), norm);
            
        // float camX   = sin(val) * radius;
        // float camZ   = cos(val) * radius;
        
        printf("%f %f %f\n", camX, camY, camZ);
        
        
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        // for (unsigned int i = 0; i < 10; i++)
        // {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[0]);
            float angle = 20.0f * 0;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 60);
        // }

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
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    // glm::vec3 norm = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::mat4(1.0f);
    yoffset *= 0.01;
    angleYZ += yoffset;
    camY   = sin(angleYZ) * 10;
    camZ   = cos(angleYZ) * 10;
    if (camZ < 0) {
        view = glm::lookAt(glm::vec3(0.0f, camY, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    } else if (camZ >= 0) {
        view = glm::lookAt(glm::vec3(0.0f, camY, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    
}
