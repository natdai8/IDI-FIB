#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;
in vec4 vertexSCO;
in vec3 normalSCO;

const vec3 llumAmbient = vec3(0.1, 0.1, 0.1);

uniform mat4 TG;
uniform mat4 Proj;
uniform mat4 View;
uniform mat4 TGM;

uniform vec3 posFocus1;
uniform vec3 posFocus2;
uniform vec3 posFocus3;
uniform vec3 posFocus4;
uniform vec3 colorFocus;

uniform vec3 posFocusM;
uniform vec3 colorFocusM;

out vec4 FragColor;


vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus)
{
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main()
{
    vec4 posFocusSCO1, posFocusSCO2, posFocusSCO3, posFocusSCO4, posFocusSCOM;
    posFocusSCO1 = View * vec4(posFocus1, 1.0);
    posFocusSCO2 = View * vec4(posFocus2, 1.0);
    posFocusSCO3 = View * vec4(posFocus3, 1.0);
    posFocusSCO4 = View * vec4(posFocus4, 1.0);
    posFocusSCOM = View * TGM * vec4(posFocusM, 1.0);

    vec3 LSCO1 = posFocusSCO1.xyz - vertexSCO.xyz;
    vec3 LSCO2 = posFocusSCO2.xyz - vertexSCO.xyz;
    vec3 LSCO3 = posFocusSCO3.xyz - vertexSCO.xyz;
    vec3 LSCO4 = posFocusSCO4.xyz - vertexSCO.xyz;
    vec3 LSCOM = posFocusSCOM.xyz - vertexSCO.xyz;

    vec3 L1 = normalize(LSCO1);
    vec3 L2 = normalize(LSCO2);
    vec3 L3 = normalize(LSCO3);
    vec3 L4 = normalize(LSCO4);
    vec3 LM = normalize(LSCOM);

    vec3 n = normalize(normalSCO);

    vec3 fcolor = Ambient() +
                  Difus(n, L1, colorFocus) + Difus(n, L2, colorFocus) +
                  Difus(n, L3, colorFocus) + Difus(n, L4, colorFocus) +
                  Difus(n, LM, colorFocusM) +
                  Especular(n, L1, vertexSCO, colorFocus) +
                  Especular(n, L2, vertexSCO, colorFocus) +
                  Especular(n, L3, vertexSCO, colorFocus) +
                  Especular(n, L4, vertexSCO, colorFocus) +
                  Especular(n, LM, vertexSCO, colorFocusM);


    FragColor = vec4(fcolor, 1);
}
