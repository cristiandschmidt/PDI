#include "mediana.h"
#include <algorithm>
Mediana::Mediana()
{

}

tuple<float, float, float> Mediana::obtenerMedianas(vector<Pixel> pPixelesVecinos)
{
    vector<unsigned> aux;
    float medianaR = 0.0, medianaG = 0.0, medianaB = 0.0;

    for (Pixel  pixel : pPixelesVecinos)
    {
        aux.push_back(pixel.getIntensidadR());
    }
    sort(aux.begin(), aux.end());
    medianaR = aux[(aux.size()-1)/2];
    aux.clear();

    for (Pixel  pixel : pPixelesVecinos)
    {
        aux.push_back(pixel.getIntensidadG());
    }
    sort(aux.begin(), aux.end());
    medianaG = aux[(aux.size()-1)/2];
    aux.clear();

    for (Pixel  pixel : pPixelesVecinos)
    {
        aux.push_back(pixel.getIntensidadB());
    }
    sort(aux.begin(), aux.end());
    medianaB = aux[(aux.size()-1)/2];
    aux.clear();

    return make_tuple(medianaR, medianaG, medianaB);
}

void Mediana::aplicar(Imagen &pImagen)
{

    float medianaR = 0.0, medianaG = 0.0, medianaB = 0.0;
    vector<Pixel> pixelesVecinos;
    vector<vector<Pixel>> matrizAux;
    matrizAux = pImagen.getMatrizPixeles();
    bool estaEnImagen = false;

    for(unsigned i = 0 ; i < pImagen.getAlto() ; ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j )
        {
            estaEnImagen = i < pImagen.getAlto() - 1  and j < pImagen.getAncho() - 1 and  i > 0 and j > 0;
            if( estaEnImagen )
            {
                pixelesVecinos = {pImagen.getPixel(i, j),  pImagen.getPixel(i+1, j),
                                  pImagen.getPixel(i+1, j-1), pImagen.getPixel(i, j-1),
                                  pImagen.getPixel(i-1, j-1), pImagen.getPixel(i-1, j),
                                  pImagen.getPixel(i-1, j+1), pImagen.getPixel(i, j+1),
                                  pImagen.getPixel(i+1, j+1)};

                medianaR = get<0>(obtenerMedianas(pixelesVecinos));
                medianaG = get<1>(obtenerMedianas(pixelesVecinos));
                medianaB = get<2>(obtenerMedianas(pixelesVecinos));

                matrizAux[i][j] = Pixel(medianaR, medianaG, medianaB);

            }
        }
    }
    pImagen.setMatrizPixeles(matrizAux);

}

Mediana::~Mediana()
{

}

