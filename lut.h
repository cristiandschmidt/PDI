#ifndef LUT_H
#define LUT_H
#include "procesadordeimagen.h"
/**
 * @class LUT
 * @brief Modela un LUT,
 * @details Aplica un LUT a una imagen a partir de una tabla de intensidades, ajustando la
 *          intensidad de sus pixeles con los datos de la tabla. Mantiene los pixeles de
 *          la imagen dentro del rango dinamico.
 *          Mantiene los pixeles de la imagen dentro del rango dinamico.
 * @author Cristian Daniel Schmidt
 */
class LUT : public ProcesadorDeImagen
{
    public:
        /**
         * @brief LUT Constructor de la clase LUT.
         */
        LUT();
        /**
        * @brief aplicar Método de clase base redefinido encargado de aplicar el LUT cargado
        *                a la imagen recibida como parámetro.
        * @param pImagen Referencia a un objeto de tipo Imagen.
         */
        void aplicar(Imagen &pImagen) override;
        /**
         * @brief cargarLUT Método que permite cargar un LUT(archivo con tabla de valores)
         * @param pDireccion String con la dirección del archivo.
         */
        void cargarLUT(const string &pDireccion);

        ~LUT() override;

    private:
        /*!
         * @brief tablaR Atributo de tipo vector de entero sin signo, que contiene las nuevas
         *               componentes R de los pixeles pertenecientes a
         *               la imagen que será pseudocoloreada.
         */
        vector <unsigned> tablaR;
        /*!
         * @brief tablaG Atributo de tipo vector de entero sin signo, que contiene las nuevas
         *               componentes G de los pixeles pertenecientes a
         *               la imagen que será pseudocoloreada.
         */
        vector <unsigned> tablaG;
        /*!
         * @brief tablaB Atributo de tipo vector de entero sin signo, que contiene las nuevas
         *               componentes B de los pixeles pertenecientes a
         *               la imagen que será pseudocoloreada.
         */
        vector <unsigned> tablaB;
};

#endif // LUT_H
