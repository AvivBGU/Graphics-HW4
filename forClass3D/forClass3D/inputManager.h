#pragma once   //maybe should be static class
#include "GLFW\glfw3.h"
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
#define SOFT 0.2f //Softening the translation.
extern Displayable_object camera;
extern roboHand main_hand;
double x_pos = 0, y_pos = 0;
int curr_button_pressed = -1;
int is_button_pressed = -1;
int x_wall_offset = 0;
int y_wall_offset = 0;
int z_wall_offset = 0;
vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
vec3 up = glm::vec3(0.0f, 1.0f, 1.0f);

inline void scroll_callback(GLFWwindow *window, double x_axis_offset, double y_axis_offset) {
	char* scroll_action_y = y_axis_offset > 0 ? "up scroll" : "down scroll";
	char* scroll_action_x = x_axis_offset > 0 ? "left scroll" : "right scroll";
	scroll_action_y = y_axis_offset == 0 ? "No action" : scroll_action_y;
	scroll_action_x = x_axis_offset == 0 ? "No action" : scroll_action_x;
	std::cout << "Wheel has been activated:" << std::endl;
	std::cout << "X action: " << scroll_action_x <<"     " << "Y action: " << scroll_action_y << std::endl;
	std::cout << "" << std::endl;
	//-1 enlarges the image, 1 smallifies it.
	if (y_axis_offset < 0) {
		camera.move_object(vec3(0, 0, 1.05));
	}
	else {
		camera.move_object(vec3(0, 0, -1.05));
	}
	//perspec =  perspec * glm::lookAt(pos, pos + forward, up);
}

inline void pos_callback(GLFWwindow *window, double x_pos_curr, double y_pos_curr) {
	int trice = 0;
	if (is_button_pressed == GLFW_RELEASE) {
		return;
	}
	//Need to check if the position is getting closer to the originial pressed position 
	//or is getting further away.
	if (curr_button_pressed == GLFW_MOUSE_BUTTON_LEFT) {
		vec3 rotation_axis = vec3(-y_pos_curr + y_pos, x_pos_curr - x_pos, 0);
		if (rotation_axis == vec3(0)) {
			return;
		}
		x_pos = x_pos_curr;
		y_pos = y_pos_curr;
		camera.rotate_object(2.5f, normalize(rotation_axis));
	}
	if (curr_button_pressed == GLFW_MOUSE_BUTTON_RIGHT) {
		vec3 movement_direction = vec3(-clamp((float)(x_pos_curr - x_pos), -SOFT, SOFT), 
			-clamp((float)(y_pos_curr - y_pos), -SOFT, SOFT), 0);
		if (movement_direction == vec3(0)) {
			return;
		}
		x_pos = x_pos_curr;
		y_pos = y_pos_curr;
		camera.move_object(movement_direction);
	}
}

inline void mouse_callback(GLFWwindow *window, int button_pressed, int action, int mods) {
	bool pressed_flag = false;
	bool valid_press = true;
	bool single_pos = true;
	char* curr_button = button_pressed == GLFW_MOUSE_BUTTON_RIGHT ? "right" : "left";
	char* curr_action = action == GLFW_PRESS ? "pressed" : "released";
	curr_button_pressed = button_pressed;
	is_button_pressed = action;
	glfwGetCursorPos(window, &x_pos, &y_pos);
	if (button_pressed > 1) {
		valid_press = false;
	}
	if (valid_press) {
		std::cout << curr_button << " button has been " << curr_action << std::endl;
		pressed_flag = action == GLFW_PRESS ? true : false; //False is button is released.
		if (pressed_flag && single_pos) { //Gets the curser current position.
			glfwGetCursorPos(window, &x_pos, &y_pos);
			single_pos = false;
		}
	}
}


inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	char key_pressed = key;
	float change_display_by = 5.0f;
	if (action != GLFW_PRESS && action != GLFW_REPEAT)
	{
		return;
	}
	if (key_pressed != ' ') {
		std::cout << "Pressed the key: " << key_pressed << std::endl;
	}
	else {
		std::cout << "Pressed the key: space bar" << std::endl;
	}
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if(action == GLFW_PRESS)
			glfwSetWindowShouldClose(window,GLFW_TRUE);
		break;
	default:
		break;
	}
}



