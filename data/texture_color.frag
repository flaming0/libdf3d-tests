uniform LOWP sampler2D diffuseMap;

varying LOWP vec2 UV;
varying LOWP vec4 color;

void main()
{
    gl_FragColor = color * texture2D(diffuseMap, UV);
}
