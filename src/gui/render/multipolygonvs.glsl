#version 330 core
layout(location = 0) in vec2 inVertex;
uniform mediump mat4 matrix;
uniform vec4 inColor;
out vec4 ourColor;
void main() {
    ourColor = inColor;
    gl_Position = matrix * vec4(inVertex, 0.0f, 1.0f);
}
