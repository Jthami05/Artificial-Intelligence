QT += widgets

HEADERS += \
        edge.h \
        node.h \
        graphwidget.h \
    city.h

SOURCES += \
        edge.cpp \
        main.cpp \
        node.cpp \
        graphwidget.cpp \
        city.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/elasticnodes
INSTALLS += target

DISTFILES += \
    Random4.tsp \
    Random30.tsp \
    Random40.tsp

RESOURCES += \
    files.qrc
