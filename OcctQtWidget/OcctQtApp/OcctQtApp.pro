QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Occt widget
LIBS += -L/opt/hal-core/src/hal/components/matrix/cpp_interface/libocct/occ_apps/OcctQtWidget/build-OcctQtLib-Desktop-Debug -lOcctQtLib
INCLUDEPATH+=/opt/hal-core/src/hal/components/matrix/cpp_interface/libocct/occ_apps/OcctQtWidget/OcctQtLib

# Dxfrw
INCLUDEPATH +=/opt/hal-core/src/hal/components/matrix/cpp_interface/libocct/occ_apps/OcctQtWidget/OcctQtLib/libdxfrw

# Opencascade
INCLUDEPATH += /opt/opencascade/oce-upstream-V7_5_0beta/inc \
               /opt/opencascade/oce-upstream-V7_5_0beta/src
LIBS+= -L/opt/opencascade/oce-upstream-V7_5_0beta/lin/gcc/lib \
       -L/opt/opencascade/oce-upstream-V7_5_0beta/lin/gcc/libd

LIBS += -lTKGeomAlgo -lTKMesh -lTKHLR -lTKBO -lTKShHealing
LIBS += -lTKPrim
LIBS += -lTKernel -lTKMath -lTKTopAlgo -lTKService
LIBS += -lTKG2d -lTKG3d -lTKV3d -lTKOpenGl
LIBS += -lTKBRep -lTKXSBase -lTKGeomBase
LIBS += -lTKXSDRAW
LIBS += -lTKLCAF -lTKXCAF -lTKCAF -lTKVCAF
LIBS += -lTKCDF -lTKBin -lTKBinL -lTKBinXCAF -lTKXml -lTKXmlL -lTKXmlXCAF
# -- IGES support
LIBS += -lTKIGES
# -- STEP support
LIBS += -lTKSTEP -lTKXDESTEP -lTKXDEIGES -lTKSTEPAttr -lTKSTEPBase -lTKSTEP209
# -- STL support
LIBS += -lTKSTL
# -- OBJ/glTF support
LIBS += -lTKRWMesh -lTKMeshVS
# -- VRML support
LIBS += -lTKVRML
# -- ViewerTest
LIBS += -lTKViewerTest

