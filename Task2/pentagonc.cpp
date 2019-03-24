#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//Vertex shader source
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec4 aCol;\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "	color = aCol;\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

//fragment shader source
const char *fragmentShaderSource = "#version 330 core\n"
    "layout(location = 0) out vec4 FragColor;\n"
    "in vec4 color;\n"
    "void main()\n"
    "{\n"
    "   FragColor = color;\n"
    "}\0";

int main()
{
	//Configuration
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//Make a window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Pentagon Color", NULL, NULL);
	if (window == NULL)
	{
	    std::cout << "Failed to create GLFW window" << std::endl;
	    glfwTerminate();
	    return -1;
	}
	glfwMakeContextCurrent(window);

	//Init glew
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
	    fprintf(stderr, "Failed to initialize GLEW\n");
	    getchar();
	    glfwTerminate();
	    return -1;
	}

	//Rendering size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Declare vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//compile vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Declare fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//compile fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Declare shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	//Link vertex and fragment shader
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Delete vertex and fragment shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);  

	//Vertices
	float vertices[] = {
		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.35f, 0.15f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.25f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	
		-0.25f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f,
		-0.35f, 0.15f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.25f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.25f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f
	};

	//Declare VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);   

	//Declare VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	//Bind VAO and VBO to buffer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Copy vertices to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Configure buffer reading
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);

	//Main loop
	while(!glfwWindowShouldClose(window))
	{
		//Check input
		processInput(window);

		//Clear Screen
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 9);

		//Check and call events and swap buffers
	    glfwSwapBuffers(window);
	    glfwPollEvents();    
	}

	//Dealocate
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    //Terminate
	glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}