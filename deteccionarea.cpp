#include "deteccionarea.h"
#include <iostream>

DeteccionArea::DeteccionArea(unsigned pFil, unsigned pCol)
{
    fil = pFil;
    col = pCol;
    tolerancia = 33;
}

void DeteccionArea::aplicar(Imagen &pImagen)
{
    pixelInicial = pImagen.getPixel(fil, col);
    vector<bool> colBooleana(pImagen.getAncho(), false);
    vector<vector<bool>> matrizBooleana(pImagen.getAlto(), colBooleana);

    rellenar(fil, col, pImagen, matrizBooleana, 1);
    rellenar(fil, col-1, pImagen, matrizBooleana, 2);
    for(unsigned i = 0 ; i < pImagen.getAlto(); ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j )
        {
            if( matrizBooleana[i][j] == true )
            {
                pImagen.setPixel(i, j, Pixel(0,0,255));
            }
        }

    }
}

DeteccionArea::~DeteccionArea()
{

}

unsigned distColor(Pixel pixel1, Pixel pixel2)
{
    return pow(((pixel1.getIntensidadR() - pixel2.getIntensidadR()) * (pixel1.getIntensidadR() - pixel2.getIntensidadR()))
               + ((pixel1.getIntensidadG() - pixel2.getIntensidadG()) * (pixel1.getIntensidadG() - pixel2.getIntensidadG()))
               +((pixel1.getIntensidadB() - pixel2.getIntensidadB() ) * (pixel1.getIntensidadB() - pixel2.getIntensidadB() )) , 0.5f);
}


void DeteccionArea::rellenar(unsigned pFil, unsigned pCol, Imagen &pImagen, vector<vector<bool>> &mb, unsigned parte)
{
    if(pFil < mb.size() and pCol < mb[0].size())
    {
        if(distColor(pixelInicial, pImagen.getPixel(pFil,pCol)) < tolerancia and not mb[pFil][pCol])
        {
            mb[pFil][pCol] = true;
            ++area;
            if(parte == 1)
            {
                rellenar(pFil-1,pCol-1,pImagen,mb,parte);
                rellenar(pFil-1,pCol,pImagen,mb,parte);
                rellenar(pFil-1,pCol+1,pImagen,mb,parte);
                rellenar(pFil,pCol+1,pImagen,mb,parte);
                rellenar(pFil+1,pCol+1,pImagen,mb,parte);

            }
            else if(parte == 2)
            {
                rellenar(pFil-1,pCol-1,pImagen,mb,parte);
                rellenar(pFil+1,pCol,pImagen,mb,parte);
                rellenar(pFil+1,pCol-1,pImagen,mb,parte);
                rellenar(pFil,pCol-1,pImagen,mb,parte);
                rellenar(pFil+1,pCol+1,pImagen,mb,parte);
            }
        }
    }
}


unsigned DeteccionArea::getTolerancia() const
{
    return tolerancia;
}

void DeteccionArea::setTolerancia(const unsigned &pTolerancia)
{
    tolerancia = pTolerancia;
}

unsigned DeteccionArea::getArea() const
{
    return area;
}
