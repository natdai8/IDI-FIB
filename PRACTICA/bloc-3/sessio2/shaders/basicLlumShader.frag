#version 330 core

// in vec3 fcolor;
out vec4 FragColor;

in vec4 vertexSCO;
in vec3 normalSCO;

in vec3 matambF;
in vec3 matdiffF;
in vec3 matspecF;
in float matshinF;

uniform vec3 colorFocus;
uniform int escena; // escena o cámara
uniform vec3 posFocus;
uniform mat4 view;


vec3 llumAmbient = vec3(0.2, 0.2, 0.2);

vec3 Ambient() {
    return llumAmbient * matambF;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdiffF * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus)
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (matshinF == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular

    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), matshinF);
    return (matspecF * colFocus * shine);
}

void main()
{
  // calcular posFocus en SCO (si cal)
    vec4 posFocusSCO;
	if (escena == 1) posFocusSCO = view * vec4(posFocus, 1.0);
	else posFocusSCO = vec4(0.0, 0.0, 0.0, 1.0);

	// calcular L en SCO
    vec3 LSCO = posFocusSCO.xyz - vertexSCO.xyz;

    // normalitzar vectors
    vec3 L = normalize(LSCO);
    vec3 n = normalize(normalSCO);

    vec3 fcolor = Ambient() + Difus(n, L, colorFocus) + Especular(n, L, vertexSCO, colorFocus);

	FragColor = vec4(fcolor,1);
}
