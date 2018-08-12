touch pp.orca && orca pp

#flex -P zz -o calc_lexer.cpp calc.l
#bison -p zz -d -r all -o calc_parse.cpp calc.y

#g++ -fPIC -shared -o ./liborca_calc.so ./calc_lexer.cpp ./calc_parse.cpp ./orcaParse.cpp -I${ORCA_HOME}/include/orca -L${ORCA_HOME}/lib -lorca
#g++ -o calc ./calc_lexer.cpp ./calc_parse.cpp ./orcaParse.cpp -I${ORCA_HOME}/include/orca -L${ORCA_HOME}/lib -lorca -lboost_system
#g++ -o calc ./calc_lexer.cpp ./calc_parse.cpp ./orcaParse.cpp -I${ORCA_HOME}/include/orca -L${ORCA_HOME}/lib -lorca -lboost_system


