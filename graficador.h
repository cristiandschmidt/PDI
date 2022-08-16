#ifndef GRAFICADOR_H
#define GRAFICADOR_H
#include <QOpenGLWidget>
#include <QApplication>
#include <QKeyEvent>
#include <QMouseEvent>
#include <vector>
#include "imagen.h"
#include "imagenaic.h"
#include "imagenpnm.h"
#include "procesadordeimagen.h"
#include "histograma.h"
#include "contraste.h"
#include "negativo.h"
#include "brillo.h"
#include "realcebordes.h"
#include "suavizado.h"
#include "mediana.h"
#include "binarizado.h"
#include "deteccionarea.h"
#include "lut.h"
#include "conv_string.h"
/**
 * @class Graficador
 * @brief Modela una estructura encarga de graficar y mostrar por pantalla diferentes objetos,
 *        ademas de identificar yresponder ante diversos eventos externos.
 * @details Se encarga de mostrar por pantalla los ditintos gráficos, se encarga de mantener
 *          la relación de aspecto de las diferentes imágenes que muestra por pantalla y de comandar
 *          las diferentes acciones desencadenadas por los eventos de interacción con el usuario detectados.
 * @author Cristian Daniel Schmidt
 */
using namespace std;

class Graficador: public QOpenGLWidget
{
    public:
        /**
          * @brief Graficador Método constructor de la clase Graficador.
        */
        Graficador();
        /**
         * @brief setListaImagenes Método encargado de cargar las imagenes de la lista
         *                         de direcciones de imagenes que se pasa como parámetro
         *                         comprobando que no estén corruptas
         * @param pListaDirImagenes Vector de strings con la lista de direcciones de imagenes a cargar.
         */
        void setListaImagenes(const vector<string> &pListaDirImagenes);
        /**
         * @brief setImagen Método encargado de selecionar la imagen actual dentro del vector de imagenes.
         * @param pNumeroImg Posicion de la imagen dentro del vector de imagenes.
         */
        void setImagen(const unsigned &pNumeroImg);
        /**
         * @brief getNombresImagenesCorrectas Método encargado de devolver un vector con los nombres
         *                                    de las imagenes que se cargaron correctamente.
         * @return Vector de strings con los nombres de imagenes correctas.
         */
        vector <string> getNombresImagenesCorrectas() const;
        /**
         * @brief getNombresImagenesCorruptas Método encargado de devolver un vector con los nombres
         *                                    de las imagenes que estaban corruptas.
         * @return Vector de strings con los nombres de imagenes corruptas.
         */
        vector <string> getNombresImagenesCorruptas() const;
        /**
         * @brief mostrar Método encargado de mostrar por pantalla la imagen actual.
         * @param pApp Objeto de tipo QApplication, el cual comandará todo lo relacionado con la interfaz
         * gráfica.
         */
        void mostrar( QApplication* pApp);
        /**
         * @brief procesarImagen Método encargado de aplicar un procesamiento a la imagen.
         * @param pImagen Refencia a un objeto de tipo Imagen, a procesar.
         * @param pProcesadorDeImagen Refencia a un objeto de tipo ProcesadorDeImagen usado como procesador.
         */
        void procesarImagen(Imagen &pImagen, ProcesadorDeImagen& pProcesadorDeImagen);

        ~Graficador() override;

    protected:
        /**
         * @brief paintGL Método que permite la realización de modificaciones sobre
         *                la interfaz gráfica con la cual trabajará el software de
         *                procesamiento de imágenes.
         */
        void paintGL() override;
        /**
         * @brief initializeGL Método que permite establecer el color de fondo con el cual se
         *                     actualizará la pantalla al registrarse un evento.
         */
        void initializeGL() override;
        /**
         * @brief resizeGL Método que permite definir el espacio de la ventana gráfica en el cual se
         *                 realizarán los gráficos de las imágenes y sus dimensiones.
         * @param w Dato de tipo entero, que se utiliza para la redimensión de la ventada gráfica.
         * @param h Dato de tipo entero, que se utiliza para la redimensión de la ventada gráfica.
         */
        void resizeGL(int w, int h) override;
        /**
         * @brief keyPressEvent Método encargado de la identificación y gestión de los eventos
         *                      detectados sobre la presión de determinadas teclas.
         * @param event Objeto de tipo QKeyEvent, encargado de la gestión de eventos de
         *              teclado dentro del método.
         */
        void keyPressEvent(QKeyEvent *event) override;
        /**
         * @brief mousePressEvent Método encargado de la identificación y gestión de los eventos
         *                        detectados sobre la presión de los botones del mouse.
         * @param event Objeto de tipo QMouseEvent, encargado de la gestión de eventos de botones
         *               del mouse identificados dentro de dicho método.
         */
        void mousePressEvent(QMouseEvent* event) override;
        /**
         * @brief mouseReleaseEvent Método encargado de la identificación y gestión de eventos
         *                          relacionados con la acción de dejar de presionar los botones
         *                          del mouse, es decir, con un cese de la presión.
         * @param event Objeto de tipo QMouseEvent, encargado de la gestión de eventos de cese
         *               de presión de los botones del mouse identificadas dentro de dicho método.
         */
        void mouseReleaseEvent(QMouseEvent* event)override;
        /**
         * @brief keyReleaseEvent Método encargado de la identificación y gestión de eventos
         *                        relacionados con la acción de dejar de presionar determinadas
         *                        teclas, es decir, con un cese de la presión de ellas.
         * @param event Objeto de tipo QKeyEvent, encargado de la gestión de eventos de
         *               cese de presión de determinadas teclas identificadas dentro de dicho método.
         */
        void keyReleaseEvent(QKeyEvent* event) override;
        /**
         * @brief mouseMoveEvent Método encargado de la identificación y gestión de los eventos
         *                       detectados sobre el movimientos del mouse.
         * @param event Objeto de tipo QMouseEvent, encargado de la gestión de
         *               eventos de movimientos del mouse.
         */
        void mouseMoveEvent(QMouseEvent* event) override;

