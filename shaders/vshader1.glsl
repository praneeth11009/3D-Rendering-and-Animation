#version 330

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

out vec3 normal;
out vec4 eye;
out vec4 COLOR;
out vec4 pos;
out float use1;
out float use2;

uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;
uniform float on1;
uniform float on2;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  normal = (normalMatrix * normalize(vNormal)); 
  eye = - (uModelViewMatrix * gl_Position); 
  COLOR = vColor; 
  pos = vPosition;
  use1 = on1;
  use2 = on2;
 }
