#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

varying vec2 vTexcoord;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_specular1;

//! [0]
void main()
{
//    gl_FragColor = vec4( texture2D(texture_diffuse1, vTexcoord));
    gl_FragColor = texture2D(texture_diffuse1, vTexcoord);
//    gl_FragColor = mix(texture2D(texture_diffuse1, vTexcoord), texture2D(texture_normal1, vTexcoord), 0.2);
//    gl_FragColor = mix(texture2D(texture_diffuse1, vTexcoord), texture2D(texture_normal1, vTexcoord), texture2D(texture_specular1, vTexcoord));
//    gl_FragColor = vec4(0.5, 0.5, 0.5, 0.5);
}
//! [0]

