/*
  A program which opens a window and draws three arms in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Written by - 
               Harshavardhan Kode [From Tutorial_07-Hierarchical Modelling]
*/
#ifndef _COLORCUBE_HPP_ 
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"
#include "shapes.hpp"
#include "human.hpp"
#include "fox.hpp"
#include "box.hpp"
#include "table.hpp"
#include "chair.hpp"
#include "stool.hpp"
#include "room.hpp"
#include "almarah.hpp"
#include "bezier.hpp"
#include "lamp.hpp"

/*
// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;
*/
// Camera position and rotation Parameters
glm::vec4 start_posn = glm::vec4(0.0,2.0,3.0,1.0);

GLfloat c_xpos = start_posn.x, c_ypos = start_posn.y, c_zpos = start_posn.z;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

glm::vec4 c_lookAt, music_box_pos;

bool recordMode = false; //set to true
bool useTexture = false;

bool start_camera = false;
double timer;

float obj_y = 22;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=true;
//Shader program attribs
GLuint vPosition,vColor,vNormal,texCoord;
GLuint vPosition1,vColor1,vNormal1;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

//relative size of the character
float size = 1;

csX75::HNode* fox,*human,*box, *table, *chair1, *stool1, *almarah, *lamp;
csX75::HNode* curr_node;

csX75::HNode* table_base;
csX75::HNode* chair1_base;
csX75::HNode* stool1_base;
csX75::HNode* almarah_base;

//------- HUMAN ---------
csX75::HNode* torso2;
csX75::HNode* torso3;
csX75::HNode* torso1;
csX75::HNode* skirt;
csX75::HNode* neck;
csX75::HNode* head;
csX75::HNode* right_ul;
csX75::HNode* right_ll;
csX75::HNode* left_ul;
csX75::HNode* left_ll;
csX75::HNode* right_sh;
csX75::HNode* left_sh;
csX75::HNode* right_ua;
csX75::HNode* right_la;
csX75::HNode* left_ua;
csX75::HNode* left_la;
csX75::HNode* right_wr;
csX75::HNode* right_ft;
csX75::HNode* left_wr;
csX75::HNode* left_ft;

//------ BOX ------
csX75::HNode* box_lid;
csX75::HNode* box_base;

//---- FOX ------
csX75::HNode* an_torso1;
csX75::HNode* an_neck;
csX75::HNode* an_head0;
csX75::HNode* an_left_fla;
csX75::HNode* an_left_fll;
csX75::HNode* an_right_fla;
csX75::HNode* an_right_fll;
csX75::HNode* an_left_hla;
csX75::HNode* an_left_hll;
csX75::HNode* an_right_hla;
csX75::HNode* an_right_hll;
csX75::HNode* an_tail;

//-----------ROOM---------------

csX75::HNode* room;

csX75::HNode* room_door;
csX75::HNode* room_window;

//--------
csX75::HNode* lamp_base;

#endif

