

#version 330

in vec3 normal;
in vec4 eye;
in vec2 tex;
in vec4 pos;

uniform mat4 viewMatrix;
uniform sampler2D texture;

in float use1;
in float use2;

out vec4 frag_color;

void main () 
{
  // Defining Materials
  vec4 diffuse = vec4(0.4, 0.4, 0.4, 1.0); 
  vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
  vec4 specular = vec4(0.2, 0.2, 0.2, 1.0);
  float shininess = 0.05;
  vec4 spec = vec4(0.0); 

  // Defining Light 
  vec4 lightPos1 = vec4(1, 10000.0, 1, 0.0);
  vec3 lightDir1 = vec3(viewMatrix*(lightPos1));  // Transforms with camera
  lightDir1 = normalize( vec3(lightDir1));

  vec4 lightPos2 = vec4(-2.0, -1.5, 0.0, 1.0);
  vec3 lightDir2 = vec3(lightPos2 - pos);  // Transforms with camera
  vec3 lightDir3 = -vec3(lightPos2 - pos);
  lightDir2 = normalize( vec3(lightDir2));
  lightDir3 = normalize( vec3(lightDir3));

  //Diffuse
  vec3 n = normalize(vec3(normal));      
  float dotProduct1 = dot(n, lightDir1);
  float intensity1 =  max( dotProduct1, 0.0);

  float dotProduct2 = dot(n, lightDir2);
  float intensity2 =  max( dotProduct2, 0.0);

  float dotProduct3 = dot(n, lightDir3);
  float intensity3 =  max( dotProduct3, 0.0);

  // Compute specular component only if light falls on vertex
  if(intensity1 > 0.0)
  {
  if(use1 > 0.5){
	  vec3 e = normalize(vec3(eye));
	  vec3 h = normalize(lightDir1 + e );
	    float intSpec = max(dot(h,n), 0.0); 
	        spec = specular * pow(intSpec, shininess);
	        }
	else {
	intensity1 = 0;
	}
  }  
  if(intensity2 > 0.0){
  if(use2 > 0.5){
	  vec3 e = normalize(vec3(eye));
	  vec3 h = normalize(lightDir2 + e );
	    float intSpec = max(dot(h,n), 0.0); 
	        spec += specular * pow(intSpec, shininess);
	}
	else {
	intensity2 = 0;
	}
  }

  if(intensity3 > 0.0){
  if(use2 > 0.5){
	  vec3 e = normalize(vec3(eye));
	  vec3 h = normalize(lightDir3 + e );
	    float intSpec = max(dot(h,n), 0.0); 
	        spec += specular * pow(intSpec, shininess);
	}
	else {
	intensity3 = 0;
	}
  }

  vec4 c1 = texture2D(texture, tex);
  vec4 color = max((intensity1 * diffuse + intensity2 * diffuse + spec)*c1, ambient*c1); // All
 //vec4 color = intensity * diffuse; // Only Diffuse  
  frag_color = color;

}
