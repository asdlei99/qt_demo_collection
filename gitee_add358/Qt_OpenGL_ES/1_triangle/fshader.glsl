#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//! [0]
void main()
{
    // Set fragment color from texture
    gl_FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
//! [0]

