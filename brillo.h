#ifndef BRILLO_H
#define BRILLO_H
#include "procesadordeimagen.h"
/**
 * @class Brillo
 * @brief Modela el brillo, encargada de aumentar o redicir el brillo de una imagen.
 * @details Aplica un ajuste de brillo a una imagen a partir de una intensidad,
 *          ajustando la intensidad de sus pixeles.
 *          Mantiene los pixeles de la imagen dentro del rango dinamico.
 * @author Cristian Daniel Schmidt
 */
class Brillo : public ProcesadorDeImagen
{
    public:
        /**
        * @brief Brillo Constructor de la clase Brillo.
        * @param pUnidades Cantidad (en intensidad) con la cual se ajusta
        *                  (suma o resta) el brillo.
        */
        Brillo(int pUnidades);
        /**
        * @brief aplicar Método de clase base redefinido encargado de aplicar el
        *                ajuste de brillo a la imagen recibida como parámetro.
        * @param pImagen Referencia a un objeto de tipo Imagen.
        */
        void aplicar(Imagen &pImagen) override;

        ~Brillo() override;
    private:
        /**
         * @brief unidades Atributo de tipo entero sin signo con el valor de intensidad
         *                 con el que se ajusta el brillo de la imagen.
         */
        unsigned unidades;
        /**
         * @brief aumentarBrillo Atributo de tipo booleano que determina si se aumenta
         *                       el brillo o se reduce a partir del signo del parámetro
         *                       del Constructor.
         */
        bool aumentarBrillo = true;
};

#endif // BRILLO_H
