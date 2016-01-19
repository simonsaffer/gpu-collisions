precision highp float;

varying vec2 v_srcCoord;
uniform sampler2D s_srcTex;

void main(){
	
	vec2 obj1Coord=vec2(0.0,v_srcCoord.s);
	vec4 obj1=texture2D(s_srcTex,obj1Coord);

	vec2 obj2Coord=vec2(v_srcCoord.t,0.0);
	vec4 obj2=texture2D(s_srcTex,obj2Coord);
	
	float dist=distance(obj1.xyz,obj2.xyz);
	
	float rad=clamp(dist-(obj1.w+obj2.w),0.0,1.0);
	
	if(rad==0.0){
		gl_FragColor = vec4(1.0);
	}else{
		gl_FragColor = vec4(0.0);
	}
}