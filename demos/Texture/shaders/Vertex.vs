uniform mat4 projectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;


varying vec3 fragmentNormal;
varying mat4 transform;

void main(void)
{

  fragmentNormal = (ViewMatrix*ModelMatrix*vec4(gl_Normal, 0.0)).xyz;
  transform=projectionMatrix*ViewMatrix*ModelMatrix;
  gl_TexCoord[0] = gl_MultiTexCoord0;

	gl_Position = transform*gl_Vertex;
}
