#version 330 core

layout(location = 0) out vec4 color;
in vec2 texPos;
uniform sampler2D tex;

void main(){
	//color = vec4(1.0, 0.75, 0.0, 1.0);
    color = texture(tex, texPos);
}
