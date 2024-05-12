#version 430 core

void main()
{
    vec2 vertices[6] =
    {
        vec2(-0.5,  0.5), //Top Left
        vec2(-0.5, -0.5), //Bottom Left
        vec2( 0.5,  0.5), //TopRight
        vec2( 0.5,  0.5), //TopRight
        vec2(-0.5, -0.5), //Bottom Left
        vec2( 0.5, -0.5)  //Bottom Right`
    };

    gl_Position = vec4(vertices[gl_VertexID], 1.0, 1.0);    
}