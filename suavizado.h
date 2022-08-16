#ifndef SUAVIZADO_H
#define SUAVIZADO_H
#include "procesadordeimagen.h"
/**
 * @class Suavizado
 * @brief Modela un filtro de suavizado (pasa bajos), encargada de filtrar una imagen.
 * @details Aplica un filtro llamado filtro de suavizado (pasa bajos), el cual toma
 *          valores de pixeles vecinos para modificar la  intensidad del pixel actual
 *          mediante la aplicacion de un kernel correspondiente.
 * @author Cristian Daniel Schmidt
 */
class Suavizado : public ProcesadorDeImagen
{
    public:
        /**
        * @brief Suavizado Constructor de la clase Suavizado.
        */
        Suavizado();
        /**
        * @brief aplicar Método de clase base redefinido encargado de aplicar el filtro de
        *                suavizado (pasa bajos) a la imagen recibida como parámetro.
        * @param pImagen Referencia a un objeto de tipo Imagen.
        */
        void aplicar(Imagen &pImagen) override;

        ~Suavizado() override;
};

#endif // SUAVIZADO_H
