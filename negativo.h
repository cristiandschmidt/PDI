#ifndef NEGATIVO_H
#define NEGATIVO_H
#include "procesadordeimagen.h"
/**
 * @class Negativo
 * @brief Modela un negativo, encargada de generar el negativo de la imagen.
 * @details Aplica un negativo a una imagen, ajustando la intensidad de sus
 *          pixeles como la diferencia entre el maximo del rango y el valor del pixel.
 *          Mantiene los pixeles de la imagen dentro del rango dinamico.
 * @author Cristian Daniel Schmidt
 */
class Negativo : public ProcesadorDeImagen
{
    public:
        /**
        * @brief Negativo Constructor de la clase Negativo
        */
        Negativo();
        /**
        * @brief aplicar Método de clase base redefinido encargado de aplicar el negativo
        *                a la imagen recibida como parámetro.
        * @param pImagen Referencia a un objeto de tipo Imagen.
        */
        void aplicar(Imagen &pImagen) override;

        ~ Negativo() override;
};

#endif // NEGATIVO_H
