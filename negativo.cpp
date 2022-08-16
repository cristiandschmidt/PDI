#include "negativo.h"

Negativo::Negativo()
{

}

void Negativo::aplicar(Imagen &pImagen)
{
    float nivelR= 0.0, nivelG = 0.0, nivelB = 0.0;
    for(unsigned i = 0; i < pImagen.getAlto(); ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j)
        {
            nivelR = (pImagen.getIntensidadMaxima()-pImagen.getPixel(i, j).getIntensidadR());
            nivelG = (pImagen.getIntensidadMaxima()-pImagen.getPixel(i, j).getIntensidadG());
            nivelB = (pImagen.getIntensidadMaxima()-pImagen.getPixel(i, j).getIntensidadB());

            pImagen.setPixel(i , j , Pixel(nivelR, nivelG, nivelB));
        }
    }
}

Negativo::~Negativo()
{

}
