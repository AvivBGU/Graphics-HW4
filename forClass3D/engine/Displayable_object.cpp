#include "Displayable_object.h"
#include <glm/gtx/euler_angles.hpp>

using namespace glm;


void Displayable_object::rotate_object(float degrees, vec3 axis) {
	rotation =  glm::rotate(degrees, axis)*rotation;

}

mat4 Displayable_object::get_result() {
	mat4 result = first_translate * rotation * second_translate;
	return (result);
}

void Displayable_object::move_object(vec3 direction) {
	second_translate = translate(second_translate, direction);
}

void Displayable_object::rotate_object_euler(float first_angle, float second_angle) {
	float rad_first_angle = glm::radians(first_angle);
	float rad_second_angle = glm::radians(second_angle);
	if (rad_first_angle != 0.0f /*&& abs(curr_angles.x + rad_first_angle) > limit*/)
	{
		return;
	}
	curr_angles.x += rad_first_angle;
	curr_angles.z += rad_second_angle;

	mat4 euler_angle_x = glm::eulerAngleX(curr_angles.x);
	mat4 euler_angle_z = glm::eulerAngleZ(curr_angles.z);
	rotation = euler_angle_z * euler_angle_x;
}