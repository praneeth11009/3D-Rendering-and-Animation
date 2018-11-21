#include "box.hpp"

csX75::HNode* get_box(float size,glm::vec4 offset)
{
    /* Box */
    
    //base of box (root of box)
	box_base = lid(3,2,glm::vec4(0,-1,0,1),NULL,skincolor,skincolor);
    box_base->set_constraints(0,0,0,0,0,0);
    box_base->change_parameters(offset.x,offset.y,offset.z,0,0,0,size);

    //Interior hexagon of box
    csX75::HNode* inner_box = lid(2.8,1.9,glm::vec4(0,-0.95,0,1),box_base,browncolor2,skincolor);
    inner_box->set_constraints(1,0,1,0,1,0);
    inner_box->change_parameters(0,0.1,0,0,0,0,size);

    //to connect boxbase and its interior
    csX75::HNode* cover_box = hexagon(3,2.8,glm::vec4(0,0,0,1),box_base,darkerwhitecolor); 
    cover_box->set_constraints(1,0,1,0,1,0);
    cover_box->change_parameters(0,1,0,0,0,0,size);
    
    //lid of box
    box_lid = lid(3,1,glm::vec4(0,-1,-sqrt(3.0)*3/2,1),box_base,browncolor2,browncolor2);
    box_lid->set_constraints(60,180,0,0,0,0);
    box_lid->change_parameters(0,1,-sqrt(3.0)*3/2,180,0,0,size);

    //interior lid
    csX75::HNode* inner_lid = lid(2.8,0.9,glm::vec4(0,-1,0,1),box_lid,skincolor,browncolor2);
    inner_lid->set_constraints(0,0,0,0,0,0);
    inner_lid->change_parameters(0,0.1,-sqrt(3.0)*3/2,0,0,0,size);

    //to connect box lid and its interior
    csX75::HNode* cover_lid = hexagon(3,2.8,glm::vec4(0,0,0,1),box_lid,darkerwhitecolor); 
    cover_lid->set_constraints(1,0,1,0,1,0);
    cover_lid->change_parameters(0,0,-sqrt(3.0)*3/2,0,0,0,size);

	return box_base;
}