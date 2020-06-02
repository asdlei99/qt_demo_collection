#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

attribute vec4 a_position;
attribute vec3 a_color;

varying vec3 v_color;

//! [0]
void main()
{
    gl_Position = a_position;
    v_color = a_color;
}
//! [0]
