#version 330 core

layout(location = 0) out vec4 color;
in vec2 texPos;
uniform sampler2D tex;

uniform vec4 col;

void main(){
	color = vec4(col);
    //color = texture(tex, texPos);
}