    private:
        /**
         * \brief graficarHistograma Método encargado de la graficación por pantalla de los histogramas
         *                           relacionados con la imagen actual.
         */
        void graficarHistograma();
        /**
         * @brief acondicionarPosiciones Método privado encargado de aplicar modificaciones
         *                               tales que las posiciones devueltas por el cursor del mouse
         *                               coincidan con la fila y la columna de la imagen actual sobre
         *                               la cual se desplaza el cursor.
         * @param posX Dato de tipo entero sin signo, que contiene la posicion en x del cursor.
         * @param posY Dato de tipo entero sin signo, que contiene la posicion en y del cursor.
         * @param momento Dato de tipo char, puede tomar dos valores, 1 o 2, los cuales representan
         *                la situación del botón izquierdo del mouse, ya sea si se presionó o se soltó.
         */
        void acondicionarPosiciones(unsigned posX, unsigned posY, char momento);
        /**
         * @brief seleccionarRegion Método privado encargado de graficar un rectángulo que abarcará
         *                          la región sobre la cual se hará un zoom.
         */
        void seleccionarRegion();

        /**
         * @brief obtenerValorValido Método privado encargado de obtener un valor válido
         *                           para la varible ingresada por consola.
         * @param pVariable Referencia a la variable que se desea obtener por consola.
         */
        void obtenerValorValido(unsigned &pVariable);
        /**
         * @brief atajos Atributo de tipo Imagen con los atajos de ayuda para el usuario.
         */
        ImagenPNM atajos;
        /**
         * @brief dirImagenesCorrectas Atributo de tipo vector de strings que contiene las
         *                             direcciones de las imagenes que se cargaron correctamente.
         */
        vector <string> dirImagenesCorrectas;
        /**
         * @brief nombresImagenesCorrectas Atributo de tipo vector de strings que contiene
         *                                 los nombres de las imagenes que se cargaron correctamente.
         */
        vector <string> nombresImagenesCorrectas;
        /**
         * @brief nombresImagenesCorruptas Atributo de tipo vector de strings que contiene
         *                                 los nombres de las imagenes corruptas.
         */
        vector <string> nombresImagenesCorruptas;
        /**
         * @brief imagenes Atributo de tipo vector de punteros a objetos de tipo
         *                 Imagen que contiene las imagenes cargadas.
         */
        vector<Imagen*> imagenes;
        /**
         * @brief imagenActual Atributo de tipo entero sin signo que indica la
         *                     posicion de la imagen actual dentro del vector de imagenes.
         */
        unsigned imagenActual = 0;
        /**
         * @brief MouseFilInicial Atributo de tipo entero sin signo, que contiene
         *                       la posición en Y sobre la imagen en donde se detectó
         *                       la presión del botón izquierdo del mouse.
         */
        unsigned mouseFilInicial = 0;
        /**
         * @brief mouseColInicial Atributo de tipo entero sin signo, que contiene
         *                        la posición en X sobre la imagen en donde se detectó
         *                        la presión del botón izquierdo del mouse
         */
        unsigned mouseColInicial = 0;
        /**
         * @brief mouseFilFinal Atributo de tipo entero sin signo, que contiene la posición
         *                     en Y sobre la imagen en donde se detectó el evento de soltar
         *                     el botón izquierdo del mouse
         */
        unsigned mouseFilFinal = 0;
        /**
         * @brief mouseColFinal Atributo de tipo entero sin signo, que contiene la posición
         *                      en X sobre la imagen en donde se detectó el evento de soltar
         *                      el botón izquierdo del mouse
         */
        unsigned mouseColFinal = 0;
        /**
         * @brief mouseFilActual Atributo de tipo entero sin signo, que contiene la posicion
         *                       en Y actual sobre la imagen en donde se detecta el movimiento
         *                       del cursor mientras se mantiene apretado el click izquierdo.
         */
        unsigned mouseFilActual = 0;
        /**
         * @brief mouseColActual Atributo de tipo entero sin signo, que contiene la posicion
         *                       en Y actual sobre la imagen en donde se detecta el movimiento
         *                       del cursor mientras se mantiene apretado el click izquierdo.
         */
        unsigned mouseColActual = 0;
        /**
         * @brief mousePosXInicial Atributo de tipo entero sin signo, que contiene la posición
         *                         en x en la cual se detectó el evento del click izquierdo.
         */
        unsigned mousePosXInicial = 0;
        /**
         * @brief mousePosYInicial Atributo de tipo entero sin signo, que contiene la posición
         *                         en y en la cual se detectó el evento del click izquierdo.
         */
        unsigned mousePosYInicial = 0;
        /**
         * @brief mousePosXFinal Atributo de tipo entero sin signo, que contiene la posición
         *                       en x en la cual se detectó el evento de dejar de presionar
         *                       el click izquierdo.
         */
        unsigned mousePosXFinal = 0;
        /**
         * @brief mousePosYFinal Atributo de tipo entero sin signo, que contiene la posición
         *                       en y en la cual se detectó el evento de dejar de presionar
         *                       el click izquierdo.
         */
        unsigned mousePosYFinal = 0;
        /**
         * @brief mousePosXActual Atributo de tipo entero sin signo, que contiene la posición
         *                        en x en la cual se detectó el evento de movimiento del
         *                        click izquierdo presionado.
         */
        unsigned mousePosXActual = 0;
        /**
         * @brief mousePosYActual Atributo de tipo entero sin signo, que contiene la posición en
         *                        y en la cual se detectó el evento de movimiento del
         *                        click izquierdo presionado.
         */
        unsigned mousePosYActual = 0;
        /**
         * @brief controlPresionado Atributo de tipo booleano, que adquiere el valor verdadero
         *                          cuando la tecla control es presionada.
         */

