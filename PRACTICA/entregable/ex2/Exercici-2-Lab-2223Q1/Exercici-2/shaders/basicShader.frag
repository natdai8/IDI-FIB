#version 330 core

in vec3 fcolor;

out vec4 FragColor;

uniform int mortyNormal;

void main() {

    if (mortyNormal == 1) FragColor = vec4(fcolor, 1);
    else FragColor = vec4(fcolor, 1) * vec4(1, 0, 0, 1);

}

