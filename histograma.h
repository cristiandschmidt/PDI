#ifndef HISTOGRAMA_H
#define HISTOGRAMA_H
#include "procesadordeimagen.h"
/**
 * @class Histograma
 * @brief Modela el histograma de una imagen y los datos estadísticos que lo acompañan.
 * @details Permite la extraccion de datos estadisticos de la imagen que se encuentra
 *          siendo analizada, como por ejemplo promedio de los valores de intensidad de
 *          la imagen en cuestion, desvio estandar de los valores de pixeles, la moda de
 *          imagenes tanto en escalas de grises como RGB, ademas contiene mapas de
 *          frecuencia que permiten realizar el histograma.
 *          Mantiene los pixeles de la imagen dentro del rango dinamico.
 * @author Cristian Daniel Schmidt
 */

class Histograma : public ProcesadorDeImagen
{
    public:
        /**
         * @brief Histograma Constructor de la clase Histograma.
         */
        Histograma();
        /**
         * @brief aplicar Método de clase base redefinido encargado de obtener los
         *                mapas de frecuencias y los datos estadísticos de la imagen.
         * @param pImagen Referencia a un objeto de tipo Imagen a la cual se aplica el procesamiento.
         */
        void aplicar(Imagen &pImagen) override;
        /**
         * @brief graficar Método que permite generar el grafico de los histogramas.
         * @param pTipo Referencia a un tipo de dato stringn que indica que histograma
         *              se desea graficar (R, G, B o grises)
         */
        void graficar(const string &pTipo);
        /**
         * @brief getMinPixelGris Método encargado de devolver valor de intensidad del
         *                        mínimo pixel en escala de grises en la imagen.
         * @return Tipo de dato T con el valor de intensidad.
         */
        T getMinPixelGris() const;
        /**
         * @brief getMinPixelesRGB Método encargado de devolverelos valores de intensidad
         *                         del mínimo pixel R, G y B.
         * @return Tupla de tipo de dato T con el valor de intensidad de cada componente.
         */
        tuple<T, T, T> getMinPixelesRGB() const;
        /**
         * @brief getMaxPixelGris Método encargado de devolver el valor de intensidad del
         *                        máximo pixel en escala de grises en la imagen.
         * @return Tipo de dato T con el valor de intensidad.
         */
        T getMaxPixelGris() const;
        /**
         * @brief getMaxPixelesRGB Método encargado de devolver los valores de intensidad
         *                         del máximo pixel R, G y B.
         * @return Tupla de tipo de dato T con el valor de intensidad de cada componente.
         */
        tuple<T, T, T> getMaxPixelesRGB() const;
        /**
         * @brief getPromedioPixelesGrises Método encargado de devolver el promedio de
         *                                 intensidad de los pixeles en escala de grises.
         * @return Tipo de dato punto flotante con el promedio.
         */
        float getPromedioPixelesGrises() const;
        /**
         * @brief getPromedioPixelesRGB Método encargado de devolver los promedios de
         *                              intensidad de los pixeles R, G y B.
         * @return Tupla de tipo de dato punto flotante con el valor de promedio de cada componente.
         */
        tuple<float, float, float> getPromedioPixelesRGB() const;

        /**
         * @brief getDesvioPixelesGrises Método encargado de devolver el desvío estándar de
         *                               los pixeles en escala de grises.
         * @return Tipo de dato punto flotante con el desvío estándar.
         */
        float getDesvioPixelesGrises() const;
        /**
         * @brief getDesvioPixelesRGB Método encargado de devolver los desvíos estándar
         *                            de los pixeles R, G y B.
         * @return Tupla de tipo de dato punto flotante con el valor
         *         de desvío estándar de cada componente.
         */
        tuple<float, float, float> getDesvioPixelesRGB() const;
        /**
         * @brief getMaxFrecuenciaModas Método encargado de devolver la frecuancia más
         *                              alta entre las modas grises, R, G o B.
         * @return Map de tipo de dato T con el valor de intesidad y la frecuencia de la
         *         moda con la frecuencia más alta.
         */
        map<T, T> getMaxFrecuenciaModas() const;
        /**
         * @brief getModaPixelesGrises Método encargado de devolver la moda de los
         *                             pixeles en escala de grises.
         * @return Map de tipo de dato T con el valor de intesidad y la frecuencia.
         */
        map<T,T> getModaPixelesGrises() const;
        /**
         * @brief getModaPixelesRGB Método encargado de devolver la moda
         *                          de los pixeles R, G y B.
         * @return Tupla de maps de tipo de dato T con el valor de intesidad
         *         y la frecuencia de cada componente.
         */
        tuple<map<T, T>, map<T,T>, map<T,T>> getModaPixelesRGB() const;

        /**
         * @brief getMapFrecuenciasPixelesGrises Método encargado de devolver el mapa de
         *                                       frecuencia de los pixeles en escala de grises.
         * @return Map de tipo de dato T con los valores de intesidad y la frecuencia.
         */
        map<T, T> getMapFrecuenciasPixelesGrises() const;
        /**
         * @brief getMapFrecuenciasPixelesR Método encargado de devolver el mapa de
         *                                  frecuencia de los pixeles R.
         * @return Map de tipo de dato T con los valores de intesidad y la frecuencia.
         */
        map<T, T> getMapFrecuenciasPixelesR() const;
        /**
         * @brief getMapFrecuenciasPixelesG Método encargado de devolver el mapa de
         *                                  frecuencia de los pixeles G.
         * @return Map de tipo tipo de dato T con los valores de intesidad y la frecuencia.
         */
        map<T, T> getMapFrecuenciasPixelesG() const;
        /**
         * @brief getMapFrecuenciasPixelesB Método encargado de devolver el mapa de
         *                                  frecuencia de los pixeles B.
         * @return Retorna un map de tipo de dato T con los valores de intesidad y la frecuencia.
         */
        map<T, T> getMapFrecuenciasPixelesB() const;

