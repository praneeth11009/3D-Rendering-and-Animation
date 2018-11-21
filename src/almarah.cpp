#include "almarah.hpp"

csX75::HNode* get_almarah(float size,glm::vec4 offset)
{
	float tl = 5;
	float th = 0.2;
	float tb = 3;
	almarah_base = cuboid(tb,0,tb,0,tb,glm::vec4(0,0,0,1),0,NULL,browncolor1,browncolor1);
	almarah_base->set_constraints(0,0,0,0,0,0);
	almarah_base->change_parameters(offset.x,offset.y,offset.z,0,0,0,size);

	csX75::HNode* back = cuboid(tb,tl,0,tl,0,glm::vec4(0,0,0,1),0,almarah_base,bluecolor,bluecolor);
	back->set_constraints(0,0,0,0,0,0);
	back->change_parameters(0,tl/2,-tb/2,0,0,0,size);

	csX75::HNode* left = cuboid(th,tl,tb,tl,tb,glm::vec4(0,0,0,1),0,almarah_base,redcolor,redcolor);
	left->set_constraints(0,0,0,0,0,0);
	left->change_parameters(-tb/2,tl/2,0,0,0,0,size);

	csX75::HNode* right = cuboid(th,tl,tb,tl,tb,glm::vec4(0,0,0,1),0,almarah_base,redcolor,redcolor);
	right->set_constraints(0,0,0,0,0,0);
	right->change_parameters(tb/2,tl/2,0,0,0,0,size);

	csX75::HNode* top = cuboid(tb,0,tb,0,tb,glm::vec4(0,0,0,1),0,almarah_base,browncolor1,browncolor1);
	top->set_constraints(0,0,0,0,0,0);
	top->change_parameters(0,tl,0,0,0,0,size);

	csX75::HNode* front = cuboid(tb,tl,th,tl,th,glm::vec4(tb/(2*sqrt(3)),0,0,1),0,almarah_base,skincolor,skincolor);
	front->set_constraints(0,0,0,0,0,0);
	front->change_parameters(-0.5,tl/2,tb-0.45,0,30,0,size);


	return almarah_base;
}