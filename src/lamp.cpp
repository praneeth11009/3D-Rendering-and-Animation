#include "lamp.hpp"

csX75::HNode* get_lamp(float size,glm::vec4 offset)
{
	float r1 = 0.7;
	float r2 = 0.6;
	float h1 = 0.7;
	float h2 = 0.8;
	float r3 = 0.15;
	float h3 = 0.25;

	lamp_base = cylinder(r1,r1,h3,glm::vec4(0,0,0,1),NULL,browncolor1,browncolor1);
	lamp_base->set_constraints(0,0,0,0,0,0);
	lamp_base->change_parameters(offset.x,offset.y,offset.z,0,0,0,size);

	csX75::HNode* lamp_back = cylinder(r3,r3,h2,glm::vec4(0,0,0,1),lamp_base,browncolor2,browncolor2);
	lamp_back->set_constraints(0,0,0,0,0,0);
	lamp_back->change_parameters(0, h3, 0, 0, 0, 0, size);


	csX75::HNode* heads = cylinder(r1+r3,r2,h1,glm::vec4(0,0,0,1),lamp_back,whitecolor,whitecolor);
	heads->set_constraints(0,0,0,0,0,0);
	heads->change_parameters(0, h2, 0, 0, 0, 0, size);
	
	return lamp_base;
}