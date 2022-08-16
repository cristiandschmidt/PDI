#include "binarizado.h"

Binarizado::Binarizado(unsigned pValorBinarizado)
{
    valorBinarizado = pValorBinarizado;
}

void Binarizado::aplicar(Imagen &pImagen)
{
    bool correcto = valorBinarizado >= 0 and valorBinarizado <= pImagen.getIntensidadMaxima();
    if( correcto )
    {
        for(unsigned i = 0; i < pImagen.getAlto(); ++i)
        {
            for(unsigned j = 0; j<pImagen.getAncho(); ++j)
            {
                if(pImagen.getPixel(i, j).getIntensidadRGB() <= valorBinarizado)
                {
                    pImagen.setPixel(i , j , Pixel(0,0,0) );
                }
                else
                {
                    pImagen.setPixel(i , j , Pixel( pImagen.getIntensidadMaxima(),
                                                    pImagen.getIntensidadMaxima(),
                                                    pImagen.getIntensidadMaxima()));
                }
            }
        }
    }
}

Binarizado::~Binarizado()
{

}
