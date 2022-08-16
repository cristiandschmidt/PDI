#include "contraste.h"
#include <iostream>

Contraste::Contraste()
{

}

void Contraste::aplicar(Imagen &pImagen)
{
    Pixel pixelOriginal, pixelContrastado;
    unsigned intensidadMax = pImagen.getIntensidadMaxima();
    unsigned minR, minG, minB, maxR = 0, maxG = 0, maxB = 0;

    minR =  pImagen.getIntensidadMaxima();
    minG = pImagen.getIntensidadMaxima();
    minB = pImagen.getIntensidadMaxima();

    for(unsigned i = 0 ; i < pImagen.getAlto(); ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j )
        {
            if ( pImagen.getPixel(i, j).getIntensidadR() < minR )
            {
                minR = pImagen.getPixel(i, j).getIntensidadR();
            }
            if ( pImagen.getPixel(i, j).getIntensidadR() > maxR )
            {
                maxR = pImagen.getPixel(i, j).getIntensidadR();
            }
            if ( pImagen.getPixel(i, j).getIntensidadG() < minG )
            {
                minG = pImagen.getPixel(i, j).getIntensidadG();
            }
            if ( pImagen.getPixel(i, j).getIntensidadG() > maxG )
            {
                maxG = pImagen.getPixel(i, j).getIntensidadG();
            }
            if ( pImagen.getPixel(i, j).getIntensidadB() < minB )
            {
                minB = pImagen.getPixel(i, j).getIntensidadB();
            }
            if ( pImagen.getPixel(i, j).getIntensidadB() > maxB )
            {
                maxB = pImagen.getPixel(i, j).getIntensidadB();
            }
        }
    }

    for(unsigned i = 0 ; i < pImagen.getAlto(); ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j )
        {
            pixelOriginal = pImagen.getPixel(i, j);

            pixelContrastado.setIntensidadR( (float)(pixelOriginal.getIntensidadR() - minR)/(maxR - minR)*intensidadMax );
            pixelContrastado.setIntensidadG( (float)(pixelOriginal.getIntensidadG() - minG)/(maxG - minG)*intensidadMax );
            pixelContrastado.setIntensidadB( (float)(pixelOriginal.getIntensidadB() - minB)/(maxB - minB)*intensidadMax );

            pImagen.setPixel(i, j, pixelContrastado);
        }
    }
}

Contraste::~Contraste()
{

}
