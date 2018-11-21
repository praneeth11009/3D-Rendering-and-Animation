#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern GLfloat c_xpos,c_ypos,c_zpos;
extern glm::vec4 c_lookAt, music_box_pos;

extern glm::vec4 start_posn;

extern bool recordMode;
extern bool start_camera;
extern double timer;

extern float obj_y;

extern GLfloat l1,l2;

extern bool enable_perspective;

extern double width,height;
extern glm::mat4 view_matrix;
extern std::vector<glm::vec4> camera_positions;
extern std::vector<glm::vec4> control_points;
extern std::vector<csX75::HNode*> click_spheres;

extern csX75::HNode* torso3, *torso2, *head, *neck, *right_ul, *left_ul, *right_ll, *left_ll,
    *right_ua, *left_ua, *right_la, *left_la,  *right_wr, *left_wr, *box_lid, *box_base, 
    *an_torso1, *an_neck, *an_head0, *an_left_fla, *an_right_fla, *an_left_fll, *an_right_fll, *an_tail, *curr_node,
    *room_door, *room, *room_window;
int current = 1;
namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS); 
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window 
    glViewport(0, 0, width, height);
  }

  void mouse_callback(GLFWwindow* window, int button, int action, int mods){
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if(recordMode){
      switch(button)
      {
        case GLFW_MOUSE_BUTTON_LEFT:
          
          if (action == GLFW_PRESS)
          { 
            GLfloat x = (xpos-width/2)/width;
            GLfloat y = (height/2-ypos)/height;
            glm::vec4 pos = glm::vec4(x,y,c_zpos,1);
            glm::mat4 inv_view = inverse(view_matrix);

            glm::vec4 orig_pos = pos*inv_view;
            orig_pos.z = c_zpos;
            orig_pos.y = orig_pos.y + c_ypos;
            orig_pos.x = orig_pos.x + c_xpos;
            camera_positions.push_back(orig_pos);
            //std::cout<<orig_pos.x<<" "<<orig_pos.y<<" "<<c_zpos<<" "<<orig_pos.a<<std::endl;
          }
          break;
        case GLFW_MOUSE_BUTTON_RIGHT:
          if (action == GLFW_PRESS)
          {
            if(control_points.size() > 0) {
              control_points.pop_back();
              click_spheres.pop_back();
            }
          }
          break;
        default:
          break;
      }
    }
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  { 
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_B && action == GLFW_PRESS){
      current = 3;
      curr_node = box_base;
    }
    else if (key == GLFW_KEY_F && action == GLFW_PRESS){
      current = 2;
      curr_node = an_torso1;
    }
    else if (key == GLFW_KEY_H && action == GLFW_PRESS){
      current = 1;
      curr_node = torso2;
    }
    else if (key == GLFW_KEY_R && action == GLFW_PRESS){
      current = 4;
      curr_node = room;
    }
    if(current == 1){
      if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        curr_node = torso2;  
      else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        curr_node = torso3; 
      else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
        curr_node = neck; 
      else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
        curr_node = head; 

      else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
        curr_node = right_ul;
      else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
        curr_node = left_ul;
      else if (key == GLFW_KEY_7 && action == GLFW_PRESS)
        curr_node = right_ll;
      else if (key == GLFW_KEY_8 && action == GLFW_PRESS)
        curr_node = left_ll;

      else if (key == GLFW_KEY_9 && action == GLFW_PRESS)
        curr_node = right_ua;
      else if (key == GLFW_KEY_0 && action == GLFW_PRESS)
        curr_node = left_ua;
      else if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
        curr_node = right_la;
      else if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
        curr_node = left_la;

      else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS)
        curr_node = right_wr;
      else if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS)
        curr_node = left_wr;
    }
    else if(current == 2){
      if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        curr_node = an_torso1;  
      else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        curr_node = an_neck; 
      else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
        curr_node = an_head0; 
      else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
        curr_node = an_left_fla; 

      else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
        curr_node = an_right_fla;
      else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
        curr_node = an_left_fll;
      else if (key == GLFW_KEY_7 && action == GLFW_PRESS)
        curr_node = an_right_fll;
      else if (key == GLFW_KEY_8 && action == GLFW_PRESS)
        curr_node = an_tail;
    }
    else if(current == 3){
      if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        curr_node = box_base;  
      else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        curr_node = box_lid; 
    }
    else if(current == 4){
      if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        curr_node = room_door;  
      else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        curr_node = room_window;
    }

    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
      curr_node->dec_ry();
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
      curr_node->inc_ry();
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS){
      if(current == 3){
        obj_y += 0.2;
        torso2->change_parameters(-2.6,obj_y,0,0.0,0.0,0.0,0.06);
      }
      curr_node->dec_rx();
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
      if(current == 3){
        obj_y -= 0.2;
        torso2->change_parameters(-2.6,obj_y,0,0.0,0.0,0.0,0.06);
      }
      curr_node->inc_rx();
    }
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
      curr_node->dec_rz();
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
      curr_node->inc_rz();

    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   

    else if (key == GLFW_KEY_A  && action == GLFW_PRESS){
      if(!recordMode) c_yrot -= 10.0;
      else c_xpos -= 0.2;
    }
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS){
      if(!recordMode) c_yrot += 10.0;
      else c_xpos += 0.2;
    }
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS){
      if(recordMode) c_zpos -= 0.2;
      else c_zpos -= 0.2;
      //std::cout<<c_xpos<<" "<<c_ypos<<" "<<c_zpos<<std::endl;
    }
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS){
      if(recordMode) c_zpos += 0.2;
      else c_zpos += 0.2;    
    }
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS){
      if(!recordMode) c_xrot += 10.0;
      else c_ypos -= 0.2;
    }
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS){
      if(!recordMode) c_xrot -= 10.0;
      else c_ypos += 0.2;
    }

    else if (key == GLFW_KEY_O && action == GLFW_PRESS){
      if(recordMode) {
        recordMode = false;
      }
      else {
        recordMode = true;
        c_xpos = start_posn.x;
        c_ypos = start_posn.y;
        c_zpos = start_posn.z;
        c_xrot = 0.0;
        c_yrot = 0.0;
        c_zrot = 0.0;
      }
    }

    else if (key == GLFW_KEY_M && action == GLFW_PRESS){
      if(! start_camera){
        start_camera = true;
        recordMode = false;
        c_xpos = start_posn.x;
        c_ypos = start_posn.y;
        c_zpos = start_posn.z;
        c_xrot = 0.0;
        c_yrot = 0.0;
        c_zrot = 0.0;
        timer = glfwGetTime();
        std::cout<<"Started timer"<<std::endl;
      }
    }

    else if (key == GLFW_KEY_Z  && action == GLFW_PRESS){
      if(l1 == 1) l1 = 0;
      else l1 = 1;
      //std::cout<<"Light 1 "<<l1<<std::endl;
    }
    else if (key == GLFW_KEY_X  && action == GLFW_PRESS){
      if(l2 == 1) l2 = 0;
      else l2 = 1;
      //std::cout<<"Light 2 "<<l2<<std::endl;
    }
  }
};  
