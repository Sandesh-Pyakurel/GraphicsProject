#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord0;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    // FragColor = texture(texture0, texCoord0) * vec4(ourColor, 1.0);
    FragColor = mix(texture(texture0, texCoord0), texture(texture1, texCoord0), 0.4);
}
