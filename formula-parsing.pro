CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = FormulaParsing
CONFIG += c++17
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc
QT = core gui widgets


HEADERS +=  src/gui/MainWindow.h \
			src/gui/TextEdit.h \
			src/gui/LineEdit.h


SOURCES +=  src/main.cpp \
			src/gui/MainWindow.cpp \
			src/gui/TextEdit.cpp \
			src/gui/LineEdit.cpp \
			src/stringVerifications.cpp \
			src/otherFunctions.cpp \
			src/data-and-operators/WorkspaceData.cpp \
			src/data-and-operators/AnyOperators.cpp \
			src/data-and-operators/AnyFunctions.cpp \
			src/formula-interpreter/FormulaInterpreter.cpp \
			src/formula-interpreter/AbstractSyntaxicNode.cpp \
			src/formula-interpreter/SyntaxicNodeLValue.cpp \
			src/formula-interpreter/SyntaxicNodeRValue.cpp \
			src/formula-interpreter/SyntaxicNodeUnaryOperator.cpp \
			src/formula-interpreter/SyntaxicNodeBinaryOperator.cpp \
			src/formula-interpreter/AssignOperatorStrategy.cpp \
			src/formula-interpreter/SyntaxicNodeFactory.cpp


RESOURCES += resources.qrc
RC_FILE += icone.rc

