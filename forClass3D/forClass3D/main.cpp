#include <Windows.h>
#include <iostream>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "inputManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Displayable_object.h"
#include "roboHand.h"
#include <stb_image.h>
#include "texture.h"

using namespace glm;

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;
static const glm::vec3 BLUE = glm::vec3(0, 0, 1);
static const glm::vec3 RED = glm::vec3(1, 0, 0);
static const glm::vec3 GREEN = glm::vec3(0, 1, 0);
static const glm::vec3 YELLOW = glm::vec3(1, 1, 0);
static const glm::vec3 TEAL = glm::vec3(0, 1, 1);
static const glm::vec3 PURPLE = glm::vec3(1, 0, 1);
Displayable_object camera;
roboHand main_hand;

int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

	Vertex box_vertices[] =
	{	//position, coordinates texture, normal, color
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),BLUE),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),BLUE),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),BLUE),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),BLUE),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),RED),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1),RED),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1),RED),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1),RED),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0),GREEN),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0),GREEN),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0),GREEN),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0),GREEN),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0),YELLOW),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0),YELLOW),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0),YELLOW),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0),YELLOW),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0),TEAL),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0),TEAL),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0),TEAL),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0),TEAL),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),PURPLE),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0),PURPLE),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0),PURPLE),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0),PURPLE)
	};
	
	unsigned int indices[] = {0, 1, 2,
							  0, 2, 3,

							  6, 5, 4,
							  7, 6, 4,

							  10, 9, 8,
							  11, 10, 8,

							  12, 13, 14,
							  12, 14, 15,

							  16, 17, 18,
							  16, 18, 19,

							  22, 21, 20,
							  23, 22, 20
	                          };

	Mesh box_mesh(box_vertices, sizeof(box_vertices) / sizeof(box_vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Shader shader("./res/shaders/basicShader");
	Shader pickingShader("./res/shaders/pickingShader");
	Texture small_cube_tex("res/textures/box0.bmp");
	Texture robo_arm_tex("res/textures/grass.bmp");
	vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
	vec3 up = glm::vec3(0.0f, 1.0f, 1.0f);
	vec3 pos = vec3(0, 0, -32.0);
	mat4 M;
	mat4 perspec = glm::perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	perspec = perspec * glm::lookAt(pos, pos + forward, up);
	glfwSetKeyCallback(display.m_window,key_callback);
	glfwSetMouseButtonCallback(display.m_window, mouse_callback);
	glfwSetScrollCallback(display.m_window, scroll_callback);
	glfwSetCursorPosCallback(display.m_window, pos_callback);
	camera.rotate_object(-90.0f, vec3(1.0, 0, 0));
	Displayable_object small_cube;
	small_cube.move_object(vec3(6.0, 0, 0));
	mat4 MVP;
	vec3 indexes;
	int counter = 0;

	while(!glfwWindowShouldClose(display.m_window))
	{
		shader.Bind();
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
		small_cube_tex.Bind(0);
		M = camera.get_rotation() * small_cube.get_result();
		MVP =  perspec * camera.get_translation()* M ;
		shader.Update(MVP, M);
		box_mesh.Draw();
		robo_arm_tex.Bind(0);
		for (int i = 0; i < 4; i++) {
			M = camera.get_rotation() * main_hand.get_link_by_index(i);
			MVP = perspec * camera.get_translation()* M;
			shader.Update(MVP, M);
			main_hand.draw_lines();
			box_mesh.Draw();
		}
		display.SwapBuffers();	
		glfwPollEvents();
	}
	return 0;
}