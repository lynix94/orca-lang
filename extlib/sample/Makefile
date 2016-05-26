CXX = g++


CFLAGS = -g -I${ORCA_HOME}/include/orca -DLINUX 

LDFLAGS = -lorca -L${ORCA_HOME}/lib



TARGET_LIB = liborca_sample.so
LIB_OBJ = sample.o


all	: $(TARGET_LIB) 

$(TARGET_LIB) : $(LIB_OBJ) Makefile
	$(CXX) -shared -o $(TARGET_LIB) $(LIB_OBJ) $(LDFLAGS)

%o : %cpp
	$(CXX) $(CFLAGS) -c -fPIC $<

install:
	sudo cp -r lib /usr/local/lib/orca

clean : 
	rm -rf $(LIB_OBJ) $(TARGET_LIB) core 
	rm -rf *.o *.bak *.*~ *~ *.stackdump *.a *.so 


