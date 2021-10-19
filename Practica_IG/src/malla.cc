#include "../include/aux.h"
#include "../include/malla.h"

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
        glBindBuffer(tipo_vbo,0);
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
//    glLineWidth(5);
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
    //volvemos al tamaño de linea predeterminado para que los ejes no se vean muy anchos
    glLineWidth(1);
    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(bool puntos, bool alambre, bool solido)
{
    //Creacion de VBOs
    if (id_vbo_vertices == 0)
    {
        id_vbo_vertices = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * v.size(), v.data());
    }

    if (id_vbo_tri == 0)
    {
        id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 3 * f.size(), f.data());
    }
    //VBOs de los vectores de colores
    if (id_vbo_color_v == 0)
    {
        id_vbo_color_v = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_vert.size(), c_vert.data());
    }
    if (id_vbo_color_a== 0)
    {
        id_vbo_color_a = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_aris.size(), c_aris.data());
    }
    if (id_vbo_color_c == 0)
    {
        id_vbo_color_c = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_cara.size(), c_cara.data());
    }

    glBindBuffer(GL_ARRAY_BUFFER, id_vbo_vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glPointSize(8);
//    glLineWidth(5);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
    glEnableClientState(GL_COLOR_ARRAY);

    if (puntos){
        glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_v);
        glColorPointer(3, GL_FLOAT, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glPolygonMode(GL_FRONT, GL_POINT);
        glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0);
    }
    if (alambre){
        glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_a);
        glColorPointer(3, GL_FLOAT, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glPolygonMode(GL_FRONT, GL_LINE);
        glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0);
    }
    if (solido){
        glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_c);
        glColorPointer(3, GL_FLOAT, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0);
    }
    //volvemos al tamaño de linea predeterminado para que los ejes no se vean muy anchos
    glLineWidth(1);
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
        if (ajedrez) draw_AjedrezDiferido(puntos,alambre,solido);
        else draw_ModoDiferido(puntos,alambre,solido);
    } else
    {
        if (ajedrez) draw_AjedrezInmediato(puntos,alambre,solido);
        else draw_ModoInmediato(puntos,alambre,solido);
    }
}

void Malla3D::draw_AjedrezDiferido(bool puntos, bool alambre, bool solido) {
//Creacion de VBOs
    if (id_vbo_vertices == 0)
    {
        id_vbo_vertices = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * v.size(), v.data());
    }

    if (id_vbo_tri == 0)
    {
        id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 3 * f.size(), f.data());
    }
    // vbos de los vectores de colores
    if (id_vbo_color_v == 0)
    {
        id_vbo_color_v = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_vert.size(), c_vert.data());
    }
    if (id_vbo_color_a== 0)
    {
        id_vbo_color_a = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_aris.size(), c_aris.data());
    }
    if (id_vbo_color_c == 0)
    {
        id_vbo_color_c = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_cara.size(), c_cara.data());
    }
    if (id_vbo_color_aj == 0)
    {
        id_vbo_color_aj = CrearVBO(GL_ARRAY_BUFFER,sizeof(float) * 3 * c_ajedrez.size(), c_ajedrez.data());
    }
    glBindBuffer(GL_ARRAY_BUFFER, id_vbo_vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glPointSize(8);
//    glLineWidth(5);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
    glEnableClientState(GL_COLOR_ARRAY);

    // dibujado segun los modos de visualizacion
    if (puntos){
        glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_v);
        glColorPointer(3, GL_FLOAT, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glPolygonMode(GL_FRONT, GL_POINT);
        glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0);
    }
    if (alambre){
        glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_a);
        glColorPointer(3, GL_FLOAT, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glPolygonMode(GL_FRONT, GL_LINE);
        glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0);
    }
    // como es el modo ajedrez, en el modo solido dibujamos 2 veces
    // una con las caras pares (la primera mitad) y otra vez
    // con las caras impares (la segunda mitad)
    if (solido){
        //un color
        glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_c);
        glColorPointer(3, GL_FLOAT, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glDrawElements(GL_TRIANGLES, (f.size()/2) * 3, GL_UNSIGNED_INT, 0);

        // el otro
        glBindBuffer(GL_ARRAY_BUFFER, id_vbo_color_aj);
        glColorPointer(3, GL_FLOAT, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glDrawElements(GL_TRIANGLES, (f.size()/2) * 3, GL_UNSIGNED_INT, (void *) (sizeof(float) * 3 * (f.size()/2)));
    }

    //volvemos al tamaño de linea predeterminado para que los ejes no se vean muy anchos
    glLineWidth(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Malla3D::draw_AjedrezInmediato(bool puntos, bool alambre, bool solido) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v.data());
    glPointSize(8);
//    glLineWidth(5);
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
    // como es el modo ajedrez, en el modo solido dibujamos 2 veces
    // una con las caras pares (la primera mitad) y otra vez
    // con las caras impares (la segunda mitad)
    if (solido)
    {
        //un color
        glColorPointer(3, GL_FLOAT, 0, c_cara.data());
        glPolygonMode(GL_FRONT, GL_FILL);
        glDrawElements(GL_TRIANGLES, (f.size()/2) * 3, GL_UNSIGNED_INT, f.data());

        // el otro
        glColorPointer(3, GL_FLOAT, 0, c_ajedrez.data());
        glPolygonMode(GL_FRONT, GL_FILL);
        glDrawElements(GL_TRIANGLES, (f.size()/2) * 3, GL_UNSIGNED_INT, f[f.size()/2]);
    }
    //volvemos al tamaño de linea predeterminado para que los ejes no se vean muy anchos
    glLineWidth(1);
    glDisableClientState(GL_VERTEX_ARRAY);
}

