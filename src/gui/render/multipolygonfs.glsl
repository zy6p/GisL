#version 330 core
in vec4 ourColor;
out vec4 fColor;
void main() {
    fColor = vec4(ourColor);
}
