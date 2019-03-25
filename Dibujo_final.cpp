/*---------------------------------------------------------*/
/* ----------------   Dibujo --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Luis Sergio Valencia Castro ---------------*/
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

void myData(void);
void display(void);
void getResolution(void);

//For Keyboard
float	movX = 0.0f,
		movY = 0.0f,
		movZ = -1.0f,
		rotY = 0.0f;

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{	
		GLfloat vertices[] = {
		//Position				//Color

1.998f,5.532f,-0.2f,    //V1
2.025f,5.466f,-0.2f,    //V2
2.064f,5.4f,-0.2f,    //V3
2.085f,5.328f,-0.2f,    //V4
2.13f,5.262f,-0.2f,    //V5
2.16f,5.196f,-0.2f,    //V6
2.196f,5.13f,-0.2f,    //V7
2.262f,5.064f,-0.2f,    //V8
2.328f,4.998f,-0.2f,    //V9
2.4f,4.932f,-0.2f,    //V10
2.466f,4.866f,-0.2f,    //V11
2.532f,4.8f,-0.2f,    //V12
2.598f,4.728f,-0.2f,    //V13
2.664f,4.662f,-0.2f,    //V14
2.73f,4.596f,-0.2f,    //V15
2.796f,4.56f,-0.2f,    //V16
2.862f,4.53f,-0.2f,    //V17
2.928f,4.464f,-0.2f,    //V18
3.0f,4.44f,-0.2f,    //V19
3.066f,4.398f,-0.2f,    //V20
3.132f,4.35f,-0.2f,    //V21
3.198f,4.332f,-0.2f,    //V22
3.264f,4.32f,-0.2f,    //V23
3.33f,4.308f,-0.2f,    //V24
3.396f,4.266f,-0.2f,    //V25
3.462f,4.266f,-0.2f,    //V26
3.528f,4.26f,-0.2f,    //V27
3.6f,4.23f,-0.2f,    //V28
3.666f,4.23f,-0.2f,    //V29
3.732f,4.2f,-0.2f,    //V30

3.732f,4.2f,-0.2f,
3.732f,1.8f,-0.2f,
2.262f,1.8f,-0.2f,
2.262f,5.064f,-0.2f,

3.732f,4.2f,-0.2f,
3.732f,1.53f,-0.2f,
5.598f,1.53f,-0.2f,
5.598f,5.532f,-0.2f,
1.998f,5.532f,-0.2f,

2.262f,5.064f,-0.2f,
3.732f,4.2f,-0.2f

	};



	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	projectionShader.use();

	// create transformations and Projection
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	
	//Use "projection" in order to change how we see the information
	projection = glm::ortho(0.0f, 15.0f, -13.0f, 13.0f, 0.1f, 10.0f);

	//Use "view" in order to affect all models
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view,glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	// pass them to the shaders
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);
	glLineWidth(5.0f);



		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.7f));
		//glDrawArrays(GL_POLYGON, 0, 10); //Bota Izquierda
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawArrays(GL_LINE_STRIP, 0, 30); //curva pantalon

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.6f, 0.9f));
		glDrawArrays(GL_POLYGON, 30, 4); //pierna izquierda
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawArrays(GL_LINE_STRIP, 30, 4); //pierna izquierda

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.6f, 0.9f));
		glDrawArrays(GL_POLYGON, 34, 5); //pierna derecha

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.6f, 0.9f));
		glDrawArrays(GL_POLYGON, 38, 3); //curva pantalon fill

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		glDrawArrays(GL_LINE_STRIP, 34,4); //pierna derecha

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.8f, 0.9f));
		//glDrawArrays(GL_POLYGON, 24, 4); //Antes de bota Izquierda
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		//glDrawArrays(GL_POLYGON, 24, 4); //Antes de bota Izquierda

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.7f));
		//glDrawArrays(GL_POLYGON, 28, 5); //Antes de bota Izquierda
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		//glDrawArrays(GL_POLYGON, 28, 5); //Antes de bota Izquierda

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.8f, 0.9f));
		//glDrawArrays(GL_POLYGON, 33, 7); //Pecho parte 1

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.8f, 0.9f));
		//glDrawArrays(GL_POLYGON, 40, 6); //Pecho parte 2

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.8f, 0.9f));
		//glDrawArrays(GL_POLYGON, 46, 5); //Pecho parte 2

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		//glDrawArrays(GL_POLYGON, 51, 13); //Pecho DELINEADO

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.7f));
		//glDrawArrays(GL_POLYGON, 64, 10); //Guante Izq
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		//glDrawArrays(GL_POLYGON, 64, 10); //Guante Izq DELINEADO
		//

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.7f));
		//glDrawArrays(GL_POLYGON, 74, 10); //Guante Der
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		//glDrawArrays(GL_POLYGON, 74, 10); //Guante Der DELINEADO

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.7f));
		//glDrawArrays(GL_POLYGON, 88, 4); //Casco

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.7f));
		//glDrawArrays(GL_POLYGON, 92, 9); //Casco 2

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.8f, 0.9f));
		//glDrawArrays(GL_POLYGON, 101, 4); //Casco 3
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		//glDrawArrays(GL_LINE_LOOP, 105, 16); //Casco delineado

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.9f, 0.8f));
		//glDrawArrays(GL_POLYGON, 121, 5); //Interno Casco
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		//glDrawArrays(GL_LINE_LOOP, 121, 5); //Interno Casco delineado

		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.7f));
		//glDrawArrays(GL_POLYGON, 131, 4); //Frente
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.9f, 0.8f));
		//glDrawArrays(GL_POLYGON, 126, 5); //Frente
		//

		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		//glDrawArrays(GL_LINE_STRIP, 131, 4); //Frente


		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		//glDrawArrays(GL_POLYGON, 146, 4); //Ojo
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		//glDrawArrays(GL_POLYGON, 150, 4); //Ojo
		//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
		//glDrawArrays(GL_POLYGON, 154, 4); //Boca
		//projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.9f, 0.5f));
		//glDrawArrays(GL_POLYGON, 139, 7); //Cara

		
		
		
		

	glBindVertexArray(0);

}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Dibujo", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	glEnable(GL_DEPTH_TEST);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

        // render
        // Backgound color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}