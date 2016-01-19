precision highp float;

varying vec2 v_srcCoord;
uniform float nbrOfObjects;
//uniform mat4x4 u_transform; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
uniform sampler2D s_srcTex;


vec4 cross(vec4 x, vec4 y){
	return vec4(cross(x.xyz,y.xyz),1.0);
}


void main(){

	// The texture should have data like this:
	// 4xorigo, 4xvec1, 4xvec2, 4xvec3, hl1, hl2, hl3, 0
	
	float texSize = nbrOfObjects*5.0;
	float one =   1.0/texSize;  //1*4
	float two =   2.0/texSize;  //2*4
	float three = 3.0/texSize; //3*4
	float four =  4.0/texSize; //4*4
	
	float halfTexel = 0.5/(nbrOfObjects*5.0);
	
	// Obj1:
	
	float obj1TexCoord = v_srcCoord.s - 0.5/nbrOfObjects + halfTexel;
	
	vec4 obj1Origin = texture2D(s_srcTex,vec2(obj1TexCoord,0.0));
	vec4 obj1vec1 = texture2D(s_srcTex,vec2(obj1TexCoord+one,0.0));
	vec4 obj1vec2 = texture2D(s_srcTex,vec2(obj1TexCoord+two,0.0));
	vec4 obj1vec3 = texture2D(s_srcTex,vec2(obj1TexCoord+three,0.0));
	vec4 obj1hls = texture2D(s_srcTex,vec2(obj1TexCoord+four,0.0));
	float obj1hl1 = obj1hls.x;
	float obj1hl2 = obj1hls.y;
	float obj1hl3 = obj1hls.z;
	
	// Obj2:
	
	float obj2TexCoord = v_srcCoord.t - 0.5/nbrOfObjects + halfTexel;
	
	vec4 obj2Origin = texture2D(s_srcTex,vec2(0.0,obj2TexCoord));
	vec4 obj2vec1 = texture2D(s_srcTex,vec2(one,obj2TexCoord));
	vec4 obj2vec2 = texture2D(s_srcTex,vec2(two,obj2TexCoord));
	vec4 obj2vec3 = texture2D(s_srcTex,vec2(three,obj2TexCoord));
	vec4 obj2hls = texture2D(s_srcTex,vec2(four,obj2TexCoord));
	float obj2hl1 = obj2hls.x;
	float obj2hl2 = obj2hls.y;
	float obj2hl3 = obj2hls.z;
	
	
	
	vec4 t = obj1Origin - obj2Origin;
	
	
	// Use obj1's basis vectors as separating axes
	vec4 l = obj1vec1;
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	l = obj1vec2;
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	l = obj1vec3;
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	// Use obj2's basis vectors as separating axes
	l = obj2vec1;
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	l = obj2vec2;
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	l = obj2vec3;
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	
	
	// Use the planes of axiscombinations as separating axes
	
	l = cross(obj1vec1,obj2vec1);
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	l = cross(obj1vec1,obj2vec2);
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	l = cross(obj1vec1,obj2vec3);
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	l = cross(obj1vec2,obj2vec1);
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	l = cross(obj1vec2,obj2vec2);
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	l = cross(obj1vec2,obj2vec3);
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	l = cross(obj1vec3,obj2vec1);
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	l = cross(obj1vec3,obj2vec2);
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	l = cross(obj1vec3,obj2vec3);
	
	if(length( dot((obj1vec1*obj1hl1+obj1vec2*obj1hl2+obj1vec3*obj1hl3),l) + dot((obj2vec1*obj2hl1+obj2vec2*obj2hl2+obj2vec3*obj2hl3),l) ) < length(dot(t,l))){
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
		return;
	}
	
	gl_FragColor = vec4(1.0,1.0,1.0,1.0);
	
	
	// Glom inte att satta
	//gl_FragColor = ????????????????????
}


