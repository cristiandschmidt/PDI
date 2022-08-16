#include "sistema.h"
#include <iostream>
#include <dirent.h>

Sistema::Sistema()
{

}

void Sistema::setListaImagenesDisponibles(const string &pDirCarpeta)
{
    string ruta;
    ruta = pDirCarpeta;
    DIR *dir = opendir(ruta.c_str());
    if ( dir != NULL )
    {
        string pto("."), ptopto("..");
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if( entry->d_name != pto and entry->d_name != ptopto )
            {
                listaImagenesDisponibles.push_back(entry->d_name);
            }
        }
        closedir(dir);
    }
}

vector<string> Sistema::getListaImagenesDisponibles() const
{
    return listaImagenesDisponibles;
}
void Sistema::setlistaDirDeCarpetas(const string &pDirEspacioTrabajo)
{
    string ruta;
    ruta = pDirEspacioTrabajo;
    DIR *dir = opendir(ruta.c_str());
    if ( dir != NULL )
    {
        string pto("."), ptopto("..");
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if( entry->d_name != pto and entry->d_name != ptopto )
            {
                listaDirDeCarpetas.push_back(entry->d_name);
            }
        }
        closedir(dir);
    }
}

void Sistema::visualizarImagenes(QApplication *pApp, vector<string> &pListaDirImagenes)
{
    Graficador graficador;
    graficador.setListaImagenes(pListaDirImagenes);
    if(graficador.getNombresImagenesCorrectas().size() == 0)
    {
        cout << "Todas las imagenes de la carpeta estan corruptas." << endl
             << "Volviendo al menu principal..." << endl;
    }
    else
    {
        unsigned cantImgCorruptas = graficador.getNombresImagenesCorruptas().size();
        cout << "Cantidad de imagenes corruptas en la carpeta: " << cantImgCorruptas << endl;
        if( cantImgCorruptas > 0 )
        {
            for (string &imagenCorrupta : graficador.getNombresImagenesCorruptas())
            {
                cout << "- " << imagenCorrupta << endl;
            }
            cout << endl;
        }
        mostrarAtajos();
        graficador.mostrar(pApp);
    }

}


