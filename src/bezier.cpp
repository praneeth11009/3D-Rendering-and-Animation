#include "bezier.hpp"

glm::vec4 getPosition(double t,std::vector<glm::vec4> control){
	for(uint i=0;i<control.size()-1;i++){
		for(uint j=0;j<control.size()-1-i;j++){
			control[j].x = control[j].x*(1-t) + control[j+1].x*t;
			control[j].y = control[j].y*(1-t) + control[j+1].y*t;
			control[j].z = control[j].z*(1-t) + control[j+1].z*t;
		}
	}
	return control[0];
}