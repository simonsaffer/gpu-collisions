attribute vec4 a_position;
attribute vec2 a_texCoord;
varying vec2 v_srcCoord;

void main(){
	gl_Position = a_position;
	v_srcCoord=a_texCoord;
}      