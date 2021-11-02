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

class ObjRevolucion : public Malla3D {
public:
    ObjRevolucion();
    ObjRevolucion(const std::string &archivo, Eje_rotacion eje, int num_instancias, bool tapa_inf = true, bool tapa_sup = true);
    ObjRevolucion(std::vector<Tupla3f> archivo, Eje_rotacion eje, int num_instancias, bool tapa_inf = true, bool tapa_sup = true);
    void draw_ModoInmediato(GLuint modo, std::vector<Tupla3f> *color, bool tapas) override;
    void draw_AjedrezInmediato(GLuint modo, std::vector<Tupla3f> *color, bool tapas) override;

    void draw_ModoDiferido(GLuint modo, GLuint color_id, bool tapas) override;
    void draw_AjedrezDiferido(GLuint modo, GLuint color_id, bool tapas) override;

    bool esObjRevolucion();

protected:
    std::vector<Tupla3f> perfil_original;
    std::vector<Tupla3f> v_ejes;
    Tupla3f vt_inf, vt_sup;
    unsigned long offset_tapas;
    Eje_rotacion mi_eje;
    void init();
    bool comparaEpsilon(float a, float b, float e) const;
    bool esEjeRotacion(Tupla3f t) const;
    virtual void crearTapas(bool inf, bool sup, int num_instancias);
    void multMatVec(double m[][3], float *v, float *r);
    Tupla3f rotarVertice(float alpha, float beta, float phi, const Tupla3f &vertice);
    void normalizarPerfil();
    void crearVertices(const std::vector<Tupla3f> &perfil_original,
                       const int num_instancias_perf);
    void crearMalla(const std::vector<Tupla3f> &perfil_original,
                    const int num_instancias_perf,
                    bool tapa_inf,
                    bool tapa_sup);

    void mezclaVector() override;
};


#endif
