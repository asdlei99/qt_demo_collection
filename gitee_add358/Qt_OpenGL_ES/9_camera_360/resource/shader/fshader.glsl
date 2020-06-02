#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

varying vec2 v_texcoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

//! [0]
void main()
{
    // Set fragment color from texture
    gl_FragColor = mix(texture2D(texture1, v_texcoord), texture2D(texture2, v_texcoord), 0.2);
//    gl_FragColor = vec4(0.5, 0.5, 0.5, 1.0);
}
//! [0]

