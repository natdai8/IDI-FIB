#version 330 core

out vec4 FragColor;
in vec4 fcolor;

void main() {

    // ----------- exercici 1

    /*if (gl_FragCoord.x < 354. && gl_FragCoord.y > 354.)
        FragColor = vec4(1., 0., 0., 1);

    if (gl_FragCoord.x < 354. && gl_FragCoord.y < 354.)
        FragColor = vec4(1., 1., 0., 1);

    if (gl_FragCoord.x > 354. && gl_FragCoord.y > 354.)
        FragColor = vec4(0., 0., 1., 1);

    if (gl_FragCoord.x > 354. && gl_FragCoord.y < 354.)
        FragColor = vec4(0., 1., 0., 1);*/

    // ----------- exercici 2

    // if (int(gl_FragCoord.y) % 20 > 7) discard;

    // ----------- exercici 4

    FragColor = fcolor;

}

