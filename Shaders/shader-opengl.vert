#version 330 core

struct Camera
{
	mat4 viewProjection;
};

struct Instance
{
	mat4 model;
};

uniform Camera camera;
uniform Instance instance;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

out vec3 fragColor;
out vec2 fragTexCoord;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    gl_Position = camera.viewProjection * instance.model * vec4(inPosition, 1.0);
    fragColor = inColor;
	fragTexCoord = inTexCoord;
}
