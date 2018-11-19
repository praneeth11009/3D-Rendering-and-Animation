#include "hierarchy_node.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

csX75::HNode* cuboid(float,float,float,float,float,glm::vec4,float,csX75::HNode*,glm::vec4,glm::vec4);
csX75::HNode* cuboid2(float,float,float,float,float,glm::vec4,float,csX75::HNode*,glm::vec4,glm::vec4);

csX75::HNode* lid(float,float,glm::vec4,csX75::HNode*,glm::vec4,glm::vec4);
csX75::HNode* cylinder(float,float,float,glm::vec4,csX75::HNode*,glm::vec4,glm::vec4);
csX75::HNode* ellipsoid(float,float,float,float,float,glm::vec4,float,csX75::HNode*,glm::vec4,glm::vec4);
csX75::HNode* ellipsoid2(float,float,float,float,float,glm::vec4,csX75::HNode*,glm::vec4,glm::vec4);
csX75::HNode* ellipse_surface(float,float,float,float,float,glm::vec4,csX75::HNode*,glm::vec4,glm::vec4);
csX75::HNode* sphere(float,float,float,glm::vec4,csX75::HNode*,glm::vec4); 
csX75::HNode* prism(float,float,float,glm::vec4,csX75::HNode*,glm::vec4,glm::vec4);
csX75::HNode* tail(float,float,float,float,csX75::HNode*,glm::vec4,glm::vec4);
csX75::HNode* hexagon(float,float,glm::vec4,csX75::HNode* parent,glm::vec4);

