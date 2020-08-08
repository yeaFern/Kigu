#version 330

layout (location = 0) in vec3 v_Position;
layout (location = 1) in vec3 v_Color;

uniform mat4 u_Projection = mat4(1.0);
uniform mat4 u_View = mat4(1.0);
uniform mat4 u_Model = mat4(1.0);

out vec3 pass_Color;

void main()
{
	pass_Color = v_Color;

	gl_Position = u_Projection * u_View * vec4(v_Position, 1.0);
}
