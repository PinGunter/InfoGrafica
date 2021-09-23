#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#define true 1
#define V_PENTAGONO 5

//vertices
float vA[] = {0,0};
float vB[] = {0.95, 0.309};
float vC[] = {0,1};
float vD[] = {-0.95, 0.309};
float vE[] = {-0.58, -0.707};
float vF[] = {0.58, -0.707};


float vertices_fan [] = {0,0,0.95,0.309,0,1,-0.95,0.309,-0.58,-0.707,0.58,-0.707,0.95,0.309};

float vertices[30];

void generarVertices(){
    int i=0;
    vertices[i++] = vA[0]; vertices[i++] = vA[1];
    vertices[i++] = vB[0]; vertices[i++] = vB[1];
    vertices[i++] = vC[0]; vertices[i++] = vC[1];

    vertices[i++] = vA[0]; vertices[i++] = vA[1];
    vertices[i++] = vC[0]; vertices[i++] = vC[1];
    vertices[i++] = vD[0]; vertices[i++] = vD[1];

    vertices[i++] = vA[0]; vertices[i++] = vA[1];
    vertices[i++] = vD[0]; vertices[i++] = vD[1];
    vertices[i++] = vE[0]; vertices[i++] = vE[1];

    vertices[i++] = vA[0]; vertices[i++] = vA[1];
    vertices[i++] = vE[0]; vertices[i++] = vE[1];
    vertices[i++] = vF[0]; vertices[i++] = vF[1];

    vertices[i++] = vA[0]; vertices[i++] = vA[1];
    vertices[i++] = vF[0]; vertices[i++] = vF[1];
    vertices[i++] = vB[0]; vertices[i++] = vB[1];
}

float colores_aristas[]  = {
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0

};


float colores_vertices[]  = {
        0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0,
        0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0
};


float color_relleno[]  = {
        0,0,1,
        0,0,1,
        0,0,1,

        0,0,1,
        0,0,1,
        0,0,1,

        0,0,1,
        0,0,1,
        0,0,1,

        0,0,1,
        0,0,1,
        0,0,1,

        0,0,1,
        0,0,1,
        0,0,1
};
//calcular los vertices del pentagono regular

void dibuja() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices_fan);

    glLineWidth(3);
    glPointSize(15);

    glColorPointer(3,GL_FLOAT, 0, colores_vertices);
    glPolygonMode(GL_FRONT, GL_POINT);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 7);

    glColorPointer(3,GL_FLOAT, 0, colores_aristas);
    glPolygonMode(GL_FRONT, GL_LINE);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 7);

    glColorPointer(3,GL_FLOAT, 0, color_relleno);
    glPolygonMode(GL_FRONT, GL_FILL);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 7);

    glutSwapBuffers();
}

int main (int argc, char * argv[]){
    generarVertices();
    int j=0;
    for (int i=0; i < 30; i+=2){
        printf("%f, %f \n", vertices[i],vertices[i+1]);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(800,800);
    glutCreateWindow("Ejemplo");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(dibuja);
    glutMainLoop();
    return(true);
}

