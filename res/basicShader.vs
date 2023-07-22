#version 330 core

in vec3 aPos;
in vec3 aColor;
in vec2 texCoord;

out vec3 ourColor;
out vec2 texCoord0;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
    texCoord0 = texCoord;
}