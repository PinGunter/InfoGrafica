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

void Malla3D::draw_ModoInmediato(bool puntos, bool alambre, bool solido)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v.data());
    glPointSize(8);
    glLineWidth(5);
    if (puntos)
    {
        glColorPointer(3, GL_FLOAT, 0, c_vert.data());
        glPolygonMode(GL_FRONT, GL_POINT);
        glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data());
    }
    if (alambre)
    {
        glColorPointer(3, GL_FLOAT, 0, c_aris.data());
        glPolygonMode(GL_FRONT, GL_LINE);
        glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data());
    }
    if (solido)
    {
        glColorPointer(3, GL_FLOAT, 0, c_cara.data());
        glPolygonMode(GL_FRONT, GL_FILL);
        glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data());
    }
    glLineWidth(1);
    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(bool puntos, bool alambre, bool solido)
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
        id_vbo_color = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_vert.size(), c_vert.data());
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

    glPolygonMode(GL_FRONT, GL_LINE);
    glPointSize(5);
    glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(bool dibuja_diferido, bool puntos, bool alambre, bool solido, bool ajedrez)
{
    if (dibuja_diferido)
    {
        if (ajedrez) draw_AjedrezDiferido();
        else draw_ModoDiferido(puntos,alambre,solido);
    } else
    {
        if (ajedrez) draw_AjedrezInmediato();
        else draw_ModoInmediato(puntos,alambre,solido);
    }
}

void Malla3D::draw_AjedrezDiferido() {

}

void Malla3D::draw_AjedrezInmediato() {

}