void Sistema::mostrarMenu(QApplication *pApp)
{

    cout << "Sistema De Procesamiento Digital De Imagenes" <<endl;

    string opcionString = "0";
    unsigned opcionExterna = 0;

    while(opcionExterna != 99)
    {
        dirEspacioDeTrabajo = "EspacioDeTrabajo/";
        listaDirDeCarpetas.clear();
        listaImagenesDisponibles.clear();
        cout << endl <<"::::::::::::::Menu Principal::::::::::::::" << endl;
        cout << "Seleccione una opcion: " <<endl;
        cout <<"1- Abrir espacio de trabajo por defecto" << endl;
        cout <<"2- Ingresar nuevo espacio de trabajo" << endl;
        cout <<"3- Ver imagenes almacenadas" << endl;
        cout <<"99- Salir del programa" << endl;
        cout << "Eleccion: ";
        cin >> opcionString;
        opcionExterna = convStringANumero<unsigned>(opcionString);
        while(opcionExterna != 1 and opcionExterna != 2 and opcionExterna != 3 and opcionExterna != 99)
        {
            cout << "Opcion incorrecta. Ingrese nuevamente." << endl;
            cout << "Eleccion: ";
            cin >> opcionString;
            opcionExterna = convStringANumero<unsigned>(opcionString);
        }
        if (opcionExterna == 2 )
        {
            string nuevoEspacioDeTrabajo;
            cout << "El Espacio de Trabajo debe tener la siguiente estructura de carpetas:" << endl;
            cout << "EspacioDeTrabajo ____ carpeta_1 ____ imagen_1.ppm" << endl
                 << "                |              |___ imagen_2.pbm" << endl
                 << "                |___ carpeta_2 ____ imagen_1.aic" << endl
                 << "                              |___ imagen_2.pgm" << endl;

            cout << "Ingrese la direccion del Espacio de Trabajo." << endl;
            cout << "Utilice ../ para subir niveles y / para bajar niveles" << endl;
            cout << "Direccion: ";
            cin >> nuevoEspacioDeTrabajo;
            nuevoEspacioDeTrabajo += "/";
            dirEspacioDeTrabajo = nuevoEspacioDeTrabajo;
        }
        if( opcionExterna == 1 or opcionExterna == 2 )
        {
            setlistaDirDeCarpetas(dirEspacioDeTrabajo);
            if( listaDirDeCarpetas.size() == 0 )
            {
                cout << "Espacio de trabajo vacio. Volviendo al menu principal..." << endl;
            }
            else
            {
                cout << "Seleccione una carpeta: " << endl;
                unsigned i = 1;
                unsigned opcionCarpeta;
                for (string &carpeta : listaDirDeCarpetas)
                {
                    cout << i << "- " << carpeta << endl;
                    i++;
                }
                cout << "Eleccion (100 para ir al menu principal): ";
                cin >> opcionString;
                opcionCarpeta = convStringANumero<unsigned>(opcionString);
                while (opcionCarpeta != 100 and not(opcionCarpeta > 0 and opcionCarpeta <= listaDirDeCarpetas.size()))
                {
                    cout << "Opcion incorrecta. Ingrese nuevamente." << endl;
                    cout << "Eleccion (100 para ir al menu principal): ";
                    cin >> opcionString;
                    opcionCarpeta = convStringANumero<unsigned>(opcionString);
                }

                if( opcionCarpeta != 100 )
                {
                    while (opcionCarpeta != 100 and not(opcionCarpeta > 0 and opcionCarpeta <= listaDirDeCarpetas.size()))
                    {
                        cout << "Opcion incorrecta. Ingrese nuevamente." << endl;
                        cout << "Eleccion (100 para ir al menu principal): ";
                        cin >> opcionString;
                        opcionCarpeta = convStringANumero<unsigned>(opcionString);
                    }
                    if(opcionCarpeta != 100)
                    {
                        setListaImagenesDisponibles(dirEspacioDeTrabajo + listaDirDeCarpetas[opcionCarpeta-1]);
                        while(opcionCarpeta != 100 and listaImagenesDisponibles.size() == 0)
                        {
                            cout << "Carpeta de imagenes vacia. Elija otra carpeta." << endl;
                            cout << "Eleccion (100 para ir al menu principal): ";
                            cin >> opcionString;
                            opcionCarpeta = convStringANumero<unsigned>(opcionString);
                            if(opcionCarpeta != 100)
                            {
                                while (opcionCarpeta != 100 and not(opcionCarpeta > 0 and opcionCarpeta <= listaDirDeCarpetas.size()))
                                {
                                    cout << "Opcion incorrecta. Ingrese nuevamente." << endl;
                                    cout << "Eleccion 100 para ir al menu principal): ";
                                    cin >> opcionString;
                                    opcionCarpeta = convStringANumero<unsigned>(opcionString);
                                }
                                if(opcionCarpeta != 100)
                                {
                                    setListaImagenesDisponibles(dirEspacioDeTrabajo + listaDirDeCarpetas[opcionCarpeta-1]);
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        vector<string> listaDirImagenes;
                        for (string &imagen : listaImagenesDisponibles)
                        {
                            listaDirImagenes.push_back(dirEspacioDeTrabajo + listaDirDeCarpetas[opcionCarpeta-1] + "/" + imagen);
                        }
                        if(opcionCarpeta != 100)
                        {
                            visualizarImagenes(pApp, listaDirImagenes);
                        }
                    }

                }

            }
        }
        if( opcionExterna == 3 )
        {
            setListaImagenesDisponibles("ImagenesAlmacenadas");
            vector<string> listaDirImagenes;
            unsigned i = 0;
            for (string &imagen : listaImagenesDisponibles)
            {
                listaDirImagenes.push_back("ImagenesAlmacenadas/" + imagen);
                i++;
            }
            visualizarImagenes(pApp, listaDirImagenes);
        }
    }
    cout << "Programa finalizado..." <<endl;
}

Sistema::~Sistema()
{

}

void Sistema::mostrarAtajos()
{
    cout << "Atajos de teclado:" << endl;
    cout << "ctrl + '->': imagen siguiente" << endl;
    cout << "ctrl + '<-': imagen anterior" << endl;
    cout << "ctrl + H: ver/ocultar histograma de la imagen" << endl;
    cout << "ctrl + S: aplicar filtro de suavizado" << endl;
    cout << "ctrl + R: aplicar filtro de realce de bordes" << endl;
    cout << "ctrl + M: aplicar filtro de mediana" << endl;
    cout << "ctrl + C: aplicar ajuste de contraste" << endl;
    cout << "ctrl + N: aplicar negativo" << endl;
    cout << "ctrl + B: aplicar binarizado" << endl;
    cout << "ctrl + '+': aumentar brillo" << endl;
    cout << "ctrl + '-': disminuir brillo" << endl;
    cout << "ctrl + '-': disminuir brillo" << endl;
    cout << "Mantener ctrl + FlechaArriba: aumentar brillo X5" << endl;
    cout << "Mantener ctrl + FlechaAbajo: disminuir brillo X5" << endl;
    cout << "ctrl + Alt + '-': (Alternativa)reducir brillo" << endl;
    cout << "ctrl + '1': Aplicar LUT 1" << endl;
    cout << "ctrl + '2': Aplicar LUT 2" << endl;
    cout << "ctrl + click izquierdo: detectar area" << endl;
    cout << "ctrl + click izquierdo y arrastrar: zoom sobre región abarcada" << endl;
    cout << "ctrl + click derecho: salir del modo zoom" << endl;
    cout << "ctrl + Z: deshacer los cambios realizados sobre la imagen" << endl;
    cout << "ctrl + G: guardar imagen actual" << endl;
    cout << "ctrl + A: ver/ocultar imagen de atajos" << endl;
}


