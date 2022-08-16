#include "brillo.h"
#include <iostream>
using namespace std;
Brillo::Brillo(int pUnidades)
{
    unidades = abs(pUnidades);
    if(pUnidades < 0)
    {
        aumentarBrillo = false;
    }
}

void Brillo::aplicar(Imagen &pImagen)
{
    unsigned intensidadMax = pImagen.getIntensidadMaxima();
    Pixel pixelModificado;

    if( aumentarBrillo ){
        for(unsigned i = 0; i < pImagen.getAlto(); ++i)
        {
            for(unsigned j = 0; j < pImagen.getAncho(); ++j )
            {
                pixelModificado.setIntensidadR(unidades);
                pixelModificado.setIntensidadG(unidades);
                pixelModificado.setIntensidadB(unidades);

                pixelModificado = pixelModificado + pImagen.getPixel(i, j);

                if( pixelModificado.getIntensidadR() > intensidadMax )
                {
                    pixelModificado.setIntensidadR(intensidadMax);
                }
                if( pixelModificado.getIntensidadG() > intensidadMax )
                {
                    pixelModificado.setIntensidadG(intensidadMax);
                }
                if( pixelModificado.getIntensidadB() > intensidadMax )
                {
                    pixelModificado.setIntensidadB(intensidadMax);
                }
                pImagen.setPixel(i, j, pixelModificado);
            }
        }
    }
    else
    {
        for(unsigned i = 0; i < pImagen.getAlto(); ++i)
        {
            for(unsigned j = 0; j < pImagen.getAncho(); ++j )
            {
                pixelModificado.setIntensidadR(unidades);
                pixelModificado.setIntensidadG(unidades);
                pixelModificado.setIntensidadB(unidades);

                pImagen.setPixel(i, j, pImagen.getPixel(i, j) - pixelModificado);
            }
        }
    }
}

Brillo::~Brillo()
{

}
