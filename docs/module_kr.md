# Orca Programming Language Module Reference

## version 0.6

written by Lee, Ki-Yeul (kiyeul.lee@gmail.com)  


# Table of Contents



*   [alg](#alg)
*   [cpp](#cpp)
*   [date,datetime,time](#date,datetime,time)
*   [dl](#dl)
*   [distribute](#distribute)
    *   [dfsd](#dfsd)
    *   [dist](#dist)
    *   [fs](#fs)
    *   [remotec](#remotec)
    *   [remoted](#remoted)
*   [encoding](#encoding)
    *   [json](#json)
    *   [xml](#xml)
    *   [base64](#base64)
*   [fdselect](#fdselect)
*   [file](#file)
*   [fun](#fun)
*   [gtk](#gtk)
*   [gui](#gui)
*   [html](#html)
*   [io](#io)
*   [ipc](#ipc)
*   [lang](#lang)
    *   [lisp](#lisp)
    *   [sh](#sh)
*   [log](#log)
*   [math](#math)
	*   [random](#random)
*   [net](#net)
    *   [httpd](#httpd)
    *   [httplib](#httplib)
    *   [osp](#osp)
*   [operator](#operator)
*   [orca](#orca)
*   [orm](#orm)
*   [os](#os)
*   [pack](#pack)
*   [queue](#queue)
*   [repr](#repr)
*   [run](#run)
*   [selector](#selector)
*   [socket](#socket)
*   [sonar](#sonar)
*   [sorted](#sorted)
*   [stopwatch](#stopwatch)
*   [storage](#storage)
    *   [cached](#cached)
    *   [sqlite3](#sqlite3)
*   [string](#string)
*   [strings](#strings)
*   [system](#system)
*   [thread](#thread)
*   [tool](#tool)
    *   [gnuplot](#gnuplot)
*   [type](#type)
*   [util](#util)
    *   [match](#match)
    *   [lru](#lru)
    *   [lock](#lock)
    *   [find_owner](#find_owner)



# alg

alg 모듈은 앞의 이터레이터 기반으로 기본 알고리즘들을 적용하는 역할을 한다. STL 의 알고리즘과 유사하다.

### traverse(obj, fun)

입력받은 obj 에 대해 fun을 실행한다.

```
$ using alg;
$ a = [1,2,3, {4:5, 6:7}, (8,0)];
$ alg.traverse(a, def.lambda(...argv) {print: argv[0];});
[ 1,2,3,{ 4:5,6:7 },( 8,0 ) ]
1
2
3
{ 4:5,6:7 }
( 4,5 )
4
5
( 6,7 )
6
7
( 8,0 )
8
0
$
```

### for_each (begin, end, function)

은 begin ~ end까지의 원소들 a에 대해 funciton(a) 를 실행한다.

의미상,

```
for a in a.begin()
{
	function(a());
}
```

과 같으나, for문과는 달리 end 반복자를 지정할 수 있다는 점이 좀 더 유연하다.

```
$ using alg;
$ a = [1..10];
[ 1,2,3,4,5,6,7,8,9,10 ]
$ alg.for_each(a.begin(), a.end(), def.lambda(...argv) { print: argv[0]; });
1
2
3
4
5
6
7
8
9
10
$ 
```

### for\_each\_iterator(begin, end, function)

for\_each 인터페이스는, value 기반으로 작동하기 때문에 컨테이너의 객체를 변경시키는데 사용하기에는 적당하지 않다. for\_each\_iterator는 for\_each와 유사하나 function으로 넘겨니는 것이 iterator 라는 점이 다르다.

```
$ a = [1..10];
[ 1,2,3,4,5,6,7,8,9,10 ]
$ alg.for_each_iterator(a.begin(), a.end(), def.lambda (...argv) { argv[0](argv[0]()*2); });
$ print: a;
[ 2,4,6,8,10,12,14,16,18,20 ]
$ 
```

### find (begin, end, value)

find 는 begin 반복자로부터 end 반복자까지 탐색하며 value와 같은 값이 있으면 그 위치의 반복자를 리턴한다. 찾는 반복자가 없는경우 end 를 리턴한다.

```
$ using alg;
$ a = [1..10];
[ 1,2,3,4,5,6,7,8,9,10 ]
$ b = alg.find(a.begin(), a.end(), 5);
listiter <0x98acc38>
$ print: b();
5
$ b = alg.find(a.begin(), a.end(), 20);
listiter <0x98ad2e8>
$ print: b();
uncaugted exception: orca.iter out of range
recent call-stack trace
>> root (/usr/local/lib/orca/alg.orca 237)              return true;
```

### find_if (begin, end, function)

find_if는 find와 유사하나 반복자가 탐색을 하면서 해당 반복자의 값을 function에 넣은 결과가 true일 때 리턴된다. 예를 들어 앞의 예제를 7의 배수를 찾는 것으로 변경해보면,

```
$ a = [11..20];
[ 11,12,13,14,15,16,17,18,19,20 ]
$ b = alg.find_if(a.begin(), a.end(), def.lambda(...argv) { return argv[0] % 7 == 0; });
listiter <0x98ae668>
$ print: b();
14
```

와 같이 작성할 수 있다. 각 원소가 function으로 전달되며 function의 실행결과가 true인 이터레이터가 리턴된다.

### erase (begin, end)

erase (begin, end) 는 컨테이너로부터 begin부터 end이전까지의 범위를 삭제한다.

```
$ a = [1..10];
[ 1,2,3,4,5,6,7,8,9,10 ]
$ s = a.begin().next(3);
listiter <0x98afc60>
$ e = a.end().prev(2);
listiter <0x98af870>
$ print: s(), ':', e();
4:9
$ alg.erase(s, e);
$ print: a;
[ 1,2,3,9,10 ]
```

### remove (begin, end, val)

remove (begin, end, val) 은 begin 부터, end까지의 반복자중에 값이 val인 원소를 삭제한다.

```
$ a = [1,2,3,2,7,2];
[ 1,2,3,2,7,2 ]
$ alg.remove(a.begin(), a.end(), 2);
$ print: a;
[ 1,3,7 ]
```

### remove_if (begin, end, function)

remove_if (begin, end, function) 는 역시 remove와 유사하나, 각 원소 a 에 대해 function(a) 를 실행한 결과가 true인 것을 삭제한다. 앞의 예제에서 10보다 작은 원소를 삭제하고 싶으면,

```
$ a = [10, 3, 2, 20, 32];
[ 10,3,2,20,32 ]
$ alg.remove_if(a.begin(), a.end(), def.lambda(...argv){ argv[0] < 10; } );
$ print: a;
[ 10,3,2,20,32 ]
```

### copy(begin, end, target)

copy 는 begin~end까지의 원소를 target iterator에 복사한다.

```
$ a = [1..10];
[ 1,2,3,4,5,6,7,8,9,10 ]
$ b = [];
[  ]
$ alg.copy(a.begin(), a.end(), b.begin());
$ print: b;
[ 1,2,3,4,5,6,7,8,9,10 ]
$ alg.copy(a.begin(), a.end(), alg.find(b.begin(), b.end(), 5));
$ print: b;
[ 1,2,3,4,1,2,3,4,5,6,7,8,9,10,5,6,7,8,9,10 ]
$ 
```

### copy_n(begin, n, target)

copy_n은 copy와 유사하나, begin으로부터 n개의 원소를 target 이터레이터로 복사한다.

```
$ a = [1..10];
[ 1,2,3,4,5,6,7,8,9,10 ]
$ b = [];
[  ]
$ alg.copy_n(alg.find(a.begin(), a.end(), 5), 3, b.begin());
$ print: b;
[ 5,6,7 ]
```

### count(begin, end, val)

count는 begin~end까지의 범위중, 값이 val인 것의 갯수를 리턴한다.

```
$ a = [2, 3, 3, 3, 2, 7, 4];
[ 2,3,3,3,2,7,4 ]
$ alg.count(a.begin(), a.end(), 3);
3
```

### count_if(begin, end, function)

역시 count와 유사하되, function의 결과가 true인 것의 갯수를 리턴한다.

앞의 예제에서 짝수의 갯수만 세고 싶으면

```
$ a = [2,3,3,3,2,7,4];
[ 2,3,3,3,2,7,4 ]
$ alg.count_if(a.begin(), a.end(), def.lambda(...argv){ return argv[0] % 2 == 0; });
3
```

와 갈이 할 수 있다.

### equal(begin, end, begin2, function)

equal은 begin~end까지의 원소와 begin2~ 의 원소들을 function(a, b)에 각각 넣어서 function이 모두 true를 리턴하면 함수도 true를 리턴한다.

예를 들어 설명하면, 아래의 두 리스트는 정수, 실수 타입이 달라 그냥 == 연산을 수행하면 false이지만, equal 을 사용하여 아래와 같이 비교할 수 있다.

```
$ a = [1, 2, 3, 2, 2];
[ 1,2,3,2,2 ]
$ b = ['1', '2', '3', '2', '2'];
[ '1','2','3','2','2' ]
$ alg.equal(a.begin(), a.end(), b.begin(), def.lambda(...argv){ return argv[0] == argv[1].integer(); });
true
```

### equal_range(begin, end, val)

equal_range는 begin~end의 구간이 val와 같은지를 검사한다.

```
$ a = [1,1,2,2,3,3,4,4];
[ 1,1,2,2,3,3,4,4 ]
$ alg.equal_range(a.begin(), a.end(), 1);
false
$ alg.equal_range(a.begin().next(2), a.begin().next(4), 2);
true
```

### replace(begin, end, from, to)

replace는 begin ~ end 구간사이에서 값이 from인 아이템을 to로 변경시킨다. 아래의 예제는 0을 3으로 바꾸는 것이다.

```
$ a = %[x%3|x<-1~10];
[ 1,2,0,1,2,0,1,2,0,1 ]
$ alg.replace(a.begin(), a.end(), 0, 3);
$ print: a;
[ 1,2,3,1,2,3,1,2,3,1 ]
```

### replace_if(begin, end, function, to)

replace_if는 begin ~ end 구간사이의 값 x에 대해 funciton(x) 가 true인 경우 to로 변경시킨다. 아래의 예제는 3의 배수를 'X'로 변경시키는 예제이다.

```
$ a = [1..10];
[ 1,2,3,4,5,6,7,8,9,10 ]
$ alg.replace_if(a.begin(), a.end(), def.lambda(...argv){ return argv[0]%3 == 0; }, 'x');
$ print: a;
[ 1,2,'x',4,5,'x',7,8,'x',10 ]
$ 
```

### transfrom(begin, end, dest, function)

### transfrom(begin, end, begin2, des, function)

transform은 인자에 따라 두 방식으로 동작하는데, alg.transfrom(begin, end, dest, function)은 begin ~ end구간사의 아이템 x에 대해서, function(x)의 결과를 dest iterator에 삽입한다.

```
$ a = [1..10];
[ 1,2,3,4,5,6,7,8,9,10 ]
$ b = [];
[  ]
$ alg.transform(a.begin(), a.end(), b.begin(), def.lambda(...argv){ return argv[0]*10; });
$ print: b;
[ 10,20,30,40,50,60,70,80,90,100 ]
```

위의 예제는 a.begin() ~ a.end() 구간을 10배 곱하여 b에 insert하는 예이다.

alg.transform(begin, end, begin2, des, function)은 앞절과 유사하되 source가 두개이다. begin~end 까지의 각 원소 a 와, 동시에 begin2 ~ 의 각 원소 b에 대해서 function(a, b)의 결과를 dest 반복자에 삽입한다.

```
$ a = [1..10];
[ 1,2,3,4,5,6,7,8,9,10 ]
$ b = %[x|x<- 100~ ];
[ 100,101,102,103,104,105,106,107,108,109, ... ]
$ using alg;
$ c = [];
[  ]
$ alg.transform(a.begin(), a.end(), b.begin(), c.begin(), def.lambda(...argv){ return argv[0] + argv[1]; });
$ print: c;
[ 101,103,105,107,109,111,113,115,117,119 ]
```

위의 예제는 리스트 a와 b를 begin~end, begin2~ 의 범위동안 각 아이템을 더하여 c에 삽입한 예제이다. b가 조건제시법 리스트라 길이가 무한하지만, 함수가 동작하는 범위는 a.begin() ~ a.end()까지의 범위임을 유의하라. 동작 길이는 a.begin()~a.end()에 한정된다.

# cpp

cpp 모듈은 user define statement 을 지원하는 모듈로서, 사용자가 cpp 로 된 객체를 손쉽게 작성할 수 있게 해준다. 오르카에서는 다른 언어들과 마찬가지로 cpp 로 만든 확장 라이브러리를 작성할 수있으나, 이런 류의 확자 라이브러리들은 편의성에 있어서 어느정도 한계를 지닌다. 실제 원하는 코드가 일부분이라 해도 언어별로 요구되는 스펙에 맞춰 구현체를 작성해야 한다.

```
   using cpp;
   
   def.cpp sum(...argv) {
	// this is cpp code
       return argv[0] + argv[1];
   };
   
   print: my.sum(10, 20);
```

위와 같은 코드를 작성하고, 해당 모듈을 실행하면 최초 실행시나 코드가 변경되서 재컴파일 할 필요가 있으면 아래와 같이 컴파일 내역이 나타나고

```
$ ./orca tt
cpp external module compile: g++ -shared -o /tmp/lib__tt_1_context.so /tmp/__tt_1_context.cpp -I${ORCA_HOME}/include/orca -L${ORCA_HOME}/lib -lorca
/usr/bin/ld: cannot find -lorca
30
```

30 이 출력된다. 위의 컴파일 메세지를 보면 tt.orca 파일로부터 해당 cpp 객체의 내용을 사용하여 /tmp/\_\_tt\_1\_context.cpp 파일을 오르카가 생성하고 이를 컴파일하여 lib\_\_tt\_1\_context.so 파일을 만든다는 것을 알 수 있다.

만들어진 모듈 파일은 리눅스의 경우 /tmp 에 저장된다. 모듈을 만들때 사용하는 오르카 라이브러리는 ORCA\_HOME/lib 에서 찾는다. 때문에 환경변수에서 이를 잘 설정해 주어야 하고, 컴파일된 동적 라이브러를 참조하기 위해 /tmp 가 LD\_LIBRARY_PATH에 추가되어야 한다.

cpp 모듈을 사용하기 위한 최초 설정이 좀 번거롭긴 하지만 한번 설정해 놓으면 바이너리 코드로 동작하는 확장 라이브러리를 손쉽게 작성할 수 있다.

cpp UDS객체에 오르카가 전달하는 파라미터는 vector argv; 형식으로 전달된다. 때문에 위의 예제에서 argv\[0\], argv\[1\] 은 orcaData 타입이다. cpp의 자동 형변환 및 연산자 재지정을 통해 c++ 코드에서도 유연한 처리가 가능하다.

아래는 \_\_tt\_1_context.cpp의 내용으로 오르카 확장 라이브러리가 요구하는 내역을 모듈이 자동으로 생성했음을 알 수있다. 코드 중간에 사용자가 def.cpp { } 안에 작성한 부분이 들어있다.

```
 #include "orcaObject.h"
   
       class __tt_1_context : public orcaObject
       {
       public:
           orcaData udf(orcaVM* vm, vector& argv)
           {
	       // this is cpp code
               return argv[0] + argv[1];   
           }
   
           orcaData operator()(orcaVM* vm, int param_n)
           {
               vector argv;
               for (int i=0; iget_param(i));
   
               return udf(vm, argv);
           }
       };
   
       #ifdef WINDOWS
       #define EXPORT __declspec(dllexport)
       #else
       #define EXPORT
       #endif
   
       extern "C" EXPORT void* get___tt_1_context()
       {
           __tt_1_context* sp = new __tt_1_context();
           return sp;
       } 
```

단, cpp 코드를 사용할 때, 별도의 헤더나 라이브러리를 인클루드 해야 할 필요가 있다. 이경우엔

```
   def.cpp sum(...argv) {
       #include #cflags -I/usr/local
       #ldflags -ltest
   
       return argv[0] + argv[1];
   }; 
```

위와 같이 #include, #cflags, #ldflags 를 지정하면 된다. #include에 지정된 것들은 생성되는 코드의 윗부분에 등록되고, cflags, ldflags 에 지정된 것들은 컴파일시, 명령행 옵션으로 추가된다.

윈도우 환경에서는 이 컴파일을 vscompile.bat가 수행한다. 기본적으로 visual c++ express edition 2008 이 설치되었다 가정하고 vscompile.bat가 작성되었다. 만약 다른 컴파일러를 사용하거나 환경에 문제가 있다면 이 배치파일을 수정하면 된다.



# datatime, date, time

시각과 시간을 관리하는 모듈들이다. datetime은 년월일시분초(및 마이크로세컨드까지) 단위로 특정 "시각"을 가르키는데 사용되며 내부적으로는 date + time으로 구성되어 있다.

date는 년월일까지의 특정 일자를 가르킨다. time이 좀 특별한데 엄밀히 하루의 특정 시각이아니라 시간이다. 즉, 자정으로부터 해당 시간까지의 간격을 값으로 가진다.

dateduration은 날짜범위의 이러한 간격이다. (두달뒤, 3주 전 과 같은 연산에 사용 할 수 있는)

시각이란 특정한 포인트이기 때문에 시각끼리 더할 수 없다. 단 시각 끼리 빼면 시각사이의 간격이 리턴되는데 date라면 최저 해상도인 날 수가, time끼리 빼면 최저 해상도인 microseconds가 정수 타입으로 리턴된다.

시간이란 간격이기 때문에 시간끼리 더하거나 뺄 수 있다. 그리고 간격이기 때문에 정수로 곱하거나 나눌 수 있다.

시각과 시간을 더하면 특정 시각으로부터의 시간만큼 진행된 시각이 리턴된다. 시각에서 시간을 빼면 해당 시각보다 전의 시간만큼 앞선 시각이 리턴된다.

이 관계를 유의해서 다음 모듈들을 각각 살펴보자

# time

자정으로 부터 경과된 시간을 의미한다. 내부적으로 hour, minute, second, microsecond를 필드로 가진다.

time.clone(format): 생성자로서 보기와 같은 포멧의 시간정보를 받아 시간 객체를 새로 생성한다.

```
$ print: a = time.clone('01:02:03.4');
01:02:03.400000
$ print: a.hour;
1
$ print: a.minute;
2
$ print: a.second;
3
```

time.time\_of\_day() : 현재시간값을 리턴한다.

```
$ print: time.time_of_day();
23:01:33.990408
```

### time.hours(h)

h 시간만큼의 duration을 리턴한다.

### time.minutes(m)

m 분만큼의 duration을 리턴한다.

### time.seconds(s)

s 초만큼의 duration을 리턴한다.

### time.microseconds(us)

us 초만큼의 duration을 리턴한다.

위의 각 함수들은 각각의 time 객체를 리턴한다. 예제는 아래와 같다.

$ print: time.clone('01:02:03') + time.hours(3) + time.microseconds(1000);
04:02:03.001000

duration 이기 때문에 각 항목들은 제한이 없다. 예를들어 minutes는 60을 넘을 수 있다.

그리고 time 은 정수와 덧셈이 가능하다. 더해지는 정수값은 microseconds를 의미한다.

```
$ print: a;
01:02:03
$ print: a + 1234;
01:02:03.001234
$ 
```

time간에는 비교연산이 가능하다. 비교의 의미는 같은 크기를 가졌는가 이다.

```
$ using time;
$ a = time.clone('01:02:03');
$ b = time.clone('01:02:04');
$ print: a > b;
false
$ print: a == b;
false
$ print: a < b;
true
```

# date

date는 일단위의 특정시각을 의미한다. 각각 year, month, day 의 필드로 구성되어 있다.

```
$ using date;
$ print: a = date.clone('2000-01-02');
2000-01-02
$ print: a.year, ' ', a.month, ' ', a.day;
2000 1 2
```

date.today 는 현재 날짜를 의미한다.

```
$ print: date.today();
2010-11-02
```

date는 시각인데 반해 년,월,일,주 단위의 간격을 의미하는 dateduration이라는 객체가 있다. 이 일자의 시간객체는 상호간에 더하고 곱하고 나눌수 있다. 단, 나누기는 각 필드에 대해 나누게 되며 나머지는 사라진다. 정수를 더할 수도 있는데 이는 최저 해상도인 일수를 의미한다.

```
$ using date;
$ print: date.years(1);
1 years 
$ print: date.months(2);
2 months 
$ print: date.days(3);
3 days 
$ print: date.weeks(4);
4 weeks 
$ print: a = date.years(3) - date.months(4) + date.weeks(2) - date.days(7);
3 years -4 months 2 weeks -7 days 
$ print: a *= 2;
6 years -8 months 4 weeks -14 days 
$ print: a /= 3;
2 years -2 months 1 weeks -4 days 
$ print: a += 1;
2 years -2 months 1 weeks -3 days 
$ print: a -= 2;
2 years -2 months 1 weeks -5 days 
```

이제 date와 dateduration을 더하고 빼서 새로운 일자를 구할 수 있다.

```
$ print: date.clone('2000-01-01') + date.months(2);
2000-03-01
```

date 끼리의 뺄셈은 두 일자 사이의 날 수를 의미한다. date에 정수를 더하고 뺄수도 있는데 이는 date.days 단위를 의미한다.

```
$ using date;
$ print: date.clone('2000-01-01');
2000-01-01
$ print: date.today() - date.clone('2000-01-01');
3958
$ print: date.clone('2000-01-01') + 100;
2000-04-10
```

# datetime

date 와 time이 더해지면 datetime 객체가 된다. 이것은 특정 date로부터 time 시간만큼 지난 특정 시각을 의미한다.

```
$ print: date.today() + time.time_of_day();
2010-11-02T23:26:12.827502
```

datetime은 다음과 같이 생성할 수도 있으며 now() 는 현재의 년월일시를 의미한다. datetime은 내부적으로 date() 와 time() 인터페이스를 가지고 있다.

```
$ print: datetime.clone('2000-01-02 03:04:05');
2000-01-02T03:04:05
$ print: a = datetime.now();
2010-11-02T23:21:56.685685
$ print: a.date(), ' ', a.time();
2010-11-02 23:21:56.685685
```

datetime은 시간인 dateduration 이나 time을 더하거나 뺄 수 있다.

```
$ print: a = datetime.clone('2000-01-01 03:04:05');
2000-01-01T03:04:05
$ print: a + date.years(10) - date.months(30) + time.hours(100) - time.minutes(2000);
2007-07-03T21:44:05
```

datetime끼리의 뺄셈은 그 시각 사이의 간격인 time객체가 리턴된다. 마이크로 세컨드를 정수값으로 리턴한다. datetime에 정수를 더하거나 빼면 최저해상도인 마이크로 세컨드 만큼의 덧, 뺄셈을 의미한다.

```
$ print: a = datetime.clone('2000-01-01 03:04:05');
2000-01-01T03:04:05
$ print: a + 1000000 * 3600 * 24 * 10;
2000-01-11T03:04:05
$ print: a - 10;
2000-01-01T03:04:04.999990
$ print: datetime.clone('2010-01-01 03:04:05') - a;
87672:00:00
```

time.msleep(msec) 이것은 좀 별다른 static 함수로서 milliseconds만큼 sleep한다.

# dl
dl 은 c library 파일에 대해 억세스하기 위한 모듈이다. (TBD with example)

# distribute
# fs, dfsd, cached

이 모듈들은 동적인 분산파일시스템, 분산캐쉬를 구현한 모듈들이다. 아직은 프로토타입 수준이지만 앞의 dist 모듈과 합쳐서 분산처리에 유용하게 쓸 수 있다.

dfsd는 분산파일 서버노드이고, cached는 key, value 기반의 분산캐쉬 노드이다. fs는 이 노드들을 현재 파일시스템 경로의 특정 경로에 mount시키는 역할을 한다.

단, 마운트 한다는 것은 오르카 언어 내에서 fs에서 제공하는 파일억세스를 할 경우 적용된다는 의미로 오르카 밖에서 마운트 되는 것은 아니다.

분산 파일서버 노드인 dfsd는 dfsd(path, port) 로서 현시스템의 특정 path를 마운트 할 수 있게 port번호로 대기한다.

```
[머신 192.168.0.2]
$ orca dfsd /home/lynix 8080

[머신 192.168.0.3]
$ orca dfsd /home/orca 8080
```

이렇게 대기하고 있는 노드에 대해 fs.mount(path, ip, port) 를 사용하여 마운트 시키는데,

```
fs.mount('/mnt/node_a', '192.168.0.2', 8080); 
fs.mount('/mnt/node_b', '192.168.0.3', 8080); 
```

와 같이 실행하면

```
data = fs.read('/mnt/node_a/foo/bar.txt');
```

위의 문장을 실행하면 192.168.0.2 머신의 /home/lynix/foo/bar.txt를 읽어 data에 저장한다.

```
data = fs.copy('/mnt/node_a/foo/bar.txt', '/mnt/node_b/')
```

위 문장을 실행하면 0.2머신의 /home/lynix/foo/bar.txt 를 0.3 머신의 /home/orca 로 복사한다.

반면, fs.read('/etc/passwd') 와 같이 실행하면 해당 path는 마운트시키지 않는 경로이므로 로컬서버의 해당 파일을 읽는다.

read와 같은 fs의 파일관련 멤버들은 다음과 같다.

mkdir, ls, remove, file_size, isexist, isfile, isdir, read, write, copy, rename 이 함수들은 os모듈에서 제공하는것과 거의 유사한 동작을 한다. 차이점은 전술했다 시키 분산파일서버가 마운트 되어 있다면 해당 서버의 파일을 대상으로 동작한다는 것이다.

따라서 확장성을 위해 (분산파일시스템과 분산 캐쉬를 사용할 수있게) 파일전체를 다루는 작업은 os 모듈을 사용하지 말고 fs모듈을 사용하여 프로그래밍 하는 것이 좋다. (설령 다른 서버를 당장 마운트 할 일이 없다 해도)

아, 추가로 os와 fs모듈의 파일 작업은 file핸들을 가지기 않고 stateless로 매번 file open, close작업을 수행하기 때문에 잦은 파일 작업은 효율적이지 않다. 이경우에는 전통적인 방식 그대로 io.open('filename', 'rw') 와 같이 열어서 파일핸들 객체를 사용해 작업하는 것이 좋다.

### fs.mount\_dist\_dir(path, ...)

fs.mount\_dist\_dir(path, list) : mount가 특정 path에 한 서버를 마운트 시킨다면, 본 인터페이스는 list에 있는 서버들을 path에 분산 마운팅 시킨다. 그리고 fs.read(path) 의 억세스가 오면 path를 해슁해서 각각의 서버들에 분산시켜 분배한다.

### fs.mount\_dist\_dir('/mnt/dir', ('192.168.0.1', 8080), ('192,168.0.2', 8081));

fs.mount\_dist\_dir('/mnt/dir', ('192.168.0.1', 8080), ('192,168.0.2', 8081)); 와 같이 사용하고

```
fs.write('/mnt/dir/file1', 'hello, file'); 
fs.write('/mnt/dir/file2', 'hello, file'); 
fs.write('/mnt/dir/file3', 'hello, file'); 
...
```

와 같이 호출하면 path의 값을 적절히 해슁해 특정 서버로 중계한다. 해당 해슁은 string.hash() 인터페이스를 사용한다.

나중에 fs.read('/mnt/dir/file1'); 을 호출하면 아까 file1이 써졌던 서버로 가서 해당 파일의 내용을 읽어온다.

cached 는 key, value 페어의 메모리 캐쉬서버이다. 캐쉬 서버라고 인터페이스를 다르게 하지 않고, 단지 dfsd와 똑같이 동작하되 파일 value를 메모리에 기록한다는 것만 다르다.

dfsd와 인터페이스가 동일하기 때문에 fs에서 moutn\_dist\_dir을 통해 여러 cached를 마운트 하면 분산 캐쉬 서버로 동작시킬 수 있다. (일관성 -_-)=b)

단, 이번 릴리즈에서는 단순히 저장하고 읽는 기능만 있다. 설정한 용량을 초과하면 오래된 목록을 제거하는 기능은 다음 릴리즈에서 제공할 예정이고, 이 기능을 이용하여 cached와 dfsd를 각각 마운트해서 cached 에 없으면 dfsd에서 읽어오고 cached에 추가하는 또다른 분산 서버 노드도 추가할 계획이다.



# remotec, remoted, dist

이 모듈들은 오르카의 원격호출, 분산처리를 지원하기 위한 모듈이다. 먼저 remoted 는 원격호출을 받아 실행해주는 서버를 띄운다.

### remoted(port)

해당 포트로부터 처리 요청이 오길 기다린다.

orca remoted 8080
\## dist server start

실행을 위해선 위와 같이 shell에서 직접 실행하거나 스크립트 내에서 remoted(8080)을 호출하면 된다.

다음, 다른 머신에서 remotec 모듈을 이용해 해당 노드로의 연결을 설정한다.

```
$ using remotec;
$ c = remotec.clone('127.0.0.1', 8080);
$ print: c.ping();
true
$
```

이러면 객체 c의 밑에서 일어나는 멤버작업들은 원격 노드에서 일어나게 된다. (.attr, .attr_last, .attr= 을 통해 구현되어 있다) 이제 원격 노드에 대해서 객체를 write, read 하는 예를 선보이겠다.

```
$ c.hello = 'hello, remote';
$ print: c.hello;
hello, remote
```

아주 간단한데, 이건 로컬의 객체 c 내부에서 작업한 게 아니라 c.hello = 'hello, remote' 하는 순간 원격 node의 root.hello 란 객체에 저 스트링을 set했고, print: c.hello 로 remotec객체 c의 hello 멤버를 참조하면 접속되어 있는 노드의 root.hello 값을 가져오게 된다.

다단계 설정도 가능하다.

```
$ c.foo.bar = 10;
$ print: c.foo.bar;
10
$
```

이렇게 하면 원격 노드의 root.foo.bar 객체에 10이 설정되고 (foo 객체는 없으면 생성된다) print: c.foo.bar로 참조하면 해당 객체의 멤버가 돌아온다.

이 때, c.foo.bar 를 하면 c객체의 foo 멤버 객체가 모두 소켓을 타고 오는게 아니라, 실제로 필요한 foo.bar만 소켓을 타고 온다. (operator\_get과 operator\_get_last를 통해 각각 구분해서 처리할 수 있게 된다) 따라서, 원격 노드의 객체path를 걱정없이 참조할 수 있다.

이제 원격 노드의 함수를 실행해보자. 실행해볼 함수도 따져보면 객체이고 해서 다음과 같이 원격노드에 실행할 함수를 set한 후 실행할 수 있다. (잠깐, 현재 쉘 인터프리터 모드에서는 객체 전달이 되지 않는다. 다음 테스트는 파일을 통해서 진행한다)

remoted 가 8080포트로 떠있는 상태에서 다음 코드를 실행시키면,

```
using remotec;

def sum(...)
{
	return argv\[0\] + argv\[1\];
}

c = remotec.clone('127.0.0.1', 8080);
c.sum = my.sum;
print: c.sum(10, 20);
```

결과값으로 30이 리턴된다. 원격 노드의 root.sum에 클라이언트에서 정의한 객체를 전달하고 그것을 실행시킨 결과값을 받아왔다.

그런데 잠깐, 원격 호출을 한다는건 저쪽 머신에만 있는 리소스를 사용해서 처리하기 위해서도 있지만 처리해야 할 일을 분담하는 의미도 있다. 그런데 위의 예에서는 원격 머신이 처리를 끝낼 때까지 클라이언트에서 블록된다. 논블록킹으로 처리가 진행되게 하려면 아래와 같이 코드를 수정하면 된다.

```
using remotec;

def sum(...)
{
	return argv[0] + argv[1];
}

c = remotec.clone('127.0.0.1', 8080);
c.sum = my.sum;
c.sum.__nowait__(10, 20);
print: c.is_done(100);
print: c.pop_obj();
```

c.sum을 호출할 때 가상의 멤버 \_\_nowait\_\_ 을 한번 더 달아주면 논블록킹으로 바로 리턴되며 (리턴값은 nil) is_done(msec) 멤버를 호출하여 처리가 끝났는지 확인할 수 있다.

isdone(msec) 은 처리가 끝났는지를 true/false로 리턴하되 인자가 없으면 바로 리턴하고, 인자가 있으면 처리 결과를 최대 밀리초만큼 기다린다. (기다리는 중에 처리가 끝나면 바로 리턴된다) 처리가 되었으면 c.pop_obj() 를 통해 저장된 결과값을 읽어올 수 있다.

위의 예가 다른 언어의 원격호출과 차별된 것은 두가지 인데, 하나는 마치 로컬의 객체를들을 다루듯 c.* 로 원격의 객체들을 다루었다는 점이며, 다른 하나는 실행할 객체를 이쪽에서 정의해서 저쪽으로 넘겨 바로 실행했다는 점이다. 오르카는 객체의 컴파일된 바이트 코드까지 바로 머신간 바로 전달 가능하다.

해서, remotec 객체의 remote_do() 함수를 이용하면 위의 코드를 다음과 같이도 실행할 수 있다.

```
using remotec;

c = remotec.clone('127.0.0.1', 8080);
c.remote_do: 10, 20, def.lambda(...argv) { 
	return argv[0] + argv[1]; 
};

print: c.is_done(100);
print: c.pop_obj();
```

이 코드는 30을 리턴한다.

remoted(...) 는 가변인자들을 인자로 하여 마지막 가변인자 함수를 원격 노드에서 논블락킹으로 실행한다. 마찬가지로 is\_done으로 처리완료 여부를 확인한 후 pop\_obj로 결과값을 확인했다.

remoted_do 의 마지막 인자는 원격 노드에서 실행할 함수인데 예에서는 람다함수를 사용해여 처리했다. 원격호출이지만 마치 로컬에서 처리하듯 자연스럽게 진행된다.

현시점에서 이정도까지 구문 상으로 유연하게 원격호출을 실행할 수 있는 언어는 오르카 뿐이라 생각된다.

dist 모듈은 remoted 리스트를 가지고서 이들에 대해 손쉽게 분산처리를 진행하기 위한 모듈이다. 현재는 간단한 스케쥴링 방식을 쓰고 있지만 이부분은 좀 더 개선할 생각이고...

### dist.add(ip, port)

dist.add(ip, port) 는 특정 원격 노드로 접속한 후, 해당 원격 노드를 내부 노드 리스트에 저장하여 처리 요청이 왔을 때 하나를 선택할 수 있도록 한다.

### dist.dist_do(...)

dist.dist\_do(...) 는 가변인자들을 인자로 가변인자의 마지막 함수를 어느 한 노드로 (모듈이 알아서 선택한) 처리를 요청한다. remotec.remote\_do 와 같으나 노드를 알아서 선택하는 것이 다르다.

### dist.dist_for(list, fun)

dist.dist\_for(list, fun) list 들을 나누어 등록되어 있는 원격노드들에 분산시켜 fun을 실행한 결과를 결과 리스트로 되돌려 받는다. dist\_do와 다르게 dist_for는 모든 결과가 처리될 때까지 블락된다. 현재는...

예를 들어 돌아가는 것을 보자.

다음은 프로젝트에 포함되어있는 test\_dist.orca이다. 테스트 프로그램은 원격노드를 port, port+1, port+2 로 세개 띄우고 dist를 통해 dist\_do, dist\_for 를 실행시킨다. dist\_do로는 간단한 sum함수를 실행시키고 dist_for로는 1~100 까지의 리스트를 분산처리로 각각 제곱한 결과를 가져오도록 하고 있다.

```
using distribute.remoted;
using distribute.remotec;
using distribute.dist;
using math.random;
using time;

random.seed();
port = random.integer(1000) + 8000;

print: '# port: ', port;


parallel do {
	server = remoted.clone();
	server(port);
}

parallel do {
	server = remoted.clone();
	server(port+1);
}

parallel do {
	server = remoted.clone();
	server(port+2);
}

time.msleep(200);

dist.add('127.0.0.1', port);
dist.add('127.0.0.1', port+1);
dist.add('127.0.0.1', port+2);


r = dist.dist_do(10, 20, def.lambda(...argv) { return argv[0] + argv[1]; });
print: r.is_done(100);
print: ret = r.pop_obj();

if ret != 30 {
	throw test.dist <- 'dist_do failed';
}

list = [1..100];
rs = dist.dist_for(list, def.lambda(...argv) { return argv[0] * argv[0]; } );
print: rs;

if rs != %[ x*x | x<-1~100 ] {
	throw test.dist <- 'dist_for failed';
}

print: '## now quit: ', dist.shutdown();
return 'OK', my;
```

다음은 위의 테스트 프로그램의 실행결과이다. 중간 dist_do 의 결과로 30 이 나왔고, \[1..100\] 을 제곱한 결과가 제대로 분산처리된 것을 확인할 수 있다.

```
# port: 8985
## dist server start
## dist server start
## dist server start
true
30
[ 1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256,289,324,361,400,441,484,52
9,576,625,676,729,784,841,900,961,1024,1089,1156,1225,1296,1369,1444,1521,1600,1
681,1764,1849,1936,2025,2116,2209,2304,2401,2500,2601,2704,2809,2916,3025,3136,3
249,3364,3481,3600,3721,3844,3969,4096,4225,4356,4489,4624,4761,4900,5041,5184,5
329,5476,5625,5776,5929,6084,6241,6400,6561,6724,6889,7056,7225,7396,7569,7744,7
921,8100,8281,8464,8649,8836,9025,9216,9409,9604,9801,10000 ]
```

하둡과 같은 다른 분산처리 시스템에 비해 매우 쉽게 구축하고 유연하게 처리할 수 있는 것을 확인할 수 있다.


# encoding

## json

xml 모듈과 마찬가지로 json 파일을 인코딩, 디코딩 하는 역할을 한다. 본 문서를 보기전에 module xml을 먼저 보는 것이 좋겠다.

### json.decoding(str)

json.decoding은 json 스트링을 오르카의 자료구조로 디코딩 한다.

### json.encoding(obj)

json.encoding은 오르카 자료구조를 json 스트링으로 인코딩한다.

### json.beutify(obj)

json.beutify는 오르카 자료구조를 json 스트링으로 인코딩하되, readable하게 indent를 맞춰준다.

변환규칙은, json의 dictionary 는 오르카의 맵으로, json의 배열은 오르카의 리스트로 변환된다. 단, xml과 마찬가지로 json의 딕셔너리는 다중키값이 가능한데 (중복된 키가 가능), 오르카의 맵은 중복을

허용하지 않기 때문에 중복이 발생했을 때는 중복되는 value들을 튜플로 만든다.

예를들어 설명해보면,

```
  str = "{ 'a':3, 'b':6, 'c':[1,2,3, { 'a':{'b':'c'}, 'd':[1,2,3], 'd':3 },   4,5,6] }";
```

이런 스트링이 존재할 때

```
ret = json.decoding(str);
```

이 함수는

```
{ 'a':3,'b':6,'c':[ 1,2,3,{ 'a':{ 'b':'c' },'d':( [ 1,2,3 ],3 ) },4,5,6 ] }
```

위와 같은 오르카 자료구조를 생성한다. 보면 (syntax가 유사하기 때문에) 거의 출력된 모습이 같다. 단,

'd'의 경우 같은 키값으로 \[1,2,3\]과 3 이 중복되기 때문에 튜플로 (\[1,2,3\], 3) 으로 변환되었다.

이제, 이 객체의 'c'의 목록을 보고싶으면 print: ret\['c'\]; 와 같은 방식으로 접근가능하다.

이제 오르카 자료구조를 json 스트링으로 변환하는 것은, str = json.encoding(ret); 과 같이 하면 되고 이 함수는

{'a':3,'b':6,'c':\[1,2,3,{'a':{'b':'c'},'d':\[1,2,3\],'d':3},4,5,6\]}

와 같이 변환해 준다. 역시 일렬로 출력되기 때문에 보기 불편한데, xml과 마찬가지로 beutify 가 존재한다.

print: str = json.beutify(ret) 을 실행하면

```
        {'a':3,
        'b':6,
        'c':    [1,
                2,
                3,
                        {'a':   {'b':'c'},
                        'd':    [1,
                                2,
                                3],
                        'd':3},
                4,
                5,
                6]}
```

위와 같이 depth를 맞춰 정렬시켜준다.

## xml

xml 모듈은 decode 구문을 사용하여 xml을 인코딩, 디코딩하는 역할을 한다. 사실 이 모듈은 개선된 decode 구문을 시험하는 측면이 있다.

순수하게 orca만을 사용하여 작성되었는데, 조만간 추가될 libxml을 사용한 cxml 을 사용하는 것이 보다 더 빠를 것이다.

### xml.decoding(string)

xml.decoding은 xml 스트링을 오르카의 자료구조로 디코딩 하며,

### xml.encoding(obj)

xml.encoding은 오르카의 자료구조를 xml 스트링으로 인코딩한다.

### xml.beutify(obj)

xml.beutify는 encoding과 비슷하나, 사람이 readable하기 좋게 indent를 맞춰서 변환한다.

변환규칙은 예를 들어 설명하겠다.

먼저 입력 스트링이 이와 같으면

```
str = '''
<?xml version="1.0"?>
<tag_a>
<tag_b attr1="value1" attr2="value2">text of tag b</tag_b>
</tag_a>
''';
```

이 xml 스트링은

```
{ '$info':'xml version="1.0"',
   'tag_a':{ 
		    'tag_b':{ '$attrs':{ 'attr1':'value1','attr2':'value2'  },'$text':'text of tag b' } 
                }
}
```

와 같이 변환된다. xml의 경로 구조를 따르고 있으며 한 노드는 (tag_a) 자기의 이름을 키로하고, 자기 밑의 child노드들을

value로 하는 map 구조이다. 특수한 노드가 $attrs와 $text, $info 가 있는데, $attrs는 안의 어트리뷰트 값들을 나타내는 맵이며, $text는 태그의 value 값이고, $info 는 document 정보이다.

기본 규칙은 이와 같은데 오르카의 맵은 중복을 허용하지 않으나 xml은 중복을 허용하기 때문에 중복되는 태그가 존재하면 튜플리스트로 관리한다.

즉, 위의 예를 좀 바꾸어

```
str = '''
<?xml version="1.0"?>
<tag_a>
<tag_b attr1="value1" attr2="value2">text of tag b</tag_b>
<tag_b>text of tag b 2nd</tag_b>
</tag_a>
''';
```

이런 입력값에 대해서 오르카는

```
{ '$info':'xml version="1.0"',
  'tag_a':{ 'tag_b':( { '$text':'text of tag b 2nd' },
			        { '$attrs':{ 'attr1':'value1','attr2':'value2' },'$text':'text of tag b' } )
	       } 
}
```

위와 같이 tag_b의 value로서 튜플로 각각의 노드들이 표현된다.

이제 이로부터 tag_a안에 무슨 노드들이 있는지 보고 싶으면

```
ret = xml.decoding(str);
ret['tag_a'].keys();
```

와 같이 하면 되고

내려가려면 ret\['tag\_a'\]\['tag\_b'\]\[1\]\['$text'\] 와 같은 식으로 tree를 탐색하면 된다. xml내에서의 search등은 다음 버전에서 지원할 생각인데, alg.traverse 함수를 사용해서 사용자가 직접 탐색조건을 지정할 수도 있다.

이제 이렇게 디코딩된 자료를

xml.encoding(ret) 을 통해 인코딩하면

```
xml.encoding(ret)

<? xml version="1.0" ?><tag_a><tag_b >text of tag b 2nd</tag_b><tag_b attr1=value1 attr2=value2 >text of tag b</tag_b></tag_a>
```

위와 같이 복원된다.

그런데 이 결과는 일렬이어서 보기 좋지 않다.

xml.beutify(ret)을 실행하면

```
<? xml version="1.0" ?>
<tag_a>
        <tag_b >
                        text of tag b 2nd
        </tag_b>
        <tag_b attr1=value1 attr2=value2 >
                        text of tag b
        </tag_b>

</tag_a>
```

와 같이 인덴트를 맞춰서 인코딩해준다.


## base64

base64 인코딩, 디코딩을 위한 모듈이다.

### base64.enc(str)

str에 대해서 base64 인코딩을 수행한다.

### base64.dec(str)

str에 대해서 base64 디코딩을 수행한다.

```
$ using base64;
$ print: a = base64.enc('12345678');
MTIzNDU2Nzg=
$ print: b = base64.dec(a);
12345678
```

# fdselect

fdselect 모듈안에 동명의 select 객체가 들어있다. Python과 유사하게 epoll 등도 이 모듈 안으로 집어넣을 것이기 때문이다.

fdselect(read\_list, write\_list, exception_list, sleep)

posix select API와 유사하게 위와같이 같이 구성할 수 있되, read_list 등은 파일 핸들들의 리스트이며, sleep은 밀리세컨드 단위의 슬립타임이다.

리턴값으로 상태에 변화가 생긴 핸들들의 리스트를 돌려준다. 아래의 server 객체는 서버소켓을 만들고 해당 소켓에서 접속이 올때까지 기다리는 예이다. 테스트용이니 본격적으로 동작하기까지 바라진 말기 바란다.

```
def server {
    sock = socket.create();

    sock.bind(8080);
    sock.listen();

    while true {
        fd = select.select([sock.get()], [], [], 1000);

        if fd[0] == [sock.get()] {
            new_cl = sock.accept();

            str = new_cl.recv();
            new_cl.send(str);

            sock.close();
            new_cl.close();
            return;
        }
    }
}
```

# file

read, write, close 인터페이스를 통해 파일 입출력을 수행할 수 있다. 간단한 예는 아래와 같다.

```
input = 'hello, file';
fh = open('test.txt', 'w');
fh.write(input);
fh.close();

fh = open('test.txt', 'r');
output = fh.read();
fh.close();
```

이 프로그램은 test.txt에 input을 기록한 후, 이를 다시 읽어오는 예이다. seek(offset, base) 멤버는 파일 포인터를 옮기는 역할을 한다. offset 은 이동할 크기이며, base는 스트링으로 'SEEK\_SET', 'SEEK\_CUR', 'SEEK_END'인데, 각각 파일의 앞, 파일 포인터의 현재, 파일의 뒤를 기준으로 한다.

tell 멤버는 현재의 파일 포인터를 리턴한다.



# fun

고차함수작업을 위한 유틸들이다. 다음과 같은 인터페이스를 제공한다.

### map(iteratable, f)

iteratable의 각 멤버에 대해 f를 적용하고 그 결과를 리스트로 되돌린다.

```
$ using fun;
$ ret = fun.map([1,2,3], def.lambda(...argv){ return argv[0] * 2; } );
$ print: ret;
[ 2,4,6 ]
```

위 코드는 \[ 1 * 2, 2 * 2, 3 * 2\] 과 같이 동작했다.

### reduce(iteratable, fun, initial)

iteratable의 각 멤버들에 대해서 fun을 적용한 누적결과를 리턴한다. initial이 존재하면 그것을 초기값으로 하고, 없으면 첫번째 원소를 초기값으로 한다.

다음은 리스트의 전체값을 더하는 코드이다.

```
$ using fun;
$ print: fun.reduce([1,2,3,4,5], def.lambda(...argv){ return argv[0] + argv[1]; });
15
```

argv\[0\]은 누적된 결과가 계속해서 들어가고, argv\[1\]에 멤버들의 각 원소가 들어간다. 따라서 위코드는 ((((1 + 2) + 3) + 4) + 5) 와 같이 동작했다.

### bind_1st(fun, arg)

fun 함수의 첫번째 파라미터에 arg를 bind한 새로운 함수를 생성한다.

즉, def mul(a, b) { return a * b; }

란 함수가 있을 때

mul10 = fun.bind_1st(..mul, 10); 과 같이 하면

```
$ print: mul10(2);
20
$ print: mul10(2.4);
4.8
```

과 같이 입력되는 값에 10을 곱하는 (mul함수의 a에 10이 바인딩되어) 새로운 함수가 나타난다.

bind\_2nd, bind\_3rd 역시 두번째, 세번째 파라미터를 특정객체로 묶는 역할을 하며, fun.bind_nth(fun, arg, n) 는 arg를 fun함수의 n번째 파라미터에 바인딩 한다.

물론 bind 는 중첩해서 가능하다.

### apply(f, list)

리스트, 튜플 타입인 list를 f 함수에 각각 파라미터에 대입시켜 실행한다.

즉 fun.apply(foo, \[1,2,3\]) 은 foo(1,2,3) 을 실행하게 된다.



# gtk
gtk 모듈은 gui 에서 사용하 linux gtk 핸들에 대한 로우레벨 라이브러리이다. gtk 모듈을 직접 사용하기 보다는 다음의 gui 모듈을 사용하기 바란다. 예제는 tests 파일에도 있지만 10min.md 의 2장에도 설명이 되어 있다.
추후, windows32 api 기반으로도 추가될 예정이다.


# gui

이번버전부터 오르카는 GUI 를 지원하게 되었다. 오르카의 유연한 객체관계 모델을 사용하여 GUI를 유연하게 표현하는 모습을 살펴보자.

단, 이 모듈은 하부단의 표현 레이어로 현재는 Gtk 만을 사용하고 있기 때문에, 현재 윈도우즈에서 이 기능을 사용하려면 windows용 gtk 라이브러리를 설치해야 한다. 이 부분이 번거롭긴 하지만 아래의 몇몇 예제를 보면 그럴만한 가치가 있다는 것을 알게 될 것이다.

```
  def main : window
   {
       my.attr['wh'] = (800, 600);
   
       def box : vbox
       {
           def menu : menubar
           {
               file = [ 'open', def.lambda() {
                                   name = dialog.fileopen(find_owner('main'));
                                   str= os.read(name);
                                   find_owner('box').hs.edit.attr['text'] = str;
                               },
                       'save', def.lambda() {
                                   str= find_owner('box').hs.edit.attr['text'];
                                   name = dialog.filesave(find_owner('main'));
                                   os.write(name, str);
                               },
                       'exit', def.lambda() {
                                   find_owner('main').quit();
                               }
                       ];
   
               my.push_back('file', file);
           }
   
           def hs : scroll
           {
               def edit : text
               {
               }
           }
       }
   }
```

위의 예제는 메모장을 오르카로 표현한 것이다. 만일 win api 나 gtk 프로그래밍을 해봤다면 코드만으로 이 작업을 하는 것이 얼마나 번거로운지 알 것이고, RAD 툴을 쓴다해도 그 툴의 표현방식과 실제 코드의 갭으로 인해 코드의 직관성이 떨어지게 된다.

반면, 오르카는 모든 데이터의 기본단위를 객체로 최소호하고 이들의 상관관계를 동적으로 설정할 수 있기 때문에 실제보여지는 GUI 객체가 코드상의 객체와 위치, 관계, 코드를 동일하게 유지할 수 있다.

오르카의 GUI에 대한 접근은 눈에 보이는, GUI객체 그 자체와 객체간의 포함관계를 코드상의 객체로 1:1 매핑하게 하는 것이 핵심이다.

즉, 하나의 버튼이 있는 윈도우를 생각해보자, 그 버튼은 윈도우 안에 속해있다.

```
   def main : window
   {
       def box : vbox
       {
           def ok : button
           {
               my.attr['text'] = 'ok';
           }
       }
   }
```

해서 그 코드는 위와 같이 표현된다. 윈도우를 상속받은 main window 안에 button 의 속성을 상속받은 ok button 이 존재한다. 단, GUI 객체를 어떤식으로 배치할지를 정하는 container 객체가 하나 있어야 하는데, vbox, hbox, fixed container 중의 하나안에 존재해야 한다.

위 코드를 아래와 같이 실행시키면 윈도우가 나타난다.

```
my.main.make();
my.main.show();
```

![](image/gui_first.jpg)

make 인터페이스는 윈도우 안의 GUI 객체들을 포함관계대로 구성하라는 의미이고, show 인터페이스는 구성된 윈도우를 보여준다.

보여준 윈도우는 아래와 같다.

아직 ok 버튼의 동작을 정의하지 않았기 때문에 클릭한다 해도 아무 일도 일어나지 않는다.

이제 실제 동작이 있는 테스트 예제를 보자

```
  def main : window
   {
       my.attr['xy'] = (50, 20);
       my.attr['wh'] = (300, 200);
   
       def box : fixed
       {
           def counter : label
           {
               my.attr['xy'] = (40, 50);
               my.attr['text'] = 0;
           }
   
           def plus : button
           {
               my.attr['xy'] = (150, 30);
               my.attr['wh'] = (100, 50);
               my.attr['text'] = '+';
               my.event['clicked'] = def.lambda() {
                   find_owner('box').counter.attr['text'] += 1;
               };
           }
   
           def minus : button
           {
               my.attr['xy'] = (150, 130);
               my.attr['wh'] = (100, 50);
               my.attr['text'] = '-';
               my.event['clicked'] = def.lambda() {
                   find_owner('box').counter.attr['text'] -= 1;
               };
           }
       }
   }
```

위의 예제는, 윈도우 안에 카운터 텍스트가 있고 이 카운터를 증감시키는 \+, \- 버튼이 존재한다. fixed container 안에 있기 때문에 attibute로 xy, wh 를 절대좌표로 지정했다.

이제, gui 이벤트는 event 어트리뷰트를 통해 정의할 수 있다. plus button 의 'clicked' 를 코드와 같이 정의하면, 해당 버튼을 클릭했을 때 그 정의된 객체가 실행된다.

코드에선 find_owner('box').counter.attr\['text'\] += 1 이 동작한다. find_owner는 util.find_owner인터페이스로 자신의 owner들을 따라 올라가면서 이름이 같은 객체를 찾는 일을한다. 해서 find_owner('box').counter는 main.box.counter를 리턴하고, counter의 'text' 속성을 1 증가시킴으로써 실제 GUI 텍스트를 변경시키게 된다.

실제 나타나는 윈도우는 아래와 같다.  
![](image/button.jpg)

짧지만 간결한 이 예제에서 볼 수 있는 것은 실제 GUI 윈도우상에 있는 객체들과 그 객체들의 관계, 이벤트가 실행됐을 때의 코드등이 일관성 있고 직관적으로 표현된다는 점이다.

이를 GTK API나 win32 api 만으로 구현하거나, MFC로 구현했을 때와 비교해 보면 차이점을 더 명확히 알 수 있다.

GUI 객체들은 현재 아래 목록들이 제공된다.

*   window : 최상위 윈도우 객체
*   button : 버튼
*   check : 체크버튼
*   combo : 콤보버튼
*   radio : 라디오버튼
*   entry : 입력 엔트리
*   fixed : 절대좌표 컨테이너
*   vbox : 세로 컨테이너
*   hbox : 가로 컨테이너
*   dialog : 기본제공 다이얼로그 (파일 오픈, 저장 등)
*   hsep : 가로 분리자
*   image : 이미지
*   label : 라벨
*   list : 리스트
*   menubar : 메뉴
*   scroll : 스크롤
*   statusbar : 상태바
*   table : 테이블
*   text : 텍스트
*   tree : 트리

각각의 객체들은 GTK 객체 속성을 나타내며 이를 상속하여 앞의 예제와 같이 윈도우를 구성할 수있다. 각각의 예제에 대해서는 tests/test_gui.orca 를 실행하면, 셈플 프로그램과 그것의 코드를 볼 수 있다.



# html
html 모듈은 웹 프로그래밍에서 html 템플릿을 동적생성할 수 있게 도와주는 모듈이다. html 에 대한 문맥확장객체 컴파일을 수행하고, form과 tag 에 대한 처리를 할 수 있게 지원한다.

자세한 내역은 10min.md 의 4장을 참조하자.

# io

입출력에 관련된 객체들이 모여있는 모듈이다.

### print(...)

print 멤버는 가변인자들을 입력 받아서 화면에 출력한다. 원래 root.io.print(‘abc’); 형태로 써야 하지만, 편의를 위해 using space에 포함되어 있다.

### put(...)

print와 같지만 개행을 하지 않는다.

### open(filename, mode)

첫번째 파라미터로 파일이름을, 두번째 파라미터로 모드를 입력받아 파일 객체를 리턴한다. 사용법은 다음의 file 객체를 참조하라.

### input()

input 멤버는 콘솔로부터 입력을 받는다.

```
$ name=io.input();
KY Lee
$ print: 'hello, ', name;
hello, KY Lee
```



# ipc

멀티 쓰레드 환경에서의 IPC, 특히 동기화를 지원하기 위한 모듈로서 현재로는 mutex, cond, semphore가 구현되어 있다.

## mutex

lock을 통해 잠기고, unlock을 통해 뮤텍스를 해제한다. 아래와 같은 예제를 실행하면,

```
using ipc;
using thread;
using time;

def sample_thread(num, mtx) {
    print: 'thread: ${num} start';    
    mtx.lock();
    print: 'thread: ${num} accuire mutex';    
    time.msleep(3000);
    mtx.unlock();
    print: 'thread: ${num} release mutex';    
    print: 'thread: ${num} end';    
}

m = clone ipc.mutex;

th1 = thread.run(my.sample_thread, 1, m);
th2 = thread.run(my.sample_thread, 2, m);
th1.join();
th2.join();

결과는 아래와 같다.

thread: 1 start
thread: 2 start
thread: 1 accuire mutex
thread: 1 release mutex
thread: 2 accuire mutex
thread: 1 end
thread: 2 release mutex
thread: 2 end

mutex는 scope object 이기 때문에 scope로 lock, unlock을 할 수도 있다.

a = mutex.clone();

a {
  fh.write('exclusive write'); 
}
```

## cond

### signal()

### wait(mutex, \[msec\]) wait(\[msec\])

조건변수로서 wait로 기다리고, signal로 깨운다.

wait는 critical section과 연계된 mutex를 받을 수 있고, 기다리는 시간인 msec을 추가로 받을 수 있다. msec이 생략되면 infinite을 뜻한다.

아래의 예제를 실행하면 wait_thread가 1초후에 깨어나게 된다.

```
using time;

def wait_thread(cond) {
    print: 'thread: wait';
    cond.wait(3000);
    print: 'thread: wakeup';
}

def signal_thread(cond) {
    time.msleep(1000);
    cond.signal();
}

c = clone ipc.cond;

th1 = thread.run(my.wait_thread, c);
th2 = thread.run(my.signal_thread, c);
th1.join();
th2.join();
```

## semaphore

세마포어로서 set을 통해 key와 max값을 지정하고, inc로 증가, dec로 감소시킨다.

아래의 간단한 예제를 실행시키면,

```
using ipc;
using thread;
using time;

def inc_thread(key) {
    sem = clone ipc.semaphore;
    sem.set(key, 10);
    for a in [1..10] {
        print: 'produced...';
        sem.inc();
        time.msleep(1000);
    }
}

def dec_thread(key) {
    sem = clone ipc.semaphore;
    sem.set(key, 10);
    for a in [1..10] {
        sem.dec();
        print: 'consumed...';
    }
}

th1 = thread.run(my.inc_thread, 1000);
time.msleep(3000);
th2 = thread.run(my.dec_thread, 1000);
th1.join();
th2.join();
```

아래와 같은 결과를 얻는다. Produce 된 뒤에 consume 되는 것을 알 수 있다.

```
produced...
produced...
produced...
produced...
consumed...
consumed...
consumed...
consumed...
produced...
consumed...
produced...
consumed...
produced...
consumed...
produced...
consumed...
produced...
consumed...
produced...
consumed...
```

# lang

## lisp

lisp 모듈은, 오르카의 parse statement로 common lisp 을 간략히 구현한 것이다. orca를 사용하여 구현하였기 때문에 lisp 구문내에서 오르카 객체와 모듈을 자연스럽게 참조할 수 있다.

lisp.compile(str)을 실행하면 컴파일된 코드가 리스트 형태로 리턴된다. 이 리턴값을 차후에 사용하고자 하면, pack.save()를 사용하여 파일에 저장할 수 있다. 실제 실행결과는 이 리스트를 lisp.execute(list) 로 호출하여 얻을 수 있다.

실행예를 보아가며 설명하겠다.

가장먼저 3 + (4 * 2) 의 리습 코드를 실행한 모습이다. 컴파일된 결과와 그 결과를 실행한 값을 볼 수 있다. 인터프리터 상이라, 컴파일 결과물도 출력된 모습을 볼 수 있다.

```
$ ret = lisp.compile('(+ 3 (* 4 2))');
( [ [ +,3,[ *,4,2 ] ] ],{ 'F':false,'T':true,'car':car <0x9d82350>,'cdr':cdr <0x9d823d8>,'do':do_list <0x9d82460>,'list':list <0x9d824e8> } )
$ lisp.execute(ret);
11
```

아래와 같이 defun, macro, let 및 if, cond 구문들도 지원한다.

```
$ lisp.execute(lisp.compile('(defun (sum x y) (+ x y) )(sum 4 4)'));
8
$ lisp.execute(lisp.compile('(defmacro (addy x) `(+ ,x y))  (let ((y 20)) (addy 10))'));
30
$ lisp.execute(lisp.compile('( cond ((>= -3 20) (* 3 10))  ((< 20 10) 3)   (T "error") )'));
error
```

또한, lisp 구문안에선 orca 객체들을 참조할 수 있다. 단, io, io.print만이 namespace에 잡혀있기 때문에, 다른 객체를 참조하기 전엔 (using path) 구문으로 등록해주어야 한다.

```
$ lisp.execute(lisp.compile('(print "hello\n")'));
hello
nil
lisp.execute(lisp.compile('(using math) (math.sin (/ 30.0 90.0))'));
0.327195
```

그리고, lisp 모듈 자체가 user defined statement 를 지원한다.

때문에 오르카 소스코드 상에서 다음과 같이 쓸 수 있다. def foo := %lisp{ (+ argv0 argv1) }; print: r = .foo(3, 4);

위 예제는 7을 출력한다. lisp UDS 객체에 파라미터는 argvN 의 형태로 전달된다. 이 모듈을 통해서, 오르카 언어상에서 유연하게 리습 구문을 사용할 수 있고, 리습에서 유연하게 오르카 객체를 참조할 수 있게되었다.

tests/test_lisp.orca에서 더 많은 테스트 예제들을 확인할 수 있고, lib/lisp.orca에서 리습모듈의 구현체를 볼 수 있다.

## sh

sh 모듈은, os.run을 사용한 쉘 스크립트 wrapper인데 오르카의 user define statement 에 사용될 수 있도록 한 것이다. 기본적으로 os.run으로 구문을 실행하되, 파라미터는 argv\[ \] 로 전달한다.

아래 예제는 tgzip이란 멤버를 sh 모듈을 사용한 사용자 정의 구문 객체로 선언하고, 이를 이용해 폴더를 tgz 로 만드는 예제이다.

```
def tgzip = %sh{ tar -xcvf argv[0] argv[1] };
my.tgzip('out.tar.gz', '/home/lynix/out');
```

# log
log 는 채널인으로 구현된 라이브러리이다.

로그는 다단계로 설정할 수 있으며 가장 명시적으로 설정된 것이 적용되나 설정되 것이 없으면 상위의 설정을 따른다. turn on/off 는 해당 필드를 호출하면서 true/false 를 파라미터로 주면 변경할 수 있다.

아래는 그 예이다

```
$ log(false);
<log - 0xd505e0>
$ log <- 'turned off';
$ a = 10;
10
$ log <- 'increaed value: %d' % (a+=1);
$ print: a;
10
$ log.socket(true);
<log - 0xd537a0>
$ log.socket.tcp <- 'turn on by log.socket';
[2019-04-30T12:49:50.820910] turn on by log.socket
$ log.socket.tcp(false);
<log - 0xd53500>
$ log.socket.tcp <- 'explicit set is applied';
$ log.socket <- 'so this will be printed';
[2019-04-30T12:50:48.631508] so this will be printed
$ log.socket.tcp.port <- 'but this is not. log.socket.tcp turn off implicit';
$ 
```
튜토리얼을 보았으면 채널인의 경우 어느 객체의 <- 멤버가 nil 인 경우 오른쪽을 evaluate 하지 않는 다는 것을 보았을 것이다.

위의 예중 'increased value: %d' % (a+=1) 을 출력하는 구문인데, log 가 꺼져 있기 때문에 <- 이 nil 로 설정되었고, 오르카 VM은 오른쪽을 evaluate 하지 않고 다음 문장으로 넘어갔다. 때문에 a 값이 증가하지 않고 10으로 유지되었다.





# math

math 는 c의 math library 에 대한 wrapper로서 다음의 인터페이스들을 제공한다.

acos, asin, atan, atan2, ceil, cos, cosh, exp, fabs, floor, fmod, frexp, ldexp, log, log10, modf, pow, sin, sinh, sqrt, tan, tanh

함수들의 인터페이스 및 스펙은 libm 의 것과 거의 유사하다. 단, 언어의 특성상 c에서는 파라미터를 통한 output이 가능하나 오르카에서는 포인터가 없기 때문에 출력값이 2개 이상인 경우는 튜플로 리턴된다. 상세한 사용예및 테스트 백터는 tests/test_math.orca 파일을 확인해보기 바란다.

## math.random
math 모듈에는 난수 발생기도 있다.
각각 아래와 같은 인터페이스들이 존재한다.

### seed
난수발생기의 seed 값을 준다. 
```
$ usnig math.random;
$ random.seed(0);
$ random.integer();
1804289383
$ random.integer();
846930886
```

### integer
정수형 난수를 리턴한다. 
파라미터로 limit 을 주면 0~limit 의 값으로 리턴한다.

```
$ random.integer();
1804289383
$ random.integer(100);
86
$ random.integer(100);
77
```

### string
전달방은 길이만큼의 랜넘 아스키 문자열을 리턴한다.

```
$ random.string();
U
$ random.string(10);
/0rsKc26q/
$ random.string(100);
RnzCVPgb6OeNdlouYzOfyZpmMg23MVijWiVdBRdY6V7Uq7LNxpu0VBEOgnRBIT3ch3DpPqFB4fxnPgF+l+rca5aPOFwq7LA7+zKv
$ 
```

### real
0~1 사이의 실수형 난수를 리턴한다.

```
$ random.real();
0.944297
$ random.real();
0.642284
$ random.real();
0.473466
```



# net


## httpd

간단하게 만들어본 http 서버이다.

### httpd(path, port)

인터페이스는httpd(path, port) 로서 자체 실행가능한 모듈이며, 명령행에서 바로 실행할 수도 있다.

./orca httpd . 80

아직 프로토타입 단계이지만, 이 모듈에서 파일을 다루는 방식은 fs 모듈을 사용하기 때문에 분산파일 시스템, 분산 캐쉬 시스템을 사용하여 호스팅 할 수 있는 장점이 있다.

현재 get, post, multipart 요청을 지원한다. 추가로, 요청되는 URI 가 .orca파일이면 자체적으로 쓰레드로 실행시켜 처리한다. (프로세스가 아니라)

그리고, *.osp 파일을 요청하면 오르카의 osp 모듈이 해당 페이지를 파싱한 후 쓰레드로 실행시킨다. (OSP = orca server page)



## httplib
http client 로서 url request 를 요청하고 데이터를 받기 위한 모듈이다.
tls 를 지원하게 한 후 한번 더 개비할 예정이다.

## osp
osp 는 orca server page 모듈로서 과거 웹 프로그래밍 시 서버 사이드 템플릿 처리를 위해 만들어졌었다. 그러나 이후 html 모듈과 sonar 를 이용하게 변경되면서 권고하지 않는다.


# operator

함수형 처리 및 lisp 모듈에서의 사용을 위해 operator 모듈이 추가되었다.

+, -, *, /, %, <, <=, >, >=, ==, !=, ||, && 의 사칙연산 및 비교연산함수들을 인터페이스로 가지고 있다. 이 멤버들은 특수기호를 포함하고 있기 때문에, 참조할 때 다음과 같이 ' ' 로 묶어서 사용한다.

```
$ operator.'+'(3, 4);
7
$ operator.'-'(3, 4);
-1
$ operator.'*'(3, 4);
12
$ operator.'%'(3, 4);
3
$ operator.'<='(3, 4);
true
```

이 함수들은 이항연산자들이다. 여러 인자에 대한 처리를 위해서는 fun.reduce, fun.apply 를 사용한다.

# orca

### load(name)

오르카 언어의 저수준 동작을 제어하기 위한 모듈이다. 현재는 모듈을 런타임에 선택적으로 로드할 수 있는 (using을 써서 정적으로 로드하는게 아니라) load, unload 인터페이스를 제공한다.

사용 예는 다음과 같다.

```
str = argv[0];
orca.load(str);
```

### unload(name)

unload(name) 인터페이스는 적재된 모듈을 내리는 역할을 한다. 주용도는 httpd, osp 모듈에서 서블릿, 서버페이지 소스가 변경 되었을 때 재적재를 위한 것이다.


# orm
rdbms 를 object 로 매핑해주는 orm 모듈이다.
sonar 에서 사용하고 있으며, orm 을 상속해서 객체를 정의한후 create_table() 로 테이블을 생성할 수 있고, save() 로 insert, where, orderby, groupby, result 로 resultset 을조회할 수 있다.

아래는 간단한 테스트 이다.

사용전에 orm.set_conn 으로변환이 될 dbms connection 을 지정해 주어야 한다. 

```
using os;
using orm;
using storage.sqlite3;

os.remove('tmp.db');

conn = sqlite3.connect('tmp.db');
orm.set_conn(conn);

def member : orm.model
{
	def id := orm.type.int().primary_key();
	def name := orm.type.text();
	def id100 := orm.type.int();
}

my.member.create_table();
m = my.member.new();
m.id = 1;
m.name = 'foo';
m.id100 = m.id * 100;
m.save();

m = my.member.new();
m.id = 2;
m.name = 'bar';
m.id100 = m.id * 100;
m.save();

rs = my.member.orderby(my.member.id).result();
for m in rs {
	print: m;
	if m.id * 100 != m.id100 {
		throw test.orm <- 'orm value invalid';
	}
}

```

10min.md 에서 게시판 관리를 orm 으로 하는 예제가 추가로 있다.


# os

### run(cmd)

run 인터페이스는 전달받은 것을 실행한다. popen이라 생각하면 된다.

```
$ using os;
$ os.run(‘ls’);
```

를 사용하면 폴더의 내용이 출력된다.

그런데, 간편함을 위해서 이를 실행하는 다른 방법도 제공한다.

```
$ ; ls -al
```

과 같이 입력하면 ls -al 이 실행된다. 세미콜론을 먼저 치면 입력한 라인이 쉘을 통해 실행된다. 즉 ; ls -al 은 os.run(‘ls -al’); 과 의미상 같다.

또 실행된 결과를 참조하기 위해 caller를 통한 역 참조를 사용하는데,

```
$ def __cout__;
$ ; ls -al    
total 2924
drwxrwxrwx+ 10 MYHOME 없음       0 Dec  1 14:56 .
drwxrwxrwx+ 24 MYHOME 없음       0 Nov 27 11:01 ..
drwxrwxrwx+  6 MYHOME 없음       0 Dec  1 02:11 .svn
-rw-rw-rw-   1 MYHOME 없음       8 Nov  8 17:26 BUILD_NUMBER
-rw-rw-rw-   1 MYHOME 없음   18007 Nov  8 17:26 COPYING
….
$ print: my.__cout__;
[ 'total 2924
','drwxrwxrwx+ 10 MYHOME 없음       0 Dec  1 14:56 .
','drwxrwxrwx+ 24 MYHOME 없음       0 Nov 27 11:01 ..
','drwxrwxrwx+  6 MYHOME 없음       0 Dec  1 02:11 .svn
','-rw-rw-rw-   1 MYHOME 없음       8 Nov  8 17:26 BUILD_NUMBER

','-rw-rw-rw-   1 MYHOME 없음   18007 Nov  8 17:26 COPYING
…
```

와 같이 run객체는 호출자에 __cout__ 이 존재하면 출력 결과를 문자열로 추가한다. 단, __cout__은 nil이거나 string 타입이어야 한다. 안그러면 예외.

### getenv(name)

환경변수를 조회할 때 사용된다.

```
$ print: os.getenv(‘PATH’);
```

는 현재 쉘의 PATH를 출력한다.

### cwd()

현재의 working directory를 반환한다.

```
$ print: os.cwd();
/root/curr
```

### mkdir(path)

입력받은 경로의 디렉토리를 새로 생성한다.

```
$ 
$ os.mkdir('newdir');
$ 
$ os.cd('newdir');
$ print: os.ls('.');
[ ]
$ 
```

### rename(src, dest)

입력받은 파일의 이름을 변경한다.

```
$ print: os.ls('.');
[ ]
$ os.mkdir('newdir');
$ print: os.ls('.');
[ './newdir' ]
$ os.rename('newdir', 'renamed_dir');
$ print: os.ls('.');
[ './renamed_dir' ]
$ 
```

### copy(src, dest)

파일을 복사한다.

```
$ print: os.ls('.');
[ './file_a' ]
$ os.copy('file_a', 'file_b');
$ print: os.ls('.');
[ './file_b','./file_a' ]
$ 
```

### remove(name)

파일을 삭제한다.

```
$ print: os.ls('.');
[ './file_a' ]
$ os.remove('file_a');
$ print: os.ls('.');
[ ]
$ 
```

### ls()

디렉터리의 파일들을 리스팅한다. 결과값은 리스트 형태로 반환된다.

```
$ os.cd('/usr');
$ print: os.ls('.');
[ './tmp','./include','./kerberos','./local','./bin','./games','./sbin','./share','./lib','./src','./etc','./libexec' ]
$ 
```

### cd(path)

디렉터리를 변경한다.

```
$ os.cd('/usr');
$ print: os.ls('.');
[ './tmp','./include','./kerberos','./local','./bin','./games','./sbin','./share','./lib','./src','./etc','./libexec' ]
$ 
```

### isexists(path)

인자로 전달받은 경로의 파일이나 디렉터리가 존재하면 true를 리턴한다.

```
$ print: os.isexists('/etc');
True
$ print: os.isexists('/etc/passwd');
True
$ print: os.isexists('/if_not_exist');
False
$ 
```

### isfile(path)

인자로 전달받은 경로가 파일이면 true를 리턴한다.

```
$ print: os.isfile('/etc/passwd');
True
$ 
$ print: os.isfile('/etc');
False
$ 
$ print: os.isfile('/if_not_exist');
False
$ 
```

### isdir(path)

인자로 전달받은 경로가 디렉터리이면 true를 리턴한다.

```
$ print: os.isdir('/etc');
True
$ print: os.isdir('/etc/passwd');
False
$ print: os.isdir('/if_not_exist');
False
$ 
```

### dir_iterator(path)

dir_iterator 는 입력받은 경로의 파일들을 순회할 수 있는 iterator 객체를 리턴한다. (튜토리얼의 iterator 객체부분을 참조하라) 사용자가 직접 next() 를 호출하여 파일을 순회할 수도 있고, for 문을 사용하여 처리할 수도 있다.

```
$ os.cd('/etc');
$ for a in os.dir_iterator('.') {
* print: a;
* }
*
./printcap
./terminfo
./rc2.d
./bash_completion.d
...
```

### dir_traverser(path)

dir\_iterator가 현재 디렉토리의 파일들만을 순회하는데 반해, dir\_traverser는 현재 디렉토리 밑의 전체 파일들을 순회한다.

```
$ for a in os.dir_traverser('/etc/yum') {
* print: a;
* }
* 
/etc/yum/pluginconf.d
/etc/yum/pluginconf.d/blacklist.conf
/etc/yum/pluginconf.d/whiteout.conf
/etc/yum/pluginconf.d/refresh-packagekit.conf
$
```

### read(filepath, size, offset)

read(filepath, size, offset) 은 filepath 파일을 읽어서 내용을 리턴한다. size가 있다면 그 길이 만큼, offset이 있다면 해당 offset부터 읽는다.

### write(filepath, data, offset)

write(filepath, data, offset) 은 filepath에 있는 파일에 data를 기록한다. offset이 있다면 해당 offset부터 기록한다.

### file_size(filepath)

file_size(filepath) 는 filepath에 있는 파일의 크기를 리턴한다.

### last\_write\_time(filepath)

last\_write\_time(filepath) 는 filepath에 있는 파일의 최종 기록시간을 datetime 형식으로 리턴한다.

```
$ os.write('foo.txt', 'hello, file');
$ print: os.read('foo.txt');
hello, file
$ print: os.file_size('foo.txt');
11
$ print: os.last_write_time('foo.txt');
2010-11-14T15:16:51
```


# pack
pack 은 save, load 를 통해 오르카 객체를 시리얼라이징할 수 있다. 뿐만 아니라 dump_code, load_code, list_code, check_code 인터페이스를 통해 객체의 실행코드까지 별도로 관리할 수 있다.

이 모듈은 distribute 의 remotec, remoted 에서 객체를 원격으로 전송한 후 호출하는데 사용된다. 상세한 활용은 distribute 모듈을 참조하기 바란다.

로컬에서 저장, 복원은 간단히 save, load 만으로 다음과 갈이 할 수 있다.

```
using pack;

def foo
{
        def a := 100;

        print: my.MEMBERS;
        return my.a;
}

ret = pack.save(my.foo);
print: ret;

bar = pack.load(ret);

print: bar;
ret = bar();
if ret != 100 {
  throw test.pack <- 'load fail';
}

print: 'OK', my;

```

실행결과는 아래와 같다.

```
~/lab/orca/tests$ orca test_pack.orca 
ofoo
Ma
i100
Ctest_pack
0
.

< - 0x781a80>
{ 'a':100 }
OK<test_pack - 0x7811d0>
```

현재 구현상의 문제로 인터프리터상에서는 팩으로 객체의 코드를 복원하지 못한다. 컴파일 모드에서만 지원한다.


# queue

queue 는 채널 인, 아웃을 지원하는 async queue 유틸이다.

clone 으로 생성할 때 용량을 지정할 수 있으며, size 는 현재 queue 에 있는 아이템 갯수, cap 은 용량을 리턴한다. push, pop 으로 아이템을 넣고, 뺄 수 있는데 용량이 다 찬경우 push 하면 다른 쓰레드가 pop 할때까지 블록되고, 비어있는 queue 에서 pop 을 하면 다른 쓰레드가 push 할때까지 block 된다.

단, push 의 경우 첫번째 파라미터는 넣을 아이템, 두번째는 타임아웃으로 해당 시간까지만 블록되고 타임아웃이 발생하면 false 를 리턴한다.

pop에 타임아웃 파라미터를 주면 해당시간까지 대기하고 타임아웃이 발생하면 nil 을 리턴한다. 

아래는 간단한 push, pop 예제이다. 네번째 push 는 타임아웃이 발생했고, 마지막 pop 은 10초간 지연되었다.


```
$ using queue;
$ q = queue.clone(3);
[  ]
$ q.size();
0
$ q.cap();
3
$ q.push(1);
true
$ q.push(2);
true
$ q.size();
2
$ q.push(3);
true
$ q.push(4, 0.1);
false
$ q.pop();
1
$ q.pop();
2
$ q.pop();
3
$ q.pop(10);
$ 
```

queue 는 <-, -> 멤버가 있기 때문에 select 구문에서 사용할 수 있다. 상세한 예제는 test_queue.orca 를 참조하면 된다.


# repr

repr 은 입력받은 파라미터의 표현형을 출력한다.
객체안에 repr 멤버가 있으면 해당 멤버의 결과를 리턴한다.

```
$ a = 'hello';
hello
$ repr(a);
"hello"
$ a = r'a-z+';
r'a-z+'
$ repr(a);
r'a-z+'

```


# run

프롬프르상에서는 오르카 모듈을 직접 실행할 수는 있어도 모듈의 멤버를 바로 실행할 수는 없다.

즉, 프롬프트 상에서 $ orca foo 는 foo 모듈을 실행하는 것인데, $ orca foo.bar 와 같이 foo안의 특정 멤버를 바로 실행할 수는 없다.

run 모듈을 사용하면, argv\[0\] 로 객체의 path를 받고 argv\[1:\] 을 인수로 객체를 실행해준다.

즉 아래와 같이 사용할 수 있다. 마지막의 nil 은 리턴값이다.

```
$ orca run io.print hello, orca
hello,orca
nil
```

간단한 유틸리티성 모듈이다.

# selector (TBD)

# socket

아직 socket option등이 미구현 되었지만 기본적인 소켓 프로그래밍을 위한 모듈이다. 인터페이스들은 아래와 같다.

### create()

소켓을 생성하여 리턴한다.

```
$ sock = socket.create();
```

### send(data)

소켓을 통해 (현재는 스트링만) 데이터를 전송한다.

```
$ sock.send(‘hello, world’);
```

### recv(\[len, \[timeout\]\])

소켓을 통해 데이터를 수신한다.

```
$ msg = sock.recv()
```

### close()

소켓을 닫는다.

```
$ sock.close();
```

### connect(ip, port)

소켓을 통해 특정 주소로 연결한다. 파라미터는 IP와 por이다.

```
$ sock = socket.create();

$ sock.connect(‘127.0.0.1’, 8080);
```

### bind(port)

말그대로 bind

```
$ sock.bind(80);
```

### listen()

bind 후 listen한다.

```
$ sock.listen();
```

### accept()

소켓을 통해 클라이언트 접속을 받는다. 리턴되는 값은 클라이언트 소켓이다.

```
$ client = sock.accept();
```

하나씩 본다면 의미가 없고, 전반적인 예제를 보자면 80포트로 수신대기한 후 수신받은 것을 그대로 되돌려주는 서버프로그램은 이와 같이 구성한다.

```
svr = socket.create();
svr.bind(80);
svr.listen();

do {
    try {
        client = svr.accept();
        msg = client.recv();
        client.send(msg);
    }
    catch {
        # 끊기면 다음 클라이언트를 받는다.
    }
} while(true);
```

차례대로 소켓을 생성해서 80으로 리슨한 후 수신 받은 것을 되돌렸다. 위의 스크립트를 실행한 후, 다른 창에서 시험해보면

```
$ using socket;
$ sock = socket.create();
$ msg = io.input();
Hello, socket
$ sock.send(msg);
$ print: sock.recv();
Hello, socket
```

와 같이 동작할 수 있다. select 모듈이나 thread 모듈을 이용해서 간단한 multiplexing, multithread 서버를 구성할 수도 있다. IOCP, async socket, epoll server등은 차차 추가될 예정이다.

# sonar
sonar 는 오르카의 웹개발 프레임웍이다.
상세한 내용은 about_sonar.md 나 10min.md 를 참조하기 바란다.

# sorted

sorted 는 a를 정렬하여 정렬된 결과를 새 컨테이너에 담아 리턴한다. 현재 처리할 수 있는 컨테이너는 리스트와 튜플이다.

# stopwatch

간단한 시간측정을 위한 유틸이다. single thread라면 그냥 모듈자체를 사용해도 되고, MT환경이거나 측정대상이 여러개라면 clone 해서 각각 측정할 수도 있다.

### start()

타이머를 초기화 한다. 이후부터 측정되는 시간은 이 시점으로부터의 변경시간이다.

### elapse()

지난 시간을 microsec 해상도의 정수로 리턴한다.

```
$ using stopwatch;
$ 
$ stopwatch.start();
$ print: stopwatch.elapse();
15007541
$ 
$ print: stopwatch.elapse();
24143768
$ 
```

### lap(msg)

지난 시간을 화면에 출력한다. day, hour, sec, ms, usec 순으로 디코딩해서 출력하며, 만일 특별한 메세지를 출력하고자 하면, 인자로 스트링을 전달하면 지연시간을 출력하기 전에 먼저 출력한다.

```
$ sw = stopwatch;
$ sw.start();
$ sw.lap('lap 1: ');
lap 1: 17 sec, 71 ms, 530 us
$ sw.lap();
20 sec, 287 ms, 624 us
$ 
```

### title(msg)

타이머의 헤더 메세지를 설정한다. 이것을 설정하고 나면 이후의 lap() 을 호출 시 자동으로 헤더 메세지가 출력된다. 만일 지우고 싶다면 단순히 title() 을 호출한다. 이 함수는 stopwatch 객체를 리턴한다. 즉, stopwatch.title('title').lap() 과 같이 호출 가능하다.

```
$ using stopwatch;
$ sw1 = stopwatch.clone();
$ sw1.title('[sw1]');
$ sw2 = stopwatch.clone();
$ sw2.title('[sw2]');
$ 
$ sw1.start();
$ sw2.start();
$ sw1.lap();
[sw1]5 sec, 792 ms, 273 us
$ sw2.lap();
[sw2]5 sec, 855 ms, 888 us
$ sw1.lap('lap1');
[sw1]lap122 sec, 128 ms, 36 us
$ sw2.lap('lap2: ');
[sw2]lap2: 32 sec, 976 ms, 62 us
$ 
```

### {, }

scope statement 를 지원한다. '{' 는 start와, '}'는 lap과 같다.

```
$ sw1.title('scope statement test:') { 
* root.time.msleep(1000);
* }
* 
scope statement test:999 ms, 425 us
$
```

# storage

## sqlite3
sqlite3 클라이언트이다. 현재 오르카에 기본 탑재되어 있고 orm 에서 사용할 수 있다. 타 DBMS는 추후 추가될 예정이다.

### connect
DB에 대한 connection 을 얻는다. 

```
conn = sqlite3.connect('tmp.db');
```
리턴되는 connection 은 다음 sqlite3conn 객체이다.


### sqlite3conn

execute 인터페이스를 이용하여 쿼리를 실행하고 결과를 얻는다.
create, insert 의 경우 실행결과가, select 구문인 경우 result set 객체가 리턴된다.

### sqlite3result

result set 은 iterater 로서 for 문으로 순회하거나 next() 로 이동하며 값을 얻을 수 있다.

아래는 종합적인 예제이다.

```
using os;
using storage.sqlite3;

os.remove('tmp.db');

conn = sqlite3.connect('tmp.db');
print: conn;

try {
	res = conn.execute('create table t1 (a int, b string, c double)');
	print: res();

	for i in [0..10] {
		query = "insert into t1 values(%d, 'str_%d', %f)" % (i, i, i + 0.1);
		res = conn.execute(query);
		print: res();
	}

	res = conn.execute('select * from t1;');
	i = 0;
	for r in res {
		print: r();
		v = r();
		if v[0] != i || v[1] != 'str_%d' % i || v[2] != (i + 0.1) {
			throw test.db <- 'select result is wrong';
		}

		i += 1;
	}
}
catch db as e {
	print: e.what();
}
```

위 예의 실행결과는 아래와 같다.

```
true
true
true
true
true
true
true
true
true
true
true
true
( 0,'str_0',0.1 )
( 1,'str_1',1.1 )
( 2,'str_2',2.1 )
( 3,'str_3',3.1 )
( 4,'str_4',4.1 )
( 5,'str_5',5.1 )
( 6,'str_6',6.1 )
( 7,'str_7',7.1 )
( 8,'str_8',8.1 )
( 9,'str_9',9.1 )
( 10,'str_10',10.1 )
```



# strings
문자열 처리와 관련된 유틸리티성 모듈이다.

### join
문자열을 병합한다. 첫번째 파라미터는 병합될 문자 사이게 구분자로 들어갈 값이다. 리스트를 병합하고 싶으면 아래의 두번째 예처럼 ... 을 사용해 리스트를 풀어야 한다.

```
$ strings.join(', ', 1, 2, 'three');
1, 2, three
$ strings.join(':', ['one', 'two', 'three']...);
one:two:three
```


### builder
문자열 생성자이다. 
write 나 push_back 을 사용해 문자열을 계속 추가할 수 있으며 string() 을 통해 문자열로 변환할 수 있다.

참고로 오르카 string 은 += 이나 push_back() 을 통해 in place update 를 할 수있다.

그러나 builder 를 사용하면 write 덕타입으로 타 API에서 응용할 수 있고 string 보다는 좀 더 효율적이다.

```
$ b = strings.builder();

$ b.write('first line\n');
first line

$ b.push_back('second line\n');
first line
second line

$ b.string();
first line
second line
```

### html_escape, html_unescape
스트링을 html 에서 사용할 수있게 escape, unescape 한다.
아래는 그 예이다.

```
$ ret = strings.html_escape('a >= (b+c)');
a &gt;= (b+c)
$ strings.html_unescape(ret);
a >= (b+c)
```


### url_escape, url_unescape
스트링을 url 에서 사용할 수 있는 값으로 escape, unescape 한다.
아래는 그 예이다.

```
$ '/info?key=%s' % strings.url_escape('abc&%_');
/info?key=abc%26%25%5F
$ strings.url_unescape('/info?key=abc%26%25%5F');
/info?key=abc&%_
```



# system

system 모듈은 시스템 정보를 조회하기 위한 것으로 다음 인터페이스를 제공한다.

### cpu_n()

시스템의 CPU 코어갯수를 리턴한다. 이 값을 참조하여 parallel for by 의 적절한 값을 주거나 다른 병렬화 정도를 결정할 수 있다.

### free()

시스템의 가용 메모리를 구한다.

### memory()

시스템의 물리 메모리 양을 구한다.

### os()

시스템의 OS정보를 문자열로 리턴한다.

### version()

오르카의 버전을 문자열로 리턴한다.

```
$ system.cpu_n();
4
$ system.free();
1422434304
$ system.memory();
2002993152
$ system.os();
Linux version 2.6.35-22-generic (buildd@rothera) (gcc version 4.4.5 (Ubuntu/Linaro 4.4.4-14ubuntu4) ) #33-Ubuntu SMP Sun Sep 19 20:34:50 UTC 2010
$ system.version();
0.5
```

# thread

쓰레드를 지원하기 위한 모듈이다. run 인터페이스로 thread를 띄우고 이 때 리턴받은 쓰레드 객체의 join 인터페이스로 기다릴 수 있다.

```
using thread;

def foo(param) {
  print: param;
}

hd = thread.run(my.foo, ‘hello, thread’);
hd.join();
```

과 같이 할 수 있다.

run 의 첫번째 인수는 쓰레드로 만들 객체이고 나머지는 전달될 인자이다.


# tool

## gnuplot

gnuplot을 손쉽게 사용하기 위한 shell 수준의 wrapper이다. wrapper로 구성되어 있으나, 오르카의 조건제시법을 이용하여 생성한 좌표를 그래프로 표기할 수 있다. 때문에, gnuplot의 단순한 그래프식을 사용하지 않고 오르카의 여러 라이브러리들을 사용한 좀 더 유연한 표현식을 그래프화 시킬 수 있다.

### gnuplot.run(cmd)

가장 먼저, 이 인터페이스를 사용하면, cat cmd | gnuplot 과 같은 동작을 수행할 수 있다. 가장 간단한 wrapper 인터페이스이다.

### gnuplot.add(title, list)

이 명령어를 수행하면 gnuplot객체의 내부 2차원 그래프 데이터에 list가 추가된다. list 는 \[(x1, y1), (x2, y2)...\] 와 같은 x, y plot 의 리스트이다.

### gnuplot.plot(cmd);

이 인터페이스는 추가된 2차원 데이터들을 화면에 출력한다. 추가적으로 cmd를 실행한 후, 그래프를 출력하는데, cmd에는 주로 'pause 1'정도를 사용하면 적절하겠다.

### gnuplot.clear();

이 인터페이스는 gnuplot 객체에 저장되어 있는 그래프 데이터를 초기화한다.

아래의 예는 한 그래프에 x^2, 2*x^2 그래프를 그리는 예이다. 플롯들은 선으로 연결되고, grid 속성이 추가 되었으며, 그래프는 1초간 나타난다.

```
   a = gnuplot.clone();
   a.clear();
   a.add('x^2', %[(x, x*x)|x<-1~1000]);
   a.add('2*x^2', %[(x, x*x*2)|x<-1~1000]);
   a.set('line');
   a.plot('pause 1');
```

출력된 그래프 이미지는 아래와 같다.  
![](image/gnuplot2d.jpg)

3차원 그래프는 좌표가 3개 필요하기 때문에, 내부 데이터와 인터페이스가 조금 다르다.

### gnuplot.sadd(title, list, group)

이 인터페이스는 gnuplot 객체에 3차원 데이터를 추가한다. group 파라미터가 따로 있는데, (x, y, z) 의 리스트가 x, y 순으로 소팅되어 있다면, 결과물에 그물모양의 라인이 추가되어 입체감을 줄 수 있게 된다. 실행결과는 아래의 그래프를 참조하면 된다.

### gnuplot.splot(cmd)

이 인터페이스는 plot과 유사하나 3차원 데이터들을 그린다. s는 space 를 의미하는 prefix 이다.

```
   sbf= %[(x, y, 40*(x*x + y*y)*math.exp(-(x*x) - (y*y)))|x<--2~2:0.1, y<- -2~2:0.1];  
   sbf2= %[(x, y, 4*y-1)|x<- -2~2:0.1, y<- 0~1:0.1];
  
   gnuplot.sadd('40*(x^2 + y^2) * exp(-x^2 -y^2)', sbf, true);
   gnuplot.sadd('4*y-1', sbf2, true);
   gnuplot.set('grid');
   gnuplot.set('line');
   gnuplot.splot('pause 1');
```

위 예제는 z = 40*(x^2 + y^2)\*exp(-x^2-y^2) 그래프와 z = 4\*y-1 그래프를 그린다. 그려진 결과는 아래와 같다.  
![](image/gnuplot3d.jpg)

여기서는 한줄짜리 조건제시법 리스트를 플로팅 했는데, 좀 더 응용하여 오르카를 사용하여 2, 3차원 플롯 리스트를 작성하면 여러 분야에 더 유용하게 사용될 수 있을 것이다.


# type

type traits 를 위한 모듈이다. 먼저 아래와 같이 동적으로 자료를 생성할 수 있다.

```
$ print: type.list(1,2,3);
[ 1,2,3 ]
$ print: type.tuple();
(  )
$ print: type.map(1,2,3,4);
{ 1:2,3:4 }
$ str = '[0-9]+';
$ print: a = type.regex(str);
r'[0-9]+'
$ print: a == '12345';
true
```

특히 기존에는 regex 객체를 constant 로만 ( r'\[0-9\]+' 와 같이) 생성할 수 있었는데, 이를 동적으로 생성하고자 하면 위와 같이 type.regex를 사용하면 된다.

그리고, type의 멤버들은 각 자료형의 type들이다. 이들을 이용해서 변수와 상수들의 형검사를 할 수 있다.

```
$ 1.type == type.int;
true
$ 'string'.type == type.string;
true
$ 1.34.type == type.int;
false
$ 
```

# util

## match
decode statement 에서 외부 함수 matching 을 지원하기 위한 유틸성 모듈이다.
상세한 사용법은 tutorial 의 decode statement 마지막 부분을 참조하면 된다.

현재 제공하는 멤버는 아래와 같다.

match.comma: , 하나를 매치하는데 {}, [] 가 있는 경우를 고려한다.
match.tag(open, close, str): open, close 로 되는 tag 를 매치한다.
match.match_string(end, str): end 를 찾을때까지 매치한다.
match.sq_string: 작은 따옴표 스트링을 매치한다.
match.dq_string: 큰 따옴표 스트링을 매치한다.
match.match_one_tag: html tag 를 하나 매치한다. 태그안의 sub tag 도 고려한다.


## lock(obj)

obj의 lang.id() 값으로 lock을 건다. scope object mutext를 반환하여 scope 를 벗어나면 lock release가 자동으로 되게 한다.

사용예는 다음과 같다.

```
util.lock(obj) {
    obj.push_back(1);
    ...
}
```

## lru

### lru.insert(k, v)

k, v pair 를 lru 리스트에 추가한다. v가, lru 로 관리되기 위한 실제 객체이며, k는 이를 구분하기 위한 키이다.

### lru.victimize()

lru 리스트로부터 가장 오래된 항목을 제거한다.

### lru.touch(k)

k 를 lru의 가장 앞단으로 옮긴다. lru 항목중 한 원소를 참조했을 때 호출해준다.

이 인터페이는 v를 리턴하는데, 만일 k, v 페어가 존재하지 않는다면 nil을 리턴한다.

### lru.size()

현재 lru 리스트의 길이를 반환한다.

```
$ using util.lru;
lru <0x858c230>
$ a = 'string a';
string a
$ lru.insert(a.id(), a);
$ b = 'string b';
string b
$ lru.insert(b.id(), b);
$ c = 'string c';     
string c               
$ lru.insert(c.id(), c);
$ lru.dump();  
string: string c
string: string b
string: string a
$ lru.victimize(); 
$ lru.dump();          
string: string c      
string: string b 
```

## find_owner
find_owner 는 자신을 소유한 객체와 그 객체의 소유자들을 따라 올라가면서 이름이 같은 객체를 찾는 유틸성 함수이다.
사용법은 gui 예제를 보면 알 수 있다.



