#include "chair.hpp"

csX75::HNode* get_chair1(float size,glm::vec4 offset)
{
	float tl = 2;
	float th = 0.2;
	float tb = 2;
	chair1_base = cuboid(tl,th,tb,th,tb,glm::vec4(0,0,0,1),0,NULL,browncolor1,browncolor1);
	chair1_base->set_constraints(1,0,1,0,1,0);
	chair1_base->change_parameters(offset.x,offset.y,offset.z,0,0,0,size);

	csX75::HNode* chair1_back = cuboid(tl,1.5*tb,th,1.5*tb,th,glm::vec4(0,0,0,1),0,chair1_base,bluecolor,bluecolor);
	chair1_back->set_constraints(0,0,0,0,0,0);
	chair1_back->change_parameters(0, 1.5*tl/2, -(tl-th)/2, 0, 0, 0, size);	

	csX75::HNode* ftlegl = cuboid(1.25*th,tl,1.25*th,tl,1.25*th,glm::vec4(0,0,0,1),0,chair1_base,bluecolor,bluecolor);
	ftlegl->set_constraints(0,0,0,0,0,0);
	ftlegl->change_parameters(-1*(tl-1.25*th)/2, -tl/2, 1*tl/3, 0, 0, 0, size);

	csX75::HNode* ftlegr = cuboid(1.25*th,tl,1.25*th,tl,1.25*th,glm::vec4(0,0,0,1),0,chair1_base,skincolor,skincolor);
	ftlegr->set_constraints(0,0,0,0,0,0);
	ftlegr->change_parameters(1*(tl-1.25*th)/2, -tl/2, 1*tl/3, 0, 0, 0, size);

	csX75::HNode* bklegl = cuboid(1.25*th,tl,1.25*th,tl,1.25*th,glm::vec4(0,0,0,1),0,chair1_base,whitecolor,whitecolor);
	bklegl->set_constraints(0,0,0,0,0,0);
	bklegl->change_parameters(-1*(tl-1.25*th)/2, -tl/2, -1*(tl-1.25*th)/2, 0, 0, 0, size);

	csX75::HNode* bklegr = cuboid(1.25*th,tl,1.25*th,tl,1.25*th,glm::vec4(0,0,0,1),0,chair1_base,redcolor,redcolor);
	bklegr->set_constraints(0,0,0,0,0,0);
	bklegr->change_parameters(1*(tl-1.25*th)/2, -tl/2, -1*(tl-1.25*th)/2, 0, 0, 0, size);

	return chair1_base;
}