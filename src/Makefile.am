

SRC = $(top_srcdir)/src
PARSER_DIR = $(SRC)/parser
VM_DIR = $(SRC)/vm
PRIMITIVE_DIR = $(SRC)/primitive
INCLUDE_DIR = $(SRC)/include
CORELIB_DIR = $(SRC)/corelib
EXTLIB_DIR = $(SRC)/extlib
KYLIB_DIR = $(SRC)/kylib

BISON = bison
FLEX = flex

AM_CPPFLAGS = -I$(PARSER_DIR) -I$(VM_DIR) -I$(PRIMITIVE_DIR) -I$(INCLUDE_DIR) -I$(CORELIB_DIR) -I$(KYLIB_DIR) `pkg-config --cflags gtk+-2.0`
DEFS += -DGCC -DLINUX -D_GNU_SOURCE -DI386 -DANSI=1 -DSYSV -DMAXPATHLEN=1024 -D_REENTRANT -DPRODUCE_ANSI_CODE -DUCI_TEMPORARY
LIBS += `pkg-config --libs gtk+-2.0`

$(PARSER_DIR)/parser.cpp : $(PARSER_DIR)/parser.y
	$(BISON) -d -r all -o $@ $< 

$(PARSER_DIR)/lexer.cpp : $(PARSER_DIR)/lexer.l
	$(FLEX) -+ -o $@ $<

bin_PROGRAMS = orca

orca_SOURCES = 	$(VM_DIR)/main.cpp
orca_CFLAGS = $(AM_CFLAGS)
orca_LDFLAGS = $(top_builddir)/src/liborca.la  

lib_LTLIBRARIES = liborca.la 

liborca_la_SOURCES = \
		$(PARSER_DIR)/parser.cpp \
		$(PARSER_DIR)/lexer.cpp \
		$(PARSER_DIR)/parserParser.cpp \
		$(PARSER_DIR)/parserCode.cpp \
		$(PARSER_DIR)/parserControl.cpp \
		$(PARSER_DIR)/parserException.cpp \
		$(PARSER_DIR)/parserOP.cpp \
		$(PARSER_DIR)/parserParse.cpp \
		$(PARSER_DIR)/parserConst.cpp \
		$(PRIMITIVE_DIR)/orcaNil.cpp \
		$(PRIMITIVE_DIR)/orcaBoolean.cpp \
		$(PRIMITIVE_DIR)/orcaInteger.cpp \
		$(PRIMITIVE_DIR)/orcaFloat.cpp \
		$(PRIMITIVE_DIR)/orcaList.cpp \
		$(PRIMITIVE_DIR)/orcaListIter.cpp \
		$(PRIMITIVE_DIR)/orcaListIterator.cpp \
		$(PRIMITIVE_DIR)/orcaListVIterator.cpp \
		$(PRIMITIVE_DIR)/orcaVirtList.cpp \
		$(PRIMITIVE_DIR)/orcaSbf.cpp \
		$(PRIMITIVE_DIR)/orcaMap.cpp \
		$(PRIMITIVE_DIR)/orcaMapIter.cpp \
		$(PRIMITIVE_DIR)/orcaMapVIter.cpp \
		$(PRIMITIVE_DIR)/orcaMapVIter2.cpp \
		$(PRIMITIVE_DIR)/orcaString.cpp \
		$(PRIMITIVE_DIR)/orcaTuple.cpp \
		$(PRIMITIVE_DIR)/orcaTupleIter.cpp \
		$(PRIMITIVE_DIR)/orcaTupleVIter.cpp \
		$(VM_DIR)/orcaData.cpp \
		$(VM_DIR)/orcaLocal.cpp \
		$(VM_DIR)/orcaObject.cpp \
		$(VM_DIR)/orcaObjectMembers.cpp \
		$(VM_DIR)/orcaObjectMembersIter.cpp \
		$(VM_DIR)/orcaObjectMembersIter2.cpp \
		$(VM_DIR)/orcaObjectParents.cpp \
		$(VM_DIR)/orcaObjectParentsIter.cpp \
		$(VM_DIR)/orcaRoot.cpp \
		$(VM_DIR)/orcaStack.cpp \
		$(VM_DIR)/orcaTrace.cpp \
		$(VM_DIR)/orcaForStack.cpp \
		$(VM_DIR)/orcaDecodeStack.cpp \
		$(VM_DIR)/orcaVM.cpp \
		$(VM_DIR)/orcaException.cpp \
		$(VM_DIR)/orcaExceptionObject.cpp \
		$(VM_DIR)/orcaGlobal.cpp \
		$(VM_DIR)/orcaParserObject.cpp \
		$(VM_DIR)/orcaSelectStack.cpp \
		$(INCLUDE_DIR)/porting.cpp \
		$(CORELIB_DIR)/base64.cpp \
		$(CORELIB_DIR)/orcaDatetime.cpp \
		$(CORELIB_DIR)/orcaPack.cpp \
		$(CORELIB_DIR)/orcaGtk.cpp \
		$(CORELIB_DIR)/orcaTime.cpp \
		$(CORELIB_DIR)/orcaQueue.cpp \
		$(CORELIB_DIR)/orcaSqlite3.cpp \
		$(CORELIB_DIR)/orcaSelector.cpp \
		$(CORELIB_DIR)/orcaSocket.cpp \
		$(CORELIB_DIR)/orcaIO.cpp \
		$(CORELIB_DIR)/orcaOS.cpp \
		$(CORELIB_DIR)/orcaIPC.cpp \
		$(KYLIB_DIR)/kyString.cpp 

liborca_la_LDFLAGS = -version-number 0:5:0
liborca_la_LIBADD = $(LIBADD_DL)
#liborca_la_LINK = $(LINK)


orcaincludedir = $(prefix)/include/orca
orcainclude_DATA = $(PARSER_DIR)/*.h $(VM_DIR)/*.h $(PRIMITIVE_DIR)/*.h $(INCLUDE_DIR)/*.h $(CORELIB_DIR)/*.h


