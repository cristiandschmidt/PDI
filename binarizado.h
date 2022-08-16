#ifndef BINARIZADO_H
#define BINARIZADO_H
#include "procesadordeimagen.h"
#include "procesadordeimagen.h"
/**
 * @class Binarizado
 * @brief Modela un binarizado, encargada de binarizar una imagen.
 * @details Aplica un binarizado a una imagen a partir de una intensidad,
 *          ajustando la intensidad de sus pixeles a dos únicos valores posibles.
 *          Mantiene los pixeles de la imagen dentro del rango dinamico.
 * @author Cristian Daniel Schmidt
 */
class Binarizado : public ProcesadorDeImagen
{
    public:
        /**
        * @brief Binarizado Constructor de la clase Binarizado.
        * @param pValorBinarizado Valor de intensidad a partir del cual se realiza el binarizado.
        */
        Binarizado(unsigned pValorBinarizado);
        /**
        * @brief aplicar Método de clase base redefinido encargado
        *                de aplicar el binarizado a la imagen recibida como parámetro.
        * @param pImagen Referencia a un objeto de tipo Imagen.
        */
        void aplicar(Imagen &pImagen) override;

        ~Binarizado() override;
    private:
        /**
         * @brief valorBinarizado Atributo de tipo entero sin signocon el valor de
         *                        intensidad a partir del cual se binariza la imagen.
         */
        unsigned valorBinarizado;
};

#endif // BINARIZADO_H
