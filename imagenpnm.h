#ifndef IMAGENPNM_H
#define IMAGENPNM_H
#include "imagen.h"
#include <iostream>
/**
 * @class ImagenPNM
 * @brief Modela una imagen en formato AIC que es capaz de abrirse y guardarse desde una direccion.
 * @details La clase hereda de la clase Imagen las propiedades de una imagen y se redefinen los
 *          métodos de apertura y guardado.
 * @author Cristian Daniel Schmidt
 */
class ImagenPNM : public Imagen
{
    public:
        /**
         * @brief ImagenPNM Constructor de la clase ImagenPNM
         */
        ImagenPNM();
        /**
        * @brief abrir Método de clase base redefinido encargado de abrir la imagen en
        *              formato PNM desde una direccion.
        * @param pDireccion String con la direccion de apertura de la imagen PNM.
        * @return Retorna una tipo de dato booleano dependiendo si pudo abrirse o no.
        */
        bool abrir(const string &pDireccion) override;
        /**
         * @brief guardar Método de clase base redefinido encargado de guardar la imagen en
         *                formato PNM en una direccion.
        * @param pDireccion Referencia a un tipo de dato string con la direccion de guardado de la imagen PNM.
        */
        void guardar(const string &pDireccion) override;


        ~ImagenPNM() override;

    private:
        /**
         * @brief Tipos Atributo de tipo Enumeración de los tipos de imagenes PNM
         */
        enum Tipos{
            P1, /**< extension pbm y pixeles en formato texto*/
            P2, /**< extension pgm y pixeles en formato texto*/
            P3, /**< extension ppm y pixeles en formato texto*/
            P4, /**< extension pbm y pixeles en formato binario*/
            P5, /**< extension pgm y pixeles en formato binario*/
            P6/**< extension ppm y pixeles en formato binario*/
        };
        /**
         * @brief tipos Atributo de tipo vector de strings con los tipos de imagenes PNM,
         *              se usa para obtener un string a partir de el enumerado.
         */
        vector<string> tipos;
};

#endif // IMAGENPNM_H
