#include "histograma.h"
#include <algorithm>
#include <iostream>

Histograma::Histograma()
{

}

void Histograma::aplicar(Imagen &pImagen)
{
    hallarMinPixeles(pImagen);
    hallarMaxPixeles(pImagen);
    hallarPromedioPixeles(pImagen);
    hallarDesvioPixeles(pImagen);
    hallarMapFrecuenciasPixeles(pImagen);
    hallarModasPixeles();
}

void Histograma::graficar(const string &pTipo)
{
    unsigned i = 0;
    if ( pTipo == "grises" )
    {
        for (auto par : mapFrecuenciasPixelesGrises)
        {
            glBegin(GL_QUADS);
            {
                glColor3f(1.0, 0.3, 0);
                glVertex3f(i, 0.0 ,0.0);
                glColor3f(0.0, 0.0, 0.0);
                glVertex3f(i, par.second ,0.0);
                glColor3f(0.0, 0.0, 0.0);
                glVertex3f(i+1, par.second ,0.0);
                glColor3f(1.0, 0.3, 0.0);
                glVertex3f(i+1, 0.0 ,0.0);
            }
            glEnd();
            i++;
        }
    }
    i=0;

    if( pTipo == "R" )
    {
        glBegin(GL_LINE_STRIP);
        {
            glColor3f(1.0,0.0, 0.0);
            for (auto par : mapFrecuenciasPixelesR)
            {
                glVertex3f(i + 0.5, par.second ,0.0);
                i++;
            }
        }
        glEnd();
    }

    i=0;
    if( pTipo == "G" )
    {
        glBegin(GL_LINE_STRIP);
        {
            glColor3f(0.0,1.0, 0.0);
            for (auto par : mapFrecuenciasPixelesG)
            {
                glVertex3f(i+0.5, par.second ,0.0);
                i++;
            }
        }
        glEnd();
    }

    i=0;
    if( pTipo == "B" )
    {
        glBegin(GL_LINE_STRIP);
        {
            glColor3f(0.0,0.0, 1.0);
            for (auto par : mapFrecuenciasPixelesB)
            {
                glVertex3f(i+0.5, par.second ,0.0);
                i++;
            }
        }
        glEnd();
    }

}


void Histograma::hallarMinPixeles(const Imagen &pImagen)
{
    unsigned min, minR, minG, minB;

    min  = pImagen.getIntensidadMaxima();
    minR = pImagen.getIntensidadMaxima();
    minG = pImagen.getIntensidadMaxima();
    minB = pImagen.getIntensidadMaxima();

    for(unsigned i = 0 ; i < pImagen.getAlto(); ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j)
        {
            if (pImagen.getPixel(i, j).getIntensidadRGB() < min )
            {
                min = pImagen.getPixel(i, j).getIntensidadRGB();
            }
            if ( pImagen.getPixel(i, j).getIntensidadR() < minR )
            {
                minR = pImagen.getPixel(i, j).getIntensidadR();
            }
            if ( pImagen.getPixel(i, j).getIntensidadG() < minG ){
                minG = pImagen.getPixel(i, j).getIntensidadG();
            }
            if ( pImagen.getPixel(i, j).getIntensidadB() < minB ){
                minB = pImagen.getPixel(i, j).getIntensidadB();
            }
        }
    }

    minPixelGris = min;
    minPixelesRGB = make_tuple(minR, minG, minB);
}

void Histograma::hallarMaxPixeles(const Imagen &pImagen)
{
    unsigned max = 0, maxR = 0, maxG = 0, maxB = 0;

    for(unsigned i = 0 ; i < pImagen.getAlto(); ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j)
        {
            if (pImagen.getPixel(i, j).getIntensidadRGB() > max)
            {
                max = pImagen.getPixel(i, j).getIntensidadRGB();
            }
            if (pImagen.getPixel(i, j).getIntensidadR() > maxR)
            {
                maxR = pImagen.getPixel(i, j).getIntensidadR();
            }
            if (pImagen.getPixel(i, j).getIntensidadG() > maxG)
            {
                maxG = pImagen.getPixel(i, j).getIntensidadG();
            }
            if (pImagen.getPixel(i, j).getIntensidadB() > maxB)
            {
                maxB = pImagen.getPixel(i, j).getIntensidadB();
            }
        }
    }
    maxPixelGris = max;
    maxPixelesRGB = make_tuple(maxR, maxG, maxB);
}



