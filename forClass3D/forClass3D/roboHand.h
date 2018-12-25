#pragma once
#include "glm\glm.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "obj_loader.h"
#include "stdio.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Displayable_object.h"
#include "GLFW/glfw3.h"


using namespace glm;

class roboHand {
public:
	roboHand();
	roboHand(int);
	~roboHand();
	void rotate_all(float, float); //When wanting to rotate with euler angles.
	void rotate_all(float, vec3); //When wanting to rotate with a given axis.
	void roboHand::rotate_specific_link(int, float, float);  //Rotates a specific link with euler angles.
	void roboHand::rotate_specific_link(int, float, vec3);  //Rotates a specific link with angle and axis.
	void roboHand::move_all(vec3); //Move everything to the specific vector location.
	void roboHand::draw_lines(); //Draws the lines for all cubes in the structure.
	mat4 get_link_by_index(int) const; //Returns the link with the given index.

private:
	int const number_of_links;
	Displayable_object* links;
	mat4 main_axis;
	mat4 main_rotation;
	mat4 main_translation;

};