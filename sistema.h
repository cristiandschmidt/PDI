#ifndef SISTEMA_H
#define SISTEMA_H
#include <QApplication>
#include "graficador.h"
#include "imagen.h"
#include "conv_string.h"
#include <vector>
#include <string>
/**
 * @class Sistema
 * @brief Modela una estructura encargada de la conexión entre el usuario y el menú de opciones
 * @details Permite la comunicaciÓn entre y el software para controlar la carga de las imagenes.
 * @author Cristian Daniel Schmidt
 */
using namespace std;

class Sistema
{
    public:
        /**
        * @brief Sistema Constructor de la clase Sistema
        */
        Sistema();
        /**
        * @brief setlistaDirDeCarpetas Método encargado de obtener la lista de carpetas disponibles
        *                              en el Espacio de Trabajo.
        * @param pDirEspacioTrabajo String con la direccion del Espacio de Trabajo.
        */
        void setlistaDirDeCarpetas(const string &pDirEspacioTrabajo);
        /**
        * @brief setListaImagenesDisponibles Método encargado de obtener la lista de imagenes
        *                                    disponibles en una carpeta.
        * @param pDirCarpeta String con la direccion de la carpeta.
        */
        void setListaImagenesDisponibles(const string &pDirCarpeta);
        /**
        * @brief getListaImagenesDisponibles Método encargado de devolver la lista de
        *                                    imagenes disponibles (nombres).
        * @return Vector de strings con la lista de imagenes (nombres).
        */
        vector <string> getListaImagenesDisponibles() const;
        /**
        * @brief visualizarImagenes Método encargado de visualizar las imagenes
        *                           disponbles en la lista de imagenes.
        * @param pApp Puntero a un objeto de tipo QApplication utilizado para controlar la interfaz gráfica.
        * @param pListaDirImagenes Vector de strings con la lista de direcciones de las imagenes.
        */
        void visualizarImagenes(QApplication *pApp, vector<string> &pListaDirImagenes);
        /**
        * @brief mostrarMenu Método que permite el despliegue de un menu interactivo que permite
        *                    al usuario seleccionar el grupo de imágenes a visualizar acompañado
        *                    de una serie de atajos sobre las opciones que se brindan.
        * @param pApp Puntero a un objeto de tipo QApplication utilizado para controlar la interfaz gráfica.
        */
        void mostrarMenu(QApplication *pApp);


        ~Sistema();

    private:
        /**
        * @brief mostrarAtajos Método encargado de mostrar por consola los atajos
        *                      disponibles para el uso del sistema.
        */
        void mostrarAtajos();

        /**
        * @brief dirEspacioDeTrabajo Atributo de tipo string con la direccion del Espacio de Trabajo.
        */
        string dirEspacioDeTrabajo;
        /**
         * @brief listaImagenesDisponibles Atributo de tipo vector de strings con los nombres
         *                                 de las imagenes disponibles en una carpeta.
         */
        vector<string> listaImagenesDisponibles;
        /**
         * @brief listaDirDeCarpetas Atributo de tipo vector de strings con las direcciones
         *                           de las carpetas disponibles en el Espacio de Trabajo.
        */
        vector<string> listaDirDeCarpetas;
};

#endif // SISTEMA_H
