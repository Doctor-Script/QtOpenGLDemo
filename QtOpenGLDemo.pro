QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    gtengine/resources/Resource.cpp \
    main.cpp \
    GtWidget.cpp \
    gtrendering/QtShader.cpp \
    gtrendering/QtRender.cpp \
    gtrendering/QtSpriteRenderDelegate.cpp \
    qtresources/QtTexture.cpp \
    qtresources/QtResources.cpp \
    $$files(gtengine/*.cpp, true)

HEADERS += \
    GtWidget.h \
#    gtengine/resources/Resource.h \
    gtrendering/QtShader.h \
    gtrendering/QtRender.h \
    gtrendering/QtSpriteRenderDelegate.h \
    qtresources/QtTexture.h \
    qtresources/QtResources.h \
    $$files(gtengine/*.h, true)

RESOURCES += \
    shaders.qrc \
    textures.qrc

INCLUDEPATH += gtengine

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
