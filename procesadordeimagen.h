#ifndef PROCESADORDEIMAGEN_H
#define PROCESADORDEIMAGEN_H
#include <tuple>
#include <algorithm>
#include <math.h>
#include "imagen.h"
/**
 * @class ProcesadorDeImagen
 * @brief Modela un procesador de imagen general que permite aplicar modificaciones a la imagen.
 * @details Realiza un procesamiento en la imagen que se encuentra siendo analizada.
 * @author Cristian Daniel Schmidt
 */
class ProcesadorDeImagen
{
    public:
        /**
        * @brief ProcesadorDeImagen Constructor de la clase ProcesadorDeImagen
        */
        ProcesadorDeImagen();
        /**
        * @brief abrir Método virtualizado encargado procesar la imagen que se recibe como parametro.
        * @param pImagen  Referencia a un objeto de tipo Imagen.
        */
        virtual void aplicar(Imagen &pImagen) = 0;

        virtual ~ProcesadorDeImagen();
};

#endif // PROCESADORDEIMAGEN_H
