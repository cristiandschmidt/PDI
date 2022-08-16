#ifndef IMAGEN_H
#define IMAGEN_H
#include <QOpenGLWidget>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "pixel.h"
/**
 * @class Imagen
 * @brief Modela una imagen que es capaz de abrirse y guardarse desde una direccion.
 * @details La imagen tinen una matriz de pixeles (tipo Pixel), puede dibujarse,
 *          así como modificar y devolver sus caracteristicas como la matriz de Pixeles,
 *          tipo, intensisdad máxima, dimensiones, etc.
 * @author Cristian Daniel Schmidt
 */
using namespace std;

class Imagen
{
    public:
        /**
     * @brief Imagen Constructor de la clase Imagen.
     */
        Imagen();

        /**
        * @brief abrir Método virtualizado encargado de abrir la imagen desde una direccion.
        * @param pDireccion Referencia a un tipo de dato string con la direccion de apertura de la imagen.
        * @return Booleano dependiendo si pudo abrirse o no.
        */
        virtual bool abrir(const string &pDireccion) = 0;
        /**
        * @brief guardar Método virtualizado encargado de guardar la imagen en una direccion.
        * @param pDireccion Referencia a un tipo de dato string con la direccion de guardado de la imagen.
        */
        virtual void guardar(const string &pDireccion) = 0;
        /*!
        * @brief dibujar Método que le permite a la imagen poder dibujarse a sí misma, plasmar su matriz de Pixeles
        * en un gráfico.
        */
        void dibujar();

        /**
         * @brief setPixel Método que permite asignar un Pixel en la matriz de pixeles.
         * @param pFila Fila en la que se asigna el Pixel.
         * @param pColumna Columna en la que se asigna el Pixel.
         * @param pPixel Objeto de tipo Pixel a asignar.
         */
        void setPixel(const unsigned &pFila, const unsigned &pColumna, const Pixel &pPixel);
        /**
         * @brief getPixel Método que permite devolver un Pixel en la imagen.
         * @param pFila Fila del Pixel dentro de la matriz de pixeles.
         * @param pColumna Columna del Pixel dentro de la matriz de pixeles.
         * @return Objeto de tipo Pixel.
         */
        Pixel getPixel(const unsigned &pFila, const unsigned &pColumna) const;

