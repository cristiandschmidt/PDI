#include "realcebordes.h"
#include <iostream>
using namespace std;
RealceBordes::RealceBordes()
{

}

void RealceBordes::aplicar(Imagen &pImagen)
{
    vector<vector<Pixel>> matrizAux;
    matrizAux = pImagen.getMatrizPixeles();
    Pixel pixelAux;
    bool estaEnImagen = false;
    unsigned intensidadMax = pImagen.getIntensidadMaxima();
    for(unsigned i = 0 ; i < pImagen.getAlto(); ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j )
        {
            estaEnImagen = i < pImagen.getAlto()-1  and j < pImagen.getAncho()-1 and  i > 0 and j > 0;

            if( estaEnImagen )
            {
                pixelAux = ((pImagen.getPixel(i,j)*5.0) - pImagen.getPixel(i-1,j)
                            - pImagen.getPixel(i,j-1)- pImagen.getPixel(i,j+1) - pImagen.getPixel(i+1,j));

                if(pixelAux.getIntensidadR() > intensidadMax)
                {
                    pixelAux.setIntensidadR(intensidadMax);
                }
                if(pixelAux.getIntensidadG() > intensidadMax)
                {
                    pixelAux.setIntensidadG(intensidadMax);
                }
                if(pixelAux.getIntensidadB() > intensidadMax)
                {
                    pixelAux.setIntensidadB(intensidadMax);
                }

                matrizAux[i][j] = pixelAux;
            }
        }
    }
    pImagen.setMatrizPixeles(matrizAux);
}

RealceBordes::~RealceBordes()
{

}
