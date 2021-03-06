in vec4 Position;

uniform mat4 ModelViewProjection;

void main() {
    gl_Position = ModelViewProjection * Position;
}
