#include "stool.hpp"

csX75::HNode* get_stool1(float size,glm::vec4 offset)
{
	float r1 = 1.25;
	float h1 = 0.35;
	float r2 = 0.2;
	float h2 = 1.5;
	float r3 = 0.15;
	float h3 = 1.2;

	stool1_base = cylinder(r1,r1,h1,glm::vec4(0,0,0,1),NULL,browncolor1,browncolor1);
	stool1_base->set_constraints(1,0,1,0,1,0);
	stool1_base->change_parameters(offset.x,offset.y,offset.z,0,0,0,size);

	csX75::HNode* stool1_back = cylinder(r2,r2,h2,glm::vec4(0,0,0,1),stool1_base,bluecolor,bluecolor);
	stool1_back->set_constraints(0,0,0,0,0,0);
	stool1_back->change_parameters(0, -h2, 0, 0, 0, 0, size);


	csX75::HNode* leg1 = ellipsoid(r3,r3,r3,r3,h3,glm::vec4(0,0,0,1),0.6,stool1_back,redcolor,redcolor);
	leg1->set_constraints(0,0,0,0,0,0);
	leg1->change_parameters(0, 3*r3, 0, 90, 0, 120, size);

	csX75::HNode* leg2 = ellipsoid(r3,r3,r3,r3,h3,glm::vec4(0,0,0,1),0.6,stool1_back,redcolor,redcolor);
	leg2->set_constraints(0,0,0,0,0,0);
	leg2->change_parameters(0, 3*r3, 0, 90, 0, -120, size);

	csX75::HNode* leg3 = ellipsoid(r3,r3,r3,r3,h3,glm::vec4(0,0,0,1),0.6,stool1_back,redcolor,redcolor);
	leg3->set_constraints(0,0,0,0,0,0);
	leg3->change_parameters(0, 3*r3, 0, 90, 0, 0, size);
	
	return stool1_base;
}