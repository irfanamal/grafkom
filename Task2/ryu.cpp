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

	//Dark 0.0f, 0.545f, 0.545f, 1.0f,
	//Light 0.0f, 1.0f, 1.0f, 1.0f,

	//Vertices
	float vertices[] = {
		//1
		-0.867f, -0.267f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		-0.7f, -0.378f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		-0.533f, -0.311f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		//2
		-0.7f, -0.378, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.117f, -0.467f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, -0.067f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		//3
		-0.117f, -0.467f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		0.0f, -0.644f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		0.0f, -0.067, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		//4
		0.0f, -0.489f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		0.083f, -0.578f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		0.083f, -0.489, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		//5
		0.0f, -0.489f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.183f, -0.489f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, -0.067, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		//6
		0.0f, -0.067f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		0.183f, -0.489f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		0.333f, 0.133f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		//7
		0.183f, -0.489f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.433f, -0.067f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.3f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		//8
		0.183f, -0.489f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		0.367f, -0.489f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		0.433f, -0.067f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		//9
		0.367f, -0.489f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.417f, -0.644f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.433f, -0.067f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		//10
		0.417f, -0.533f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		0.6f, -0.178f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		0.433f, 0.311f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		//11
		0.533f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.433f, 0.311f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.422f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		//12
		0.5f, 0.333f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		0.617f, 0.422f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		0.5f, 0.422f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		//13
		0.5f, 0.333f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.583f, 0.333f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.617f, 0.422f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		//14
		0.5f, 0.422f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.555f, 0.422f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.3f, 0.6f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		//15
		0.0f, -0.067f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.333f, 0.133f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.45f, 0.578f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		//16
		0.333f, 0.133f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		-0.083f, 0.667f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
		-0.45f, 0.578f, 0.0f, 0.0f, 0.545f, 0.545f, 1.0f,
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
		glDrawArrays(GL_TRIANGLES, 0, 48);

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