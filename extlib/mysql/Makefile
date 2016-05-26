CXX = g++


CFLAGS = -g -I${ORCA_HOME}/include/orca -DLINUX  -I/usr/include/mysql

LDFLAGS = -lorca `mysql_config --libs`



TARGET_LIB = liborca_mysql.so
LIB_OBJ = orcaMysql.o


all	: $(TARGET_LIB) 

$(TARGET_LIB) : $(LIB_OBJ) Makefile
	$(CXX) -shared -o $(TARGET_LIB) $(LIB_OBJ) $(LDFLAGS)

%o : %cpp
	$(CXX) $(CFLAGS) -c -fPIC $<

install:
	sudo cp libmysql.so /usr/local/lib/orca

clean : 
	rm -rf $(LIB_OBJ) $(TARGET_LIB) core 
	rm -rf *.o *.bak *.*~ *~ *.stackdump *.a *.so 


