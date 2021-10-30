#include <objply.h>
#include <ply_reader.h>
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );
   inicializar(Tupla3f(0,1,0),
                   Tupla3f(1,0,0),
                   Tupla3f(0,0,1),
                   Tupla3f(1, 0.24, 0.71));
}