        bool controlPresionado = false;
        /**
         * @brief clickIzquierdoPresionado Atributo de tipo booleano, que adquiere el valor
         *                                 verdadero cuando el click izquierdo del mouse es presionada.
         */
        bool clickIzquierdoPresionado= false;
        /**
         * @brief moviendo Atributo de tipo booleano, que adquiere el valor verdadero
         *                 cuando se detecta el evento de movimineto
         *                 del mouse.
         */
        bool moviendo = false;
        /**
         * @brief restablecerImagen Atributo de tipo booleano, que contiene verdadero
         *                          si la imagen esta en tamaño normal, y contiene falso si
         *                          se suelta el click para aplicar zoom.
         */
        bool restablecerImagen = true;
        /**
         * @brief zoom Atributo de tipo booleneano, que establece si hay un zoom aplicado.
         */
        bool zoom = false;
        /**
         * @brief mostrarHistograma Atributo de tipo booleano, que contiene verdadero
         *                          si se esta mostrando el histograma de la imagen
         *                          seleccionada, y falso si no se está mostrando el histograma.
         */
        bool mostrarHistograma = false;
        /**
         * @brief mostrarAtajos Atributo de tipo booleano, que contiene verdadero si se esta
         *                      mostrando la imagen de atajos, y falso si no se está mostrando.
         */
        bool mostrarAtajos = false;
        /**
         * @brief escala Atributo de tipo punto flotante, contiene un coeficiente necesario para
         *               mantener la relación de aspecto de la imagen en relación a la ventana.
         */
        float escala = 0.0f;
        /**
         * @brief desplImgX Atributo de tipo punto flotante, contiene información acerca de cuanto
         *                  se debe desplazar la imagen en el eje X para poder centrarla,
         *                  una vez que fue escalada.
         */
        float desplImgX = 0.0f;
        /**
         * @brief desplImgY Atributo de tipo punto flotante, contiene información acerca de
         *                  cuanto se debe desplazar la imagen en el eje Y
         *                  para poder centrarla, una vez que fue escalada.
         */
        float desplImgY = 0.0f;
        /**
         * @brief dimensionX Atributo de tipo entero sin signo, valor constante en X
         *                   que tomará la ventana gráfica en donde se observarán
         *                   las imágenes en cumplimiento de ciertas condiciones.
         */
        unsigned dimensionX = 0;
        /**
         * @brief dimensionY Atributo de tipo entero sin signo, valor constante en Y
         *                   que tomará la ventana gráfica en donde se observarán
         *                   las imágenes en cumplimiento de ciertas condiciones.
         */
        unsigned dimensionY = 0;
};

#endif // GRAFICADOR_H

