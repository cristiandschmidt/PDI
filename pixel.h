#ifndef PIXEL_H
#define PIXEL_H
#include <vector>
/**
 * @class Pixel
 * @brief Modela un pixel, el componente fundamental de información de una imagen.
 * @details Permite la realizacion de diferentes operaciones entre objetos del mismo
 *          tipo Pixel y ademas con tipos de datos fundamentales, como por ejemplo
 *          tipos punto flotante. Ademas permite modificar parametros individuales
 *          relacionados con la intensidad de este.
 * @author Cristian Daniel Schmidt
 */
using namespace std;
typedef unsigned T;

class Pixel
{
    public:
        /**
        * @brief Pixel Constructor de la clase Pixel
        */
        Pixel();
        /**
        * @brief Pixel Constructor alternativo para pixeles en escala de grises.
        * @param pIntensidadRGB Valor de tipo T con la intensidad del pixel
        */
        Pixel(const T &pIntensidadRGB);
        /**
        * @brief Pixel Constructor alternativo para pixeles RGB.
        * @param pIntensidadR Valor de tipo T con la intensidad R del pixel.
        * @param pIntensidadG Valor de tipo T con la intensidad G del pixel.
        * @param pIntensidadB Valor de tipo T con la intensidad B del pixel.
        */
        Pixel(const T &pIntensidadR, const T &pIntensidadG, const T &pIntensidadB);
        /**
        * @brief getIntensidadRGB Método encargado de devolver la intenisdad del pixel.
        * @return Valor de tipo T con la intensidad del pixel.
        */
        T getIntensidadRGB() const;
        /**
        * @brief setIntensidadRGB Método encargado de asignar la intenisdad del pixel.
        * @param pIntensidadRGB Valor de tipo T con la intensidad del pixel.
        */
        void setIntensidadRGB(const T &pIntensidadRGB);
        /**
        * @brief setIntensidadR Método encargado de asignar la intenisdad R del pixel.
        * @param pIntensidadR Valor de tipo T con la intensidad R del pixel.
        */
        void setIntensidadR(const T &pIntensidadR);
        /**
        * @brief getIntensidadR Método encargado de devolver la intenisdad R del pixel.
        * @return Valor de tipo T con la intensidad R del pixel.
        */
        T getIntensidadR() const;
        /**
         * @brief setIntensidadG Método encargado de asignar la intenisdad G del pixel.
        * @param pIntensidadG Valor de tipo T con la intensidad G del pixel.
        */
        void setIntensidadG(const T &pIntensidadG);
        /**
         * @brief getIntensidadG Método encargado de devolver la intenisdad G del pixel.
        * @return Valor de tipo T con la intensidad G del pixel.
        */
        T getIntensidadG() const;
        /**
        * @brief setIntensidadB Método encargado de asignar la intenisdad B del pixel.
        * @param pIntensidadB Valor de tipo T con la intensidad B del pixel.
        */
        void setIntensidadB(const T &pIntensidadB);
        /**
        * @brief getIntensidadB Método encargado de devolver la intenisdad B del pixel.
        * @return Valor de tipo T con la intensidad B del pixel.
        */
        T getIntensidadB() const;
        /*!
        * @brief operator + Método que sobrecarga de manera local el operador '+' para
        *                   permitirle al Pixel realizar la operación suma con otro Pixel.
        * @param pPixel Objeto de tipo Pixel, representa al pixel con el cual se hará la operación.
        * @return Retorna un objeto de tipo Pixel, resultado de la suma entre el Pixel actual y el
        *         Pixel pasado por parámetro.
        */
        Pixel operator+(const Pixel &pPixel);
        /*!
        * @brief operator - Método que sobrecarga de manera local el operador '-' para permitirle al
        *                   Pixel realizar la operación resta con otro Pixel.
        * @param pPixel Objeto de tipo Pixel, representa al pixel con el cual se hará la operación.
        * @return Retorna un objeto de tipo Pixel, resultado de la suma entre el Pixel actual y el
        *         Pixel pasado por parámetro.
        */
        Pixel operator-(const Pixel &pPixel);
        /*!
        * @brief operator * Método que sobrecarga de manera local el operador '*' para permitirle al
        *                   Pixel realizar operaciones
        * con números de punto flotante.
        * @param pNumero Tipo punto flotante, dato por el cual se multiplica al Pixel.
        * @return Retorna un objeto de tipo Pixel, resultado del producto entre el dato tipo flotante y el Pixel.
        */
        Pixel operator*(const float &pNumero);
        /*!
        * @brief operator < Método que sobrecarga de manera local el operador '<' para permitirle
        *                   al Pixel compararse con otro Pixel a partir de su intensidad.
        * @param pPixel Objeto de tipo Pixel, representa al pixel con el cual se hará la operación.
        * @return Retorna un booleano, resultado de la comparación.
        */
        bool operator<(const Pixel &pPixel);
        /*!
        * @brief operator > Método que sobrecarga de manera local el operador '>' para permitirle
        *                   al Pixel compararse con otro Pixel a partir de su intensidad.
         * @param pPixel Objeto de tipo Pixel, representa al pixel con el cual se hará la operación.
        * @return Retorna un booleano, resultado de la comparación.
        */
        bool operator>(const Pixel &pPixel);
        /*!
        * @brief operator == Método que sobrecarga de manera local el operador '==' para permitirle
        *                    al Pixel compararse con otro Pixel a partir de su intensidad.
        * @param pPixel Objeto de tipo Pixel, representa al pixel con el cual se hará la operación.
        * @return Retorna un booleano, resultado de la comparación.
        */
        bool operator==(const Pixel &pPixel);

    private:
        /**
        * @brief intensidadR Atributo de tipo T con el valor R del pixel.
        */
        T intensidadR;
        /**
        * @brief intensidadG Atributo de tipo T con el valor G del pixel.
         */
        T intensidadG;
        /**
        * @brief intensidadB Atributo de tipo T con el valor B del pixel.
        */
        T intensidadB;
};

#endif // PIXEL_H
