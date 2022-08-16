#include "graficador.h"
#include "sistema.h"
#include <QString>

Graficador::Graficador()
{
    dimensionX = GetSystemMetrics(SM_CXSCREEN) - GetSystemMetrics(SM_CXSCREEN)/2;

    dimensionY = GetSystemMetrics(SM_CYSCREEN) - GetSystemMetrics(SM_CYSCREEN)/2;

    atajos.abrir("atajos.pnm");

}

void Graficador::setImagen(const unsigned &pNumeroImg)
{
    imagenActual = pNumeroImg;
}

vector<string> Graficador::getNombresImagenesCorrectas() const
{
    return nombresImagenesCorrectas;
}

vector<string> Graficador::getNombresImagenesCorruptas() const
{
    return nombresImagenesCorruptas;
}

void Graficador::mostrar( QApplication *pApp)
{
    resize(dimensionX, dimensionY);
    show();
    pApp->exec();
}

void Graficador::setListaImagenes(const vector<string> &pListaDirImagenes)
{
    for (unsigned i = 0; i < pListaDirImagenes.size(); ++i)
    {
        if( pListaDirImagenes[i].find(".aic") != string::npos )
        {
            Imagen *aux = new ImagenAIC;
            if( aux->abrir(pListaDirImagenes[i]) )
            {
                imagenes.push_back(aux);
                dirImagenesCorrectas.push_back(pListaDirImagenes[i]);
                nombresImagenesCorrectas.push_back(aux->getNombre());
            }
            else
            {
                string nombre = pListaDirImagenes[i];
                unsigned pos = nombre.rfind("/");
                nombre.erase(0, pos + 1);
                nombresImagenesCorruptas.push_back(nombre);
                delete aux;
            }

        }
        else if( pListaDirImagenes[i].find(".ppm") != string::npos or
                 pListaDirImagenes[i].find(".pbm") != string::npos or
                 pListaDirImagenes[i].find(".pgm") != string::npos or
                 pListaDirImagenes[i].find(".pnm") != string::npos )
        {
            Imagen *aux = new ImagenPNM;
            if( aux->abrir(pListaDirImagenes[i]) )
            {
                imagenes.push_back(aux);
                dirImagenesCorrectas.push_back(pListaDirImagenes[i]);
                nombresImagenesCorrectas.push_back(aux->getNombre());
            }
            else
            {
                string nombre = pListaDirImagenes[i];
                unsigned pos = nombre.rfind("/");
                nombre.erase(0, pos + 1);
                nombresImagenesCorruptas.push_back(nombre);
                delete aux;
            }
        }
    }
}

void Graficador::procesarImagen(Imagen &pImagen, ProcesadorDeImagen &pProcesadorDeImagen)
{
    pProcesadorDeImagen.aplicar(pImagen);
}

Graficador::~Graficador()
{
    for (unsigned i = 0; i < imagenes.size(); i++)
    {
        delete imagenes[i];
    }
}

