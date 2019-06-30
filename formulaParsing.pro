CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = formulaParsing
CONFIG += c++11
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT = core gui widgets


INCLUDEPATH += $$(BOOST_PATH)


HEADERS +=  CODE/GUI/MainWindow.h \
			CODE/GUI/TextEdit.h \
			CODE/GUI/LineEdit.h


SOURCES +=  CODE/main.cpp \
			CODE/GUI/MainWindow.cpp \
			CODE/GUI/TextEdit.cpp \
			CODE/GUI/LineEdit.cpp \
			CODE/stringVerifications.cpp \
			CODE/otherFunctions.cpp \
			CODE/DATA_AND_OPERATORS/ProjectData.cpp \
			CODE/DATA_AND_OPERATORS/AnyOperators.cpp \
			CODE/DATA_AND_OPERATORS/AnyFunctions.cpp \
			CODE/FORMULA_INTERPRETER/FormulaInterpreter.cpp \
			CODE/FORMULA_INTERPRETER/AbstractSyntaxicNode.cpp \
			CODE/FORMULA_INTERPRETER/SyntaxicNodeLValue.cpp \
			CODE/FORMULA_INTERPRETER/SyntaxicNodeRValue.cpp \
			CODE/FORMULA_INTERPRETER/SyntaxicNodeUnaryOperator.cpp \
			CODE/FORMULA_INTERPRETER/SyntaxicNodeBinaryOperator.cpp \
			CODE/FORMULA_INTERPRETER/AssignOperatorStrategy.cpp \
			CODE/FORMULA_INTERPRETER/SyntaxicNodeFactory.cpp


RESOURCES += resources.qrc
RC_FILE += icone.rc

