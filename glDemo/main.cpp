
#include "core.h"


// global variables

// Window size
const unsigned int initWidth = 512;
const unsigned int initHeight = 512;

// Example variables to change when doing keyboard input

// the position of our object
float x = 0.0f;
float y = 0.0f;

// amount we change x, y when keys are pressed
const float movementSpeed = 0.005f;

// flags to track when a movement key is pressed
bool wPressed = false;
bool sPressed = false;
bool aPressed = false;
bool dPressed = false;


// Function prototypes
void renderScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateScene();


int main() {

	//
	// 1. Initialisation
	//
	

	// Initialise glfw and setup window
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "Real-Time Computer Graphics", NULL, NULL);

	// Check window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	

	// Set callback functions to handle different events
	glfwSetFramebufferSizeCallback(window, resizeWindow); // resize window callback
	glfwSetKeyCallback(window, keyboardHandler); // Keyboard input callback


	// Initialise glew
	glewInit();

	
	// Setup window's initial size
	resizeWindow(window, initWidth, initHeight);

	// Initialise scene - geometry and shaders etc
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // setup background colour to be black

	// *** setup viewplane to the appropriate size
	gluOrtho2D(-8.0f, 8.0f, -8.0f, 8.0f);

	//
	// 2. Main loop
	// 
	

	// Loop while program is not terminated.
	while (!glfwWindowShouldClose(window)) {

		updateScene();
		renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		// Poll events (key presses, mouse events)
		// glfwWaitEvents();				// Use this if no animation.
		// glfwWaitEventsTimeout(1.0/60.0);	// Use this to animate at 60 frames/sec (timing is NOT reliable)
		glfwPollEvents();					// Use this version when animating as fast as possible
	}

	glfwTerminate();
	return 0;
}



// renderScene - function to render the current scene
void renderScene()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render objects here...

	// *** triangle of the original size
	/*glBegin(GL_TRIANGLES);

	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, -0.5f);

	glEnd();*/

	// *** square from 2 triangles
	/*glBegin(GL_TRIANGLES);

	glVertex2f(-0.5f, -0.5f);
	glVertex2f(-0.5f, 0.5f);
	glVertex2f(0.5f, 0.5f);

	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(-0.5f, -0.5f);
	
	glEnd();*/


	// *** an extra - adding a moveable triangle
	// Note: This is using an offset (x, y) to represent where the object is in the scene.
	// There are 2 fundamental things to address here: 
	// 1) This is a basic example of translation - when we introduce transformations, we'll look at doing this more effectively with matrices
	// 2) Anything we animate needs to be based on time elapsed.  This code is not (it's only a basic intro :)  We'll look at timing for animation later!
	glBegin(GL_TRIANGLES);

	glVertex2f(x + -0.5f, y + -0.5f);
	glVertex2f(x + 0.0f, y + 0.5f);
	glVertex2f(x + 0.5f, y + -0.5f);

	glEnd();

}


// Function to call when window resized
void resizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}


// Function to call to handle keyboard input
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;

			case GLFW_KEY_W:
				wPressed = true;
				break;

			case GLFW_KEY_S:
				sPressed = true;
				break;

			case GLFW_KEY_A:
				aPressed = true;
				break;

			case GLFW_KEY_D:
				dPressed = true;
				break;

			default:
			{
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		// handle key release events

		// check which key was released...
		switch (key)
		{
			case GLFW_KEY_W:
				wPressed = false;
				break;

			case GLFW_KEY_S:
				sPressed = false;
				break;

			case GLFW_KEY_A:
				aPressed = false;
				break;

			case GLFW_KEY_D:
				dPressed = false;
				break;

			default:
				{
				}
		}
	}
}


// Function called to animate elements in the scene
void updateScene() {

	if (wPressed) {
		y += movementSpeed;
	}

	if (sPressed) {
		y -= movementSpeed;
	}

	if (aPressed) {
		x -= movementSpeed;
	}

	if (dPressed) {
		x += movementSpeed;
	}
}

