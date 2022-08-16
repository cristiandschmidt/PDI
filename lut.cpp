#include "lut.h"

LUT::LUT()
{

}

void LUT::aplicar(Imagen &pImagen)
{
    int valorIndice = 0;
    float R, G, B;
    for(unsigned i = 0; i < pImagen.getAlto(); ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j)
        {
            valorIndice = (pImagen.getPixel(i,j).getIntensidadRGB());

            R = tablaR[valorIndice];
            G = tablaG[valorIndice];
            B = tablaB[valorIndice];
            pImagen.setPixel(i, j, Pixel(R,G,B));
        }
    }
}

void LUT::cargarLUT(const string &pDireccion)
{
    ifstream archi(pDireccion,ios::in | ios::binary);
    uint indice, colorR, colorG, colorB;
    tablaR.clear();
    tablaG.clear();
    tablaB.clear();
    if(archi.is_open())
    {
        string titulo;
        getline(archi, titulo, '\n');
        while(archi >> indice >> colorR >> colorG >> colorB)
        {
            tablaR.push_back(colorR);
            tablaG.push_back(colorG);
            tablaB.push_back(colorB);
        }
    }
}

LUT::~LUT()
{

}
