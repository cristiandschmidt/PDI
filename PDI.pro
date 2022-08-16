QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

QT += widgets
LIBS+=-lopengl32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        binarizado.cpp \
        brillo.cpp \
        contraste.cpp \
        deteccionarea.cpp \
        graficador.cpp \
        histograma.cpp \
        imagen.cpp \
        imagenaic.cpp \
        imagenpnm.cpp \
        lut.cpp \
        main.cpp \
        mediana.cpp \
        negativo.cpp \
        pixel.cpp \
        procesadordeimagen.cpp \
        realcebordes.cpp \
        sistema.cpp \
        suavizado.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    binarizado.h \
    brillo.h \
    contraste.h \
    conv_string.h \
    deteccionarea.h \
    graficador.h \
    histograma.h \
    imagen.h \
    imagenaic.h \
    imagenpnm.h \
    lut.h \
    mediana.h \
    negativo.h \
    pixel.h \
    procesadordeimagen.h \
    realcebordes.h \
    sistema.h \
    suavizado.h
