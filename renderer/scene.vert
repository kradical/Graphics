layout(location = SCENE_POSITION_ATTRIB_LOCATION)
in vec4 Position;

layout(location = SCENE_TEXCOORD_ATTRIB_LOCATION)
in vec2 TexCoord;

layout(location = SCENE_NORMAL_ATTRIB_LOCATION)
in vec3 Normal;

out vec4 vertex_position;
out vec2 vertex_texCoord;
out vec3 vertex_normal;
out vec4 shadow_map_coord;

uniform mat4 ModelWorld;
uniform mat4 ModelViewProjection;
uniform mat3 Normal_ModelWorld;
uniform mat4 LightMatrix;

void main()
{
    vertex_texCoord = TexCoord;
    vertex_normal = Normal_ModelWorld * Normal;
    vertex_position = ModelWorld * Position;
    gl_Position = ModelViewProjection * Position;
    shadow_map_coord = LightMatrix * Position;
}