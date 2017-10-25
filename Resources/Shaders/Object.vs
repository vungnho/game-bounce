
//vertex position
attribute vec2 a_pos;
//texture point
attribute vec2 a_uv;
//variable
varying   vec2 v_uv;
//uniform
uniform   mat4 u_mvp;
//
varying   vec2 v_pos;
uniform   mat4 u_world;

void main()
{
	v_pos = (u_world * vec4(a_pos, 0.0, 1.0)).xy;
	v_uv = a_uv;
	gl_Position = u_mvp * vec4(a_pos, 0.0, 1.0);
}
   
   