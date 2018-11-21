#include "hierarchy_node.hpp"
#include "texture.hpp"

#include <iostream>

extern GLuint vPosition, vNormal, texCoord, uModelViewMatrix, normalMatrix;
extern GLuint vPosition1, vColor1, vNormal1, uModelViewMatrix1, normalMatrix1;
extern GLuint on1,on2,on11,on21;
extern GLfloat l1,l2;
extern glm::mat3 normal_matrix;
extern std::vector<glm::mat4> matrixStack;


namespace csX75
{

	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_normals, glm::vec4* a_colours, std::size_t v_size, std::size_t n_size, std::size_t c_size)
	{

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		normal_buffer_size = n_size;
		color_buffer_size = c_size;
		// initialize vao and vbo of the object;

		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, vbo);

		//bind them
		glBindVertexArray (vao[0]);
		glBindBuffer (GL_ARRAY_BUFFER, vbo[0]);

		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + normal_buffer_size + color_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
	  	glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours);
	  	glBufferSubData( GL_ARRAY_BUFFER, color_buffer_size+vertex_buffer_size, normal_buffer_size, a_normals );

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition1 );
		glVertexAttribPointer( vPosition1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( vColor1 );
		glVertexAttribPointer( vColor1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		//Normal
	  	glEnableVertexAttribArray( vNormal1 );
	  	glVertexAttribPointer( vNormal1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size+color_buffer_size) );

		// set parent

		if(a_parent == NULL)
		{
			parent = NULL;
		}
		else
		{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;
		texture_on = false;

		update_matrices();
	}
	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_normals, glm::vec2* a_tex_coords, std::size_t v_size, std::size_t n_size, std::size_t t_size)
	{

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		normal_buffer_size = n_size;
		texture_buffer_size = t_size;
		// initialize vao and vbo of the object;

		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (2, vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (2, vbo);

		//bind them
		glBindVertexArray (vao[0]);
		glBindBuffer (GL_ARRAY_BUFFER, vbo[0]);

		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + normal_buffer_size + texture_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
	  	glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, texture_buffer_size, a_tex_coords);
	  	glBufferSubData( GL_ARRAY_BUFFER, texture_buffer_size+vertex_buffer_size, normal_buffer_size, a_normals );

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( texCoord );
	  	glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size) );

 		//Normal
	  	glEnableVertexAttribArray( vNormal );
	  	glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size+texture_buffer_size) );

		// set parent

		if(a_parent == NULL)
		{
			parent = NULL;
		}
		else
		{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;
		texture_on = true;

		update_matrices();
	}

	void HNode::update_matrices()
	{
		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));
	}

	void HNode::add_child(HNode* a_child)
	{
		children.push_back(a_child);

	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz,float size)
	{
		tx = size*atx;
		ty = size*aty;
		tz = size*atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	//!Set the values for max and min angles a HNode can rotate in all 3 directions
	void HNode::set_constraints(GLfloat rx1,GLfloat rx2,GLfloat ry1,GLfloat ry2,GLfloat rz1,GLfloat rz2)
	{
		rx_min = rx1;
		rx_max = rx2;
		ry_min = ry1;
		ry_max = ry2;
		rz_min = rz1;
		rz_max = rz2;
	}

	void HNode::render()
	{

		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);

		if(texture_on) glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		else glUniformMatrix4fv(uModelViewMatrix1, 1, GL_FALSE, glm::value_ptr(*ms_mult));

		normal_matrix = glm::transpose (glm::inverse(glm::mat3(*ms_mult)));
		
  		if(texture_on) {
  			glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  			glUniform1f(on1,l1);
			glUniform1f(on2,l2);
		}
  		else {
  			glUniformMatrix3fv(normalMatrix1, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  			glUniform1f(on11,l1);
			glUniform1f(on21,l2);
		}

		glBindVertexArray (vao[0]);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);


		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree()
	{
		
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for(size_t i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	void HNode::inc_rx()
	{
		if(rx_min <= rx_max && rx+10 > rx_max)
			return;
		rx+=10;
		update_matrices();
	}


	void HNode::inc_ry()
	{
		if(ry_min <= ry_max && ry+10 > ry_max)
			return;
		ry+=10;
		update_matrices();
	}

	void HNode::inc_rz()
	{
		if(rz_min <= rz_max && rz+10 > rz_max) 
			return;
		rz+=10;
		update_matrices();
	}

	void HNode::dec_rx()
	{
		if(rx_min <= rx_max && rx-10 < rx_min)
			return;
		rx-=10;
		update_matrices();
	}

	void HNode::dec_ry()
	{
		if(ry_min <= ry_max && ry-10 < ry_min)
			return;
		ry-=10;
		update_matrices();
	}

	void HNode::dec_rz()
	{
		if(rz_min <= rz_max && rz-10 < rz_min)
			return;
		rz-=10;
		update_matrices();
	}

	
	glm::vec3 HNode::get_rot(){
		return glm::vec3(rx,ry,rz);
	}
	glm::vec3 HNode::get_pos(){
		return glm::vec3(tx,ty,tz);
	}


	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack)
	{
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(size_t i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}