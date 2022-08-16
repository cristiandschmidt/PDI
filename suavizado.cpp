#include "suavizado.h"
#include <stdlib.h>

Suavizado::Suavizado()
{

}

void Suavizado::aplicar(Imagen &pImagen)
{
    vector<vector<Pixel>> matrizAux;
    matrizAux = pImagen.getMatrizPixeles();
    Pixel pixelAux;
    bool estaEnImagen = false;
    for(unsigned i = 0 ; i < pImagen.getAlto(); ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j )
        {
            estaEnImagen = i < pImagen.getAlto()-1  and j < pImagen.getAncho()-1 and  i > 0 and j > 0;

            if(estaEnImagen)
            {
                pixelAux = (pImagen.getPixel(i,j) + pImagen.getPixel(i+1,j)
                            + pImagen.getPixel(i+1,j-1) + pImagen.getPixel(i,j-1)
                            + pImagen.getPixel(i-1,j-1) + pImagen.getPixel(i-1,j)
                            + pImagen.getPixel(i-1,j+1) + pImagen.getPixel(i,j+1)
                            + pImagen.getPixel(i+1,j+1))*(1.0/9);
                matrizAux[i][j] = pixelAux;
            }
        }
    }
    pImagen.setMatrizPixeles(matrizAux);
}

Suavizado::~Suavizado()
{

}

