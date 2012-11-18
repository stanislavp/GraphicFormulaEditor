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
    Dialogs/src/CreateFraction.cpp \
    Dialogs/src/CreateFunction.cpp \
    Dialogs/src/CreateLeveled.cpp \
    Dialogs/src/CreateOperation.cpp \
    Dialogs/src/CreateVariable.cpp \
    Dialogs/src/CreateBrackets.cpp \
    GraphicSystem/src/BracketsPair.cpp \
    GraphicSystem/src/Dummy.cpp

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
    Dialogs/CreateFraction.h \
    Dialogs/CreateFunction.h \
    Dialogs/CreateLeveled.h \
    Dialogs/CreateOperation.h \
    Dialogs/CreateVariable.h \
    Dialogs/CreateBrackets.h \
    GraphicSystem/BracketsPair.h \
    GraphicSystem/Dummy.h

OTHER_FILES += \
    Config/files.pri
