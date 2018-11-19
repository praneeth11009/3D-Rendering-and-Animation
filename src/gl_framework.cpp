#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;

extern bool enable_perspective;

extern csX75::HNode* torso3, *torso2, *head, *neck, *right_ul, *left_ul, *right_ll, *left_ll,
    *right_ua, *left_ua, *right_la, *left_la,  *right_wr, *left_wr, *box_lid, *box_base,
    *an_torso1, *an_neck, *an_head0, *an_left_fla, *an_right_fla, *an_left_hla, *an_right_hla, *an_tail, *curr_node;

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
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  { 
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    else if (key == GLFW_KEY_B && action == GLFW_PRESS) //Box
    {
      current = 3;
      curr_node = box_base;
    }
    else if (key == GLFW_KEY_F && action == GLFW_PRESS) //Fox
    {
      current = 2;
      curr_node = an_torso1;
    }
    else if (key == GLFW_KEY_H && action == GLFW_PRESS) //Human
    {
      current = 1;
      curr_node = torso2;
    }

    if(current == 1) //Human
    {
      if (key == GLFW_KEY_1 && action == GLFW_PRESS) //lower torso (root of human)
        curr_node = torso2;  
      else if (key == GLFW_KEY_2 && action == GLFW_PRESS) //upper torso
        curr_node = torso3; 
      else if (key == GLFW_KEY_3 && action == GLFW_PRESS) //neck
        curr_node = neck; 
      else if (key == GLFW_KEY_4 && action == GLFW_PRESS) //head
        curr_node = head; 

      else if (key == GLFW_KEY_5 && action == GLFW_PRESS) //right upper leg
        curr_node = right_ul;
      else if (key == GLFW_KEY_6 && action == GLFW_PRESS) //left upper leg
        curr_node = left_ul;
      else if (key == GLFW_KEY_7 && action == GLFW_PRESS) //right lower leg
        curr_node = right_ll;
      else if (key == GLFW_KEY_8 && action == GLFW_PRESS) //left lower leg
        curr_node = left_ll;

      else if (key == GLFW_KEY_9 && action == GLFW_PRESS) //right upper arm
        curr_node = right_ua;
      else if (key == GLFW_KEY_0 && action == GLFW_PRESS) //left upper arm
        curr_node = left_ua;
      else if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) //right lower arm
        curr_node = right_la;
      else if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) //left lower arm
        curr_node = left_la;

      else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS) //left wrist
        curr_node = left_wr;
      else if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS) //right wrist
        curr_node = right_wr;
    }

    else if(current == 2) //Fox
    {
      if (key == GLFW_KEY_1 && action == GLFW_PRESS) //Fox body (root of fox)
        curr_node = an_torso1;  
      else if (key == GLFW_KEY_2 && action == GLFW_PRESS) //neck
        curr_node = an_neck; 
      else if (key == GLFW_KEY_3 && action == GLFW_PRESS) //head
        curr_node = an_head0; 

      else if (key == GLFW_KEY_4 && action == GLFW_PRESS) //left fore leg
        curr_node = an_left_fla; 
      else if (key == GLFW_KEY_5 && action == GLFW_PRESS) //right fore leg
        curr_node = an_right_fla;
      else if (key == GLFW_KEY_6 && action == GLFW_PRESS) //left hind leg
        curr_node = an_left_hla;
      else if (key == GLFW_KEY_7 && action == GLFW_PRESS) //right hind leg
        curr_node = an_right_hla;

      else if (key == GLFW_KEY_8 && action == GLFW_PRESS) //tail
        curr_node = an_tail;
    }

    else if(current == 3) //Box
    {
      if (key == GLFW_KEY_1 && action == GLFW_PRESS) //Box base (root of box)
        curr_node = box_base;  
      else if (key == GLFW_KEY_2 && action == GLFW_PRESS) //lid of box
        curr_node = box_lid; 
    }

    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
      curr_node->dec_ry();
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
      curr_node->inc_ry();
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
      curr_node->dec_rx();
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
      curr_node->inc_rx();
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
      curr_node->dec_rz();
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
      curr_node->inc_rz();

    // else if (key == GLFW_KEY_P && action == GLFW_PRESS)
    //   enable_perspective = !enable_perspective;   

    else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
      c_yrot -= 10.0;
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS)
      c_yrot += 10.0;
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS)
      c_xrot -= 10.0;
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS)
      c_xrot += 10.0;        
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS)
      c_zrot -= 10.0;
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS)
      c_zrot += 10.0;   
  }
};  
  


