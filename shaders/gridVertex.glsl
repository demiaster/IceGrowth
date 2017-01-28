#version 330 core

//first input attribute inis the vertex position

layout (location = 0) in vec3 inVert;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;

//our model / view / project transform
uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 normalMatrix;
out vec4 lightIntensity;
uniform vec3 lightPos = vec3(5, 12, 12);

void main()
{   
    gl_Position = MVP * vec4(inVert, 1.0f);
    vec3 tnorm = normalize(normalMatrix * normal);
    vec4 eyeCoords = MV * vec4(inVert, 1.0);
    vec3 s = normalize(vec3(lightPos - eyeCoords.xyz));
    lightIntensity.rgb = color.rgb * max(dot(s, tnorm), 0.0);
    lightIntensity.a = color.a;
    //lightIntensity.rgb = colorrgb /** max(dot(s, tnorm), 0.0)*/;
    //lightIntensity.a = 1.0;
}
