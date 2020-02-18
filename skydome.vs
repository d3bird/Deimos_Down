attribute   vec4 vPosition;
attribute   vec4 vNormal;

// output values that will be interpretated per-fragment
varying  vec3 fN;
varying  vec3 fE;
varying  vec3 fL;

uniform mat4 ModelView;  //the model
uniform vec4 LightPosition;
uniform mat4 Projection; //the screen size
uniform mat4 view; // the cam view

void main()
{
  fN = vNormal.xyz;
  fE = vPosition.xyz;
  fL = LightPosition.xyz;
    
  //  if(LightPosition.w != 0.0) {
  //    fL = LightPosition.xyz - vPosition.xyz;
  //  }

  gl_Position = Projection * view * ModelView * vPosition;
   // gl_Position = vPosition;
}
