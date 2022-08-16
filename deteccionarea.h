#ifndef DETECCIONAREA_H
#define DETECCIONAREA_H
#include "procesadordeimagen.h"
/**
 * @class DeteccionArea
 * @brief Modela la deteccion de área, encargada de detectar un área sobre la imagen.
 * @details Detecta un área en la imagen a partir de las posciones iniciales de un
 *          pixel utilizando el algoritmo del pintor.
 *          Mantiene los pixeles de la imagen dentro del rango dinamico.
 * @author Cristian Daniel Schmidt
 */

class DeteccionArea : public ProcesadorDeImagen
{
    public:
        /**
         * @brief DeteccionArea Constructor de la clase DeteccionArea.
         * @param pFil Fila del pixel inicial para detectar el área.
         * @param pCol Columna del pixel inicial para detectar el área.
         */
        DeteccionArea(unsigned pFil, unsigned pCol);
        /**
         * @brief aplicar Método de clase base redefinido encargado de detectar un área sobre la imagen
         *                mediante un algoritmo recursivo (algoritmo del pintor),
         *                dicha área se resalta en azul.
         * @param pImagen Referencia a un objeto de tipo Imagen.
         */
        void aplicar(Imagen &pImagen) override;
        /**
         * @brief getArea Método que devuelve el área de la región
         *                que se detecta (en cantidad de pixeles).
         * @return Entero sin signo con el valor del área.
         */
        unsigned getArea() const;

        /**
         * @brief getTolerancia Método que devulve la tolerancia con
         *                      la que se comparan las intensidades de los pixeles.
         * @return Entero sin signo con el valor de tolerancia.
         */
        unsigned getTolerancia() const;
        /**
         * @brief setTolerancia Método que permite modificar el valor
         *                      de tolerancia con la que se comparan las intensidades
         *                      de los pixeles.
         * @param pTolerancia Nuevo valor de tolerancia.
         */
        void setTolerancia(const unsigned &pTolerancia);

        ~DeteccionArea() override;

    private:

        /**
         * @brief rellenar Método privado encargado de implementar el algoritmo del pintor
         *                 para determinar el área y 'rellenarla' con el color azul.
         * @param pFil Fila a partir de la cual se inspeccionan los pixeles vecinos.
         * @param pCol Columna a partir de la cual se inspeccionan los pixeles vecinos.
         * @param pImagen Imagen a la cual se le realiza la deteccion del área.
         * @param mb Matriz de booleanos que terminan las posiciones que se deben rellenar.
         * @param parte Lado de la superficie donde el algoritmo actuará, esto permite
         *              dividir el pintado en dos partes.
         */
        void rellenar(unsigned pFil, unsigned pCol, Imagen &pImagen, vector<vector<bool>> &mb, unsigned parte);
        /**
         * @brief fil Atributo de tipo entero sin signo, con el valor de la fila
         *             a partir de la cual se comienza a detectar el área.
         */
        unsigned fil;
        /**
         * @brief col Atributo de tipo entero sin signo, con el valor de la columna
         *            a partir de la cual se comienza a detectar el área.
         */
        unsigned col;
        /**
         * @brief tolerancia Atributo de tipo entero sin signo, con el valor
         *                   de tolerancia con la que se comparan las intensidades de los pixeles.
         */
        unsigned tolerancia;
        /**
         * @brief area Atributo de tipo entero sin signo, con el valor del
         *             área de la región detectada en cantidad de pixeles.
         */
        unsigned area;

        /**
         * @brief pixelInicial Pixel inicial a partir del cual se comienza a detectar el área.
         */
        Pixel pixelInicial;
};

#endif // DETECCIONAREA_H
