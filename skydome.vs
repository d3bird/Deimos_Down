#version 330 core
layout (location = 0) in  vec4 vPosition;
layout (location = 1) in  vec4 vNormal;

// output values that will be interpretated per-fragment
out  vec3 fN;
out  vec3 fE;
out  vec3 fL;

uniform mat4 ModelView;  //the model
uniform vec4 LightPosition;
uniform mat4 Projection; //the screen size
uniform mat4 view; // the cam view

uniform float time;
out float iTime;

void main()
{
  fN = vNormal.xyz;
  fE = vPosition.xyz;
  fL = LightPosition.xyz;
    
  //  if(LightPosition.w != 0.0) {
  //    fL = LightPosition.xyz - vPosition.xyz;
  //  }

  gl_Position = Projection * view * ModelView * vPosition;
  //gl_Position = view * ModelView * vPosition;

   iTime = time;
}
