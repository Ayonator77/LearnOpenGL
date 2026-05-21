#version 330 core

layout (location = 0) in vec3 aPos; // the possition variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

out vec3 ourColor; // output a color to the fragment shader
uniform vec4 transVec;

void main() {
    gl_Position = transVec + vec4(aPos, 1.0);
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
}