#ifndef CONV_STRING_H
#define CONV_STRING_H

#include <string>
#include <sstream>
/**
 * @brief Modulo con plantillas de funciones que permiten la conversion entre tipos numericos y strings.
 * @author Cristian Daniel Schmidt
 */
using namespace std;

template<class T>
/**
 * @brief convStringANumero Plantilla de funcion que permite convertir un string a numero.
 * @param pCadena Variable de tipo string a convertir.
 * @return Variable numérica que se obtiene de la convesión.
 */
T convStringANumero(string pCadena);

template<class B>
/**
 * @brief convNumeroAString Plantilla de funcion que permite convertir un numero a string.
 * @param pNumero Variable de tipo numérica a convertir.
 * @return Variable de tipo string que se obtiene de la conversión.
 */
string convNumeroAString(B pNumero);

template<class T>
T convStringANumero(string pCadena){
    T resultado;

    istringstream iss;
    iss.str(pCadena);
    iss >> resultado;

    return resultado;
}

template<class B>
string convNumeroAString(B pNumero){
    string resultado;

    ostringstream oss;
    oss << pNumero;
    resultado = oss.str();

    return resultado;
}

#endif // CONV_STRING_H
