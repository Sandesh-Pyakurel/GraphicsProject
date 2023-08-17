#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{
    vec3 diffuseColor1 = texture(texture_diffuse1, TexCoords).rgb;
    vec3 diffuseColor2 = texture(texture_diffuse2, TexCoords).rgb;
    vec3 diffuseColor3 = texture(texture_diffuse3, TexCoords).rgb;

    vec3 finalDiffuseColor = (diffuseColor1 + diffuseColor2 + diffuseColor3) / 3.0;
    
    vec3 specularColor1 = texture(texture_specular1, TexCoords).rgb;
    vec3 specularColor2 = texture(texture_specular2, TexCoords).rgb;

    vec3 finalSpecularColor = (specularColor1 + specularColor2) / 2.0;


    vec3 finalColor = finalDiffuseColor + 0.5 * finalSpecularColor;

    FragColor = vec4(finalColor, 1.0);

    // FragColor = texture(texture_diffuse1, TexCoords);
}