void Histograma::hallarPromedioPixeles(const Imagen &pImagen)
{
    Pixel suma = 0;
    float prom;
    float promR;
    float promG;
    float promB;
    for(unsigned i = 0 ; i < pImagen.getAlto(); ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j)
        {
            suma = suma + pImagen.getPixel(i, j);
        }
    }

    prom = (float)suma.getIntensidadRGB()/(pImagen.getAlto()*pImagen.getAncho());
    promR = (float)suma.getIntensidadR()/(pImagen.getAlto()*pImagen.getAncho());
    promG = (float)suma.getIntensidadG()/(pImagen.getAlto()*pImagen.getAncho());
    promB = (float)suma.getIntensidadB()/(pImagen.getAlto()*pImagen.getAncho());

    promedioPixelesGrises = prom;
    promedioPixelesRGB = make_tuple(promR, promG, promB);
}


void Histograma::hallarDesvioPixeles(const Imagen &pImagen)
{
    float sumaCuadrados = 0, varianza, sumaCuadradosR = 0, sumaCuadradosG = 0, sumaCuadradosB = 0, varianzaR, varianzaG, varianzaB;

    for(unsigned i = 0 ; i < pImagen.getAlto(); ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j)
        {
            sumaCuadrados += pow(pImagen.getPixel(i, j).getIntensidadRGB() - promedioPixelesGrises, 2);
            sumaCuadradosR += pow(pImagen.getPixel(i, j).getIntensidadR() - get<0>(promedioPixelesRGB), 2);
            sumaCuadradosG += pow(pImagen.getPixel(i, j).getIntensidadG() - get<1>(promedioPixelesRGB), 2);
            sumaCuadradosB += pow(pImagen.getPixel(i, j).getIntensidadB() - get<2>(promedioPixelesRGB), 2);

        }
    }
    varianza = sumaCuadrados/(pImagen.getAlto()*pImagen.getAncho());
    varianzaR = sumaCuadradosR/(pImagen.getAlto()*pImagen.getAncho());
    varianzaG = sumaCuadradosG/(pImagen.getAlto()*pImagen.getAncho());
    varianzaB = sumaCuadradosB/(pImagen.getAlto()*pImagen.getAncho());

    desvioPixelesGrises = sqrt(varianza);
    desvioPixelesRGB = make_tuple(sqrt(varianzaR), sqrt(varianzaG), sqrt(varianzaB));
}

void Histograma::hallarMapFrecuenciasPixeles(const Imagen &pImagen)
{
    map<T, T>::iterator it_buscado;
    map<T, T>::iterator it_buscadoR;
    map<T, T>::iterator it_buscadoG;
    map<T, T>::iterator it_buscadoB;
    unsigned intensidadGrises;
    unsigned intensidadR;
    unsigned intensidadG;
    unsigned intensidadB;

    for(unsigned i = 0 ; i < pImagen.getAlto(); ++i)
    {
        for(unsigned j = 0; j < pImagen.getAncho(); ++j)
        {
            intensidadGrises = pImagen.getPixel(i, j).getIntensidadRGB();
            intensidadR = pImagen.getPixel(i, j).getIntensidadR();
            intensidadG = pImagen.getPixel(i, j).getIntensidadG();
            intensidadB = pImagen.getPixel(i, j).getIntensidadB();

            it_buscado = mapFrecuenciasPixelesGrises.find(intensidadGrises);
            it_buscadoR = mapFrecuenciasPixelesR.find(intensidadR);
            it_buscadoG = mapFrecuenciasPixelesG.find(intensidadG);
            it_buscadoB = mapFrecuenciasPixelesB.find(intensidadB);

            if(it_buscado != mapFrecuenciasPixelesGrises.end())
            {
                mapFrecuenciasPixelesGrises[intensidadGrises] += 1;
            }
            else
            {
                mapFrecuenciasPixelesGrises[intensidadGrises] = 1;
            }
            if(it_buscadoR != mapFrecuenciasPixelesR.end())
            {
                mapFrecuenciasPixelesR[intensidadR] += 1;
            }
            else
            {
                mapFrecuenciasPixelesR[intensidadR] = 1;
            }
            if(it_buscadoG != mapFrecuenciasPixelesG.end())
            {
                mapFrecuenciasPixelesG[intensidadG] += 1;
            }
            else
            {
                mapFrecuenciasPixelesG[intensidadG] = 1;
            }
            if(it_buscadoB != mapFrecuenciasPixelesB.end()){
                mapFrecuenciasPixelesB[intensidadB] += 1;
            }
            else
            {
                mapFrecuenciasPixelesB[intensidadB] = 1;
            }
        }
    }
}

