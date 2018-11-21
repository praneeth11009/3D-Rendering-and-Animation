/*

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013


*/


#include "model.hpp"
#include "texture.hpp"


GLuint shaderProgram;
GLuint shaderProgram1;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;
GLuint uModelViewMatrix1;

glm::mat3 normal_matrix;

GLuint viewMatrix;
GLuint normalMatrix;

GLuint tex_table,tex_box, tex_chair, tex_almarah, tex_room, tex_stool;

double param = 0;


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

double width = 1200;
double height = 700;

std::vector<glm::vec4> camera_positions;
std::vector<glm::vec4> control_points;
std::vector<csX75::HNode*> click_spheres;


//-----------------------------------------------------------------

void initBuffersGL(void)
{
  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("./shaders/vshader.glsl");
  std::string fragment_shader_file("./shaders/fshader.glsl");

  std::string vertex_shader_file1("./shaders/vshader1.glsl");
  std::string fragment_shader_file1("./shaders/fshader1.glsl");

  std::vector<GLuint> shaderList;
  std::vector<GLuint> shaderList1;

  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderList1.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file1));
  shaderList1.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file1));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  shaderProgram1 = csX75::CreateProgramGL(shaderList1);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");


  vNormal = glGetAttribLocation( shaderProgram, "vNormal" ); 
  texCoord = glGetAttribLocation( shaderProgram, "texCoord" );
  normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
  viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");

  vPosition1 = glGetAttribLocation( shaderProgram1, "vPosition" );
  vColor1 = glGetAttribLocation( shaderProgram1, "vColor" ); 
  uModelViewMatrix1 = glGetUniformLocation( shaderProgram1, "uModelViewMatrix");


  camera_positions.clear();


  // Human 
  useTexture = false;

  size = 0.06; // set human size
  human = curr_node = get_human(size,glm::vec4(-2.6,obj_y,0,1));
  
  // // Fox
  useTexture = false;

  size = 0.2; // set fox size
  fox = get_fox(size,glm::vec4(-1,2,0,1));

  // Hexagonal box  
  useTexture = true;
  tex_box=LoadTexture("images/music.bmp",256,256);

  size = 0.16; //set box size
  box = get_box(size,glm::vec4(-1.8,7.4,0,1));  

  useTexture = true;
  tex_table=LoadTexture("images/dark-wood.bmp",256,256);

  size = 0.4;
  table = get_table(size, glm::vec4(-1,2.5,0,1));

  useTexture = true;
  tex_chair=LoadTexture("images/music.bmp",256,256);

  size = 0.4;
  chair1 = get_chair1(size, glm::vec4(-1,2,-3.5,1));

  useTexture = true;
  tex_almarah=LoadTexture("images/dark-wood.bmp",256,256);

  size = 0.6;
  almarah = get_almarah(size, glm::vec4(5,0.1,-2.5,1));

  useTexture = true;
  tex_room=LoadTexture("images/light-wood.bmp",256,256);

  size = 3;
  room = get_room(size,glm::vec4(0,0,0,1));

  useTexture = true;
  tex_stool=LoadTexture("images/music.bmp",256,256);

  size = 0.4;
  stool1 = get_stool1(size, glm::vec4(-5,1.8,-2.5,1)); 

}

void renderGL(void)
{ 

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos;
  if(! recordMode) c_pos = glm::vec4(c_xpos,c_ypos,c_zpos,1.0)*c_rotation_matrix;
  else c_pos = glm::vec4(c_xpos,c_ypos,c_zpos,1.0);

  if(recordMode) c_lookAt = glm::vec4(0,0,-1.0,1.0) + c_pos;
  else c_lookAt = glm::vec4(0,0,0,1); 

  if(start_camera && control_points.size() > 0){
    if(clock() - timer > 1000){
      param += 0.0001;
      if(param > 1) {
        start_camera = false;
        control_points.clear();
        click_spheres.clear();
        param = 0;
      }
      else{
        glm::vec4 current_pos = getPosition(param,control_points);
        c_pos = current_pos;
        c_xpos = c_pos.x;c_ypos = c_pos.y;c_zpos = c_pos.z;
      }
    }
  }

  glm::vec4 c_up;
  if(recordMode) c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0);
  else c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(c_lookAt),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    //projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 15.0); //changed values so as to render correctly
    projection_matrix = glm::perspective(glm::radians(60.0),width/height,0.0001,100.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -10.0, 10.0); //changed values so as to render correctly

  view_matrix = projection_matrix*lookat_matrix;

  

  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
  modelview_matrix = view_matrix*model_matrix;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  normal_matrix = glm::transpose (glm::inverse(glm::mat3(modelview_matrix)));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));

  matrixStack.push_back(view_matrix);

  glUseProgram(shaderProgram);
  glBindTexture(GL_TEXTURE_2D, tex_box);
  box->render_tree();

  // // glUseProgram( shaderProgram1);
  // // fox->render_tree();

  glUseProgram( shaderProgram1);
  human->render_tree();

  glUseProgram( shaderProgram);
  glBindTexture(GL_TEXTURE_2D, tex_table);
  table->render_tree();

  glUseProgram( shaderProgram);
  glBindTexture(GL_TEXTURE_2D, tex_chair);
  chair1->render_tree();

  glUseProgram( shaderProgram);
  glBindTexture(GL_TEXTURE_2D, tex_almarah);
  almarah->render_tree();
  
  glUseProgram( shaderProgram);
  glBindTexture(GL_TEXTURE_2D, tex_stool);
  stool1->render_tree();
  
  glUseProgram( shaderProgram);
  glBindTexture(GL_TEXTURE_2D, tex_room);
  room->render_tree();
  
  if(recordMode){
    for(uint i=0;i<camera_positions.size();i++){
      glm::vec4 pos = camera_positions[i];
      pos.z = pos.z -0.5;
      camera_positions[i].z -= 0.5;
      click_spheres.push_back(sphere(0.01,0.01,0.01,glm::vec4(0,0,0,1),NULL,whitecolor));
      click_spheres[click_spheres.size()-1]->change_parameters(pos.x,pos.y,pos.z,0,0,0,1);
      control_points.push_back(camera_positions[i]);
      camera_positions.pop_back();
    }
    glUseProgram( shaderProgram1);
    for(uint i=0;i<click_spheres.size();i++){
      click_spheres[i]->render_tree();
    }
  }

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
  window = glfwCreateWindow(width,height, "CS475/CS675 Assignment 2: Hierarchical Modelling", NULL, NULL);
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
  glfwSetMouseButtonCallback(window, csX75::mouse_callback);

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

