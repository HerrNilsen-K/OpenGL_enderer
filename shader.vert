#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 aTexPos;

uniform mat4 model;
uniform mat4 view;

out vec2 texPos;

void main(){
	gl_Position =   view * model * vec4(position, 0, 1);
	texPos = aTexPos;
}