CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = formulaParsing
CONFIG += c++11 console
DESTDIR = $$MODE
OBJECTS_DIR = $$DESTDIR/objects
MOC_DIR = $$DESTDIR/moc


INCLUDEPATH += $$(BOOST_PATH)
			
			
SOURCES +=  CODE/main.cpp \
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
			CODE/FORMULA_INTERPRETER/SyntaxicNodeFactory.cpp

