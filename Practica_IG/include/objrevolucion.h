// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include <aux.h>
#include <malla.h>

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
public:
       ObjRevolucion();
       ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_inf=true, bool tapa_sup=true) ;
       ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_inf=true, bool tapa_sup=true) ;
protected:
    std::vector<Tupla3f> perfil_original;
    std::vector<Tupla3f> v_ejes;
    Tupla3f vt_inf, vt_sup;
    void init();
    void crearTapas(bool inf, bool sup, int num_instancias);
    void multMatVec(double m[][3], float * v, float *r);
    Tupla3f rotarVertice(float alpha, float beta, float phi, const Tupla3f & vertice);
    void normalizarPerfil();
    void crearVertices(const std::vector<Tupla3f> & perfil_original,
                       const int                    num_instancias_perf);
    void crearMalla(const std::vector<Tupla3f> & perfil_original,
                    const int                    num_instancias_perf,
                    bool                         tapa_inf,
                    bool                         tapa_sup);

} ;




#endif
