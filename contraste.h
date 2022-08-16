#ifndef CONTRASTE_H
#define CONTRASTE_H
#include "procesadordeimagen.h"
/**
 * @class Contraste
 * @brief Modela el contraste, encargada de ajustar el contraste de una imagen.
 * @details Aplica un ajuste de contraste a una imagen, extendiendo el rango
 *          de valores de los pixeles entre el mínimo y máximo.
 *          Mantiene los pixeles de la imagen dentro del rango dinamico.
 * @author Cristian Daniel Schmidt
 */
class Contraste : public ProcesadorDeImagen
{
    public:
        /**
        * @brief Contraste Constructor de la clase Contraste.
        */
        Contraste();
        /**
        * @brief aplicar Método de clase base redefinido encargado de aplicar el
        *                ajuste de contraste a la imagen recibida como parámetro.
        * @param pImagen Referencia a un objeto de tipo Imagen.
        */
        void aplicar(Imagen &pImagen) override;

        ~ Contraste() override;
};

#endif // CONTRASTE_H
