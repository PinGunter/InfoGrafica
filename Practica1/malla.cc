#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram)
{
    GLuint id_vbo;
    glGenBuffers(1, &id_vbo);
    glBindBuffer(tipo_vbo, id_vbo);

    glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);
    //    glBindBuffer(tipo_vbo,0);
    return id_vbo;
}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(GLenum modo_dibujado)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, c.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v.data());
    glPolygonMode(GL_FRONT, modo_dibujado);
    glPointSize(5);
    glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data());
    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(GLenum modo_dibujado)
{
    if (id_vbo_vertices == 0)
    {
        id_vbo_vertices = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * v.size(), v.data());
    }

    if (id_vbo_tri == 0)
    {
        id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 3 * f.size(), f.data());
    }

    if (id_vbo_color == 0)
    {
        id_vbo_color = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c.size(), c.data());
    }
    glBindBuffer(GL_ARRAY_BUFFER, id_vbo_vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);

    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glPolygonMode(GL_FRONT, modo_dibujado);
    glPointSize(5);
    glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int modo_visualizacion, bool dibuja_diferido)
{
    GLenum modo;
    switch(modo_visualizacion){
        case (int)GL_POINT: //GL_POINT
            modo = GL_POINT;
            break;
        case (int)GL_LINE: //GL_LINE
            modo = GL_LINE;
            break;
        case (int)GL_FILL: //GL_FILL
            modo = GL_FILL;
            break;
        case 3: //AJEDREZ
            modo = GL_FILL;
            break;
    }
    if (dibuja_diferido){
        if (modo_visualizacion != 3){
            draw_ModoDiferido(modo);
        } else draw_AjedrezDiferido();
    } else {
        if (modo_visualizacion != 3){
            draw_ModoInmediato(modo);
        } else draw_AjedrezInmediato();
    }
}

void Malla3D::draw_AjedrezDiferido() {

}

void Malla3D::draw_AjedrezInmediato() {

}

