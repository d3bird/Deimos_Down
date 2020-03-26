#version 330
attribute vec4 vPosition;
//attribute vec4 vColor;
varying vec4 color2;

uniform mat4 Projection;
uniform mat4 model_trans;
uniform mat4 model_view;


uniform vec4 objColor;

void main() 
{

	vec4 temp;
  
	  temp.x = (1.0/1000.0)*(vPosition.x );
	  temp.y = (1.0/1000.0)*(vPosition.y );
	  temp.z = (1.0/1000.0)*(vPosition.z );
	  temp.w =1;


	  //gl_Position =Projection* model_view  * ((temp ));
	  gl_Position =Projection* model_view * model_trans * ((temp ));
	  //gl_Position = temp;
  
  //if(vPosition.x == 135 || vPosition.y == 135 || vPosition.z == 135 ){
  if((vPosition.x >= 0 && vPosition.x <=135) && (vPosition.z >= 0 && vPosition.z <=135 )  ){
	color2= vec4(1.0, 0.0, 0.0, 1.0);
  }else{
	color2 = objColor;
  }
} 