        ~Histograma() override;

    private:
        /**
         * @brief hallarMinPixeles Método privado encargado de hallar los pixeles
         *                          mínimos en escala de grises, R, G y B.
         * @param pImagen Referencia a un objeto de tipo Imagen.
         */
        void hallarMinPixeles(const Imagen &pImagen);
        /**
         * @brief hallarMaxPixeles Método privado encargado de hallar los pixeles
         *                         máximos en escala de grises, R, G y B.
         * @param pImagen Referencia a un objeto de tipo Imagen.
         */
        void hallarMaxPixeles(const Imagen &pImagen);
        /**
         * @brief hallarPromedioPixeles Método privado encargado de hallar los
         *                              promedios de los pixeles en escala de grises, R, G y B.
         * @param pImagen Referencia a un objeto de tipo Imagen.
         */
        void hallarPromedioPixeles(const Imagen &pImagen);
        /**
         * @brief hallarDesvioPixeles Método privado encargado de hallar los desvíos
         *                            estándar de los pixeles en escala de grises, R, G y B.
         * @param pImagen Referencia a un objeto de tipo Imagen.
         */
        void hallarDesvioPixeles(const Imagen &pImagen);
        /**
         * @brief hallarMapFrecuenciasPixeles Método privado encargado de hallar los mapas
         *                                    de frecuencias de los pixeles en escala de grises, R, G y B.
         * @param pImagen Referencia a un objeto de tipo Imagen.
         */
        void hallarMapFrecuenciasPixeles(const Imagen &pImagen);
        /**
         * @brief hallarModasPixeles Método privado encargado de hallar las modas de los pixeles
         *                           en escala de grises, R, G y B.
         */
        void hallarModasPixeles();

        /**
         * @brief minPixelGris Atributo de tipo T, con el valor de intensidad del
         *                     mínimo pixel en escala de grises.
         */
        T minPixelGris;
        /**
         * @brief maxPixelGris Atributo de tipo T, con el valor de intensidad del
         *                     máximo pixel en escala de grises.
         */
        T maxPixelGris;
        /**
         * @brief minPixelesRGB Atributo de tipo tupla de T, con los valores de
         *                      intensidad mínimos de los pixeles R, G y B.
         */
        tuple<T, T, T> minPixelesRGB;
        /**
         * @brief maxPixelesRGB Atributo de tipo tupla de T, con los valores de
         *                      intensidad máximos de los pixeles R, G y B.
         */
        tuple<T, T, T> maxPixelesRGB;

        /**
         * @brief promedioPixelesGrises Atributo de tipo float, con el valor del
         *                              promedio de los pixeles en escala de grises.
         */
        float promedioPixelesGrises;
        /**
         * @brief promedioPixelesRGB Atributo de tipo tupla de float,con los valores de
         *                           promedio de los pixeles R, G y B.
         */
        tuple<float, float, float> promedioPixelesRGB;
        /**
         * @brief desvioPixelesGrises Atributo de tipo T, con el valor del desvío estándar
         *                            de los pixeles en escala de grises.
         */
        float desvioPixelesGrises;
        /**
         * @brief desvioPixelesRGB Atributo de tipo tupla de float, con los valores de desvíos
         *                         estándar de los pixeles R, G y B.
         */
        tuple<float, float, float> desvioPixelesRGB;

        /**
         * @brief maxFrecuenciaModas Atributo de tipo map de T, con la intensidad y frencuencia
         *                           de la moda con mayor frecuencia.
         */
        map<T,T> maxFrecuenciaModas;

        /**
         * @brief modaPixelesGrises Atributo de tipo map de T, con la moda (intensidad y frecuencia)
         *                          de los pixeles en escala de grises.
         */
        map<T,T> modaPixelesGrises;
        /**
         * @brief modaPixelesRGB Atributo de tipo tupla de map de T, con la moda (intensidad y frecuencia)
         *                       de los pixeles R, G y B.
         */
        tuple<map<T, T>, map<T,T>, map<T,T>> modaPixelesRGB;

        /**
         * @brief mapFrecuenciasPixelesGrises Atributo de tipo map de T, con las intensidades y
         *                                    frecuencias de los pixeles en escala de grises.
         */
        map<T, T> mapFrecuenciasPixelesGrises;
        /**
         * @brief mapFrecuenciasPixelesR Atributo de tipo map de T, con las intensidades y
         *                               frecuencias de los pixeles R.
         */
        map<T, T> mapFrecuenciasPixelesR;
        /**
         * @brief mapFrecuenciasPixelesG Atributo de tipo map de T, con las intensidades y
         *                               frecuencias de los pixeles G.
         */
        map<T, T> mapFrecuenciasPixelesG;
        /**
         * @brief mapFrecuenciasPixelesB Atributo de tipo map de T, con las intensidades y
         *                               frecuencias de los pixeles B.
         */
        map<T, T> mapFrecuenciasPixelesB;
};

#endif // HISTOGRAMA_H
