#ifndef _HNODE_HPP_
#define _HNODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "gl_framework.hpp"


namespace csX75	 
{ 
	// A simple class that represents a node in the hierarchy tree  
	class HNode 
	{	
		public:
		//glm::vec4 * vertices;
		//glm::vec4 * colors;
		GLfloat tx,ty,tz,rx,ry,rz;
		GLfloat rx_min,ry_min,rz_min,rx_max,ry_max,rz_max;

		bool texture_on;

		std::size_t vertex_buffer_size;
		std::size_t color_buffer_size;
		std::size_t normal_buffer_size;
		std::size_t texture_buffer_size;

		GLuint num_vertices;
		GLuint vao[2],vbo[2];

		glm::mat4 rotation;
		glm::mat4 translation;
		
		std::vector<HNode*> children;
		HNode* parent;

		void update_matrices();

	  
		HNode (HNode*, GLuint, glm::vec4*,  glm::vec4*, glm::vec4*, std::size_t, std::size_t, std::size_t);
		HNode (HNode*, GLuint, glm::vec4*,  glm::vec4*, glm::vec2*, std::size_t, std::size_t, std::size_t);

		void add_child(HNode*);
		void render();
		void change_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,float);
		void render_tree();
		void inc_rx();
		void inc_ry();
		void inc_rz();
		void dec_rx();
		void dec_ry();
		void dec_rz();
		glm::vec3 get_rot();
		glm::vec3 get_pos();
		void set_constraints(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
	};

	glm::mat4* multiply_stack(std::vector <glm::mat4> );
};	

#endif
