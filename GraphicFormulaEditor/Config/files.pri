SOURCES += main.cpp\
        MainWindow.cpp \
    GraphicSystem/src/Variable.cpp \
    GraphicSystem/src/Space.cpp \
    GraphicSystem/src/Row.cpp \
    GraphicSystem/src/Operation.cpp \
    GraphicSystem/src/Level.cpp \
    GraphicSystem/src/Glyph.cpp \
    GraphicSystem/src/Function.cpp \
    GraphicSystem/src/Fraction.cpp \
    GraphicSystem/src/Composite.cpp \
    GraphicSystem/src/IteratorBacklight.cpp \
    Exceptions/src/IsPlainGlyph.cpp \
    Iterators/src/GlyphIterator.cpp \
    GraphicSystem/src/BracketsPair.cpp

HEADERS  += MainWindow.h \
    GraphicSystem/Variable.h \
    GraphicSystem/Space.h \
    GraphicSystem/Row.h \
    GraphicSystem/Operation.h \
    GraphicSystem/Level.h \
    GraphicSystem/Glyph.h \
    GraphicSystem/Function.h \
    GraphicSystem/Fraction.h \
    GraphicSystem/Composite.h \
    GraphicSystem/IteratorBacklight.h \
    Exceptions/IsPlainGlyph.h \
    Iterators/Iterator.h \
    Iterators/GlyphIterator.h \
    GraphicSystem/BracketsPair.h

OTHER_FILES += \
    Config/files.pri
