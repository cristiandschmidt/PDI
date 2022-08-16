#include "imagenaic.h"

#include <iostream>
#include <sstream>
#include "conv_string.h"

ImagenAIC::ImagenAIC()
{

}

bool ImagenAIC::abrir(const string &pDireccion)
{
    nombre = pDireccion;
    int pos = nombre.rfind('/');
    nombre.erase(0, pos + 1);
    unsigned contador = 0;
    unsigned intensidad = 0;
    ifstream entradaAIC(pDireccion);
    getline(entradaAIC, tipo, '\n');

    if (tipo != "P2C")
    {
        return false;
    }

    getline(entradaAIC, metadatos,'\n');

    entradaAIC >> ancho >> alto;

    dimensionar(alto, ancho);

    entradaAIC >> intensidadMaxima;

    if (intensidadMaxima == 0 or alto == 0 or ancho == 0)
    {
        return false;
    }

    entradaAIC >> intensidad >> contador;
    for(unsigned i = 0; i < alto ; ++i)
    {
        for(unsigned j =0; j < ancho ;++j)
        {

            if(contador == 0)
            {
                entradaAIC >> intensidad >> contador;
            }
            matrizPixeles[i][j] = Pixel(intensidad , intensidad, intensidad);
            contador--;
        }
    }

    entradaAIC.close();
    return true;
}

void ImagenAIC::guardar(const string &pDireccion)
{
    ofstream salidaAIC(pDireccion);

    salidaAIC << "P2C" << endl << metadatos << endl << ancho << " " << alto << endl << intensidadMaxima << endl;

    Pixel auxiliar;
    int contador = 0;
    unsigned intensidadActual = 0, valorAcomparar = 0;
    auxiliar.setIntensidadR(matrizPixeles[0][0].getIntensidadR());
    auxiliar.setIntensidadG(matrizPixeles[0][0].getIntensidadG());
    auxiliar.setIntensidadB(matrizPixeles[0][0].getIntensidadB());

    intensidadActual = auxiliar.getIntensidadRGB();

    for(unsigned i = 0; i < alto; ++i)
    {
        for(unsigned j = 0; j < ancho; ++j)
        {
            auxiliar.setIntensidadR(matrizPixeles[i][j].getIntensidadR());
            auxiliar.setIntensidadG(matrizPixeles[i][j].getIntensidadG());
            auxiliar.setIntensidadB(matrizPixeles[i][j].getIntensidadB());

            valorAcomparar = auxiliar.getIntensidadRGB();

            if(intensidadActual == valorAcomparar)
            {
                ++contador;
            }
            else
            {
                salidaAIC << intensidadActual << " " << contador << " " ;
                intensidadActual = valorAcomparar;
                contador = 1;
            }
            if (i == alto -1  and j == ancho -1 )
            {
                salidaAIC << intensidadActual << " " << contador;
            }
        }
    }
    salidaAIC.close();
}

ImagenAIC::~ImagenAIC()
{

}

