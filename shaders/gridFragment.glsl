# version 330 core

layout (location = 0) out vec4 fragColor;
uniform vec4 color;
in vec3 lightIntensity;
void main()
{
    //set everything to white
    fragColor.rgb = lightIntensity;
}
