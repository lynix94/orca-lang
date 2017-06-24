CXX = g++


CFLAGS = -g -I${ORCA_HOME}/include/orca -DLINUX 

LDFLAGS = -lcgi



TARGET_LIB = liborca_cgi.so
LIB_OBJ = orcaCgi.o


all	: $(TARGET_LIB) 

$(TARGET_LIB) : $(LIB_OBJ) Makefile
	$(CXX) -shared -o $(TARGET_LIB) $(LIB_OBJ) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $(CFLAGS) -c -fPIC $<

install:
	cp orca /usr/local/bin
	rm -rf /usr/local/lib/orca
	cp -r lib /usr/local/lib/orca

clean : 
	rm -rf $(LIB_OBJ) $(TARGET_LIB) core 
	rm -rf *.o *.bak *.*~ *~ *.stackdump *.a *.so 