bool mayor(pair<unsigned, unsigned> moda_1, pair<unsigned, unsigned> moda_2){
    return moda_1.second < moda_2.second;
};

void Histograma::hallarModasPixeles()
{
    map<unsigned, unsigned> modaR, modaG, modaB;
    auto it_moda = max_element(mapFrecuenciasPixelesGrises.begin(), mapFrecuenciasPixelesGrises.end(), mayor);
    auto it_modaR = max_element(mapFrecuenciasPixelesR.begin(), mapFrecuenciasPixelesR.end(), mayor);
    auto it_modaG = max_element(mapFrecuenciasPixelesG.begin(), mapFrecuenciasPixelesG.end(), mayor);
    auto it_modaB = max_element(mapFrecuenciasPixelesB.begin(), mapFrecuenciasPixelesB.end(), mayor);

    unsigned claves [] = {it_moda->first, it_modaR->first, it_modaG->first, it_modaB->first};
    unsigned valores[] = {it_moda->second, it_modaR->second, it_modaG->second, it_modaB->second};

    unsigned maxFrec = *max_element(valores, valores+3);

    maxFrecuenciaModas[*find(claves, claves + 3, maxFrec)] = maxFrec;

    modaPixelesGrises[it_moda->first] = it_moda->second;

    modaR[it_modaR->first] = it_modaR->second;
    modaG[it_modaG->first] = it_modaG->second;
    modaB[it_modaB->first] = it_modaB->second;

    modaPixelesRGB = make_tuple(modaR, modaG, modaB);

}

map<T, T> Histograma::getMapFrecuenciasPixelesB() const
{
    return mapFrecuenciasPixelesB;
}

map<T, T> Histograma::getMapFrecuenciasPixelesG() const
{
    return mapFrecuenciasPixelesG;
}

map<T, T> Histograma::getMapFrecuenciasPixelesR() const
{
    return mapFrecuenciasPixelesR;
}

map<T, T> Histograma::getMapFrecuenciasPixelesGrises() const
{
    return mapFrecuenciasPixelesGrises;
}

tuple<map<T, T>, map<T, T>, map<T, T> > Histograma::getModaPixelesRGB() const
{
    return modaPixelesRGB;
}

map<T, T> Histograma::getMaxFrecuenciaModas() const
{
    return maxFrecuenciaModas;
}

tuple<float, float, float> Histograma::getDesvioPixelesRGB() const
{
    return desvioPixelesRGB;
}

float Histograma::getDesvioPixelesGrises() const
{
    return desvioPixelesGrises;
}

tuple<float, float, float> Histograma::getPromedioPixelesRGB() const
{
    return promedioPixelesRGB;
}

float Histograma::getPromedioPixelesGrises() const
{
    return promedioPixelesGrises;
}

tuple<T, T, T> Histograma::getMaxPixelesRGB() const
{
    return maxPixelesRGB;
}

tuple<T, T, T> Histograma::getMinPixelesRGB() const
{
    return minPixelesRGB;
}

T Histograma::getMaxPixelGris() const
{
    return maxPixelGris;
}

T Histograma::getMinPixelGris() const
{
    return minPixelGris;
}

map<T,T> Histograma::getModaPixelesGrises() const
{
    return modaPixelesGrises;
}

Histograma::~Histograma()
{

}

