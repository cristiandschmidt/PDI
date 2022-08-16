#ifndef REALCEBORDES_H
#define REALCEBORDES_H
#include "procesadordeimagen.h"
/**
 * @class RealceBordes
 * @brief Modela un filtro de realce de bordes (pasa altos), encargada de filtrar una imagen.
 * @details Aplica un filtro llamado filtro de realce de bordes (pasa altos), el cual toma
 *          valores de pixeles vecinos para modificar la  intensidad del pixel actual
 *          mediante la aplicacion de un kernel correspondiente.
 * @author Cristian Daniel Schmidt
 */
class RealceBordes : public ProcesadorDeImagen
{
    public:
        /**
        * @brief RealceBordes Constructor de la clase RealceBordes
        */
        RealceBordes();

        /**
        * @brief aplicar Método de clase base redefinido encargado de aplicar el filtro de
        *                realce de bordes (pasa altos) a la imagen recibida como parámetro.
        * @param pImagen Referencia a un objeto de tipo Imagen.
        */
        void aplicar(Imagen &pImagen) override;

        ~RealceBordes() override;

};

#endif // REALCEBORDES_H
