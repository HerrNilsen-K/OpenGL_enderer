#version 330 core

layout(location = 0) out vec4 color;
in vec2 texPos;
uniform sampler2D tex;
uniform sampler2D tex2;

void main(){
	//color = vec4(1.0, 0.75, 0.0, 1.0);
    color = mix(texture(tex, texPos), texture(tex2, texPos), 0.5);
}
