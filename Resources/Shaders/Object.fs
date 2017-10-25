precision mediump float;

uniform sampler2D u_texture;
uniform   mat4 u_mvp;
uniform vec2 u_tile;
uniform vec3 u_EyePos;
varying vec2 v_pos;
varying vec2 v_uv;




void main()
{
	vec4 texelColor = texture2D(u_texture, v_uv*u_tile);

	gl_FragColor = texelColor;
	
}
