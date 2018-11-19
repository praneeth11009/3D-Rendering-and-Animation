/*

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013


*/


#include "model.hpp"


GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;


//colors
glm::vec4 skincolor = glm::vec4(1.0,227.0/255,159.0/255,1.0);
glm::vec4 darkskincolor = glm::vec4(234.0/255,192.0/255,134.0/255,1.0);
glm::vec4 darkerwhitecolor = glm::vec4(0.9,0.9,0.9,1.0);
glm::vec4 darkwhitecolor = glm::vec4(0.95,0.95,0.95,1.0);
glm::vec4 whitecolor = glm::vec4(1,1,1,1.0);
glm::vec4 blackcolor = glm::vec4(0.0,0.0,0.0,1.0);
glm::vec4 lightbluecolor = glm::vec4(0.3,0.5,1.0,1.0);
glm::vec4 bluecolor = glm::vec4(0,0,1.0,1.0);
glm::vec4 browncolor1 = glm::vec4(204.0/255,102.0/255,0.0,1.0);
glm::vec4 browncolor2 = glm::vec4(184.0/255,92.0/255,0.0,1.0);
glm::vec4 redcolor = glm::vec4(1.0,0.0,0.0,1.0);
//-----------------------------------------------------------------



//-----------------------------------------------------------------

void initBuffersGL(void)
{
  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("./shaders/vshader.glsl");
  std::string fragment_shader_file("./shaders/fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");


  // Hexagonal box  
  size = 0.6; //set box size
  box = get_box(size,glm::vec4(-7.5,-1,0,1));  
  
  // Human 
  size = 0.6; // set human size
  human = curr_node = get_human(size,glm::vec4(-1,1.5,0,1));
  
  // Fox
  size = 0.6; // set fox size
  fox = get_fox(size,glm::vec4(8,0,0,1));

  size = 1;
  table = get_table(size, glm::vec4(0,0,0,1));

  size = 1;
  chair1 = get_chair1(size, glm::vec4(0,0,0,1)); 

  size = 1;
  stool1 = get_stool1(size, glm::vec4(0,0,0,1)); 

}

void renderGL(void)
{ 

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    // projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 15.0); //changed values so as to render correctly
    projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -10.0, 10.0); //changed values so as to render correctly

  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);

  // box->render_tree();
  // fox->render_tree();
  // human->render_tree();
  // table->render_tree();
  // chair1->render_tree();
  stool1->render_tree();

}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(700,700, "CS475/CS675 Assignment 2: Hierarchical Modelling", NULL, NULL);
  if (!window)
  {
  glfwTerminate();
  return -1;
  }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