        /**
         * @brief setIntensidadMaxima Método que permite asignar la intensidad máxima de los pixeles de la imagen.
         * @param pIntensidadMaxima Referencia a un tipo de dato string con el valor de intensidad a asignar.
         */
        void setIntensidadMaxima(const T &pIntensidadMaxima);
        /**
         * @brief getIntensidadMaxima Método que permite devolver la intensidad máxima de los pixeles de la imagen.
         * @return Entero sin signo con la intenisdad máxima.
         */
        unsigned getIntensidadMaxima() const;
        /**
         * @brief setMetadatos Método que permite asignar los metadatos a la imagen.
         * @param pMetadato String con los metadatos a asignar.
         */
        void setMetadatos(const string &pMetadato);
        /**
         * @brief getMetadatos Método que permite devolver los metadatos de la imagen.
         * @return String con los metadatos.
         */
        string getMetadatos() const;
        /**
         * @brief getAncho Método que permite devolver el ancho de la imagen(cantidad columnas).
         * @return Entero sin signo con el valor del ancho de la imagen.
         */
        unsigned getAncho() const;
        /**
         * @brief getAlto Método que permite devolver el alto de la imagen(cantidad filas).
         * @return Entero sin signo con el valor del alto de la imagen.
         */
        unsigned getAlto() const;
        /**
         * @brief dimensionar Redimensiona la matriz de pixeles de la imagen.
         * @param pAlto Alto con el cual se redimensiona la matriz (cantidad filas).
         * @param pAncho Ancho con el cual se redimensiona la matriz (cantidad columnas).
         */
        void dimensionar(const int &pAlto, const int &pAncho);
        /**
         * @brief setMatrizPixeles Método que permite asignar una matriz de pixeles a la imagen.
         * @param pMatrizPixeles Matriz (vector de vector) con tipo de datos Pixel a asignar.
         */
        void setMatrizPixeles(const vector<vector<Pixel> > &pMatrizPixeles);
        /**
         * @brief getMatrizPixeles Método que permite devolver la matriz de pixeles de la imagen.
         * @return Matriz (vector de vector) con tipo de datos Pixel.
         */
        vector <vector<Pixel>> getMatrizPixeles() const;
        /**
         * @brief setTipo Método que permite asignar un tipo a la imagen.
         * @param pTipo String con el tipo de imagen a asignar.
         */
        void setTipo(const string &pTipo);
        /**
         * @brief getTipo Método que permite devolver el tipo la imagen.
         * @return String con el tipo de imagen.
         */
        string getTipo() const;
        /**
         * @brief setNombre Método que permite asignar un nombre a la imagen.
         * @param pNombre String con el nombre a asignar.
         */
        void setNombre(const string &pNombre);
        /**
         * @brief getNombre Método que permite devolver el nombre la imagen.
         * @return String con el nombre de la imagen.
         */
        string getNombre() const;
        /**
         * @brief setDireccionDeGuardado Método que permite asignar una direccion de guardado a la imagen.
         * @param pDireccionDeGuardado String con la direccion de guardado a asignar.
         */
        void setDireccionDeGuardado(const string &pDireccionDeGuardado);
        /**
         * @brief getDireccionDeGuardado Método que permite devolver la direccion de guardado de la imagen.
         * @return String con la direccion de guardado.
         */
        string getDireccionDeGuardado() const;
        /**
         * @brief setTipoAnterior Método que permite el tipo anterior al cambio de formato
         * @param pTipoAnterior String con el tipo anterior al cambio de formato.
         */
        void setTipoAnterior(const string &pTipoAnterior);
        /**
         * @brief getTipoAnterior Método que permite obtener el tipo anterior de una imagen.
         * @return String con el tipo anterior al cambio de formato.
         */
        string getTipoAnterior() const;
        /**
         * @brief setBinarizada Método que permite establecer si la imagen está binarizada o no.
         * @param pBinarizada Booleano con el estado de binarizado de la imagen.
         */
        void setBinarizada(bool pBinarizada);
        /**
         * @brief getBinarizada Método que permite devolver el estado de binarizado de la imagen.
         * @return Booleano con el estado, (true si esta binarizada, false en caso contrario).
         */
        bool getBinarizada() const;


        virtual ~Imagen();

    protected:
        /**
         * @brief matrizPixeles Atributo Matriz (vector de vector) con tipo de datos Pixel,
         *                      que representa los pixeles de la imagen.
         */
        vector <vector<Pixel>> matrizPixeles;
        /**
         * @brief tipo Atributo de tipo string con el tipo de imagen.
         */
        string tipo;
        /**
         * @brief tipoAnterior Atributo de tipo string que contiene el tipo anterior al cambio de formato.
         */
        string tipoAnterior;
        /**
         * @brief nombre Atributo de tipo string con el nombre de la imagen.
         */
        string nombre;
        /**
         * @brief metadatos Atributo de tipo string con los metadatos de la imagen.
         */
        string metadatos;
        /**
         * @brief ancho Atributo de tipo entero sin signo con el ancho de la imagen(cantidad columnas).
         */
        unsigned ancho;
        /**
         * @brief alto Atributo de tipo entero sin signo con el alto de la imagen(cantidad filas).
         */
        unsigned alto;
        /**
         * @brief intensidadMaxima Atributo de tipo entero sin signo la intensidad máxima de los pixeles de la imagen.
         */
        unsigned intensidadMaxima;
        /**
         * @brief direccionDeGuardado Atributo de tipo string con la direccion de guardado de la imagen.
         */
        string direccionDeGuardado;
        /**
         * @brief binarizada Atributo de tipo booleano con el estado de binarizado de la imagen.
         */
        bool binarizada = false;
};

#endif // IMAGEN_H
