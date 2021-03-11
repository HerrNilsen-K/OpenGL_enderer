#version 330 core

layout(location = 0) in vec2 position;
uniform mat4 pos;

void main(){
	gl_Position =   pos * vec4(position, 0, 1);
}