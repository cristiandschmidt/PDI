#include "imagenpnm.h"

ImagenPNM::ImagenPNM()
{
    tipos.push_back("P1");
    tipos.push_back("P2");
    tipos.push_back("P3");
    tipos.push_back("P4");
    tipos.push_back("P5");
    tipos.push_back("P6");
}

bool ImagenPNM::abrir(const string &pDireccion)
{
    ifstream entradaPNM(pDireccion, ios::in | ios::binary);
    nombre = pDireccion;
    int pos = nombre.rfind('/');
    nombre.erase(0, pos + 1);
    getline(entradaPNM, tipo, '\n');
    tipoAnterior = tipo;
    auto buscado = find(tipos.begin(), tipos.end(), tipo);

    if (buscado == tipos.end())
    {
        return false;
    }

    getline(entradaPNM, metadatos,'\n');

    entradaPNM >> ancho >> alto;
    dimensionar(alto, ancho);

    if (alto == 0 or ancho == 0)
    {
        return false;
    }
    bool pixelesComoTexto = (tipo == tipos[P1] or tipo == tipos[P2] or tipo == tipos[P3]) ? true : false;

    unsigned intensidad = 0, intensidadR = 0, intensidadG = 0, intensidadB = 0;
    if(pixelesComoTexto)
    {
        unsigned char opcion = (tipo == tipos[P1] ? P1 : tipo == tipos[P2] ? P2 : P3);

        switch (opcion)
        {
            case P1:
            {
                intensidadMaxima = 255;
                for(unsigned i = 0; i < alto; ++i)
                {
                    for(unsigned j = 0; j < ancho; ++j)
                    {
                        entradaPNM >> intensidad;
                        setPixel(i, j, Pixel(intensidad));
                    }
                }
                break;
            }
            case P2:
            {
                entradaPNM >> intensidadMaxima;
                if (intensidadMaxima == 0)
                {
                    return false;
                }
                for(unsigned i = 0; i < alto; ++i)
                {
                    for(unsigned j = 0; j < ancho; ++j)
                    {
                        entradaPNM >> intensidad;
                        setPixel(i, j, Pixel(intensidad));
                    }
                }
                break;
            }
            case P3:
            {
                entradaPNM >> intensidadMaxima;
                if (intensidadMaxima == 0)
                {
                    return false;
                }
                for(unsigned i = 0; i < alto; ++i)
                {
                    for(unsigned j=0; j < ancho; ++j)
                    {
                        entradaPNM >> intensidadR >> intensidadG >> intensidadB;
                        setPixel(i, j, Pixel(intensidadR, intensidadG, intensidadB));
                    }
                }
                break;
            }
        }
    }
    else
    {
        unsigned char opcion = (tipo == tipos[P4] ? P4 : tipo == tipos[P5] ? P5 : P6);
        switch ( opcion )
        {
            case P4:
            {
                intensidadMaxima = 255;
                char tamanioDato = 1;
                entradaPNM.seekg(0, ios::end);
                unsigned posLectura = unsigned(entradaPNM.tellg()) - (ancho*alto);
                entradaPNM.seekg(posLectura);
                for(unsigned i = 0; i < alto; ++i)
                {
                    for(unsigned j = 0; j < ancho; ++j)
                    {
                        entradaPNM.read((char*)&intensidad, tamanioDato);
                        setPixel(i, j, Pixel(intensidad));
                    }
                }
                break;
            }
            case P5:
            {
                entradaPNM >> intensidadMaxima;
                if (intensidadMaxima == 0)
                {
                    return false;
                }
                char tamanioDato = 4;
                if (intensidadMaxima <= 255)
                {
                    tamanioDato = 1;
                }
                entradaPNM.seekg(0, ios::end);
                unsigned posLectura = unsigned(entradaPNM.tellg()) - (ancho*alto);
                entradaPNM.seekg(posLectura);
                for(unsigned i = 0; i < alto; ++i)
                {
                    for(unsigned j = 0; j < ancho; ++j)
                    {
                        entradaPNM.read((char*)&intensidad, tamanioDato);
                        setPixel(i, j, Pixel(intensidad));
                    }
                }
                break;
            }
            case P6:
            {

                entradaPNM >> intensidadMaxima;
                if (intensidadMaxima == 0)
                {
                    return false;
                }
                char tamanioDato = 4;
                if (intensidadMaxima <= 255)
                {
                    tamanioDato = 1;
                }
                entradaPNM.seekg(0, entradaPNM.end);
                unsigned posLectura = unsigned(entradaPNM.tellg()) - ((ancho*alto*3));
                entradaPNM.seekg(posLectura);
                for(unsigned i = 0; i < alto; ++i)
                {
                    for(unsigned j = 0; j < ancho; ++j)
                    {
                        entradaPNM.read((char*)&intensidadR, tamanioDato);
                        entradaPNM.read((char*)&intensidadG, tamanioDato);
                        entradaPNM.read((char*)&intensidadB, tamanioDato);
                        setPixel(i, j, Pixel(intensidadR, intensidadG, intensidadB));
                    }
                }
                break;
            }

        }
    }
    entradaPNM.close();
    return true;
}

