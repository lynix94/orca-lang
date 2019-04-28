
NOW developing 0.5 again (move to github.com/lynix94/orca-lang)

-----------------
now orca release 0.4 beta

in this version
it supports

* user defined function in decode statement 
  (See the lib/xml.orca for it's example)
* improve iterator
* remote, distribute processing (It will be very interesting)
* xml, json encoding/decoding
* httpd, osp(orca server page) module
  (you can check it from http://orca-lang.or.kr:8080/hello.osp)
* base64, fun(functional), datetime, date, time module
* operator_get, operator_set, operator_get_last extension
* prototypes for distribute file system
* mysql module

see the TUTORIAL.txt and MODULE.txt for more detail spec.
And you can check from test vectors in tests/*.orca files 
And you can visit community page in 
  http://orca-lang.or.kr/


2010. 11. 16
Lee, Ki-Yeul (kiyeul.lee@gmail.com)

----------------------------

now orca release 0.3 beta

in this version
it supports

* decode statement
* parallel do, parallel for statement
* set builder form list
* extends os module
* stopwatch module
* cgi module

see the tests/*.orca files about new spec.

2010. 6. 20
Lee, Ki-Yeul (kiyeul.lee@gmail.com)


-------------------------------

now orca release 0.2 beta

in this version, 
it support

* big number
* real number
* scope statement
* lambda function
* thread, ipc
* socket, select

2009. 12. 2
Lee, Ki-Yeul (kiyeul.lee@gmail.com)

-------------------------------

orca is yet another script interpreter which supports OO features and have a plan for some funny syntax. 
it is made by C++/STL/BOOST so core source is extremely small, efficient and easily bind with C++ class.

now, it release 0.1 beta. 
despite of this lower version, it is implemented basic operation.
likes.. arithmetic operation, control statements(if, do, while, for) 
string processing, regular expression processing, function & object define and inheritance,
garbage collection, redefinable operator and exception handling.

I hope you enjoy this. 

2009. 10. 07
Lee, Ki-Yeul (kiyeul.lee@gmail.com)


