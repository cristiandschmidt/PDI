#ifndef IMAGENAIC_H
#define IMAGENAIC_H
#include "imagen.h"
/**
 * @class ImagenAIC
 * @brief Modela una imagen en formato AIC que es capaz de abrirse y guardarse desde una direccion.
 * @details La clase hereda de la clase Imagen las propiedades de una imagen y se redefinen los
 *          métodos de apertura y guardado.
 * @author Cristian Daniel Schmidt
 */
class ImagenAIC : public Imagen
{
    public:
        /**
        * @brief ImagenAIC Constructor de la clase ImagenAIC.
        */
        ImagenAIC();
        /**
        * @brief abrir Método de clase base redefinido encargado de abrir la imagen en
        *              formato AIC desde una direccion.
        * @param pDireccion String con la direccion de apertura de la imagen AIC.
        * @return Retorna una tipo de dato booleano dependiendo si pudo abrirse o no.
        */
        bool abrir(const string &pDireccion) override;
        /**
        * @brief guardar Método de clase base redefinido encargado de guardar la imagen en
        *                formato AIC en una direccion.
        * @param pDireccion Referencia a un tipo de dato string con la direccion de guardado de la imagen AIC.
        */
        void guardar(const string &pDireccion) override;

        ~ImagenAIC() override;
};

#endif // IMAGENAIC_H