void ImagenPNM::guardar(const string &pDireccion)
{
    ofstream salidaPNM;
    bool pixelesComoTexto = (tipo == tipos[P1] or tipo == tipos[P2] or tipo == tipos[P3]) ? true : false;

    if(pixelesComoTexto)
    {
        unsigned char opcion = (tipo == tipos[P1] ? P1 : tipo == tipos[P2] ? P2 : P3);
        switch (opcion)
        {
            case P1:
            {
                salidaPNM.open(pDireccion, ios::out | ios::binary);
                salidaPNM << tipo << endl;
                salidaPNM << metadatos << endl;
                salidaPNM << ancho << " " << alto << endl;

                for (unsigned i = 0; i < alto; ++i)
                {
                    for(unsigned j = 0; j < ancho; ++j)
                    {
                        salidaPNM << matrizPixeles[i][j].getIntensidadRGB() << " ";
                    }
                }
                salidaPNM.close();
                break;
            }
            case P2:
            {
                unsigned intensidad = 0;
                salidaPNM.open(pDireccion,  ios::out | ios::binary);
                salidaPNM << tipo << endl;
                salidaPNM << metadatos << endl;
                salidaPNM << ancho << " " << alto << endl << intensidadMaxima << endl;

                for (unsigned i = 0; i < alto; ++i)
                {
                    for(unsigned j = 0; j < ancho; ++j)
                    {
                        if(tipoAnterior == "P3" or tipoAnterior == "P6")
                        {
                            intensidad = ((matrizPixeles[i][j].getIntensidadR() * 0.2989) + (matrizPixeles[i][j].getIntensidadG() * 0.5870)
                                          +(matrizPixeles[i][j].getIntensidadB() * 0.1140));

                        }
                        else
                        {
                            intensidad = matrizPixeles[i][j].getIntensidadRGB();
                        }
                        salidaPNM << intensidad << " ";
                    }
                }
                salidaPNM.close();
                break;
            }
            case P3:
            {
                salidaPNM.open(pDireccion,  ios::out | ios::binary);
                salidaPNM << tipo << endl;
                salidaPNM << metadatos << endl;
                salidaPNM << ancho << " " << alto << endl << intensidadMaxima << endl;

                for (unsigned i = 0; i < alto; ++i)
                {
                    for(unsigned j = 0; j < ancho; ++j)
                    {
                        salidaPNM << matrizPixeles[i][j].getIntensidadR() << " " <<  matrizPixeles[i][j].getIntensidadG() << " " <<  matrizPixeles[i][j].getIntensidadB() << " ";
                    }
                }

                salidaPNM.close();
                break;
            }
        }
    }
    else
    {
        unsigned char opcion = (tipo == tipos[P4] ? P4 : tipo == tipos[P5] ? P5 : P6);
        switch  ( opcion )
        {
            case P4:
            {
                unsigned intensidad = 0;
                char tamanioDato = 1;
                salidaPNM.open(pDireccion , ios::out | ios::binary);
                salidaPNM << tipo << endl;
                salidaPNM << metadatos << endl;
                salidaPNM << ancho << " " << alto << endl;
                for (unsigned i = 0; i < alto; ++i)
                {
                    for(unsigned j = 0; j < ancho; ++j)
                    {
                        intensidad = matrizPixeles[i][j].getIntensidadRGB();
                        salidaPNM.write((char*)&intensidad, tamanioDato);
                    }
                }
                salidaPNM.close();
                break;
            }
            case P5:
            {
                unsigned intensidad = 0;
                char tamanioDato = 4;
                if (intensidadMaxima <= 255)
                {
                    tamanioDato = 1;
                }
                salidaPNM.open(pDireccion , ios::out | ios::binary);
                salidaPNM << tipo << endl;
                salidaPNM << metadatos << endl;
                salidaPNM << ancho << " " << alto << endl << intensidadMaxima << endl;
                for (unsigned i = 0; i < alto; ++i)
                {
                    for(unsigned j = 0; j < ancho; ++j)
                    {
                        if(tipoAnterior == "P3" or tipoAnterior == "P6")
                        {
                            intensidad = ((matrizPixeles[i][j].getIntensidadR() * 0.2989) + (matrizPixeles[i][j].getIntensidadG() * 0.5870)
                                          +(matrizPixeles[i][j].getIntensidadB() * 0.1140));

                        }
                        else
                        {
                            intensidad = matrizPixeles[i][j].getIntensidadRGB();
                        }
                        salidaPNM.write((char*) &intensidad, tamanioDato);
                    }
                }
                salidaPNM.close();
                break;
            }
            case P6:
            {
                unsigned intensidadR = 0, intensidadG = 0, intensidadB = 0;
                char tamanioDato = 4;
                if (intensidadMaxima <= 255)
                {
                    tamanioDato = 1;
                }
                salidaPNM.open(pDireccion , ios::out | ios::binary);
                salidaPNM << tipo << endl;
                salidaPNM << metadatos << endl;
                salidaPNM << ancho << " " << alto << endl << intensidadMaxima << endl;
                for (unsigned i = 0; i < alto; ++i)
                {
                    for(unsigned j = 0; j < ancho; ++j)
                    {
                        intensidadR = matrizPixeles[i][j].getIntensidadR();
                        intensidadG = matrizPixeles[i][j].getIntensidadG();
                        intensidadB = matrizPixeles[i][j].getIntensidadB();
                        salidaPNM.write((char*) &intensidadR, tamanioDato);
                        salidaPNM.write((char*) &intensidadG, tamanioDato);
                        salidaPNM.write((char*) &intensidadB, tamanioDato);
                    }
                }
                salidaPNM.close();
                break;
            }
        }
    }
    tipoAnterior = tipo;
}

ImagenPNM::~ImagenPNM()
{

}