void Graficador::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    unsigned maxColumnas = imagenes[imagenActual]->getAncho();
    unsigned maxFilas = imagenes[imagenActual]->getAlto();
    float relAncho = ((float)width())  / ((float)maxColumnas);
    float relAlto  = ((float)height()) / ((float)maxFilas);

    escala = 1.0f;
    desplImgX = 0.0f;
    desplImgY = 0.0f;

    if( relAncho < relAlto )
    {
        escala = relAncho;
        desplImgY = (height() - maxFilas*escala)*0.5f;
    }
    else
    {
        escala = relAlto;
        desplImgX = (width() - maxColumnas*escala)*0.5f;
    }

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    float zmin, zmax;
    zmin = -1;
    zmax = 1;

    if( restablecerImagen )
    {
        glOrtho(0 , width() , 0 , height() , zmin , zmax);
        zoom = false;
    }
    else
    {
        if( mousePosXInicial < width() - desplImgX and mousePosYInicial < height() - desplImgY
                and mousePosXInicial > desplImgX and mousePosYInicial > desplImgY )
        {
            unsigned xmin = 0, xmax = 0, ymax = 0, ymin = 0;
            if( mousePosXInicial > mousePosXFinal )
            {
                xmin = mousePosXFinal;
                xmax = mousePosXInicial;
            }
            else
            {
                xmax = mousePosXFinal;
                xmin = mousePosXInicial;
            }
            if( mousePosYInicial > mousePosYFinal )
            {
                ymax = height() - mousePosYFinal;
                ymin = height() - mousePosYInicial ;
            }
            else
            {
                ymin = height() - mousePosYFinal;
                ymax = height() - mousePosYInicial;
            }
            if( mousePosXActual <= desplImgX )
            {
                xmin = desplImgX + 1 ;
                xmax = mousePosXInicial - 1;
            }
            if( mousePosYActual <= desplImgY )
            {
                ymin = height() - mousePosYInicial;
                ymax = height() - desplImgY -1;
            }
            if( mouseColActual >= imagenes[imagenActual]->getAncho() )
            {
                xmax = width() - desplImgX - 1;
            }
            if( mouseFilActual >= imagenes[imagenActual]->getAlto() )
            {
                ymin = desplImgY  + 1;
            }

            glOrtho(xmin, xmax , ymin , ymax, zmin, zmax);

            zoom = true;
        }
        else
        {
            glOrtho(0 , width() , 0 , height() , zmin , zmax);
            zoom = false;
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    {
        glTranslatef(desplImgX, desplImgY, 0.0f);
        glScalef(escala, escala, 0.0);
        imagenes[imagenActual]->dibujar();

        if( moviendo and controlPresionado and not zoom and mouseFilInicial >=0
                and mouseColInicial >=0 and mouseFilInicial <= imagenes[imagenActual]->getAlto()
                and mouseColInicial <= imagenes[imagenActual]->getAncho() )
        {
            seleccionarRegion();
        }
    }
    glPopMatrix();

    if( mostrarHistograma )
    {
        graficarHistograma();
    }

    if( mostrarAtajos ){
        glPushMatrix();
        {
            glClearColor(1.0 , 1.0 , 1.0 , 0);
            glClear(GL_COLOR_BUFFER_BIT);
            glTranslatef(width()/4, 0, 0.0f);
            glScalef((float)width()/atajos.getAncho()-0.5, (float)height()/atajos.getAlto(), 0.0);
            atajos.dibujar();
            glClearColor(0.1 , 0.1 , 0.1 , 0);
        }
        glPopMatrix();
    }
}

void Graficador::initializeGL()
{
    glClearColor(0.1 , 0.1 , 0.1 , 0);
}

void Graficador::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}


