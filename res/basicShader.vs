#version 330 core

in vec3 aPos;
in vec3 aColor;
in vec2 texCoord;

out vec3 ourColor;
out vec2 texCoord0;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
    texCoord0 = texCoord;
}