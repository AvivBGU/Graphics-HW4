#ifndef DISPLAYABLE_OBJECT_INCLUDED_H
#define DISPLAYABLE_OBJECT_INCLUDED_H

#include "glm\glm.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "stdio.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Displayable_object.h"


using namespace glm;

class Displayable_object {
	public: 
		//Constructor
		Displayable_object()  {
			first_translate = mat4(1);
			rotation = mat4(1);
			second_translate = mat4(1);
			curr_angles = vec3(0);
		}

		void reset() {
			first_translate = mat4(1);
			rotation = mat4(1);
			second_translate = mat4(1);
			curr_angles = vec3(0);
		}

		virtual ~Displayable_object(){}
		void rotate_object(float degrees, vec3 axis);
		void rotate_object_euler(float, float);
		void move_object(vec3 direction);
		mat4 get_result();
		mat4 get_rotation() {
			return rotation;
		}
		mat4 get_translation() {
			return second_translate;
		}

	private:
		mat4 first_translate;
		mat4 rotation;
		mat4 second_translate;
		vec3 curr_angles;

};
#endif