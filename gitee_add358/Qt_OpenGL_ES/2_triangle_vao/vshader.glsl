#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

attribute vec4 a_position;

//! [0]
void main()
{
    gl_Position = a_position;
}
//! [0]
