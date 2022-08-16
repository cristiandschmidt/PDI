#include <QApplication>
#include "sistema.h"
#include "imagenaic.h"
int main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    Sistema sistema;
    try
    {
        sistema.mostrarMenu(&App);
    }
    catch (...)
    {
        cout << " Ocurrió un error inesperado. Reiniciando..." << endl;
        sistema.mostrarMenu(&App);
    }

}
