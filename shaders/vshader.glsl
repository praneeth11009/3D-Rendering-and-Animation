#version 330

in vec4 vPosition;
in vec2 texCoord;
in vec4 vNormal;

out vec4 eye;
out vec2 tex;
out vec3 normal;
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
  vec3 vn = vNormal.xyz;
  normal = (normalMatrix * normalize(vn)); 
  eye = -gl_Position; 
  tex = texCoord; 
  pos = vPosition;
  use1 = on1;
  use2 = on2;
}


