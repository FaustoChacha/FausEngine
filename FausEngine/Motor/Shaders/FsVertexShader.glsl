#version 330 core

//orden en la inicializacion de buffers! (Mesh.h)
layout (location = 0) in vec3 position;			
layout (location = 1) in vec3 normal;	
layout (location = 2) in vec2 texture;

uniform mat4 model;			
uniform mat4 view;			
uniform mat4 projection;	

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    gl_Position = projection * view *  model * vec4(position, 1.0f);	
    Normal = mat3(transpose(inverse(model))) * normal;	
	TexCoord = texture;
		
	FragPos = vec3(model * vec4(position, 1.0f));	
}