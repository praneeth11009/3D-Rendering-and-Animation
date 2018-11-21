#include "room.hpp"

csX75::HNode* get_room(float size,glm::vec4 offset){

	float thick = 0.06;
	float height = 2;
	float length = 3;
	float width = 2.5;

	float door_h = 1.2;
	float door_l = 0.65;

	float fthick = 0.04;

	float wh = 0.8;
	float wl = 0.6;

	csX75::HNode* room_floor = cuboid(length,fthick,width,fthick,width,glm::vec4(0,0,0,1),0,NULL,browncolor1,redcolor);
	room_floor->change_parameters(0,0,0,0,0,0,size);
	room_floor->set_constraints(1,0,1,0,1,0);

	csX75::HNode* back_wall = cuboid(length+2*thick,height+2*fthick,thick,height+2*fthick,thick,glm::vec4(0,0,0,1),0,room_floor,browncolor1,redcolor);
	back_wall->change_parameters(0,(height+fthick)/2,-(width+thick)/2,0,0,0,size);

	csX75::HNode* front_wall_l = cuboid(length/2+thick-door_l/2,height+2*fthick,thick,height+2*fthick,thick,glm::vec4(0,0,0,1),0,room_floor,browncolor1,redcolor);
	front_wall_l->change_parameters(door_l/4+length/4+thick/2,(height+fthick)/2,(width+thick)/2,0,0,0,size);

	csX75::HNode* front_wall_r = cuboid(length/2+thick-door_l/2,height+2*fthick,thick,height+2*fthick,thick,glm::vec4(0,0,0,1),0,room_floor,browncolor1,redcolor);
	front_wall_r->change_parameters(-(door_l/4+length/4+thick/2),(height+fthick)/2,(width+thick)/2,0,0,0,size);

	csX75::HNode* front_wall = cuboid(door_l,height-door_h+2*fthick,thick,height-door_h+2*fthick,thick,glm::vec4(0,0,0,1),0,room_floor,browncolor1,redcolor);
	front_wall->change_parameters(0,height/2+door_h/2+fthick/2,(width+thick)/2,0,0,0,size);

	room_door = cuboid(door_l,door_h,thick/2,door_h,thick/2,glm::vec4(door_l/2,0,0,1),0,room_floor,bluecolor,bluecolor);
	room_door->change_parameters(-door_l/2,(door_h-fthick)/2,(width+thick/2)/2,0,-80,0,size);
	room_door->set_constraints(0,0,-90,0,0,0);

	csX75::HNode* left_wall_left = cuboid(thick,height+2*fthick,(width-wl)/2,height+2*fthick,(width-wl)/2,glm::vec4(0,0,0,1),0,room_floor,browncolor1,redcolor);
	left_wall_left->change_parameters(-(length+thick)/2,(height+fthick)/2,-(width+wl)/4,0,0,0,size);

	csX75::HNode* left_wall_right = cuboid(thick,height+2*fthick,(width-wl)/2,height+2*fthick,(width-wl)/2,glm::vec4(0,0,0,1),0,room_floor,browncolor1,redcolor);
	left_wall_right->change_parameters(-(length+thick)/2,(height+fthick)/2,(width+wl)/4,0,0,0,size);

	csX75::HNode* left_wall_top = cuboid(thick,(height-wh)/2+2*fthick,wl,(height-wh)/2+2*fthick,wl,glm::vec4(0,0,0,1),0,room_floor,browncolor1,redcolor);
	left_wall_top->change_parameters(-(length+thick)/2,(3*height+wh+2*fthick)/4,0,0,0,0,size);

	csX75::HNode* left_wall_bottom = cuboid(thick,(height-wh)/2+fthick,wl,(height-wh)/2+fthick,wl,glm::vec4(0,0,0,1),0,room_floor,browncolor1,redcolor);
	left_wall_bottom->change_parameters(-(length+thick)/2,(height-wh)/4,0,0,0,0,size);

	room_window = cuboid(thick/2,wh-fthick,wl,wh-fthick,wl,glm::vec4(0,0,wl/2,1),0,room_floor,bluecolor,bluecolor);
	room_window->change_parameters(-(length+thick/2)/2,height/2,-wl/2,0,-60,0,size);
	room_window->set_constraints(0,0,-90,0,0,0);

	csX75::HNode* right_wall = cuboid(thick,height+2*fthick,width,height+2*fthick,width,glm::vec4(0,0,0,1),0,room_floor,browncolor1,redcolor);
	right_wall->change_parameters((length+thick)/2,(height+fthick)/2,0,0,0,0,size);

	csX75::HNode* room_ceil = cuboid(length,fthick,width,fthick,width,glm::vec4(0,0,0,1),0,room_floor,browncolor1,redcolor);
	room_ceil->change_parameters(0,height+fthick,0,0,0,0,size);

	return room_floor;
}