#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

attribute vec4 aPosition;
attribute vec3 aNormal;
attribute vec2 aTexcoords;

varying vec2 vTexcoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

//! [0]
void main()
{
    vTexcoord = vec2(aTexcoords.x, 1.0 - aTexcoords.y);
    gl_Position = projection * view * model * aPosition;
}
//! [0]
