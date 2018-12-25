#include "roboHand.h"
#include <glm/gtx/euler_angles.hpp>

using namespace glm;
#define default_num_of_links 4

roboHand::roboHand() : number_of_links{ default_num_of_links },
links{ new Displayable_object[number_of_links] } { //Use initialization list afterwards.
	mat4 main_axis = mat4(1);
	mat4 main_rotation = mat4(1);
	mat4 main_translation = mat4(1);
	for (int i = 0; i < number_of_links; i++) {
		links[i].move_object(vec3(0.0, 0, 4.0*i + 1));
	}
}

roboHand::roboHand(int num_of_links) : number_of_links{num_of_links},
links{ new Displayable_object[number_of_links] } { //Use initialization list afterwards.
	mat4 main_axis = mat4(1);
	mat4 main_rotation = mat4(1);
	mat4 main_translation = mat4(1);
	for (int i = 0; i < number_of_links; i++) {
		links[i].move_object(vec3(2.0*i, 0, 0));
	}
}

roboHand::~roboHand() {
	delete[] links;
}

void roboHand::rotate_all(float angle_first, float angle_second) { //When wanting to rotate with euler angles.

}

void roboHand::rotate_all(float angle, vec3 axis) { //When wanting to rotate with a given axis.

}

void roboHand::rotate_specific_link(int link_index, float angle_first, float angle_second) { //Rotates a specific link with euler angles.

}
void roboHand::rotate_specific_link(int link_index, float angle, vec3 axis) { //Rotates a specific link with angle and axis.

}

void roboHand::move_all(vec3 direction) { //Move everything to the specific vector location.
	for (int i = 0; i < number_of_links; i++) {
		links[i].move_object(direction);
	}
}

void roboHand::draw_lines() { //Draws the lines for all cubes in the structure.
	for (int i = 0; i < number_of_links; i++) {
		glLineWidth(2); //Width is 1
		glColor3f(0.0, 0.0, 0.0); //Color is white?
		glBegin(GL_LINES); //The function that calls it.
		glVertex3f(5.0, 0, -1); //Main line on x axis.
		glVertex3f(-5.0, 0, -1); 
		glVertex3f(0, 5.0, -1); //Main line on y axis.
		glVertex3f(0, -5.0, -1);
		glEnd();
	}
}

mat4 roboHand:: get_link_by_index(int index) const {
	if (index >= 0 && index < number_of_links) {
		return links[index].get_result()*scale(vec3(1.0, 1.0, 2.0));
	}
	return mat4(1);
}