void Graficador::graficarHistograma()
{
    Histograma histograma;
    procesarImagen(*imagenes[imagenActual], histograma);
    bool esRGB = imagenes[imagenActual]->getTipo() == "P3" or imagenes[imagenActual]->getTipo() == "P6";

    if( esRGB )
    {
        unsigned minR, minG, minB, maxR, maxG, maxB;
        float promR, promG, promB;
        float desvioR, desvioG, desvioB;
        map<unsigned, unsigned> modaR, modaG, modaB;

        minR = get<0>(histograma.getMinPixelesRGB());
        minG = get<1>(histograma.getMinPixelesRGB());
        minB = get<2>(histograma.getMinPixelesRGB());

        maxR = get<0>(histograma.getMaxPixelesRGB());
        maxG = get<1>(histograma.getMaxPixelesRGB());
        maxB = get<2>(histograma.getMaxPixelesRGB());

        promR = get<0>(histograma.getPromedioPixelesRGB());
        promG = get<1>(histograma.getPromedioPixelesRGB());
        promB = get<2>(histograma.getPromedioPixelesRGB());

        desvioR = get<0>(histograma.getDesvioPixelesRGB());
        desvioG = get<1>(histograma.getDesvioPixelesRGB());
        desvioB = get<2>(histograma.getDesvioPixelesRGB());

        modaR = get<0>(histograma.getModaPixelesRGB());
        modaG = get<1>(histograma.getModaPixelesRGB());
        modaB = get<2>(histograma.getModaPixelesRGB());

        auto it_modaR = modaR.begin();
        auto it_modaG = modaG.begin();
        auto it_modaB = modaB.begin();

        cout << "******Minimos y Maximos******" << endl;
        cout << "Minimo valor R: " << minR << endl;
        cout << "Maximo valor R: " << maxR << endl;
        cout << "Minimo valor G: " << minG << endl;
        cout << "Maximo valor G: " << maxG << endl;
        cout << "Minimo valor B: " << minB << endl;
        cout << "Maximo valor B: " << maxB << endl;
        cout << "******Promedios******" << endl;
        cout << "Promedio R: " << promR << endl;
        cout << "Promedio G: " << promG << endl;
        cout << "Promedio B: " << promB << endl;
        cout << "******Desvios******" << endl;
        cout << "Desvio R: " << desvioR << endl;
        cout << "Desvio G: " << desvioG << endl;
        cout << "Desvio B: " << desvioB << endl;
        cout << "******Modas******" << endl;
        cout << "Moda R: " << "Intensidad: " << it_modaR->first << " Frecuencia: " << it_modaR->second << endl;
        cout << "Moda G: " << "Intensidad: " << it_modaG->first << " Frecuencia: " << it_modaG->second << endl;
        cout << "Moda B: " << "Intensidad: " << it_modaB->first << " Frecuencia: " << it_modaB->second << endl;
    }
    else
    {
        unsigned min, max;
        float prom;
        float desvio;
        map<unsigned, unsigned> moda;

        min = histograma.getMinPixelGris();
        max = histograma.getMaxPixelGris();

        prom = histograma.getPromedioPixelesGrises();

        desvio = histograma.getDesvioPixelesGrises();

        moda = histograma.getModaPixelesGrises();
        auto it_moda = moda.begin();

        cout << "******Minimo y Maximo******" << endl;
        cout << "Minimo valor Gris: " << min << endl;
        cout << "Maximo valor Gris: " << max << endl;
        cout << "******Promedio******" << endl;
        cout << "Promedio Gris: " << prom << endl;
        cout << "******Desvio******" << endl;
        cout << "Desvio Gris: " << desvio << endl;
        cout << "******Moda******" << endl;
        cout << "Moda Gris: " << "Intensidad: " << it_moda->first << " Frecuencia: " << it_moda->second << endl;
    }

    glClearColor(1.0 , 1.0 , 1.0 , 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    {
        map<unsigned, unsigned> maxFrec = histograma.getMaxFrecuenciaModas();
        auto it = maxFrec.begin();
        glScalef(width()/ (imagenes[imagenActual]->getIntensidadMaxima()*1.0f + 1), (height()*1.0f/(it->second) * 0.95), 0.0);
        if(esRGB){
            histograma.graficar("grises");
            histograma.graficar("R");
            histograma.graficar("G");
            histograma.graficar("B");
        }
        else
        {
            histograma.graficar("grises");
        }
    }
    glPopMatrix();
    glClearColor(0.1 , 0.1 , 0.1 , 0);
}

void Graficador::acondicionarPosiciones(unsigned posX, unsigned posY, char momento)
{
    if( momento == 1 )
    {
        mouseFilInicial = (posY - desplImgY) / escala;
        mouseColInicial = (posX - desplImgX) / escala;
    }

    if( momento == 2 )
    {
        mouseFilFinal = (posY - desplImgY) / escala;
        mouseColFinal = (posX - desplImgX) / escala;
    }

    if( momento == 3 )
    {
        mouseFilActual = (posY - desplImgY) / escala;
        mouseColActual = (posX - desplImgX) / escala;
    }
}

void Graficador::seleccionarRegion()
{

    if(int(mouseColInicial) >=0 and mouseColInicial <= imagenes[imagenActual]->getAncho()
            and int(mouseFilFinal) >= 0 and mouseFilInicial <= imagenes[imagenActual]->getAlto())
    {
        if( mousePosXActual <= desplImgX)
        {
            mouseColActual = 0;
            cout << "Entra-";
        }

        if( mousePosYActual <= desplImgY)
        {
            mouseFilActual = 0;
            cout << "Entra-";
        }

        if( mouseFilActual >= unsigned(imagenes[imagenActual]->getAlto()) )
        {
            mouseFilActual = imagenes[imagenActual]->getAlto();
        }

        if( mouseColActual >= unsigned(imagenes[imagenActual]->getAncho()) )
        {
            mouseColActual = imagenes[imagenActual]->getAncho();
        }

        glColor3f(1,0,0);
        glLineWidth(2);
        glBegin(GL_LINE_LOOP);
        glVertex3f( mouseColInicial, imagenes[imagenActual]->getAlto() - mouseFilInicial, 0);
        glVertex3f( mouseColInicial, imagenes[imagenActual]->getAlto() -  mouseFilActual, 0);
        glVertex3f( mouseColActual, imagenes[imagenActual]->getAlto() -  mouseFilActual, 0);
        glVertex3f( mouseColActual, imagenes[imagenActual]->getAlto() -  mouseFilInicial, 0);
        glEnd();

    }
}

void Graficador::obtenerValorValido(unsigned &pVariable)
{
    string valorString;
    while(true)
    {
        cin >> valorString;
        pVariable = convStringANumero<unsigned>(valorString);
        if( pVariable == 0 )
        {
            cout << "Tipo de dato ingresado no valido. Ingrese nuevamente" << endl;
            cout << "Eleccion: ";
        }
        else
        {
            break;
        }
    }
}

void Graficador::mouseReleaseEvent(QMouseEvent *evento)
{

    if( mousePosXInicial < width() - desplImgX and mousePosYInicial < height() - desplImgY
            and mousePosXInicial > desplImgX and mousePosYInicial > desplImgY and
            controlPresionado and moviendo and evento->button() == Qt::LeftButton and not zoom)
    {
        mousePosXFinal = this->mapFromGlobal( QCursor::pos()).x();
        mousePosYFinal = this->mapFromGlobal( QCursor::pos()).y();
        cout << "XF: " << mousePosXFinal << endl;
        cout << "YF: " << mousePosYFinal << endl;

        int diferenciaX = mousePosXInicial - mousePosXFinal;
        int diferenciaY = mousePosYInicial - mousePosYFinal;

        clickIzquierdoPresionado = false;
        moviendo = false;
        if( abs(diferenciaX) > 25 and abs(diferenciaY) >25 )
        {
            restablecerImagen = false;
        }
        controlPresionado = false;
        acondicionarPosiciones(this->mapFromGlobal( QCursor::pos()).x(), this->mapFromGlobal( QCursor::pos()).y(), 2);
    }

    if( clickIzquierdoPresionado and controlPresionado and int(mouseFilInicial) >= 0
            and int(mouseColInicial) >=0 and mouseColInicial <= imagenes[imagenActual]->getAncho()
            and mouseFilInicial <= imagenes[imagenActual]->getAlto() and restablecerImagen )
    {
        controlPresionado = false;
        restablecerImagen = true;
        acondicionarPosiciones(this->mapFromGlobal( QCursor::pos()).x(), this->mapFromGlobal( QCursor::pos()).y(), 1);

        DeteccionArea detector(mouseFilInicial, mouseColInicial);
        procesarImagen(*imagenes[imagenActual], detector);
        cout << "ctrl + click izquierdo: deteccion de area" << endl;
        cout << "Area detectada: " << detector.getArea() << endl;
    }
    repaint();
}

void Graficador::mousePressEvent(QMouseEvent *evento)
{
    if( evento->button() == Qt::LeftButton and not zoom )
    {
        acondicionarPosiciones(this->mapFromGlobal( QCursor::pos()).x(), this->mapFromGlobal( QCursor::pos()).y(), 1);
        clickIzquierdoPresionado = true;
        mousePosXInicial = this->mapFromGlobal( QCursor::pos()).x();
        mousePosYInicial = this->mapFromGlobal( QCursor::pos()).y();
        cout << "XI: " << mousePosXInicial << endl;
        cout << "YI: " << mousePosYInicial << endl;
    }


    if( evento->button() == Qt::RightButton and controlPresionado )
    {
        controlPresionado = false;
        restablecerImagen = true;
    }
}

void Graficador::keyReleaseEvent(QKeyEvent *event)
{
    if( event->modifiers() & Qt::ControlModifier )
    {
        controlPresionado = false;
    }

}

void Graficador::mouseMoveEvent(QMouseEvent *event)
{
    if( event->buttons() & Qt::LeftButton and controlPresionado and not zoom )
    {

        moviendo = true;

        mousePosYActual = this->mapFromGlobal( QCursor::pos()).y();
        if(this->mapFromGlobal( QCursor::pos()).x() < 0){
            mousePosXActual = 0;
        }
        else
        {
          mousePosXActual = this->mapFromGlobal( QCursor::pos()).x();
        }
        if(this->mapFromGlobal( QCursor::pos()).y() < 0){
            mousePosYActual = 0;
        }
        else
        {
          mousePosYActual = this->mapFromGlobal( QCursor::pos()).y();
        }
        acondicionarPosiciones(this->mapFromGlobal( QCursor::pos()).x(),this->mapFromGlobal( QCursor::pos()).y(), 3 );
        //cout << "XI: " << this->mapFromGlobal( QCursor::pos()).x() << endl;
       // cout << "YI: " << this->mapFromGlobal( QCursor::pos()).y() << endl;
    }
    repaint();
}

void Graficador::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers()& Qt::ControlModifier)
    {
        controlPresionado = true;
    }

    bool deshacerCambiosImagen = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_Z;
    if( deshacerCambiosImagen )
    {
        imagenes[imagenActual]->setBinarizada(false);
        imagenes[imagenActual]->abrir(dirImagenesCorrectas[imagenActual]);
        cout << "ctrl + Z: deshace los cambios" << endl;
    }

    bool imagenAnterior = event->modifiers() & Qt::ControlModifier and
                          event->key() == Qt::Key_Left and imagenActual != 0;
    bool imagenSiguiente = event->modifiers() & Qt::ControlModifier and
                           event->key() == Qt::Key_Right and imagenActual < nombresImagenesCorrectas.size()-1;

    if( imagenAnterior )
    {
        imagenActual--;
        cout << "ctrl + '<-': imagen anterior" << endl;
        cout << "Imagen actual: " << imagenes[imagenActual]->getNombre() << endl;
    }

    if( imagenSiguiente )
    {
        imagenActual++;
        cout << "ctrl + '->': imagen siguiente" << endl;
        cout << "Imagen actual: " << imagenes[imagenActual]->getNombre() << endl;
    }

    bool aplicarLUT_1 = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_1;
    if( aplicarLUT_1 )
    {
        LUT lut_1;
        lut_1.cargarLUT("grupo_luts/glow.lut");
        procesarImagen(*imagenes[imagenActual], lut_1);
        cout << "ctrl + 1: aplica LUT 1" << endl;
    }

    bool aplicarLUT_2 = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_2;
    if( aplicarLUT_2 )
    {
        LUT lut_2;
        lut_2.cargarLUT("grupo_luts/sepia.lut");
        procesarImagen(*imagenes[imagenActual], lut_2);
        cout << "ctrl + 2: aplica LUT 2" << endl;
    }

    bool aplicarSuavizado = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_S;
    if( aplicarSuavizado )
    {
        Suavizado filtroSuavizado;
        procesarImagen(*imagenes[imagenActual], filtroSuavizado);
        cout << "ctrl + S: aplica suavizado" << endl;
    }
    bool aplicarRealceBordes = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_R;
    if( aplicarRealceBordes )
    {
        RealceBordes filtroRealceBordes;
        procesarImagen(*imagenes[imagenActual], filtroRealceBordes);
        cout << "ctrl + R: aplica realce de bordes" << endl;
    }

    bool aplicarMediana = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_M;
    if( aplicarMediana )
    {
        Mediana filtroMediana;
        procesarImagen(*imagenes[imagenActual], filtroMediana);
        cout << "ctrl + m: aplica filtro mediana" << endl;
    }

    bool aplicarNegativo = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_N;
    if( aplicarNegativo )
    {
        Negativo negativo;
        procesarImagen(*imagenes[imagenActual], negativo);
        cout << "ctrl + N: aplica Negativo" << endl;
    }

    bool binarizar = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_B;
    if( binarizar )
    {
        hide();
        unsigned cantidad = 0;
        Histograma hist;
        procesarImagen(*imagenes[imagenActual], hist);
        unsigned val_recomendado = hist.getPromedioPixelesGrises();
        cout << endl << "Ingrese el valor de intensidad para binarizar la imagen [" << 0 << "-"
             << imagenes[imagenActual]->getIntensidadMaxima() <<"]" << endl;
        cout << "Valor recomendado: " << val_recomendado << endl;
        cout << "Cantidad: ";
        obtenerValorValido(cantidad);
        Binarizado binarizado(cantidad);
        bool esRGB = imagenes[imagenActual]->getTipo() == "P3" or imagenes[imagenActual]->getTipo() == "P6";
        bool esEscalaDeGrises = imagenes[imagenActual]->getTipo() == "P2" or imagenes[imagenActual]->getTipo() == "P5" or imagenes[imagenActual]->getTipo() == "P2C";
        if( esRGB and not imagenes[imagenActual]->getBinarizada() )
        {
            Pixel aux;
            for(unsigned i = 0; i < imagenes[imagenActual]->getAlto(); i++)
            {
                for(unsigned j = 0; j < imagenes[imagenActual]->getAncho(); j++)
                {
                    aux.setIntensidadRGB(((float)imagenes[imagenActual]->getPixel(i, j).getIntensidadR() * 0.2989) +
                                         ((float)imagenes[imagenActual]->getPixel(i, j).getIntensidadG() * 0.5870) +
                                         ((float)imagenes[imagenActual]->getPixel(i, j).getIntensidadB() * 0.1140));
                    imagenes[imagenActual]->setPixel(i, j, aux);
                }
            }
            procesarImagen(*imagenes[imagenActual], binarizado);
            imagenes[imagenActual]->setBinarizada(true);
            cout << "ctrl + B: aplica binarizado" << endl;
        }
        else if ( esEscalaDeGrises and not imagenes[imagenActual]->getBinarizada() )
        {
            procesarImagen(*imagenes[imagenActual], binarizado);
            imagenes[imagenActual]->setBinarizada(true);
            cout << "ctrl + B: aplica binarizado" << endl;
        }
        else
        {
            cout << "La imagen actual ya está binarizada..." << endl;
            system("pause");
        }
        show();
    }

    bool aumentarBrilloX5 = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_Up;
    if( aumentarBrilloX5 )
    {
        Brillo brillo(5);
        procesarImagen(*imagenes[imagenActual], brillo);
    }

    bool disminuirBrilloX5 = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_Down;
    if( disminuirBrilloX5 )
    {
        Brillo brillo(-5);
        procesarImagen(*imagenes[imagenActual], brillo);
    }

    bool aumentarBrillo = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_Plus;
    if( aumentarBrillo )
    {
        hide();
        unsigned cantidad = 0;
        cout << endl << "Ingrese la cantidad de brillo a aumentar [" << 0 << "-" << imagenes[imagenActual]->getIntensidadMaxima() <<"]" << endl;
        cout << "Cantidad: ";
        obtenerValorValido(cantidad);
        Brillo brillo(cantidad);
        procesarImagen(*imagenes[imagenActual], brillo);
        cout << "ctrl + '+': aumenta el brillo" << endl;
        show();
    }

    bool disminuirBrillo = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_Minus;
    if( disminuirBrillo )
    {
        hide();
        unsigned cantidad = 0;
        cout << endl << "Ingrese la cantidad de brillo a disminuir [" << 0 << "-" << imagenes[imagenActual]->getIntensidadMaxima() << "]" << endl;
        cout << "Cantidad: ";
        obtenerValorValido(cantidad);
        Brillo brillo(-cantidad);
        procesarImagen(*imagenes[imagenActual], brillo);
        cout << "ctrl + '-': disminuye el brillo" << endl;
        show();
    }

    bool ajustarContraste = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_C;
    if( ajustarContraste )
    {
        Contraste contraste;
        procesarImagen(*imagenes[imagenActual], contraste);
        cout << "ctrl + C: ajusta el contraste" << endl;
    }

    bool mostrar_ocultarHistograma = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_H;
    if( mostrar_ocultarHistograma ){
        if(mostrarHistograma == true){
            mostrarHistograma = false;
            cout << "ctrl + H: oculta histograma" << endl;
        }
        else
        {
            mostrarHistograma = true;
            cout << "ctrl + H: muestra histograma" << endl;
        }
    }

    bool mostrar_ocultarAtajos = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_A;
    if( mostrar_ocultarAtajos ){
        if(mostrarAtajos == true)
        {
            mostrarAtajos = false;
            cout << "ctrl + A: oculta atajos" << endl;
        }
        else
        {
            mostrarAtajos = true;
            cout << "ctrl + A: muestra atajos" << endl;
        }
    }

    bool guardarImagen = event->modifiers() & Qt::ControlModifier and event->key() == Qt::Key_G;
    if( guardarImagen )
    {
        hide();
        string nombre;
        string extension;

        cout << "Ingrese los datos para guardar la imagen actual." << endl;
        cout << "Nombre: ";
        cin >> nombre;
        cout << "Ingrese extension de la imagen almacenada:" << endl
             <<"    -> pbm(monocromatica)" << endl
            <<"    -> pgm(escala de grises) "<< endl
           <<"    -> ppm(RGB)" << endl
          <<"    -> aic(escala de grises en formato texto" << endl;
        cout << "Extension: ";
        cin >> extension;
        while(extension != "pbm" and extension!="ppm" and  extension != "pgm" and extension !="aic" )
        {
            cout << "Formato no valido, vuelva a ingresar la extension: " << endl;
            cout << "Extension: ";
            cin >> extension;

        }

        if(extension != "aic")
        {
            string txt_o_bin;
            cout << "Desea guardar el archivo como binario o texto" << endl;
            cout << "Eleccion: ";
            cin >> txt_o_bin;


            while(txt_o_bin != "texto" and txt_o_bin != "binario")
            {
                cout << "Seleccion incorrecta, vuelva a ingresar la opcion(texto o binario)";
                cout << "Eleccion: ";
                cin >> txt_o_bin;
            }
            unsigned char tipo;
            if(extension == "pbm")
            {
                tipo = 0;
            }else if (extension == "pgm")
            {
                tipo = 1;
            }
            else
            {
                tipo = 2;
            }
            switch(tipo)
            {
                case 0: ///PBM
                {
                    bool esEscalaDeGrises = imagenes[imagenActual]->getTipo() == "P2" or imagenes[imagenActual]->getTipo() == "P5";
                    unsigned cantidad = 0;
                    if( esEscalaDeGrises and not imagenes[imagenActual]->getBinarizada())
                    {
                        Histograma hist;
                        procesarImagen(*imagenes[imagenActual], hist);
                        unsigned val_recomendado = hist.getPromedioPixelesGrises();
                        cout << endl << "Ingrese el valor de intensidad para binarizar la imagen [" << 0 << "-" << imagenes[imagenActual]->getIntensidadMaxima() <<"]" << endl;
                        cout << "Valor recomendado: " << val_recomendado << endl;
                        cout << "Cantidad: ";
                        obtenerValorValido(cantidad);
                        Binarizado binarizado(cantidad);
                        procesarImagen(*imagenes[imagenActual], binarizado);
                        imagenes[imagenActual]->setBinarizada(true);
                    }
                    bool esRGB = imagenes[imagenActual]->getTipo() == "P3" or imagenes[imagenActual]->getTipo() == "P6";
                    if( esRGB and not imagenes[imagenActual]->getBinarizada())
                    {
                        for(unsigned i = 0; i < imagenes[imagenActual]->getAlto(); i++)
                        {
                            for(unsigned j = 0; j < imagenes[imagenActual]->getAncho(); j++)
                            {
                                Pixel aux;
                                aux.setIntensidadRGB(((float)imagenes[imagenActual]->getPixel(i, j).getIntensidadR() * 0.2989) +
                                                     ((float)imagenes[imagenActual]->getPixel(i, j).getIntensidadG() * 0.5870) +
                                                     ((float)imagenes[imagenActual]->getPixel(i, j).getIntensidadB() * 0.1140));
                                imagenes[imagenActual]->setPixel(i, j, aux);
                            }
                        }
                        Histograma hist;
                        procesarImagen(*imagenes[imagenActual], hist);
                        unsigned val_recomendado = hist.getPromedioPixelesGrises();
                        cout << endl << "Ingrese el valor de intensidad para binarizar la imagen [" << 0 << "-" << imagenes[imagenActual]->getIntensidadMaxima() <<"]" << endl;
                        cout << "Valor recomendado: " << val_recomendado << endl;
                        cout << "Cantidad: ";
                        obtenerValorValido(cantidad);
                        Binarizado binarizado(cantidad);
                        procesarImagen(*imagenes[imagenActual], binarizado);
                        imagenes[imagenActual]->setBinarizada(true);
                    }
                    if(txt_o_bin == "texto")
                    {
                        string tipoAnterior = imagenes[imagenActual]->getTipo();
                        imagenes[imagenActual]->setTipoAnterior(tipoAnterior);
                        imagenes[imagenActual]->setTipo("P1");
                    }

                    if(txt_o_bin == "binario")
                    {
                        string tipoAnterior = imagenes[imagenActual]->getTipo();
                        imagenes[imagenActual]->setTipoAnterior(tipoAnterior);
                        imagenes[imagenActual]->setTipo("P4");
                    }
                    imagenes[imagenActual]->guardar(imagenes[imagenActual]->getDireccionDeGuardado() + "/" + nombre + "." + extension);
                    cout << "Se ha guardado la imagen actual en formato (" << extension << ")" << endl;
                    break;
                }
                case 1: ///PGM
                {
                    if(imagenes[imagenActual]->getTipo() == "P1" or imagenes[imagenActual]->getTipo() == "P4"){
                        cout << "No se puede guardar una imagen monocromatica como imagen en Escala de Grises" << endl;
                    }
                    else
                    {
                        if(txt_o_bin == "texto")
                        {
                            string tipoAnterior = imagenes[imagenActual]->getTipo();
                            imagenes[imagenActual]->setTipoAnterior(tipoAnterior);
                            imagenes[imagenActual]->setTipo("P2");
                        }
                        if(txt_o_bin == "binario")
                        {
                            string tipoAnterior = imagenes[imagenActual]->getTipo();
                            imagenes[imagenActual]->setTipoAnterior(tipoAnterior);
                            imagenes[imagenActual]->setTipo("P5");
                        }
                        imagenes[imagenActual]->guardar(imagenes[imagenActual]->getDireccionDeGuardado() + "/" + nombre + "." + extension);
                        cout << "Se ha guardado la imagen actual en formato (" << extension << ")" << endl;
                    }
                    break;
                }
                case 2: ///PPM
                {
                    if(txt_o_bin == "texto")
                    {
                        string tipoAnterior = imagenes[imagenActual]->getTipo();
                        imagenes[imagenActual]->setTipoAnterior(tipoAnterior);
                        imagenes[imagenActual]->setTipo("P3");
                    }
                    if(txt_o_bin == "binario")
                    {
                        string tipoAnterior = imagenes[imagenActual]->getTipo();
                        imagenes[imagenActual]->setTipoAnterior(tipoAnterior);
                        imagenes[imagenActual]->setTipo("P6");
                    }
                    imagenes[imagenActual]->guardar(imagenes[imagenActual]->getDireccionDeGuardado() + "/" + nombre + "." + extension);
                    cout << "Se ha guardado la imagen actual en formato (" << extension << ")" << endl;

                    break;
                }
            }
        }
        else
        {
            ImagenAIC nuevaIMG;
            nuevaIMG.setTipo("P2C");
            nuevaIMG.setMetadatos(imagenes[imagenActual]->getMetadatos());
            nuevaIMG.dimensionar(imagenes[imagenActual]->getAlto(), imagenes[imagenActual]->getAncho());
            nuevaIMG.setIntensidadMaxima(imagenes[imagenActual]->getIntensidadMaxima());
            nuevaIMG.setNombre(imagenes[imagenActual]->getNombre());
            nuevaIMG.setMatrizPixeles(imagenes[imagenActual]->getMatrizPixeles());
            nuevaIMG.guardar(nuevaIMG.getDireccionDeGuardado() + "/" + nombre + "." + extension);
            cout << "Se ha guardado la imagen actual en formato (" << extension << ")" << endl;
        }
        imagenes[imagenActual]->abrir(dirImagenesCorrectas[imagenActual]);
        imagenes[imagenActual]->setBinarizada(false);
        system("pause");
        show();
    }
    repaint();
}
