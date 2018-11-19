#include "table.hpp"

csX75::HNode* get_table(float size,glm::vec4 offset)
{
	float tl = 3;
	float th = 0.2;
	float tb = 3;
	table_base = cuboid(tl,th,tb,th,tb,glm::vec4(0,0,0,1),0,NULL,browncolor1,browncolor1);
	table_base->set_constraints(1,0,1,0,1,0);
	table_base->change_parameters(offset.x,offset.y,offset.z,0,0,0,size);

	csX75::HNode* ftlegl = cuboid(1.25*th,tl,1.25*th,tl,1.25*th,glm::vec4(0,0,0,1),0,table_base,bluecolor,bluecolor);
	ftlegl->set_constraints(0,0,0,0,0,0);
	ftlegl->change_parameters(-3*tl/8, -tl/2, 3*tl/8, 0, 0, 0, size);

	csX75::HNode* ftlegr = cuboid(1.25*th,tl,1.25*th,tl,1.25*th,glm::vec4(0,0,0,1),0,table_base,skincolor,skincolor);
	ftlegr->set_constraints(0,0,0,0,0,0);
	ftlegr->change_parameters(3*tl/8, -tl/2, 3*tl/8, 0, 0, 0, size);

	csX75::HNode* bklegl = cuboid(1.25*th,tl,1.25*th,tl,1.25*th,glm::vec4(0,0,0,1),0,table_base,whitecolor,whitecolor);
	bklegl->set_constraints(0,0,0,0,0,0);
	bklegl->change_parameters(-3*tl/8, -tl/2, -3*tl/8, 0, 0, 0, size);

	csX75::HNode* bklegr = cuboid(1.25*th,tl,1.25*th,tl,1.25*th,glm::vec4(0,0,0,1),0,table_base,redcolor,redcolor);
	bklegr->set_constraints(0,0,0,0,0,0);
	bklegr->change_parameters(3*tl/8, -tl/2, -3*tl/8, 0, 0, 0, size);

	return table_base;
}