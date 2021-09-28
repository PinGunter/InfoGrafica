#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){
    GLuint id_vbo;
    glGenBuffers(1, & id_vbo);
    glBindBuffer(tipo_vbo,id_vbo);

    glBufferData(tipo_vbo,tamanio_bytes,puntero_ram,GL_STATIC_DRAW);
    glBindBuffer(tipo_vbo,0);
    return id_vbo;
}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3,GL_FLOAT,0,c.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,v.data());
    glPolygonMode(GL_FRONT,GL_LINE);
    glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
    if (id_vbo_vertices == 0){
        id_vbo_vertices = CrearVBO(GL_ARRAY_BUFFER,v.size()*3,v.data());
    }

    if (id_vbo_tri == 0){
        id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,f.size()*3,v.data());
    }

    glBindBuffer(GL_ARRAY_BUFFER,id_vbo_vertices);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
    glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw()
{
//    draw_ModoDiferido();
draw_ModoInmediato();
   // completar .....(práctica 1)

}

