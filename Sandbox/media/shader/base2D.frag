#version 430 core
out vec4 FragColor;

in vec4 vertex_color;
in vec2 fragment_texCoord;
uniform sampler2D texture_default;

void main()
{
    vec3 tex_col = texture(texture_default, fragment_texCoord).rgb;
    FragColor = vertex_color;//vec4(fragment_texCoord, 0.0, 1.0);
}