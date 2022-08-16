#include "pixel.h"

Pixel::Pixel()
{

}

Pixel::Pixel(const T &pIntensidadRGB)
{
    setIntensidadRGB(pIntensidadRGB);
}

Pixel::Pixel(const T &pIntensidadR, const T &pIntensidadG, const T &pIntensidadB)
{
    intensidadR = pIntensidadR;
    intensidadG = pIntensidadG;
    intensidadB = pIntensidadB;
}

T Pixel::getIntensidadRGB() const
{
    return (intensidadR + intensidadG + intensidadB)/3;
}

void Pixel::setIntensidadRGB(const T &pIntensidadRGB)
{
    intensidadR = pIntensidadRGB;
    intensidadG = pIntensidadRGB;
    intensidadB = pIntensidadRGB;
}

T Pixel::getIntensidadR() const
{
    return intensidadR;
}

void Pixel::setIntensidadR(const T &pIntensidadR)
{
    intensidadR = pIntensidadR;
}

T Pixel::getIntensidadG() const
{
    return intensidadG;
}

void Pixel::setIntensidadG(const T &pIntensidadG)
{
    intensidadG = pIntensidadG;
}

T Pixel::getIntensidadB() const
{
    return intensidadB;
}

void Pixel::setIntensidadB(const T &pIntensidadB)
{
    intensidadB = pIntensidadB;
}

Pixel Pixel::operator+(const Pixel &pPixel)
{
    unsigned nivelR = this->intensidadR + pPixel.getIntensidadR();
    unsigned nivelG = this->intensidadG + pPixel.getIntensidadG();
    unsigned nivelB = this->intensidadB + pPixel.getIntensidadB();
    return Pixel(nivelR , nivelG , nivelB);
}

Pixel Pixel::operator-(const Pixel &pPixel)
{
    unsigned nivelR = 0;
    unsigned nivelG = 0;
    unsigned nivelB = 0;

    if ( this->intensidadR > pPixel.getIntensidadR() )
    {
        nivelR = this->intensidadR - pPixel.getIntensidadR();
    }
    if ( this->intensidadG > pPixel.getIntensidadG() )
    {
        nivelG = this->intensidadG - pPixel.getIntensidadG();
    }
    if ( this->intensidadB > pPixel.getIntensidadB() )
    {
        nivelB = this->intensidadB - pPixel.getIntensidadB();
    }

    return Pixel(nivelR , nivelG , nivelB);
}

Pixel Pixel::operator*(const float &pNumero)
{
    unsigned nivelR = this->intensidadR * pNumero;
    unsigned nivelG = this->intensidadG * pNumero;
    unsigned nivelB = this->intensidadB * pNumero;
    return Pixel(nivelR , nivelG , nivelB);
}

bool Pixel::operator<(const Pixel &pPixel)
{
    return this->getIntensidadRGB() < pPixel.getIntensidadRGB();
}

bool Pixel::operator>(const Pixel &pPixel)
{
    return this->getIntensidadRGB() > pPixel.getIntensidadRGB();
}

bool Pixel::operator==(const Pixel &pPixel)
{
    return this->getIntensidadRGB() == pPixel.getIntensidadRGB();
}
