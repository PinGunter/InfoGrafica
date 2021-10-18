#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );
   id_vbo_tri = id_vbo_vertices = id_vbo_color_v = id_vbo_color_a = id_vbo_color_c = id_vbo_color_aj = 0;
   for (int i = 0; i < v.size(); i++)
    {
        c_vert.push_back(Tupla3f(0,1,0));
        c_aris.push_back(Tupla3f(1,0,0));
        c_cara.push_back(Tupla3f(0,0,1));
        c_ajedrez.push_back(Tupla3f(1, 0.24, 0.71));
    }
}


