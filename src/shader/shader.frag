#version 450 core

layout(location = 0) out vec4 color;
uniform vec4 col;
uniform vec2 centre;

void inCircle(vec2 pos, float radius) {
    const vec2 cent = centre;
    if (distance(pos, cent) > radius)
        discard;
}

void main(){
    vec2 pos = gl_FragCoord.xy / vec2(600, 600);
    const float radius = 0.05;

    inCircle(pos, radius);

    color = vec4(col);
}
