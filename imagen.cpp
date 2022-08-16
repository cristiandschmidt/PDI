#include "imagen.h"

Imagen::Imagen()
{
    direccionDeGuardado = "ImagenesAlmacenadas/";
}

void Imagen::dibujar()
{
    Pixel pixelAux;
    glPushMatrix();
    {
        glBegin(GL_QUADS);
        {
            for(int i = (alto - 1); i >= 0; --i)
            {
                for(unsigned j = 0; j < ancho; ++j)
                {
                    pixelAux = getPixel(i, j);
                    glColor3f((float)pixelAux.getIntensidadR()/intensidadMaxima, (float)pixelAux.getIntensidadG()/intensidadMaxima, (float)pixelAux.getIntensidadB()/intensidadMaxima);
                    glVertex3f(j, alto - i, 0);
                    glVertex3f(j+1, alto - i, 0);
                    glVertex3f(j + 1, alto - (i+1), 0);
                    glVertex3f(j, alto-(i+1), 0);
                }
            }
        };
        glEnd();

    } glPopMatrix();
}

Pixel Imagen::getPixel(const unsigned &pFila, const unsigned &pColumna) const
{
    return matrizPixeles[pFila][pColumna];
}

void Imagen::setPixel(const unsigned &pFila, const unsigned &pColumna, const Pixel &pPixel)
{
    matrizPixeles[pFila][pColumna] = pPixel;
}

void Imagen::dimensionar(const int &pAlto,  const int &pAncho)
{
    ancho = pAncho;
    alto = pAlto;
    matrizPixeles.resize(pAlto);
    for(unsigned i= 0; i< matrizPixeles.size();++i)
    {
        matrizPixeles[i].resize(pAncho);
    }

}

vector<vector<Pixel> > Imagen::getMatrizPixeles() const
{
    return matrizPixeles;
}

void Imagen::setMatrizPixeles(const vector<vector<Pixel>> &pMatrizPixeles)
{
    matrizPixeles = pMatrizPixeles;
}

Imagen::~Imagen()
{

}

string Imagen::getDireccionDeGuardado() const
{
    return direccionDeGuardado;
}

void Imagen::setDireccionDeGuardado(const string &pDireccionDeGuardado)
{
    direccionDeGuardado = pDireccionDeGuardado;
}

void Imagen::setTipoAnterior(const string &pTipoAnterior)
{
    tipoAnterior = pTipoAnterior;
}

bool Imagen::getBinarizada() const
{
    return binarizada;
}

void Imagen::setBinarizada(bool pBinarizada)
{
    binarizada = pBinarizada;
}

string Imagen::getTipoAnterior() const
{
    return tipoAnterior;
}

void Imagen::setNombre(const string &pNombre)
{
    nombre = pNombre;
}

string Imagen::getNombre() const
{
    return nombre;
}


string Imagen::getTipo() const
{
    return tipo;
}

void Imagen::setTipo(const string &pTipo)
{
    tipo = pTipo;
}

unsigned Imagen::getAncho() const
{
    return ancho;
}


unsigned Imagen::getAlto() const
{
    return alto;
}


unsigned Imagen::getIntensidadMaxima() const
{
    return intensidadMaxima;
}

void Imagen::setIntensidadMaxima(const unsigned &pIntensidadMaxima)
{
    intensidadMaxima = pIntensidadMaxima;
}

void Imagen::setMetadatos(const string &pMetadato)
{
    metadatos = pMetadato;
}

string Imagen::getMetadatos() const
{
    return metadatos;
}

