attribute vec3 a_vertex3;
attribute vec2 a_txCoord;

uniform mat4 u_worldViewProjectionMatrix;
uniform LOWP vec4 material_diffuse;

varying LOWP vec2 UV;
varying LOWP vec4 color;

void main()
{
    color = material_diffuse;
    gl_Position = u_worldViewProjectionMatrix * vec4(a_vertex3, 1.0);
    UV = a_txCoord;
}
