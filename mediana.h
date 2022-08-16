#ifndef MEDIANA_H
#define MEDIANA_H
#include "procesadordeimagen.h"
/**
 * @class Mediana
 * @brief Modela un filtro de mediana, encargada de filtrar una imagen.
 * @details Aplica un filtro llamado filtro de mediana, el cual actua tomando
 *          la mediana de los pixeles vecinos de diferentes pixeles en la imagen
 *          y cambiándoles su intensidad, de forma tal de eliminar el ruido tipo
 *          sal y pimienta de la imagen.
 *          Mantiene los pixeles de la imagen dentro del rango dinamico.
 * @author Cristian Daniel Schmidt
 */
class Mediana : public ProcesadorDeImagen
{
    public:
        /**
        * @brief Mediana Método constructor de la clase Mediana
        */
        Mediana();
        /**
        * @brief aplicar Método de clase base redefinido encargado de aplicar el filtro
        *                de mediana a la imagen recibida como parámetro.
        * @param pImagen Referencia a un objeto de tipo Imagen.
        */
        void aplicar(Imagen &pImagen) override;

        ~ Mediana () override;

    private:
        /**
         * @brief obtenerMedianas Método encargado de obtener las medianas para los
        *                        valores R G y B de los pixeles vecinos.
        * @param pPixelesVecinos Vector de pixeles conteniendo los pixeles vecinos de un pixel.
        * @return Tupla de flotantes con las medianas de los valores R, G y B respectivamente.
        */
        tuple<float, float, float> obtenerMedianas(vector<Pixel> pPixelesVecinos);

};

#endif // MEDIANA_H
