 

Orca Programming Language Tutorial
==================================


written by Lee, Ki-Yeul (kiyeul.lee@gmail.com)  


Table of Contents
=================

0.  [What's this](#what's-this)
1.  [들어가며](#들어가며)
2.  [변수와 자료형](#변수와-자료형)
    1.  [지역변수](#지역변수)
    2.  [정수형](#정수형)
    3.  [실수형](#실수형)
    4.  [문자열](#문자열)
    5.  [정규표현식](#정규표현식)
    6.  [리스트](#리스트)
    7.  [튜플](#튜플)
    8.  [맵](#맵)
    9.  [조건 제시법](#조건-제시법)
    10.  [반복자](#반복자)
3.  [제어문](#제어문)
    1.  [if](#if)
    2.  [while](#while)
    3.  [do while](#do-while)
    4.  [for](#for)
    5.  [switch](#switch)
    6.  [select](#select)
    7.  [scope object](#scope-object)
    8.  [parallel do](#parallel-do)
    9.  [parallel call](#parallel-call)
    10.  [parallel for](#parallel-for)
    11.  [decode statement](#decode-statement)
        1.  [문자열 매치](#문자열-매치)
        2.  [정규표현식 매치](#정규표현식-매치)
        3.  [리스트 매치](#리스트-매치)
        4.  [decode 함수](#decode-함수)
4.  [함수와 객체](#함수와-객체)
    1.  [함수](#함수)
    2.  [객체](#객체)
        1.  [객체 정의](#객체-정의)
        2.  [my, owner 축약식](#my,-owner-축약식)
        3.  [특수문자를 포함한 멤버참조](#특수문자를-포함한-멤버참조)
        4.  [one time initializer](#one-time-initializer)
        5.  [name'string' 표현형식](#name'string'-표현형식)
    3.  [상속](#상속)
    4.  [using](#using)
    5.  [가상멤버](#가상멤버)
        1.  [TYPE](#TYPE)
        2.  [TYPENAME](#TYPENAME)
        3.  [STATIC_MEMBERS](#STATIC_MEMBERS)
        4.  [MEMBERS](#MEMBERS)
        5.  [PARENTS](#PARENTS)
        6.  [ID](#ID)
    6.  [예외](#예외)
    7.  [람다](#람다)
    8.  [연산자 재정의](#연산자-재정의)
    9.  [체널 객체](#체널-객체)
	10.	[폴더 객체](#폴더-객체)
5.  [특수 객체](#특수-객체)
    1.  [Native 객체](#Native-객체)
    2.  [parse 객체](#parse 객체)
    3.  [문맥 확장 객체](#문맥-확장-객체)

What's this
===========

본 문서는 오르카의 간단한 튜토리얼로서 아직 부족하지만 계속 업데이트가 이루어지고 있다.

아직 부족한 부분은 본 문서외에 tests폴더 밑의 test 파일들을 참조하여 파악해주시기 바라며, 버그 및 이슈는 github(https://github.com/lynix94/orca-lang) 에 남겨주시기 바란다.

본 문서는 상업적인 목적이 아니라면 변형 및 배포에 제한이 없으나 (자주 바뀔 것이기 때문에) 혹시라도 배포하게 된다면 원본의 위치를 명시해 주시기 바란다.

들어가며
====

먼저 가장 전통적인 예로부터 시작해 보겠다.



```
./orca
```



라고 콘솔에 입력하면 인터프리터 창이 뜬다. 물론 ./orca test.orca 혹은 ./orca test 와 같이 파일 이름을 주어 직접 파일을 바로 실행할 수도 있다.

어쨌든 나타난 인터프리터 창에 아래와 같이 입력하면,

```
$ print('hello, world');
hello, world
```

위와 같은 결과가 나타난다.

너무나 간단해서 이 부분에 대해서는 더 설명할 것이 없는데, 재밌는 것은 위 문장은

```
print: 'hello, world';
```

로 입력해도 된다.

function\_name( expression\_list ) 와 같이 함수호출형의 표현식은 function\_name : expression\_list 와 같은 간축 형태와 같은 의미를 지닌다.

이는 simple call statement 라고 명명했는데, 단순히 손가락을 편하게 하려는 목적이 아니라 코드블럭(람다라고도 할수 있는)을 이용한 함수형 프로그래밍 구문에선 가독성을 높이는 역할을 할 수도 있다.

즉, 첫번째 파라미터의 각 요소에 대해 두번재 파라미터의 코드블럭을 실행하는 for_each 함수가 있다하면, 일반 표현식은 아래와 같지만,

```
for_each( list_a, lambda(...argv) { print(argv[0]); } );
```

simple call statement를 이용하면 아래와 같이 표기할 수 있다.

```
for_each: list_a, lambda(...argv) {
    print(argv[0]);
};
```

불행이도 예제의 코드블럭이 길지 않아서 def실감이 안나는데.. 좀 길다고 상상을 해보자 마지막 중괄호 뒤에 세미콜론을 붙이는 것을 잊지말자.

변수와 자료형
=======

지역변수
----

먼저 함수안에 위치하는 변수들은 지역변수로 처리된다. (전문적으로, VM의 로컬 변수 스택에서 관리되며, 재진입 가능하다는 뜻이다)

```
$ a = 10;
$ print: a;
10
$ a = 'hello';
$ print: a;
hello
```

위와 같은 결과가 나타난다. 첫번째 line에서 a에 10을 대입한 후 출력하였고,

다시 a에 문자열 'hello'를 대입한 후 출력하였다.

오르카는 동적 type 언어이기 때문에 변수에는 어떤 값이든 대입될 수 있다.

정수형
-----

정수형의 기본적인 연산을 지원하되 0.2 버전부터 정수형의 한계를 없앴다. 때문에 이제 정수형 자료형은 크기 제한 없는 연산이 가능하다. 확인해 보면 다음과 같다.

```
$ print: 10000000000000000000000 * 33333333333333333333333333333;
333333333333333333333333333330000000000000000000000
```

정수형은 내장 자료형으로 string(), float() 이 있다 각각, 스트링과 float으로 형변환 해주는 함수이다. string() 은 인자로서 출력 포멧을 가질 수 있다.

```
$ print: 1.string();
1
$ print: 10.string('%010d');
0000000010
$ print: 30.float();
30
$
```

정수형에서의 16진, 2진수 표현은 다음과 같이 한다.

```
$ print: 0xaabbcc;
11189196
$ print: 0xaabbccddeeff00112233445566778899;
226943873990930480490908391077492263065                                                                                            
$ print: 0b11110000;   
240                                                                                                                                
$ print: 0b11110000111100001111000011110000111100001111000011110000;
67818912035696880      
```

​                                                                                                            

10진 정수형과 마찬가지로 big number도 무리없이 처리가능하다.

실수형
---

실수형도 지원한다. precision 은 c의 double과 같다. 확인해 보면 아래와 같다.

```
$ print: 1.0 / 3.0;
0.333333
```

실수형도 형변환 함수로서 string() 과 integer() 를 내장하고 있다.

```
$ print: 0.3.string();
0.3
$ print: 0.3.string('%3.3f');
0.300
$ print: 0.3.string('%10e');
3.000000e-01
$ print: 1.2.integer();
1
```



문자열
-----

문자열의 구분자는 ‘, “ 둘 다 될 수 있으며 escape character를 지원한다. C/C++의 방식과 유사하나, 편의상 ‘ ‘ 구분자를 지원하는 정도만 다르다. 또한, python과 유사하게 “““, ‘‘‘ 구분자도 지원하는데, 두 구분자 사이에 있는 것은 전체를 텍스트로 처리한다. 단, ‘‘‘ 구분자는 텍스트 내의 ${} 표현식 처리를 하는데 반해 “““ 구분자는 정말 변환없이 그대로 출력한다.

스트링내의 표현식은 ruby 스타일과 비슷한데 구분자는 ${ expression } 이다.

```
$ name = ‘james’;
$ print: ‘hello, ${name}’;
hello, james
```

와 같은 결과를 낸다. ${ } 안에는 표현식이(연산 함수호출등) 존재할 수 있다.

String 은 c/c++ 배열과 유사하게 \[\] 연산자를 적용할 수 있는데, 간단한 예는 다음과 같다.

```
$ ‘hello, world’[0];
h
$ ‘hello, world’[-1];
d
```

마이너스 값은 뒤쪽에서부터의 인덱스 값이다.
```
$ ‘hello, world’[0:5];
hello
```
slicing 연산자는 위와 같이 쓰여, from:to에 해당되는 영역으로 새로운 string을 구성하여 리턴한다.
```
$ ‘hello, world’[2:0];
le
```
slicing의 index가 뒤집혀 있다면, 알아서 뒤집어서 가져온다.

```
$ ‘hello, world’[0:5+];
hello,
```

Slicing을 쓸 때 오른쪽을 +] 로 하면 가장 오른쪽 원소를 포함한 slicing된 값을 리턴한다.

따라서, 위의 스트링을 뒤집고 싶다면

```
$ ‘hello, world’[-1:0+];
dlrow, olleh
```

와 같이 따로 reverse 인터페이스 없이 슬라이싱으로 처리 가능하다.

string은 +, * 연산자를 지원한다. + 는 스트링을 concat하는 동작을 수행하는데, 다른 인수가 스트링타입이 아니라면 스트링으로 변환시켜서 더한다.

```
$ print: ‘hello, ‘ + ‘world’;
hello, world

$ print: ‘3 + 4 = ‘ + 7;
3 + 4 = 7
```

\* 연산자는 스트링의 내용을 n 회만큼 반복한다.

```
$ print: ‘5 times’ * 5;
5 times5 times5 times5 times5 times 
```

String은 현재 length, find, find\_all, strip, lstrip, rstript, integer, replace, hash, starts\_with, ends\_with, chomp, push\_back 인터페이스를 제공하며, 0.5에서 추가로 char, lower, upper 인터페이스를 지원한다.

간단한 예제와 함께 설명하겠다.

length() 는 스트링의 길이를 계산한다.

```
$ print: ‘hello, world’.length();
12
```

find()는 해당 문자열이 있는 위치를 리턴한다.

```
$ print: 'hello, world'.find('world');
7
```

find_all은 해당 스트링이 나타나는 모든곳을 리스트로 만드어 리턴한다.

```
$ print: 'hello, world'.find_all('o');
[ 4,8 ]
```

find 및 fina\_all의 첫번째 인수로는 다음에 설명할 정규표현식이 올 수 있다. find, find\_all의 두번째 세번째 인수로는 검색을 할 start, end index가 올 수 있다.

```
$ print: '"', '    hello,    '.rstrip() + '  world   '.strip() + ' ! '.lstrip(), '"';
"    hello,world! "

$ print: ‘123’.integer() + 100;
223
```

integer() 는 정수형으로 형변환 한다.

```
$ print: '30.8'.float();
30.8
$ print: '30e14'.float();
3e+15
$           
```

float() 은 실수형으로 형변환한다.

```
$ print: ‘hello, world’.replace(‘world’, ‘earth’);
Hello, earth
```

replace의 첫번째 인수로는 다음에 설명할 정규표현식이 올 수 있다. Replace 의 두번째 세번째 인수로는 치환을 수행할 범위를 지정하기 위한 것으로 string의 start, end index가 올 수 있다.

hash(mod) 은 스트링에 대한 간단한 정수 해쉬값을 리턴한다. INT_MAX까지의 값이 반환되는데, mod 값이 입력되면 나머지 값이 리턴된다.

```
$ a = 'hello, world!';
$ print: a.hash();
1193
$ print: a.hash(100);
93
```

split(by, n)는 문자열을 by들로 나누어 리스트에 담아 리턴한다. by에는 스트링이 올 수도 있고 정규표현식이 올 수도 있다. n 은 가르는 최대 갯수이다.

```
$ a = 'aaaa-bbbb-cccc-dddd';
$ print: a.split('-');
[ 'aaaa','bbbb','cccc','dddd' ]
$ 
$ a = 'aaaa-bbbb_cccc:dddd';
$ print: a.split(r'[^a-zA-Z]');
[ 'aaaa','bbbb','cccc','dddd' ]
$ 
$ a = 'aaaa-bbbb_cccc-dddd';
$ print: a.split(r'[-_]');
[ 'aaaa','bbbb','cccc','dddd' ]
$ 
```

스트링은 슬라이싱과 문자열 비교를 통해 일부비교가 가능하지만 특별히 잦은 앞과 뒤의 비교를 위해 starts\_with, ends\_with 인터페이스도 제공한다. 사실 이 인터페이스는 Java에서 따왔는데, 비교 파라미터로 정규표현식이 올수도 있어 더 유용하게 사용할 수 있다.

```
$ 
$ a = '1111aaaa0000bbbb';
$ print: a.starts_with('1111');
true
$ print: a.starts_with('bbbb');
false
$ print: a.ends_with('bbbb');
true
$ print: a.ends_with('1111');
false
$ print: a.starts_with(r'[0-9]+');
true
$ print: a.ends_with(r'[a-z]+');
true
$ print: a.ends_with(r'[0b]+');
true
```

upper()와 lower() 는 문자열을 대문자, 소문자로 변경한다.

```
$ 'Hello, World!'.upper();
HELLO, WORLD!
$ 'Hello, World!'.lower();
hello, world!
```

char(idx)는 idx위치의 문자코드를 리턴한다.

```
$ 'abc123'.char(0);
97
$ 'abc123'.char(1);
98
$ 'abc123'.char(2);
99
$ 'abc123'.char(3);
49
$ 'abc123'.char(4);
50
```

문자열의 특별한 형태로 16진, 2진수 문자열을 표기할 수 있다. 16진, 2진 스트링을 표현할 수 있게 되었다. 기존의 스트링 표현식 앞에 h, b를 붙여주면 된다.

```
$ print: h'3031323334';
01234
$ print: b'01110011';
s
$ print: b'01110011 01110100';
st
```

python style의 포멧스트링도 지원한다. 형식은 파이썬 스타일과 같으며, 내부적으로는 string의 modulo operator를 오버라이딩하여 구현된 것이다.

```
$ 'i: %d, f: %f, e: %e, s: %s' % (100, 12.34, 12.34, 'hello, world!');
i: 100, f: 12.340000, e: 1.234000e+01, s: hello, world!
```



%TYPE 을 사용하는 포멧스트링에서 한단계 더 나아가 오르카는 맵타입의 포맷스트링도 지원한다. 이 기능은 나중에 html 모듈에서 유용하게 사용된다. 포맷스트링 안에 %{NAME} 형식의 포멧이 있으면 파라미터의 가장 마지막 인수를 map type 으로 가정하고 해당 map 에서 NAME의 값을 대입시킨다.

예를들어 아래의 경우는 hello, orca 를 출력한다.

```
print: 'hello, %{name}' % ({'name':'orca'});
```

map 타입 포멧은 기존의 포멧과 같이 섞여쓸 수 있으나 map 타입 포멧은 한번만 나와야 하며 인수로서 가장 마지막에 위치해야 한다.

```
print: 'format i: %d, name: %{name}, f: %f, age: %{age}' % (10, 12.34, {'name':'orca', 'age':20});
```

출력결과는 format i: 10, name: orca, f: 12.340000, age: 20 와 같다.



정규표현식
-----

정규표현식은 문자열 앞에 r 을 붙여서 표현한다. r'\[0-9\]+' 는 숫자에 대한 정규표현식을 의미한다.

orca에서 제공하는 정규표현식은 boost::regex를 사용하여 구현되었다. 상세한 표현방식은 해당 라이브러리의 문서를 참조하기 바라며 여기서는 사용법만을 기술하겠다.

정규표현식을 이용한 처리는 match, find, replace 연산이 있는데,

먼저 match의 경우엔 아래와 같이 할 수 있다.

```
str = '123abc456def';
if str == r'[0-9a-z]+' {
    print: ‘matched’
}
```

위의 예제는 matched를 출력한다. 따로 match() 인터페이스를 두지 않고, ==, != 연산자를 통해 이 작업을 수행할 수 있다.

위의 str에 대해 아래와 같이 find를 수행하면,

```
$ print: str.find(r’[a-z]+[0-9]+’);
( 'abc456',3,9 )
```

와 같은 결과를 얻는다. 튜플의 첫번째 값은 찾아진 매치된 문자열이고, 두번째 값은 시작 인덱스, 세번쩨는 마지막 인덱스이다.

```
$ print: str.find_all(r'[0-9]+[a-z]+');
[ ( '123abc',0,6 ),( '456def',6,12 ) ]
```

find_all은 위와 같이 매치되는 모든 결과들을 리스트로 만들어서 리턴한다.

```
$ print: str.find_all(r'([0-9]+)[a-z]+');
[ ( ( '123abc',0,6 ),( '123',0,3 ) ),( ( '456def',6,12 ),( '456',6,9 ) ) ]
```

정규표현식은 또한 subgroup을 지원하는데, 파라미터로 건네지는 정규표현식에 괄호를 쳐서 그 일부를 subgroup으로 만들 수 있다. 결과값에선 보다시피 해당 서브 그룹이 또다른 튜플로 추가된다. 서브 그룹을 구분하기 위해 튜플로 한번 더 감싸져 있는 것에 유의하기 바란다. Subgroup에 대한 자세한 내역은 boost::regex를 참조하기 바란다.

```
$ print: str.replace(r'[0-9]+', '{{$0}}');
{{123}}abc{{456}}def
```

보기와 같이 매치된 내역을 변환시킬 수도 있다.

Orca의 정규표현식은 똑같은 string 인터페이스에서 처리하도록 했으며, 결과값을 또하나의 matching객체를 사용하지 않고, 바로 리스트, 튜플 조합으로 인덱스로 참조할 수 있도록 했다.

리스트
---

리스트는 추가 가능한 원소들의 나열을 나타낸다.

```
$ a = [1,2,3,4,5];
$ print: a,' ',a[0],' ',a[-1];
[1,2,3,4,5] 1 5
```

물론 대입 및 중첩도 가능하다.

```
$ a[1] = ['abc', 3];
$ print: a;
[1, ['abc', 3], 3, 4, 5]
$ print: a[1][0];
abc
```

슬라이싱도 지원한다. 슬라이싱 방식은 스트링의 그것과 유사하다.

리스트는 내장 함수로 먼저 원소를 앞에서 삽입, 삭제하는 push\_front, pop\_front가 있고, 뒤에서 삽입, 삭제하는 push\_back, push\_front 함수가 있다. 이 함수의 리턴값은 삽입, 삭제가 일어난 리 스트의 최종 모습이다.

```
$ a= [1,2,3];
$ print: a.push_back(4);
[ 1,2,3,4 ]
$ print: a.pop_back();
[ 1,2,3 ]
$ print: a.push_front('100');
[ '100',1,2,3 ]
$ print: a.pop_front();
[ 1,2,3 ]
```

tuple() 인터페이스는 리스트를 같은 순서의 튜플로 변환해 준다.

```
$ a = [1..10];
$ print: a, a.tuple();
[ 1,2,3,4,5,6,7,8,9,10 ]( 1,2,3,4,5,6,7,8,9,10 )
```

size() 인터페이스는 리스트의 길이를 반환한다. empty() 는 리스트가 비어있을 경우 true를 리턴한다. clear() 는 리스트를 초기화 한다.

```
$ a = [1..10];
[ 1,2,3,4,5,6,7,8,9,10 ]
$ print: a.size();
10
nil
$ a.empty();
false
$ a.clear();
[  ]
$ a.empty();
true
$ 
```

list 의 반복자는 value 를 리턴하며 순회하는 value 기반 반복자를 리턴하는 iter() 인터페이스가 있고, position 기반의 반복자를 리턴하는 piter(), first(), last(), end() 가 있다. 이는 리스트, 튜플, 맵에 모두 공통이다. 자세한 내용은 뒤의 반복자 파트를 참고하기 바란다.

iter() 는 리스트의 첫번째를 가르키며, next 를 실행할때마다 다음 값을 리턴하고 마지막까지 참조한 후에는 orca.iter.end exception 을 발생시킨다.

```
$ list = [1,2,3];
[ 1,2,3 ]
$ i = list.iter();
<iter - 0x16edd70>
$ i.next();
1
$ i.next();
2
$ i.next();
3
$ i.next();
uncaugted exception: orca.iter.end out of range
recent call-stack trace
>> root (internal 0)
```

 

position 기반 iterator 중 piter 는 첫번째 아이템의 이전 (next 를 수행하면 첫번째 아이템위치의 iterator 를 리턴) 이며, first 는 첫번째 아이템, last 는 마지막 아이템, end 는 마지막 아이템의 다음 위치로 invalid 한 값을 의미한다. (c++ stl 의 end 와 같다) position iterator 는 iterator 간의 위치를 비교할 수 있으며, iterator 를 실행하면 현재위치의 값이 리턴되고, iterator 를 실행할때 값을 주면 현재 위치의 값을 변경할 수 있다. 이 점이 앞의 value iterator 보다 사용성이 뛰어난 점으로 간단히 값을 순회하기 위해서는 앞의 iter() 인터페이스를 사용하고, 추가적인 기능을 사용할 때는 piter, first, last, end 를 사용하면 된다.

```
$ list = [1,2,3];
[ 1,2,3 ]
$ f = list.first();
<iter - 0x16f7f30>
$ l = list.last();
<iter - 0x16f82f0>
$ f();
1
$ l();
3
$ f.next();
<iter - 0x16f7f30>
$ f();
2
$ f(3);
3
$ print: list;
[ 1,3,3 ]
$ print: f == l;
false
$ f.next();
<iter - 0x16f7f30>
$ print: f == l;
true

```

find(value) 인터페이스는 value가 있는 위치의 반복자를 반환한다.

```
$ list = [1,2,3];
$ i = list.find(2);
$ print: i();
2
$ i.prev();
$ print: i();
1
```

리스트 반복자는 insert(), remove() 인터페이스를 갖는다. 각각 자기 위치의 앞에 새로운 원소를 삽입하거나 자기 위치의 원소를 삭제한다.

```
$ list = [1,2,3];
$ i = list.find(2);
$ i.insert(100);
$ print: list;
[ 1,100,2,3 ]
$ i = list.find(100);
$ i.erase();
$ print: list;
[ 1,2,3 ]
```

반복자에 대해 유의할 것이, 원본 리스트는 타임스탬프를 유지하고 있어서 내부 원소의 위치가 바뀌면 (삽 입, 삭제로) 타임스탬프가 증가한다.

그러면 이전 타임스탬프일 때 생성한 반복자는 무효해지고 이 반복자 를 사용하게 되면 exception이 발생한다. STL의 경우 무효화된 반복자를 사용하지 않는 것은 프로그래머 책임인데 (때문에 seg. fault도 날 수 있다), 일단 오르카에선 무효화 여부를 라이브러리가 체크해주고 exception을 날린다.

마지막으로, 리스트를 정렬하는 sort 인터페이스가 있다. 단순히 sort를 호출하면 지정된 방식으로 정렬을 수행하지만, sort의 인자로 비교함수를 전달하면 해당 함수를 '<' 함수로 사용하여 대소비교를 수행한다.

```
$ a = [1,3,2,4,2];
[ 1,3,2,4,2 ]
$ a.sort();
[ 1,2,2,3,4 ]
$ print: a;
[ 1,2,2,3,4 ]
$ 
$ a.sort(labmda(...argv){ return argv[0] >= argv[1]; });
[ 4,3,2,2,1 ]
```

위의 예에서 마지막 부분은, 역순으로 정렬하고자 '<'와 정반대로 동작하는 람다함수를 인자로 전달한 예를 보여준다.


튜플
-----

튜플은 리스트와 외형상으로는 거의 같으나 크기가 고정되어 있다는 점이 다르고 사용자에게 드러나지는 않으나 랜덤 억세스시 탐색속도가 더 빠르다는 장점이 있다.

튜플은 인터페이스 측면에서는 리스트와 거의 유사하다.

```
$ a = ( 1, 3, 4 );
$ print: a,' ',a[1];
( 1, 3, 4 ) 3
```

내장 함수로서 삽입, 삭제는 push\_back, pop\_back 인터페이스만 제공한다.

```
$ a = (1,2,3);
$ print: a.push_back(100);
( 1,2,3,100 )
$ print: a.pop_back();
( 1,2,3 )
```

list() 인터페이스는 순서가 같은 리스트를 생성하고, size() 인터페이스는 튜플의 길이를 리턴한다. empty() 는 비어있을 경우 true를 리턴한다. clear() 는 튜플을 초기화 한다.

```
$ a = (1..10);
$ print: a, a.list();
( 1,2,3,4,5,6,7,8,9,10 )[ 1,2,3,4,5,6,7,8,9,10 ]
$ print: a.size();
10
$ a = (1..10);
( 1,2,3,4,5,6,7,8,9,10 )
$ a.empty();
false
$ a.clear();
(  )
$ a.empty();
true
```

tuple의 경우도 리스트와 유사하게 iter(), piter(), first(), last(), end(), find() 를 제공한다. 단, insert, remove는 제공하지 않는다.

```
$$ tp = (1,2,3);
( 1,2,3 )
$ f = tp.first();
<tupleiter - 0x16fa2d0>
$ l = tp.last();
<tupleiter - 0x16fa4c0>
$ f();
1
$ f.next();
<tupleiter - 0x16fa2d0>
$ f();
2
$ f(3);
3
$ print: tp;
( 1,3,3 )
$ print: f == l;
false
$ f.next();
<tupleiter - 0x16fa2d0>
$ print: f== l;
true
$ tp = (1,2,3);
( 1,2,3 )
$ i = tp.find(2);
<tupleiter - 0x16fb4c0>
$ i();
2
$ i.prev();
<tupleiter - 0x16fb4c0>
$ i();
1
$ tp = (1,2,3);
$ i = tp.find(2);
$ print: i();
2
$ i.prev();
$ print: i();
1
```





맵 
-----

파이썬, 루비의 딕셔너리 및 STL의 map 과 같은 자료구조이다.

```
$ a = { ‘harry’:100, ‘tom’:20 };
$ print: a[‘harry’];
100
```

이런 식으로 처음 선언할 때는 slicing처럼 key, value pair를 나열하고, \[\] 연산자를 이용하여 참조한다.

map 은 원소의 갯수를 반환하는 size() 인터페이스를 가진다. empty() 는 비어있을 경우 true를 리턴한다. clear() 는 맵을 초기화 한다.

```
$ a = { 1:2, 3:4 };
$ print: a.size();
2
$ a.empty();
false
$ a.clear();
{  }
$ a.empty();
true
$ 
```

has\_key 인터페이스는 해당 key 값이 존재하는지를 true/false 로 알려준다. erase\_key 는 해당 키를 가지는 원소를 삭제한다.

```
$ a = {1:2, 3:4 };
$ print: a;
{ 1:2,3:4 }
$ print: a.has_key(1);
true
$ print: a.has_key(100);
false
$ print: a.erase_key(1);
nil
$ print: a.has_key(1);
false
$ print: a;
{ 3:4 }
$ 
```

map의 경우도 iter, piter, first, last, end 인터페이스를 지원한다. map 은 정렬연관 컨테이너이기 때문에 iterator 의 next로 순회하면 정렬 순서대로 아이템들을 억세스할 수 있다.

map 의 경우 k, v 쌍이기 때문에 iter 외에 k, v 를 리턴하는 iter2 인터페이스도 제공한다.

반복자로부터 값을 참조하려면 반복자를 실행시키면 되는데 map의 경우는 key-value pair이다 보니 실행하면 ( key, value ) 의 튜플이 반환된다. key, value 를 따로 억세스하기 위해서는 it.key(), it.value() 인터페이스를 각각 호출한다.

```
$ m = {1:100, 2:200, 3:300};
{ 1:100,2:200,3:300 }
$ a = m.first();
<mapiter - 0x16fc5e0>
$ print: a(), a.key(), a.value();
( 1,100 )1100
$ a.next();
<mapiter - 0x16fc5e0>
$ print: a(), a.key(), a.value();
( 2,200 )2200
$ a.next();
<mapiter - 0x16fc5e0>
$ print: a(), a.key(), a.value();
( 3,300 )3300
$ a.next();
uncaugted exception: orca.iter.end out of range
recent call-stack trace
>> root (internal 0)
```

반복자로부터 값을 변경하는 것은 반복자에 변경될 값을 입력하여 호출하면 되는데 맵의 경우 키를 바꿀 수는 없고 (키를 바꾼다는 것은 정렬순서가 바뀌는 것이며 반복자가 정렬순서를 바꾸면서 유효할 수 없다) value 값이 변경된다.

```
$ a = {1:100, 2:200, 3:300};
{ 1:100,2:200,3:300 }
$ it = a.first();
<mapiter - 0x1700170>
$ it(1000);
( 1,1000 )
$ it.next();
<mapiter - 0x1700170>
$ it(2000);
( 2,2000 )
$ it.next();
<mapiter - 0x1700170>
$ it(3000);
( 3,3000 )
$ a;
{ 1:1000,2:2000,3:3000 }
```

find() 는 해당 키값을 가르키는 반복자를 리턴한다.

```
$ a = {1:100, 2:200, 3:300};
$ it = a.find(2);
$ print: it();
( 2,200 )
$ 
$ it = a.find(100);
$ print: it == a.end();
true
$ print: it();
uncaugted exception: orca.iter out of range
recent call-stack trace
>> mapiter      (internal 0)
>> orcaRoot     (internal 0)
>> orcaRoot     (internal 0)
>> orcaRoot     (internal 0)
```

맵은 upper\_bound와 lower\_bound도 제공한다. find와 유사하나 find는 찾는 키가 존재하지 않으면 end() 반복자를 리턴하는데 반해, lower\_bound, upper\_bound는 정렬이 깨지지 않는 상황에서 삽입할 수 있는 위치를 리턴하는데, 찾는 값이 있다면 lower\_bound는 해당 키의 위치를, upper\_bound는 그 다음 위치를 리턴한다.

```
$   a = { 1:1, 2:2, 4:4, 5:5, 6:6 };
$   i = a.lower_bound(3);
$   print: i();
( 4,4 )
$   i = a.upper_bound(3);
$   print: i();
( 4,4 )
$  i = a.lower_bound(4);
$  print: i();
( 4,4 )
$   i = a.upper_bound(4);
$   print: i();
( 5,5 )
```

keys() 는 맵의 key 값들을 리스트로 반환한다. values()는 맵의 value 값들을 리스트로 만들어 반환한다.

```
$ a = { 1:'value 1', 'two':2, 'key3':[1,2,3] };
$ print: a.keys();
[ 1,'key3','two' ]
$ print: a.values();
[ 'value 1',[ 1,2,3 ],2 ]
```





조건 제시법
------

### 조건 제시법은 조만간 제거되고, python style의 list comprehension 으로 대체될 예정이다. (후자가 가독성이 더 뛰어나 보여)

조건제시법을 통해 지연연산되는 논리적인 리스트를 작성할 수 있다.

원래 수학의 조건 제시법은, 예를들어 1부터 100까지의 짝수는 다음과 같이 표현된다.

```
[x|x<-n, 1<x<10, n%2=0]
```

그런데, 이것이 프로그래밍의 표현식으로 나타나기 위해서는 몇가지 변형이 가해져야 하는데, 일단 오르카의 조건제시법은 정수에 대해서만 가능하기 때문에, x<-n 은 따로 표시안해도 되고, x<-1~10 과 같이 한번에 표시될 수 있다.

그리고, 처음부터 원소가 정해져 있는 일반 리스트와 구분하기 위해 처음에 %를 붙이게 된다. 해서 1부터 10까지의 짝수는 다음과 같이 표시될 수 있다.

```
$ print: %[x|x<- 1~10, x%2 == 0];
[2,4,6,8,10]
```

이제 세세하게 한 항목식 따져 보자면..

%\[x|x<-1~10, x%2==0\] 는 세 부분으로 나뉠 수 있는데, | 전에 오는 항목은 오른쪽에서 걸려진 값의 최종 표현식이다. 만일 위의 예를 %\[x-1|x<-1~10, x%2==0\] 과 같이 바꾸면 1~10까지의 홀수가 출력된다.

다음 x<-1~10 은 발생절인데, 규칙에 맞게 일정 범위의 정수를 발생시킨다. x<-1~10은 1~10 까지의 정수를 발생시키고, x<- -10~ 은 -10이상의 정수를 발생시키고 (이렇게 되면 무한대의 정수가 발생되는데, 이게 가능한 이유는 지연연산을 지원하기 때문이다. 추후 다시 설명) x<-~100 은 100이하의 정수를 발생시킨다.

위와 같이 범위를 통한 발생절도 가능하고, 특정 리스트를 통해 발생시키는 것도 가능하다. 앞의 예제는, %\[x|x<-\[1..10\], x%2==0\] 과 결과적으로는 동일하다. x<-\[1..10\] 이란 오른쪽의 리스트들의 각 원소들에 대해서.. 라는 뜻이다. 오른 쪽은 위와 같이 상수형의 리스트가 올 수도 있지만, x<-y 와 같이 변수형태로 올 수도 있고, 다른 조건제시법이나 이터레이터형 오브젝트가 올 수도 있다.

단, 이런 형태는 어쨌거나 런타임 시에 고정된 형태의 리스트가 오는 것이기 때문에 처음의 범위형태와 다르게 지연연산의 효과가 약간 줄어든다.

```
$ a = %x[x|x<-1~100000000];
$ print: a[10]
11
```

범위형을 쓰면 지연연산(필요한 순간에 그 값을 취함)때문에 위와 같은 형태가 가능하고 출력도 즉시 나타나지만,

```
$ a = %x[x|x<-[1..1000000000]];
$ print: a[10];
```

이를 실행시키면 결국 필요한 것은 열한번째 원소일 뿐이지만, 첫줄의 조건제시법을 구성할 때 쓰이는 \[1..1000000000\] 리스트를 만들기 위해 엄청난 메모리와 시간을 소모한다. 때문에 시스템의 메모리가 부족하면 프로그램이 더 진행되지 않을 것이고, 충분하다 하더라도 출력시까지 delay 가 나타날 것이다.

이제 처음예제의 마지막 항목으로 돌아가보면 x%2 == 0 이 있는데, 이는 왼쪽의 발생자들로부터 나오고 조건자들로부터 걸러진 항목들을 다시한번 거르는 조건자이다. 왼쪽의 발생자가 1~10 까지의 정수를 발생시켰으니 이것들의 각각에 대해서 2로 나누었을 때 나머지가 0인지를 거르는 것이다.

조건자는 boolean expression 으로 구성되어야 하며, 여러개를 쓸 수 있다. print: %\[x|x<-1~10, x%2==0, x%3==0\] 은 \[6\] 을 출력한다. 첫 발생자는 첫번째 조건자를 통해 2,4,6,8,10 의 정수가 걸러지지 않고 통과한 후, x%3==0 이란 조건자를 만나 6만이 조건을 만족하게 되기 때문이다.

발생자도 겹쳐져서 사용될 수 있는데 , 아래 의 구문은

```
$ print: %[(x,y)|x<-1~5, y<-3~5];
[ ( 1,3 ),( 1,4 ),( 1,5 ),( 2,3 ),( 2,4 ),( 2,5 ),( 3,3 ),( 3,4 ),( 3,5 ),( 4,3 ),( 4,4 ),( 4,5 ),( 5,3 ),( 5,4 ),( 5,5 ) ]
```

와 같은 결과가 나타난다. x가 1~5까지를 발생하는 동안, y는 3~5까지를 발생시키며 각각의 조합들에 대해서 (x,y) 와 같이 최종적으로 튜플을 구성하는 예이다.

물론 여기에 x,y 를 사용하는 조건절도 집어넣을 수 있는데,

```
$ print: %[(x,y)|x<-1~5, y<-3~5, x==y];
[ ( 3,3 ),( 4,4 ),( 5,5 ) ]
$
```

위와 같이 발생된 항목들중에 x==y 인 것만 추리게 되므로 출력은 위와 같아진다.

조건제시법의 항목을 세세하게 설명하다 보니 지루한 예제가 반복 되었는데, 좀 더 실용적으로 솟수를 구하는 예제를 보자.

솟수의 정의는 1과 자기자신을 제외하고는 나누어 떨어지는 값이 없는 수인데, 어떤 수를 입력받았을 때 이것이 나누어 떨어지는 리스트를 구하는 함수를 아래와같이 정의할 수 있다.

```
$ def factor(n)
* {
*   return %[x|x<-1~n, n%x==0];
* }
* 

$ print: .factor(100);
[ 1,2,4,5,10,20,25,50,100 ]
```

시험해보면 잘 동작한다. 1~100까지의 숫자중 100이 나누어떨어지는 경우는 위의 경우와 같다.

이제 1부터 입력받은 숫자 n사이에 존재하는 솟수를 출력하는 함수를 다음과 같이 정의해보자

```
def prime(n)
{
  return %[x|x<-1~n, ..factor(x) == [1, x]];
}
```

위함수는 n을 입력받은 후, 1~n 까지의 숫자들 각각에 대해 factor를 구하고(나누어떨어지는 수들의 리스트) 구해진 factor가 1과 자기자신인 것만을 리턴한다.

한번 아래와 같이 시험해보면...

```
$ print: .prime(100);
[ 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97 ]
$ 
```

잘 작동한다!!!

참고로 이 예제는 haskell programming 이란 책에서 따왔다.

이제 지연연산에 대해서 언급해본다. a = \[1, 2, 3\]; 과 같은 리스트 형식은 런타임 순간에 오른쪽의 리스트를 완성해서 왼쪽의 a에 대입시키는데, a = %\[x|x<-1~3\]; 과 같이 하면 "1부터 3까지의 정수"라는 조건제시법을 a에게 대입시킨다.

때문에 리스트의 총 길이가 얼마이고, 각 원소가 무엇무엇인지는 실제 사용하는 순간까지 미뤄지고 참조되는 순간, 계산된다. 이것을 지연연산이라(lazy evaluation) 부른다.

오르카의 리스트는 기본적으로 지연연산이 아니나, 조건제시법으로 표현된 리스트는 지연연산으로 동작한다.

위의 솟수 계산 프로그램이 도는 중 x 가 10일 때 10이 솟수인지 아닌지, ..factor(10) == \[1, 10\] 을 통해 계산하게 된다.

이때 만일 이것이 지연연산이 아니라면, factor(10) 을 "모두 계산하여" \[1, 2, 5, 10\] 이 factor(10)의 리턴값이 되고, 오른쪽 리스트와 비교하여 실패를 리턴하는데,

factor(10)은 %\[x|x<-1~10, 10%x == 0\] 이라는 조건제시법을 리턴한다. 이렇게 되면 오르카는 비교식을 처리하면서 첫번째, 두번째, 세번째 ... 항목을 각각 비교하며 중간에 실패시 false를 리턴하게 되므로 왼쪽의 조건제시법 객체는 \[1,2,5,10\]을 모두 계산하지않고, \[1,2, ????\] 까지만 계산하면 된다.

이로서 factor 함수는 1~10 까지에 대해 조건을 모두 조사한(그러니까 10번) 것이 아니라, 1과 2에 대해서만 계산을 수행 하여 총 두번만 실행된 셈이 된다.

이제 앞절에서 언급되었던 quick sort 예제를 다시 설명하겠다.


```
def.decode qsort(a)
{
  case []:
    {
      return [];
    }
  case %x[%xs]:
    {
      return qsort(%[a|a<-xs, a<=x]) + [x] +  qsort(%[b|b<-xs, b>x]);
    }
}

$ print: .qsort([-7, 1.2, 30, 4]);
[ -7,1.2,4,30 ]
```

decode 함수인 qsort 는 리스트를 입력받아서 비어있으면 그냥 리턴하고, 비어있지 않다면 맨 앞의 원소를 떼어낸 후(예제에선 x), 나머지 들중에서 x보다 작은것은 앞쪽에, 큰것은 뒤쪽에 배열한 후 다시 각각 배열한 앞, 뒤쪽의 원소들에 대해서도 quick sort를 똑같이 수행한다. (리스트가 빌 때까지)

이것은 quick sort 의 알고리즘 정의와 정확히 똑같이 정의될 수 있는 것으로, 조건제시법과 def.decode 함수를 통해 간결하게 구현할 수 있다.

조건제시법의 발생자는 정수뿐만 아니라 실수 및 다른 자료형도 가능하다 단, 다른 자료형일 때는, 시작과 끝값외에도 step 을 지정해주어야 한다.

step 이 있는 발생자의 표기 형식은 x <- START ~ END : STEP 과 같다. 정수형일때는 STEP 이 생략되면 1로 가정된다.

예를들어 다음 조건제시법은 0 ~ 10까지의 실수들을 0.1 단위로 생성한다.

```
$ a = %[x|x<- 0 ~ 10 : 0.1];
[ 0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5,5.1,5.2,5.3,5.4,5.5,5.6,5.7,5.8,5.9,6,6.1,6.2,6.3,6.4,6.5,6.6,6.7,6.8,6.9,7,7.1,7.2,7.3,7.4,7.5,7.6,7.7,7.8,7.9,8,8.1,8.2,8.3,8.4,8.5,8.6,8.7,8.8,8.9,9,9.1,9.2,9.3,9.4,9.5,9.6,9.7,9.8,9.9,10 ]

```
조건제시법 리스트는 특성상 무한길이가 가능하기 때문에, 이 경우 출력포맷은 아래와 같이 ... 으로 나타나고,

```
$ a = %[x|x<-1~];
[ 1,2,3,4,5,6,7,8,9,10, ... ]
```

size() 인터페이스는 -1을 리턴한다. 이 경우는 리스트가 조건제시법이면서 길이를 알 수 없다는 뜻이다.

```
$ print: a.size()
-1
```

반복자
-----

현재 구현되어 있는 반복자들의 규칙은 다음과 같다.

* 다음으로 이동하기 위해서는 반복자의 next() 를 호출하면 자기 자신의 위치를 변경하되 다음 값이나, 자기 자신을 리턴한다. (list 설명에서의 value 반복자와 position 반복자 참고)

* 이전으로 이동하기 위해서는 prev()를 호출한다.

* next, prev의 결과가 유효범위를 벗어나면 orca.iter.end exception 을 발생시킨다.

* 값을 참조하기 위해서는 반복자를 호출한다. (반복자가 a 라면 value = a() 와 같이)

* 반복자가 가르키는 값을 변경하려면 변경될 값을 반복자의 파라미터로 하여 반복자를 호출한다. ( 반복자가 a 이고 1로 변경하고 싶으면 a(1) 과 같이)

* 반복자는 동등 비교 ( ==, !=) 를 할 수 있다.

* map 의 반복자의 경우는 특별히 대소 비교 ( <, <=, >, >=) 까지 할 수 있다.

  ​

여기까지가 구현되어 있는 반복자들의 일반 규칙이며 추가로 각각의 컨테이너들은 다음 규칙과 같이 동작한다.

*   list, tuple, map 의 첫번째 아이템의 반복자는 해당 컨테이너의 first()을 호출하면 얻어지며
*   next(), prev() 는 이동 단위를 인자로 받을 수 있다. next(2) 는 next(), next() 와 같다.
*   마지막 아이템의 반복자는 last() 를 호출하면 얻어진다
*   마지막 아이템의 다음 반복자는 end() 를 호출하면 얻어진다
*   컨테이너의 find() 를 통해 특정 값이 위치한 이터레이터를 찾을 수 있다.
*   컨테이너의 반복자의 erase()를 호출하면 컨테이너에서 해당 값이 삭제된다.
*   컨테이너의 반복자의 insert()를 호출하면 가능한 경우 (list 일 때만 허용) 해당 위치에 값을 삽입할 수 있다.
*   컨테이너의 자료들의 순서에 변동이 일어나면 해당 컨테이너의 반복자들은 무효화 되서 이를 사용하려할 때 orca.iter exception 이 발생한다.

기존 반복자 규칙에 비해 복잡하긴 하나, 자세히 보면 STL방식을 따르고 있으며, 유효성 여부를 자동적으로 관리한다는 점이 다르다.

삽입, 삭제, 참조, 변경이 가능하고 반복자간 비교까지 가능하기 때문에 훨씬 유연해 졌다.

기존에 구현되어 있는 반복자들은 위의 규칙들을 따르고 있으며, 향후 사용자 정의 반복자를 구현할 때도 이 규칙을 따라 구현하는 것이 일관성 유지에 좋다.

제어문
===

if
--

가장 기본적인 if 문의 구조는 if bool_expr { statement } 이다. 여기에 elif 와 else가 추가 될 수 있고, statement 자리에는 { } 으로 감싸인 문장 블럭이 올 수 있다.

while
-----

while 문은 while bool_expr { statement } 의 구조를 가지며, C/C++의 while과 비슷하게 동작한다.

```
a = sum = 0;
while a < 10 {
  sum  += a;
  a+=1;
}
```

위 문장은 0부터 9까지 더하는 예제이다.

do while
--------

가끔은 while 대신 do while 이 필요할 때가 있다.

do while 문은 do { statement } while bool_expr 의 형태를 띈다.

```
a = sum = 0;
do {
  sum += a;
  a += 1;
} while a < 10;
```

위 예제는 앞절과 같은 기능을 수행한다. 

for
---

for 문은 for a in b { statement } 의 형태를 띈다.

b에는 list, tuple, map 이 오거나 나중에 나올 iterator, generator 객체가 올 수도 있다.

a 는 b에서의 원소를 차례로 대입 받게 될 지역변수로서 statement에서 참조될 값이다. 설명보단 간단한 예제를 보자.

```
sum = 0;
for a in [1..10] {
  sum += a;
}

print: sum;
```

위의 예제는 1 부터 10까지의 합계를 더한 결과를 출력하는데, b 자리에 있는 리스트 생성식 \[1..10\] 이 \[1,2,3,4,5,6,7,8,9,10\] 인 리스트를 생성하고, a에는 차례대로 앞에서부터 하나씩의 원소가 대입되면서 statement 에 해당하는 sum += a 를 실행하게 된다.

iterator도 지원하는데, for a in b 의 b에는 next() 인터페이스를 가지고 있는 객체가 올 수 있다. 간단한 예제는 아래와 같다.

```
def one_to_hundred 
{
  my.cur = 0;
  return my;

  def cur;
  def next() {
    owner.cur += 1;
    if owner.cur > 100 {
		throw done;
	}

    return owner.cur;
  }
}

it = my.one_to_hundred();

sum = 0;
for i in it {
  sum += i;
}
print: sum;
```

switch
--------
switch 구문은 일반적인 언어의 그것과 같다. 판별할 인자와 동일한 case 문이 실행된다. 아래 예제의 경우는 20이 출력된다.

C/C++ 과는 다르게 break 를 쓸 필요는 없으나 fallthrough 가 있어서 다음 case 까지 실행할 수 있다.

```
a = 20;
switch a
{
    case 10: print('case 10');
    case 20: print('case 20');
    case 30: print('case 30');
    default: print('default');
}
```



switch 는 동일성을 판별 조건으로 하기 때문에, == operator 의 실행결과로 동일성을 판별한다. 따라서 regex 에 해당하는지를 다음과 같이 할 수 있다. regex 와 string 의 비교이나 == 연산자로 비교했을 때 동일하기 때문에 alphabet_only 가 출력된다.



```
switch r'[a-zA-Z_]+'
{
case 'a10': print('case a10');
case 'abc?': print('case a10');
case 'alphabet_only': print('alphabet_only');
default: print('default');
}
```



select
------

select 구문은 go lang 에서 영향을 받았으며 채널이나 fd 를 기다릴 수 있다. 그런데, 다음 장의 체널객체에서 살펴보겠지만 오르카에서는 채널이라는 개념을 사용하지 않고 ->, <- 란 연산자로 일반화 시켰다. 때문에, 채널 변수만이 아니라 ->, <- 를 가지고 있는 모든 자료형, 객체가 select 구문에 사용될 수 있다.

먼저 리스트, 튜플을 사용한 예이다.

```
a = [,];
b = (,);

select {
    case a -> ret:
    	print: 'case 1', ret;
    case b -> ret:
    	print: 'case 2', ret;
    default:
    	print: 'default';
}
```

a, b 가 비어있으므로 default 가 출력된다. select 구문의 default 는 대기없이 바로 선택되게 하는 경우에 사용된다. (golang 의 경우와 같다)


아래는 좀 더 복잡한 예제이다. lambda 객체가 실행되면서, tuple b  에 0.1초마다 100, 200, 300 을 채널로 집어넣는다. select 문에서는 a 나 b에 멤버가 삽입될 때까지 대기했다가 (이번에는 default 가 없다) -> 이 가능한 경우 아이템을 하나씩 빼서 result 에 넣은 후 최종 출력했다.

```
using thread;
using time;

def a := [,];
def b := (,);

thread.run: lambda() {
    for i in (0, 3) {
        time.sleep(0.1);
        print('signal...');
        ..b <- 100, 200, 300;
    }
};

result = [];
select {
case .a -> ret:
    print(ret);
    print: 'case 1';

case .b -> ret:
    print(ret);
    print: 'case 2';

    result.push_back(ret);

    if result.size() >= 6 {
        break;
    }
    continue;
}

print: result;
```



최종 출력결과는 아래와 같은데, 여기서 튜플을 사용했기 때문에 -> 로 빼낸 결과가 뒤에서부터 가져와 100, 200, 300 중 300, 200, 100 의 순으로 result 에 들어가게 된다. 튜플은 pop_back 만을 지원하기 때문에 순서가 뒤집혔고, list 의 경우였으면 -> 연산자가 pop_front 를 실행하기 때문에 100, 200, 300 순서대로 result 에 들어갔을 것이다.

```
signal...
300
case 2
200
case 2
100
case 2
signal...
300
case 2
200
case 2
100
case 2
[ 300,200,100,300,200,100 ]
```

여기서는 일단 tuple, list 만을 대상으로 설명했는데, 일반적인 channel object, socket, file 및 timer, ticker 에도 똑같이 사용될 수 있다.

더 자세한 내역은 테스트의 test_select, test_timer 에서 볼 수 있다.



scope object
--------

엄밀히 말해서 scope 객체가 제어문은 아니지만, 코드 흐름과 관계된 내용이어서 여기서 소개한다. 단, 본 절의 예제를 이해하려면 함수, 객체에 대한 내역을 알아야 하기 때문에 예제가 이해 안된다면 다른 부분을 먼저 본 후 다시 보기 바란다.

scope statement 는 다음과 같은 형태를 띈다.

```
object { 
  statement list
}
```

이런 식으로 구성되면 statement list 가 실행되기 전에, object."{"() 가 자동적으로 실행되고, 마지막에 object."}"()가 실행된다. 또한, object."}"()는 exception 이 발생하거나, statement list안에서 return 을 하더라도 실행되는 것이 보장된다.

예를 들어 어느 구문을 뮤텍스로 잡고 싶다면.

```
using ipc;

def scope_mutex 
{
    def mtx;
    
    def new {
        owner.clone();
        ..mtx = new ipc.mutex;
    }
    
    def "{" {
        ..mtx.lock();
    }
    
    def "}" {
        ..mtx.unlock();
    }
}


def fun {
    mtx = ..scope_mutex.new();

    mtx {
        foo();
        bar();
    }
}
```

와 같은 구문을 구성하고 fun() 를 실행하면,

```
mtx."{"();
foo();
bar();
mtx."}"();
```

순서대로 실행된다. 짐작하겠지만 "{"에서는 mutex를 얻고, "}"에서는 mutex를 풀며 그 사이 영역을 상호배제 시키는 예제이다.

하지만 이것이 단순히 {, } 를 중괄호 시작과 끝에 단순 대입하는 것만은 아니다.

만일 foo(), bar() 에서 어떤 exception이 발생하고, foo에서 이를 catch하지 않아서 외부로 전파되게 되면, mtx."}"가 그 시점 (stack unwinding 시점)에서 자동으로 호출된다. 또는

```
mtx {
  foo();
  return;
}
```

인 상황에서도 return 전에 mtx."}"가 호출된다.

해서 위의 코드는 mutex unlock이 되지않아 다른 쓰레드를 데드락으로 만들지 않게 보장한다. C++의 생성자, 소멸자를 이용한 블럭킹 테크닉을 생각하면 된다. (하지만 이게 더 가독성이 높지?)

물론 이런 특징외에도 timer 라든지, trace 등등 시작과 끝이 짝으로 이루어지는 여러유형의 동작에 응용할 수 있다.

애초 이 구문은 위와 같은 exception, return safe한 동작을 구성하기 위해 만들어졌지만, CGI 를 가독성있게 처리하기 위한 의도도 있다. cgi 모듈의 tag 부분을 보면 이의 또다른 응용을 볼 수 있다.

parallel do
-----------

병렬 처리를 위해 orca는 thread 모듈을 제공하지만, API 기반으로 병렬처리를 수행하는 것은 설계단에서부터 세심한 주의를 필요로 하고, 메인 로직의 기본 흐름이 순차적 처리와 매우 달라지게 된다.

늘어나는 CPU를 효과적으로 사용하기 위해 orca는 parallel 구문을 지원하는데, 기본적인 설계사상은 메인로직의 큰 변경없이 병렬처리할 수 있는 것들을 손쉽게 병렬화 시키는 것이다.

이를 위해 현재 구현된 것은 parallel do와 parallel for 구문이다.

```
b = foo(a);
user_log ('result of foo: ${b}');
bar(b);
```

위와 같은 경우를 생각해보자, 메인 로직이 foo를 실행하고 이것의 결과를 이용해 bar를 실행한다. 그런데, foo의 결과값을 파일에 로깅하고 싶어 user\_log 함수를 불렀다 치면, 사실 user\_log 함수는 메인 로직의 부차적인 부분으로 병렬처리된다 해도 큰 지장이 없는 부분이다.

이런 경우에 대해서

```
b = foo(a);
parallel do {
  user_log('result of foo: ${b}');
}
bar(b);
```

와 같이 고치면 메인 쓰레드는 b = foo(a); bar(b); 만 실행되고

b = foo(a); 가 끝나는 시점에 서브 쓰레드가 하나 생성되어 parallel do 구문의 중괄호 안의 것을 실행하고 리턴된다!!!

이것이 혁신적으로 보이는 이유는... 그리고 실제로 혁신적인 이유는, 메인 쓰레드의 지역 변수 스텍을 참조할 수 있기 때문이다. 즉 일반 적인 thread 모듈을 사용한 쓰레드 생성시는 독립적인 지역변수를 가지고 새로운 쓰레드가 생기고 전달해줘야 하는 정보는 생성시의 파라미터나 전역변수를 사용해야 하는데,

위의 보기처럼 parallel do 구문은 메인 쓰레드의 지역변수인 b를 바로 참조할 수 있게 된다. 구조적으로 orca는 최종 로컬 스택 프레임을 서브 쓰레드에도 복사시켜 참조할 수 있게 한다. 때문에 단순히 parallel do { } 를 침으로써 메인 로직을 손쉽게 병렬화 시킬 수 있다 !!!!!

이런 구조이기 때문에 (마지막 지역변수 스택을 복사하는 방식) 유의해야 할 점은

```
def foo
{
    def value; 
}

a = 10;
b = .foo.clone();
b.value = 10;

parallel do {
  a = 20;
  b.value = 20;
}

print: a;
print: b.value;
```

와 같이 실행한다면 메인 쓰레드의 최종 결과값이 a는 10, b.value 는 20이 된다. 왜냐하면 a는 POD로서 (integer 이기 때문에 별도의 레퍼런스 없이 값이 그대로 복사되고 관리되는 타입) 서브 쓰레드에서 20으로 변경시킨다 해도 서브 쓰레드 로컬 스택의 값만 바뀌고 메인 쓰레드의 것은 변경되지 않는 반면, b의 경우 객체의 레퍼런스값이기 때문에 서브 쓰레드에서 값을 바꾸면 메인 쓰레드의 것도 영향을 받는다.

쉽게 말해

```
a = .foo.clone();
b = a;
b.value = 10;
```

과 같이 했을 때, a.value 도 10이 되는 것과 마찬가지지만

```
a = 20;
b = a;
b = 10;
```

을 한다 해도 a 는 20 그대로인 이유와 같다.

음... 복잡했다면 이 부분은 나중에 찬찬히 생각해 보기 바란다 : )

한가지 더, parallel do 구문은 쓰레드 기반이기 때문에 순서를 보장하진 않는다. 무슨 소린고 하니

```
foo();
parallel do { sub_1(); }
bar();
parallel do { sub_2(); }
```

와 같이 하면

```
main thread: foo(), bar();
thread 1 : sub_1();
thread 2 : sub_2();
```

의 세 쓰레드가 별도로 돌지 서브 쓰레드가 sub\_1(), sub\_2() 와 같이 순서대로 실행하지는 않는 다는 것이다.

본 구문과 곧 추가될 parallel for 구문을 이용하면 멀티코어 환경에서 효율적인 프로그래밍이 가능할 것이다.

개인적인 추천은 parallel do 구문은 blocking IO 에 사용하고 parallel for 구문은 CPU bound job에 활용하면 좋을 듯 하다.

```
using time;
using stopwatch;

sw = stopwatch;

sw.start();
time.sleep(1.0);

sw.lap('without parallel do: ');

sw.start();
parallel do {
  time.sleep(1.0);
}

sw.lap('with parallel do: ');

without parallel do: 999 ms, 599 us

with parallel do: 399 us
```

위와 같이 parallel do 구문을 쓰면 메인 쓰레드가 sleep을 지나쳐 오므로 보기와 같이 빠르게 sw.lap() 까지 도달한다.


parallel call
-----------
parallel 로 특정 함수를 call할수도 있다. parallel 다음에 함수호출식을 쓰면 병령로 실행된다.

다음은 그 예이다.

```
using time;

def foo
{
	time.sleep(1.0);
	print: "I'm foo";
}


parallel my.foo();
print: "may be this will be shown faster";

```

parallel for
------------

```
parallel for a in input
{
  statement_list;
}
```

parallel for 구문은 위와 같은 형식으로 쓰여, list형 (list, set builder form, iterator) 객체인 input에 대해 statement 를 실행시킨다. 이 구문은 Intel 의 threading building block 라이브러리에서 영감을 받아 작성했는데, 그보다는 범용적이고 편하게 쓸 수 있도록 구성됐다.

예를 들어가며 설명하자면

```
parallel for a in [1,2,3,4,5]
{
  foo(a);
}
```

위 구문은 for(1), foo(2), foo(3), foo(4), foo(5)를 각각 병렬적으로 실행한다. 단, 최적 처리를 위해 이 구문이 동시 실행하는 쓰레드의 숫자는 시스템의 CPU 숫자와 같다. 즉 듀얼코어 시스템에서는 2개의 쓰레드가 리스트를 나눠가며 실행하고, 쿼드코어라면 4개의 쓰레드가 실행된다.

이 구문도 parallel do 와 같이 최종단의 지역변수스텍을 복사하여 실행한다. 때문에, 기존에 쓰였던 for 문 앞에 parallel 만 붙이는 것으로도 쉽게 병렬화 시킬 수 있고 여의치 않으면 손 쉽게 원래대로 돌아올 수도 있어서 프로그램 병렬화에 큰 수고를 들이지 않고 작업을 수행할 수 있다.

이 구문은 parallel do 와는 달리 for 문이 다 종료될 때까지 main thread 가 대기한다. (parallel do 구문은 서브 쓰레드의 종료와 상관없이 메인구문은 다음으로 바로 진행했다)

단, 리스트들의 원소를 각 쓰레드에 할당하는 작업이 오버헤드가 있기 때문에 간단한 작업에서는 더 느릴 수도 있다.

```
using time;
using stopwatch;

sw = stopwatch;

sw.start();
for a in [1..10] {
  print: a;

  c = 0;
  for b in %[x|x<-1~100000] {
    c = c+1;
  }
}

sw.lap('with for: ');

sw.start();
parallel for a in [1..10] {
  print: a;

  c = 0;
  for b in %[x|x<-1~100000] {
    c = c+1;
  }
}

sw.lap('with parallel for: ');

C:\Lab\orca>orca test_for
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
with for: 421 ms, 875 us
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
with parallel for: 93 ms, 750 us
```

시험에 사용된 PC는 쿼드코어 인데, 위와 같이 전체 실행시간이 대략 1/4정도로 줄어든 것을 볼 수 있다. :>

parellel for 구문은 옵션으로 by, per 를 붙일 수 있다.

```
parallel for a in [1..100] by 3 per 30 {
  print: a;
}
```

를 지정하면 3개의 쓰레드가 30개 단위로 리스트들을 처리한다. 즉, 리스트를 \[1..30\], \[31..60\], \[61..90\], \[91..100\] 의 구간으로 나누어 3개의 쓰레드가 병렬처리 한다.

by와 per는 옵션으로 생략가능하며 생략되었을 때의 기본값은 by는 cpu num, per는 1이다. 단, cpu 가 1개인 경우엔 by 가 2인데, 멀티 쓰레드를 생각하고 실행코드에 blocking IPC를 사용했을 수 있어 최소값은 2로 설정하였다.

by, per의 값으로는 연산식도 가능하다. 추가로 제공될 system 모듈을 사용해서,

```
a = [1..1000];
parallel for i in a by (cpu = system.cpu_n() * 2) per (a.size() / cpu) {
  print: i;
}
```

와 같이 cpu 갯수와 배열 길이를 참조하여 어뎁티브하게 돌 수 있게 지정도 가능하다. 물론 가독성 있게 이렇게 쓰는게 좋을 것이다.

```
parallel for i in a by (cpu = system.cpu_n() * 2) per (a.size() / cpu)
```

decode statement
----------------

이 구문은 기존의 switch 구문과도 유사하고, 얼랑의 패턴매칭과도 유사한데 그보다 더 편의성과 범용성을 갖추도록 설계되었다. 이 구문을 사용하면 스트링과 리스트의 처리, 프로토콜 처리 등에 있어서 매우 유용하고 직관적으로 프로그래밍을 할 수 있다.

기본적으로 decode statement는

```
decode A
{
  case pattern_list: statement_list
  case pattern_list: statement_list
  case pattern_list: statement_list
  ...
}
```

와 같은 구성을 띄우며 입력된 A에 대해서 왼쪽의 pattern과 일치하면 오른쪽의 statement_list를 실행하는 형식을 띈다.

A에는 list, vector, list type object(SBF, iterator), string 이 올 수 있으며, pattern_list의 각 패턴들에는 스트링, 정규표현식, 리스트등이 올 수 있다.

각 상황에 대해 구분해서 간단한 예제와 함께 보도록 하겠다.

### 문자열 매치

```
decode 'orca'
{
  case 'orca': print: 'orca, matched';
  case 'python': print: 'python, matched';
}
```

이 구문을 실행하면, 'orca, matched'가 출력된다. 마치 단순한 switch 구문을 보는 것 같다. (약간 더 편하긴 하지만)

좀 더 복잡하게 해보면,

```
decode str
{
  case 'send:', %to, ':', %msg: ..send(to, msg);
  case 'connect:', %to: ..connect(to);
  case %fail: ..error(fail);
} 
```

간단한 채팅서버 프로토콜에 대한 패턴 매칭이라 생각하고 위의 예제를 보면 메세지를 전송하는 프로토콜은 첫번째 패턴과 매칭된다. 'send:tom:hello, tom' 과 같은값이 입력으로 온다면 첫번째 패턴과 매칭되고, to에 tom이, msg에 hello, tom 이 대입된 후 오른쪽의 구문이 실행된다.

입력에 'connect:tom' 이 온다면 두번째 패턴 리스트와 매칭되어 ..connect('tom') 이 실행된다. 마지막 패턴의 경우는 좀 특별한데, 아직 decode 구문에는 switch의 default: 와 같은 구문이 제공되지 않고 있다. 하지만 맨 아래와 같이 함으로써 마지막까지 온 입력값은 여기서 100% 매칭되게 되고, 입력값이 fail에 대입된 후 오른쪽 ..error(fail)이 실행되게 되단.

예제를 보는 것이 더 간단할 수도 있지만, 패턴 매칭의 규칙에 대해서 단계대로 다시 설명하겠다.

입력으로 'send:tom:hello, tom' 이 오게 된 후, 첫번째 패턴리스트를 만나게 되면, 패턴 리스트 'send:', %to, ':', %msg 중에서 첫번째 패턴을 먼저 비교한다. 입력값의 첫 다섯자가 'send:'이기 때문에 매칭에 성공하고, 입력값의 나머지 'tom:hello, tom' 이 계속 비교되게 된다. 패턴 리스트의 두번째 패턴은 %to 인데, 이것은 가능한 길이의 것과 매칭되는데 다음 패턴이 오기 전까지 매칭된다. 즉, 예제의 패턴 리스트에서 다음 세번째 패턴은 ':'니까 지역변수 to 에 'tom:hello, tom' 의 처음부터 ':' 까지의 값인 'tom'이 입력된다. 매칭된 다음의 남은 입력값은 ':hello, tom'인데, 세번째 패턴을 만나서 ':'이 다시 없어지고, 마지막 남은 'hello, tom'이 마지막 패턴인 %msg와 매칭을 시도한다. %msg의 뒤에는 아무것도 없으므로 남은 입력값 전체가 msg에 대입되게 된다.

패턴으로 가능한 것은 'send:', ':' 와 같은 상수 스트링 뿐 아니라, 대입을 위한 %name형의 지역변수도 가능하고, 그 외의 지역, 멤버변수도 가능하다.

즉, 프로토콜의 헤더로서 매직넘버용으로 ''을 붙인다고 하고, 이 매직 넘버의 버전정보는 바뀔수 있다고 가정하면

위의 예제를 다음과 같이 쓸 수도 있다.

```
magic = '';
...
decode str
{
  case magic, 'send:', %to, ':', %msg: 
    { 
      ..send(to, msg); 
    }
  case magic, 'connect:', %to:
    { 
      ..connect(to); 
    }
  ... 
```

위의 패턴 리스트에서 magic 은 패턴 비교를 위해 쓰였고, to, msg 는 패턴의 대입을 위해 쓰였다. 이 구분을 위해서 to, msg앞에 % 를 굳이 붙인 것이다.

### 정규 표현식 매치

decode 구문의 패턴에는 정규표현식이 쓰여 표현식을 더 풍부하게 해줄 수 있다.

```
decode str
{
 case 'id:', r'[a-zA-Z][a-zA-Z_0-9]*', ', number:', r'[0-9]+': print('matched!!');
 case %fail: print('failed..');
}
```

위와 같은 구문은 'id:lynix, number:103'와 같은 입력에는 matched!!를 출력하지만 'id:3aa, number:10', 'id:lynix, number:10a', 와 같은 것에는 failed 를 출력한다.

그런데, 이런 정규표현식을 사용할 때 실제 매치되는 값이 어떤 값인지 궁금할 때가 있다. 이처럼 정규표현식을 변수에 대입하고자 하면 위의 예제를..

```
decode str
{
 case 'id:', %id=r'[a-zA-Z][a-zA-Z_0-9]*', ', number:', %number=r'[0-9]+': print('matched!!, id=${id}, number=${number}');
 case %fail: print('failed..');
}
```

와 같이 하면 'id:lynix, number:103'은 matched!!, id=lynix, number=103 을 출력하게 된다.

### 리스트 매치

리스트에 대한 매칭도 가능하다. 리스트 매칭을 위한 패턴에는 리스트 타입이 와야한다.

```
decode [1,2,3,4,5]
{
  case [1, 2], %mid, [4, 5]: print(mid);
}
```

위의 예제는 \[3\] 을 출력한다.

앞에서와 유사하게 로컬변수 mid에 중간값을 대입하게 했는데, 이런 대입법 외에도 리스트 연산에 효율적으로 쓰이는 head:body 대입도 가능하다.

```
decode [1,2,3,4,5]
{
  case []: print('empty');
  case %head[%tail]: print('head: ${head}, tail: ${tail}');
}
```

위 예제는 head: 1, tail: \[2,3,4,5\] 를 출력한다. 참고로, 비어있는 리스트라 하더라도 head, tail에 각각 NIL이 매칭 되기 때문에, 전통적인 head:tail 재귀 처리일 때는 앞쪽 패턴에는 빈 리스트를 처리하기 위한 \[\] -> print: 'empty'; 같은 구문이 하나 있어야 한다. (한번만 쓰일 거면 없어도 된다)

내부적으로 head, body 대입에서 body에 대입되는 리스트는 \[2,3,4,5\]를 새로 생성하는게 아니라 원본 리스트의 두번째부터 접근되도록 한 가상의 리스트이기 때문에 별도의 생성, 복사 오버헤드 없이 진행 가능하다.

### decode 함수

decode 구문을 리스트에 적용하게 되면, 아무래도 LISP의 그 수많은 사용예와 같이 재귀적으로 사용되게 된다. 그런데, 리스트를 차례대로 출력하는 함수를 그냥 구성하면

```
def print_list(a)
{
  decode a
    {
		case []: print: 'done';
		case %head[%tail]: {
			print: head;
			print_list(tail);
		}
    }
}

.print_list([1,2,3,4,5]);
```

이 예제는,

```
1
2
3
4
5
done
```

을 출력한다.

그런데, 단순한 재귀 함수인데 def print_list(a), decode(a) 가 같이 있는게 가독성이 떨어지기 때문에, 위의 구문과 동일하게,

```
def.decode print_list(a)
{
  case []: print: 'done';
  case %head[%tail]: {
		print: head;
		print_list(tail);
  }
}
```

이렇게 표기할 수 있다.

리스트에 대한 def.decode 구문을 통해 함수형 프로그래밍을 흉내내 볼 수 있다. 함수형 프로그래밍에 가장 자주 언급되는 quick sort 를 오르카로 구성해보자. 이 decode 구문안에는 조건제시법이 쓰이기 때문에, 이 함수에 대한 설명은 다음 조건제시법 파트에서 다시한번 자세히 설명하겠다. 여기서는 일단 구경만...

```
def.decode qsort(a)
{
  case []:
    {
      return \[\];
    }
  case %x[%xs]: 
    {
      return qsort(%[a|a<-xs, a<=x]) + [x] +  qsort(%[b|b<-xs, b>x]);
    }
} 

$ print: .qsort([-7, 1.2, 30, 4]);
[ -7,1.2,4,30 ]
```

또한 디코드 구문은 0.4 버전부터 매칭 패턴에 사용자 정의 함수를 돌입할 수 있게 되었는데, 간단한 업그레이드였으나 효과는 매우 좋아서, xml 모듈과 json 모듈을 참고해보면 알겠지만 xml, json과 같은 netsted되어있는 구조를 수십 라인 만으로 간단히 처리할 수 있다.

간단한 예로 만일 아래와 같은 형식의 스트링이 있다치자면 str = " \[1, \[2\], 3 \] "

이것을 읽어서 \[ 1, \[2\], 3 \] 과 같은 리스트로 변경하는 것을 생각해보자. (원본 스트링을 eval 한다는 식의 변칙말고 정석대로 디코딩한다 생각하자)

이것을 기존의 (개선되기 전의) decode 구문으로 파싱하려 시도할 때,

```
def.decode tolist(str)
{
	case '[', %body, ']':
		{
			ret = tolist(body);
			if type.is_tuple(ret): 
				return ret.list(); 
			return [ ret ];
		}
	case %head, ',', %tail:
		{
			h = tolist(head);			
			t = tolist(tail);
			if type.ist_tuple(t) {
				t = t.list();
			}

			return t.push_front(h);
		}
	case %value = r'[0-9]+':
		{
			return value.integer();
		}
}
```

와 같이 시도해 볼 수 있다. 이 때 프로그래머는 body에 \[ \] 쌍이 맡게 body는 "1, \[2\], 3" 이 대입되기를 바랬을텐데 실제로는 body에 "1, \[2" 이 대입되고 (가장 먼저 나타나는 것을 매치하니) 나머지는 매치되지 않아, 첫번째 것에서는 매치를 실패하고 두번째로 넘어가서 head에 "\[1" 이 taild에 ", \[2\], 3\]" 이 매치되서 엉망이된다.

이때 위 구문을

```
using util.match;

def.decode tolist(str)
{
	case '[', %body = match.bracket, ']': 
		{
			ret = tolist(body);
			if type.is_tuple(ret): 
				return ret.list(); 
			return [ ret ];
		}
	case %head = match.comma, ',', %tail:
		{
			h = tolist(head);			
			t = tolist(tail);
			if type.ist_tuple(t) {
				t = t.list();
			}

			return t.push_front(h);
		}
	case %value = r'[0-9]+':
		{
			return value.integer();
		}
}
```

와 같이 match.bracket라는 함수를 이용해 match하게 변경해보면, match.bracket에게 decode구문은 "1, \[2\], 3\]" 라는 스트링을 전달해 준다. (맨 앞의 "\["은 앞에서 매치됐으니 제외하고) 그러면 이 함수는 이 안에서 중첩에 맞게 "1, \[2\], 3" 까지를 매치시켜서 리턴하고 남은 영역을 decode구문에게 알려준다. 그러면 decode는 남은 "\]"을 매치시켜 첫번째 매치구문이 성공하고, body에는 "1, \[2\], 3"이 입력된다. 이러면 action code로 들어가서 body를 재귀호출 하게 되는데 이러면 두번째 매치 구문이 시도되서 head에 "1"이 tail에 "\[2\], 3"이 매치되서 다시 되돌고 되돌아서.. (의도한 대로 딱딱 끊어져서) 최종적으로 \[ 1, \[2\], 3 \] 과 같은 리스트로 생성된다.

참고로 위에서 match.comma는 입력이 "\[1 , 2\], 3" 일때 head에 "\[1", 이 들어가지 않고 "\[1, 2\]"이 들어가도록 (\[ \] 쌍의 밖에 있는 쉼표와 매치되도록) 해주는 사용자 정의함수이다.

이처럼 오르카는 스트링을 유연하게 처리할 수 있고, 부수효과 없이 함수형 처리도 할 수 있다.

함수와 객체
======

함수
-----

일단 편의상 함수라 먼저 말하고, 멤버변수가 없는 객체를 설명하고자 한다. (다시 말해 말만 함수이지 맴버 변수가 없는 객체인 것이다)

함수를 선언하려면

```
def name {
  statement_list
}
```

와 같은 형식으로 선언한다.

예를 들어 두 값을 더하는 간단한 함수 add는

```
def add(a, b) {
    return a + b;
}
```

print: my.add(10, 20);

은 30을 출력한다.

가변인자가 필요할 때는 선언 시

```
def sum_all(…argv) {
    sum = 0;
    for a in argv {
        sum += a;
	}

	return sum;
}

print: my.sum_all(1,2,3);
6
```

과 같이 할 수 있다. …argv 는 가변인자를 받겠다는 의미이며, 받은 가변인자는 argv 리스트로 넘겨받는다. …argv 는 함수 선언의 다른 파라미터와 섞여 사용될 수 있으나 가장 마지막에 와야 한다. 즉, def (a, …b, c) 는 안되고, def (a, b, …c) 는 된다는 의미이다.

객체
-----

### 객체 정의

먼저 위의 함수란 것은 사실 객체를 하나 생성한 것이다. 그렇다면 멤버변수가 있는 그럴듯한 객체를 하나 만들어보자

```
def counter {
    def c;

    def inc {
        owner.c += 1;
    }
    
    def dec {
        owner.c -= 1;
    }
    
    my.c = 0;
}

foo = my.counter.clone();
foo();
print: foo.c;
foo.inc();
print: foo.c;
foo.dec();
print: foo.c;
```

위의 예제는 0, 1, 0을 차례대로 출력한다. 먼저 기본 클래스인 counter를 정의하고 그 안의 멤버변수로 c를, 함수로 init, inc, dec를 정의했다. 그런데, 보다시피 사실 함수나 객체나 def { } 로 정의한다. 왜냐면 정말 전부다 객체니까.

위에서 선언된 모든 것들 counter, c, init, inc, dec는 모두 독립된 하나의 객체들이다. 이것들이 멤버변수, 멤버함수처럼 동작하기 위해서는 서로의 정의된 “관계”에 의해서 억세스 가능한다.

Inc, dec 입장에서는 counter란 자신을 소유하고 있는 객체로서 owner로 접근 가능하다. owner.c += 1 이란 것은 자신을 소유한 객체의 c란 멤버를 1만큼 증가시키라는 의미이다.

counter또한 my.c = 0 이라는 코드를 포함하고 있는데, foo() 로 실행하게 되면 해당 코드가 실행된다. counter자신에 속한 c를 0으로 초기화 하기 위해 my를 사용했다. (이것은 python의 self라 생각해도 된다). 만일 c = 0 이라고만 했다면 지역변수를 초기화 하는 것으로 생각했을 것이다.

그러니까 오르카가 다른 객체지향 언어와 다른 것은 이런 억세스 관계도에서 보다 엄밀하게 객체를 추구한 점인데,

사실,

```
class counter:
  def __init__(self):
    self.c = 0;

  def inc(self):
    self.c += 1;

  def dec(self):
    self.c -= 1;
```

파이썬으로는 위와 같이 할 수 있겠는데 이런 방식은 익숙하긴 하지만 수많은 가정을 담고 있다. 이런 전통적인 방식은 객체와 함수를 분리하게 만들어 미니멀하고 아토믹한 특징을 사라지게 만든다. (헉, 이건 대체 무슨소리람… ㅠ_ㅠ). 다시 말하자면, inc 입장에서 self란 것이 자신을 의미하지 않고 클래스 본체를 의미하게 되는데 다시 생각해보니 이상하지 않은가?

즉 강하게 바인딩 되어 있다. 위의 python inc는 counter와만 엮여서 돌아가지만, orca의 inc는 독립된 객체고 현재 owner가 counter 일 뿐이기 때문에 clone을 통해 다른 객체에 삽입되어 동작할 수도 있다.

그리고, thread 를 띄우는 어떤 인터페이스를 생각해면 파이썬에선 언어 설계단계에서 객체를 받을 지 함수 객체를 받을지 인터페이스를 결정해야 하는데, 함수도 객체라면 이런 수고를 안해도 된다.

```
def foo {
    print: ‘hello, thread’;
}

thread.run(my.foo);
```

도 되고,

```
def foo {
    # some init code here
    …
    my.run();
    return;

    def run {
    
    
    }
    
    def blah {
    
    }
}

Thread.run(my.foo);
```

와 같이 thread가 자신만의 멤버들을 유지하게 할 수 있다. (뭔가 일관성이 있지?)

사실 약간 설계사상적인 측면인데, 이런 식으로 최소한의 단일 객체들을 선언할 수 있고 이것들이 owner, my, parent, caller 등으로 연결되어 동작되어 런타임 시 동적으로 상속가능하고 클래스 본체들이 필요에 따라 멤버가 변해갈 수도 있는 등등의 유연함을 원했다.

지금은 혼돈스럽겠지만.. 나는 이런식의 접근이 보다 일관성있고 확장가능하며 명확하다 생각했고, 이런 류의 접근 방식으로 돌아가는 언어가 아직 없었기에 새로 만들 생각을 한 것이다. 이의 유용성은 차차 보여주겠다.

일단 현 시점에서 이해가 잘 안 된다면 일단은 python의 self대신 owner가 쓰인다고 생각하자. my가 아닌 owner인 이유는 상위 객체에 속한 멤버이기 때문이다. 내 함수(객체) 내의 멤버가 아니라.

### my, owner 축약식

my, owner가 의외로 치기 성가시고, 한눈에 안 들어오기 때문에 간축형을 지원한다. . 은 my. 를 의미하고, .. 은 owner. 를 의미한다. Shell의 현재, 부모 디렉토리 표식을 생각하면 된다.

이로서 위의 표현은

```
def counter {
    def c;

    def inc {
        ..c += 1;
    }
    
    def dec {
        ..c -= 1;
    }
    
    .c = 0;
}
```

로 다시 쓸 수 있다.

### 특수문자를 포함한 멤버참조

객체의 멤버를 정의할 때는 원칙적으로 특수문자가 없어야 하나, 특수문자를 포함한 멤버를 정의하고자 할 때는 따옴표를 주고 정의하고 참조할 수 있다.

```
def foo
{
  def ‘+’(rhs)
    {
      …
    }
}
```

위와 같은 방식으로 foo 에 ‘+’ 멤버를 정의할 수 있으며, 이를 참조할 때는 foo.’+’ 와 같이 사용할 수 있다.

실제로 operator 모듈은 다음과 같은 멤버를 가지고 있다.

```
$ operator.members;
{ '!=':!=,'%':%,'&&':&&,'*':*,'+':+,'-':-,'/':/,'<':<,'<=':<=,'==':==,'>':>,'>=':>=,'||':||, }
$ operator.'+'(3,4);
7
```

### one time initializer

입력값을 받아서 자신의 멤버 item에 리스트로 저장하는 함수를 생각해보면 간단하게는,

```
def foo(a)
{
	def item;

	if my.item == nil: 
		my.item = [];
	
	my.item.push_back(a);
}
```

와 같은 식으로 구현했었다. item의 특성을 선언단에서 지정해줄 수 없고 런타임에서 결정해주어야 했기 때문인데, 이런 형테의 구현을 간편하게 하기 위하여 one time initialize expression 을 도입하였다.

```
def name := expression
```

과 같은 형태로 쓰이며, expression의 값이 name 멤버에 대입되어 모듈이 로드된다. 이 구문은 모듈로드시 한번만 수행되며 런타임에는 수행되지 않는다.

우의 예제를 다시 쓰면 다음과 같다.

```
def foo(a)
{
	def item := [];
	my.item.push_back(a);
}
```

### name'string' 표현형식

date 객체를 예로들면, 2010-01-01 과 2011-04-03 일 사이의 날 수를 구하고 싶으면,

```
$ using date;
$ print: date.clone('2011-04-03') - date.clone('2010-01-01');
457
```

과 같이 실행하면 된다. 그런데, 많은경우 object\_name.clone('string') 의 표현이, date와 같이 일회성인 경우 타이핑하기 번거롭기도 하고 가독성도 떨어진다. 해서 object\_name'string' == object_name.clone('string') 과 동일한 의미를 같도록 하였다.

해서 date.clode('2011-04-03')은 date'2011-04-03' 과 같은 의미를 같는다. 해서 위의 표현은 다음과 같이 다시 쓸 수 있다.

```
$ date'2011-04-03' - date'2010-01-01';
457
```





상속
-----

객체를 상속하는 방법은

def derived : base { … }

같이 콜론 오른쪽에 부모 객체를 지정해 주면 된다. 이렇게 되면 Derived 객체내의 어떤 멤버를 참조하게 되었을 때, derived 객체내에 해당 name이 존재하지 않으면 base 객체에서 찾게 된다.

상속한 객체를 사용할 때는 clone 구문을 사용한다.

a = b.clone(10);

는 b 객체를 새로 생성하여 a 에 대입한다. C/C++의 new 와 같다 생각하면 된다.

b.clone()을 수행하면, b에 init 멤버가 있으면 객체 생성 후 b.init(10) 이 자동적으로 호출된다.

using
-----

using은 오르카 모듈을 적재하고 절대경로 없이 사용할 수 있도록 파서의 namespace에 추가하는 역할을 한다.

sample.orca 파일이

def foo { }

와 같이 있다면, foo를 호출하기 위해서는

$ using sample;

을 입력하면, 오르카는 sample.orca 를 찾아 필요하다면 컴파일 한 후 root 밑으로 집어넣는다. 이제 sample 객체의 foo를 호출하려면

$ root.sample.foo();

를 할 수도 있고, using 문을 통해서 sample이 namespace에 추가 되었기 때문에

$ sample.foo();

만을 입력해도 된다.

애초에 using 구문을 $ using sample.foo; $ foo();

와 같이 sample안의 특정 객체를 지정할 수도 있다. 이경우엔 오르카는 sample.orca를 적재하는 것 까지는 동일하게 동작하되, sample.foo를 namespace에 추가했기 때문에 바로 foo를 접근할 수 있게 된다.

참고로, sample.orca를 찾는 위치는 현재 디렉토리와 환경변수 ORCA_PATH로 지정된 위치를 탐색한다.

가상멤버
----

오르카의 객체 및 자료들은 가상의 멤버들을 가지고 있다. 만일 이 멤버들이 프로그래머에 의해 명시적으로 정의되었다면 그 정의를 따르지만, 정의되어 있지 않다면 사전정의된 방식으로 동작한다. 아래는 각 가상멤버들에 대한 설명이다. 가상멤버는 가독성과 구분을 위해 대문자로 표현했다.

### TYPE

type type은 객체의 형식을 나타내는 자료형으로, 객체의 형과 상속관계 검사를 일관성있게 처리하기 위해 도입되었다.

오르카의 변수나 상수에 대해 .TYPE 을 붙이면 이 자료의 형을 의미하게된다.

먼저 자료의 type 검사는 다음과 같이할 수 있다.


```
a = 1;
a.TYPE == 2.TYPE; 
```

위는 1의 타입과 2의 타입이 같은 지를 검사하는 구문인데, 정수형으로 같기 때문에 true가 리턴된다.

```
a.TYPE == type.int;
```

도 같은 결과를 얻는다.

```
a.TYPE != 2.TYPE;
```

는 반대로 false를 리턴한다.

type 간의 < 연산은 상속관계를 의미한다.

```
a.TYPE < b.TYPE;
```
위의 연산은 a가 b를 상속했으면 true, 아니면 false를 리턴한다.



object < object.TYPE < 연산은 인스턴스 관계를 의미한다.

```
a < b.TYPE
```
위 연산은 a가 b의 인스턴스인지를 알려준다.

### TYPENAME

TYPENAME은 자료의 type을 스트링 형태로 리턴한다. 형검사는 .TYPE 을 이용하지만 때에 따라 스트링으로 처리하고자 할 때는 이 멤버를 사용한다.

```
$ print: 1.TYPENAME;
int

$ print: r'regex'.TYPENAME;
regex

$ print: io.TYPENAME;
object io

$ print: [1,2,3].TYPENAME;
list
```

### STATIC_MEMBERS

이는 객체의 static member들을 map 형태로 구성하여 리턴한다. map형태라고 한 이유는, 실제 map이 아니라 map과 유사한 인터페이스를 제공하기 때문이다. 즉,

```
   def foo
   {
     static bar;
     def non_static;
   }

   a = my.foo.STATIC_MEMBERS;
   print: a;
   a['new_member'] = 1;
   print: a;
   print: my.foo.STATIC_MEMBERS;
   print: my.foo.new_member;
```

위 코드를 실행하면,

```
{ 'bar':nil }
{ 'bar':nil,'new_member':1 }
{ 'bar':nil,'new_member':1 }
1
```

의 결과가 출력되는데, 이와 같이 이 객체는 map과 인터페이스가 같지만, 그 내용을 변경하면 원본객체의 멤버들에도 변경이 가해진다.

STATIC_MEMBERS 는 has\_key, erase_key, keys, values, begin, last, end, find 인터페이스를 제공한다. begin, last, end, find 는 멤버들에 대한 반복자를 리턴한다.

### MEMBERS

STATIC_MEMBERS는 static 멤버들만 반환한다면, MEMBERS 는 static, non-static 멤버들을 모두 반환한다. 상세한 동작은 STATIC_MEMBERS 와 같다.

### PARENTS

PARENTS는 객체가 상속한 parents들을 리스트 형태로 반환한다. parents는 push\_back, pop\_back, push\_front, pop\_front, begin, end, last, find 인터페이스를 제공한다.

### ID

id는 객체가 힙상에 존재하는 경우라면 그 객체의 고유주소를 리턴한다.

```
$   print: 1.ID;
0

$    print: 'str'.ID;
167178248

$    print: io.ID;
166676848
```

예외
------

Exception 이 발생했을 때 이를 throw 할 수 있고, 그 구문은 기존의 C/C++ 의 방식과 같다. 단, 프로그래머의 편의를 위해 throw 하는 첫 번째 인자는 객체가 아니라 path name 이다.

무슨 소린고 하니, throw io.error.disconnected 와 같은 식으로 마치 모듈의 path 인 것처럼 던지게 되는데, 해당 io.error.disconnect 는 실제 존재하는 모듈이 아니고, 그냥 thorw 에서 던지는 계층있는 이름일 뿐이다. 이것을 받을 때는 catch io.error.disconnect 처럼 명시적으로 지정해 줄 수도 있고, catch io나 catch io.error 를 하여 앞쪽의 대분류가 맞아도 묵시적으로 catch가 가능하다.

따라서 아래와 같은 코드가 가능하다.

```
try {
    …
    throw io.diconn;
    …
    throw io.timeout;
    …
    throw app.input.invalid;
    …
}
catch io.timeout {
    print: ‘timeout’;
}
catch io.disconn {
    print: ‘disconnected’;
}
catch io {
    print: ‘general io exception’;
}
catch app {
    print: ‘application exception’;
}
catch {
    print: ‘unknown exception’;
}
finally {
    print: ‘finally is always called ’;
}
```

Pathname을 사용함으로서 보다 예외처리를 분류해서 할 수 있게 된다.

Throw 할 때는 두번째 인자부터는 파라미터로 전달된다. 바로 다음과 같이.

```
try {
    throw app.test <- 10, ‘test’;
}
catch app -> num, msg {
    print: num, msg;
}
```

catch 시에는 tag name 뒤에 콜론을 하나 붙인 후, 받고자 하는 파라미터 목록을 나열한다.

람다
-----

간단한 용도를 위해서 람다 객체도 지원하는데, 선언법은

lambda { statement_list } 와 같다.

이는 이름만 없을 뿐이지 모든 면에서 일반 오르카 객체와 동일하다. 자체적으로 멤버변수를 가질 수 있고, 생성되는 람다의 owner는 람다가 정의된 객체이다.

아래는 test_lambda.orca 에 있는 코드이다.

```
def for_each(list, functor) {
    for a in list {
        functor(a);
    }
}

my.for_each([1..10], lambda(...argv){ print(argv[0]); });

below is same with above statement

my.for_each: [1..10], lambda(...argv) {
    print: argv[0];
};
```

말했다시피 람다는 객체와 동일하기 때문에

```
$ a = lambda { print: ‘foo’; };
$ a();
foo
```

와 같이 대입이나 clone등 객체와 관계되는 모든 연산이 가능하다.

람다함수가 받는 인수는 argv 인데… 루비처럼 { var\_list | statement\_list } 방식으로 할까도 잠시 고민했으나, 함수 본체가 커진다면 지금 방식이 더 가독성이 좋겠다 싶고 일관성을 유지하고자 그대로 argv를 사용했다.

연산자 재정의
-------

연산자 재정의는 친숙한 복소수 객체에 대한 예를 들어보이며 설명하겠다. 아래는 테스트 소스인 test_operator.orca에 있는 복소수 객체의 정의와 그것의 연산자들을 재정의한 것이다.

```
def complex
   {
     def real;
     def img;

     def init(r, i) {
       ..real = r;
       ..img = i;
     }
       
     def '+'(rhs) {
       if owner.type == rhs {
           result = owner.clone(owner.real + rhs.real, owner.img + rhs.img);
		}
       else {
           result = owner.clone(owner.real + rhs, owner.img);
		}
       return result;
     }
       
     def '-'(rhs) {
       if owner.type == rhs {
           result = owner.clone(owner.real - rhs.real, owner.img - rhs.img);
		}
       else {
           result = owner.clone(owner.real - rhs, owner.img);
		}
       return result;
     }
       
     def '-rev'(lhs) {
       result = owner.clone(lhs - owner.real, -owner.img);
       return result;
     }
       
     def mag() {
       m = ..real * ..real + ..img * ..img;
       return m;
     }
       
     def '<'(rhs) {
       return ..mag() < rhs.mag();
     }
       
     def '=='(rhs) {
       return ..mag() == rhs.mag();
     }

　　def string() {
       return '${..real} + ${..img}j';
     }   
　} 
```

사칙연산은 ‘+’, ‘-‘, ‘*’, ‘/’ 로 되어있고, 파라미터는 오른쪽에 위치하는 인수이다. 비교 연산자의 경우 ‘==’, ‘<’만 정의하면 ‘!=’, ‘<=’, ‘>’, ‘>=’는 두 개를 조합해서 해결해준다.

연산자 오버로딩 함수로서 ‘.’, ‘.$’, ‘.=’이 추가되었다.

먼저 .은 어떤 객체 a에서 멤버 b를 요청할 때, 만일 b가 멤버중에 속하지 않으면 (자신 뿐만 아니라 부모 객체에도 없으면) .이 호출된다. 파라미터는 요청되는 멤버의 이름이다.

```
def day_of_month
{
	def ‘.’(name)
	{
		decode(name)
		{
		'January' -> return 31;
		'Febuary' -> return 28;
		'March' -> return 31;
		'April' -> return 30;
		'May' -> return 31;
		'June' -> return 30;
		'July' -> return 31;
		'August' -> return 31;
		'September' -> return 30;
		'October' -> return 31;
		'November' -> return 30;
		'December' -> return 31;
		}		

		throw orca.name <- name + ' not found';
	}
}

$ p = my.day_of_month.clone();
$ print: p.April
30
$ print: p.foo
uncaugted exception: orca.name foo not found
recent call-stack trace
>> operator_get (internal 0)
>> orcaRoot     (internal 0)
```

보기와 같이 p.April을 요청하면 .attr('April') 가 호출되었다.

.=은 어떤 객체 a의 멤버 b에 어떤 값을 대입할 때, 만일 b란 이름의 멤버가 존재하지 않으면 .=이 호출된다.

.=(name, obj는ect) 와 같은 형태로서

a.b = 10; 이 란 문장이 있을 때 a가 .=을 재정의 했고, b란 멤버가 없으면 .=('b', 10) 이 호출된다.

.$ 는 좀 특이한데 만일 이 함수가 재정의 되지 않으면 객체를 참조할 때 .만이 호출되지만 만일 재정의 됐다치면,

어떤 객체 a에서 멤버를 참조할 때, a.b.c 이면 먼저 .('b')가 호출되지만 a.b 이면 .$('b')가 호출된다.

참조하는 멤버가 객체 path 표현식의 가장 마지막일때만 .$가 호출된다.

굳이 이것을 구분한 이유는 remote 객체 억세스를 위한 것이 었는데, remotec 모듈의 소스를 보면 이를 이용해서 리모트 머신 a의 root.b.c 를 참조할 때, a.b.c 를 사용하면 말단의 c 만 가져오게 했다. (만일 .만 있다면 a.b 하는 순간 b 전체가 이쪽으로 올 것이다. 필요한 것은 a.b 밑의 c만 필요한 상황에서...)

추가로 인덱싱 연산자도 재정의 할 수 있다. ‘\[\]’ 와 ‘\[\]=’ 이 그것이다. 만일 obj 가 \[\] 와 \[\]= 을 재정의 했다면,

a = obj\[b\] 는 a = obj.’\[\]’(b) 가 호출되고, obj\[b\] = c 는 obj.’\[\]’(b, c) 가 호출된다.

이 두 연산자는 객체를 리스트나, 맵과 같은 인터페이스로 다루기 위해 사용된다.

재정의된 연산자는 객체가 왼쪽에 있을 때 적용되데, 오른쪽에 있더라도 왼쪽에 있는 객체가 연산자가 재정의되지 않았다면 적용된다. 즉, obj 가 + 연산자가 재정의된 객체라 할때,

obj + 1 은 obj.'+'(1) 이 호출되는데 1 + obj 의 경우도 오르카가 알아서 obj.'+'(1) 을 호출해준다. 단, obj_b 가 '+'연산자를 정의했다면.

obj + obj\_b 는 obj.'+'(obj\_b) 를 호출하지만, obj\_b + obj 은 obj\_b.'+'(obj) 를 호출한다. 좌측 우선이되 적용되지 않고 교환법칙이 성립하는 연산자이면 우측 객체의 연산자를 사용한다.

단, -, / 연산자는 교환법칙이 성립하지 않는다.

obj - 1 은 obj.'-'(1) 이 호출되지만 1 - obj 은 obj.'-rev'(1) 가 호출된다. -rev 객체에서 순서를 바꾼 후 처리하게 구현하면 된다.





체널 객체
--------

오르카에는 ->, <- 연산자도 존재한다. 이 연산자는 해당 객체에 ->, <- 가 재정의 되어 있으면 실행된다. -> 는 채널 아웃 연산자로 해당 객체에서 데이터를 뽑아낼 수 있으면 해당 값이 오른쪽 변수에 대입된다. 리스트의 경우는 아이템의 가장 왼쪽부터 (즉, pop_front)  빼서 대입시킨다.

튜플은 pop_front 가 없기 때문에 뒤에서부터 빼내며, 아래와 같은 예제였다면 b에는 10이 대입된다.

```
$ a = [1..10];
[ 1,2,3,4,5,6,7,8,9,10 ]
$ a -> b;
1
$ a;
[ 2,3,4,5,6,7,8,9,10 ]
$ b;
1
```

<- 은 해당 객체에 오른쪽 파라미터를 대입시키는 채널인 연산자이다.

동일하게 빈리스트에 아래와 같이 실행할 수 있다.

```
$ a = [,];
[  ]
$ a<-1;
[ 1 ]
$ a<-2;
[ 1,2 ]
$ a;
[ 1,2 ]
```



여기까지만 보면 채널은 단순한 push, pop 인터페이스라 생각할 수 있으나 근본적인 차이가 있다. select 구문에서 채널아웃으로 채널 객체를 기다리면 size() 를 실행해보고 (때문에 채널객체를 select 에서 쓰려면 size 가 멤버로 있어야 한다) 비어있으면 해당 객체를 기다린다. 이후 다른 쓰레드에서 해당 객체에 채널인으로 데이터를 추가하면 오르카 VM 이 기다리던 쓰레드에 통지를 해주고 select 에서 계속 진행할 수 있게 된다.

즉 위의 리스트, 튜플 만으로도 제한적인 sync queue 처럼 쓸 수 있다.상세한 내용과 예는 앞장의 select 를 참조하면 된다.

추가로, 채널인은 한가지 특징을 더 가지는데, 오르카 VM 이 특정 객체의 <- 연산자를 얻었을때 nil 이 리턴되면 채널인 될 구문을 실행하지 않고 다음으로 넘어간다.

C/C++ 의 경우 #ifdef 로 특정 디버그 출력을 아예 코드에서 제거할 수 있으나 그 외 나머지 언어들의 경우, 예를 들어 아래와 같은 로깅 구문이 있다 할때,

```
log(INFO, "result of foo: %s", foo());
```

로그 레벨을 ERROR 이상으로 올려 위 로그를 출력하고 싶지 않게 해도, 위 로그의 foo() 는 evaluate 되고 단지 출력이 되지 않을 뿐이다. 이는 의도하지 않은 부수효과도 낳을 수 있고 (만일 foo() 함수가 외부 변수를 변경했다면), foo() 가 실행되는 오버헤드가 존재한다.

오르카의 로그 라이브러리는 채널을 이용해서 구현했다.  예를 들어 로그를 아래와 같이 출력하면,

```
using log;
log.tcp(false);
  
log <- 'log print';
log.tcp <- 'log.tcp print';
log.tcp.socket <- 'log.tcp.socket print';
log.udp <- 'log.udp print';
```

log 는 기본적으로 켜져 있으나, log.tcp 는 껐기 때문에 log print, log.udp print 만 출력된다. log.tcp 이하의 것들은 오른쪽 채널인 데이터를 구성하는 부분을 VM에서 지나쳐서 다음 구문으로 가기 때문에 오버헤드, 부수효과가 나타나지 않는다. 



폴더 객체
------

객체의 내용이 커지면 모듈화의 필요성이 생긴다.
파이썬의 경우 폴더에 __init__.py 의 존재 여부로 결정하고, golang 의 경우 package 정의로 구분하나 오르카에서는 좀 더 일반적이 직관적인 방식으로 정의하였다.

특정 폴더의 이름이 .orca 확장자를 가지면 해당 폴더는 오르카 객체로 인식된다. 그리고 해당 폴더 안의 orca 파일들은 해당 객체의 멤버로 정의된다. 만일 이 폴더객체에 실행 코드가 필요한 경우 해당 폴더객체에 CODE.orca (오르카에서 가상 멤버는 대문자로 정의함을 기억하라) 로 정의하면 별도의 CODE 라는 멤버가 생기는게 아니라 이 폴더 객체의 실행코드가 된다. 

먼저 아래와 같이 sample.orca 라는 폴더에서 아래와 같은 파일을 정의해 보자.


```
~$ cd sample.orca/
~/sample.orca$ ls *.orca
CODE.orca  bar.orca  foo.orca

~/sample.orca$ cat CODE.orca

print: "I'm %s" % my.NAME;
print: "My members: ", my.MEMBERS;

for k, v in my.MEMBERS {
        v();
}
~/sample.orca$ cat foo.orca
print: "I'm foo";
~/sample.orca$ cat bar.orca
print: "I'm bar";

```


sample.orca 를 실행하면 CODE.orca 가 실행되며 sample.orca 의 멤버들을 출력, 실행해주는 결과이다.

```
~$ orca sample.orca
I'm sample
My members: { 'bar':<bar - 0x1f20f50>,'foo':<foo - 0x1f220a0> }
I'm bar
I'm foo
```

orca 의 lib 폴더를 보면 이런식으로 다단계의 폴더 오브젝트들이 정의되어있는 것을 볼 수 있다.







특수 객체
=====

Native 객체
---------

오르카의 장점 중 하나가 Native Module을 쉽게 작성할 수 있다는 점이다.

orcaFile.h를 보면 아래와 같은데 일단 소스를 한번 쭈욱 보자.

```
class orcaFile : public orcaObject 
{
public:
    orcaFile(void* vp) : m_fp(NULL) { }

    orcaFile() : m_fp(NULL)
    {
        set_name("file");
    
        insert_native_function("open", (object_fp)&orcaFile::ex_open);
        insert_native_function("close", (object_fp)&orcaFile::ex_close);
        insert_native_function("read", (object_fp)&orcaFile::ex_read);
        insert_native_function("write", (object_fp)&orcaFile::ex_write);
    }
    
    ~orcaFile() {
        if (m_fp) {
            fclose(m_fp);
        }
    }
    
    orcaObject* v_clone() {
        orcaFile* fp = new orcaFile(NULL);
        return fp;
    }
    
    orcaData ex_open(orcaVM* vm, int n) 
    {
        if (n<1) {
            return NIL;
        }
    
        string& name = vm->get_param(0).String();
    
        string mode;
        if (is(vm->get_param(1))) 
            mode = "rw";
        else
            mode = vm->get_param(1).String();
    
        if (m_fp != NULL) {
            fclose(m_fp);
        }
    
        m_fp = fopen(name.c_str(), mode.c_str());
        if (m_fp == NULL) {
            throw orcaException("io.file.handle", "invalide file handle");
        }
    
        fseek(m_fp, 0, SEEK_END);
        m_size = ftell(m_fp);
        fseek(m_fp, 0, SEEK_SET);
    
        return NIL;
    }
    
    orcaData ex_close(orcaVM* vm, int n) 
    {
        if (m_fp != NULL) {
            fclose(m_fp);
            m_fp = NULL;
        }
    
        return NIL;
    }
    
    orcaData ex_read(orcaVM* vm, int n) 
    {
        if (m_fp == NULL) {
            return NIL;
        }
    
        string s;
        s.resize(m_size);
    
        fread(&s[0], 1, m_size, m_fp);
        s.resize(strlen(&s[0]));
    
        return s;
    }
    
    orcaData ex_write(orcaVM* vm, int n) 
    {
        string& in = vm->get_param(0).String();
    
        if (m_fp == NULL) {
            return NIL;
        }
    
        return (int)fwrite(in.c_str(), 1, in.length()+1, m_fp);
    }

private:
    FILE* m_fp;
    int m_size;
}; 
```

native function call 은 어느 언어든지 지원하지만, file 객체를 이렇게 간단하게 만들기는 쉽지 않을 듯 하다. 왜냐면, 다른 언어들은 function 기반인데반해, orca는 함수마저도 객체다 보니 함수를 확장하는 것이나 객체를 확장하는 것이나 같은 의미이기 때문이다.

즉, 위의 소스와 같이 orca내의 file에 대응하는 orcaObject 클래스를 똑같이 구성할 수 있다. 물론 파라미터 패싱방법이 다르고 생성자에서 함수를 등록해주는 부가적인 작업이 필요하긴 하지만..

추가적으로 소스의 corelib 밑의 다른 파일들을 살펴봐도 좋고, orcaList, orcaTuple 등을 구경해도 재미있다. orcaList는 stl::list로, orcaTuple은 stl::vector로 구성되어 있다.

단, 위의 파일들은 언어자체에 내장되어 있는 라이브러리이고, dll, so 를 만들어 사용하려면 한 단계를 더 걸쳐야 하는데, sample.dll 혹은 libsample.so 란 이름의 dll을 구성했다면, 내부에 extern “C” void* get_sample() 함수를 정의하고, orcaObject* 를 생성해서 해당 객체를 리턴하게 하면 된다. 이러면 앞절에서 서술한 using sample “cpp”로 모듈을 로드할 수 있다.

```
#include "stdafx.h"
#include "sample.h"

extern "C" SAMPLE_API void samplefoo()
{
    printf("foo called\n");
}

class sample : public orcaObject
{
public: 
    orcaData operator()(orcaVM* vm, int param_n) {
        printf("sample called\n");

        int a, b;
        a=vm->get_param(0).Integer();
        b=vm->get_param(1).Integer();
    
        return a + b;
    }
};

extern "C" SAMPLE_API void* get_sample() 
{
    sample* sp = new sample();
    return sp;
}
```

이건 프로젝트에 포함된 windows용 dll 제작 소스인데, get_sample은 새로운 orcaObject* sample을 리턴하게 되어있다.

sample 클래의 code 부분은 void operator() 로 정의할 수 있는데, 첫번째, 두번째 파라미터를 integer로 받아서 더한 후 스택에 push하면 두 값을 더하는 초간단 예제가 구성된다. Sample 객체 자체를 실행하지 말고 sample객체에 다른 객체를 삽입하려면,

그것이 C native 함수라면 앞의 orcaFile.h 의 방식대로 등로하면 되고, 독립된 오르카 객체를 추가하길 원하면 orcaObject로 해당 객체를 생성한 후 insert\_static이나 insert\_member 로 등록하면 되는데, (insert_static 은 스태틱 멤버로 등록)

orcaIO.h 가 해당 케이스의 좋은 예이다. 해당 파일의 일부만을 가져오면

```
class orcaIO : public orcaObject 
{
public:

    class ex_print : public orcaObject 
    {
    public:
        virtual orcaData operator()(orcaVM* vm, int n) {
            string str;
            for (int i=0; i<n; i++)
				get_param(i).to_str(vm, str);
    
            str += "\n";
    
            cout << str;
    
            return NIL;
        }
    };
    
    orcaIO() 
    {
        set_name("io");
        insert_static("print", new ex_print());
    }
}; 
```

위와 같이 io 밑에 print라는 객체를 생성하고 삽입시켰다. 실제 orca의 io 객체는 이렇게 구현되어 있다.

등록하는 방법이 여럿이라 오히려 햇갈리는데, 이 확장 부분에 대한 설명은 차후 다시 보강하겠다.

parse 객체
--------

오르카는 user define statement 를 보다 유연하게 지원하기 위해 내부에 LALR(1) 파서를 내장하고 있다. 해서 오르카를 사용하여 새로운 구문분석기를 매우 쉽게 구현할 수 있다.

기본적인 동작방식은 bison (혹은 yacc) 의 BNF 표기방식과 같다. 단, lexical anayser 가 내장되어 표현된다.

아래의 calc 객체는 간단한 사칙연산기를 parse 구문으로 구현한 것이다.

```
def.parse calc(str)
   {
       stmt : stmt '+' mul
                   lambda (...argv) {
                       return argv[0] + argv[2];
                   }
           | stmt '-' mul
                   lambda (...argv) {
                       return argv[0] - argv[2];
                   }
           | mul
                   lambda (...argv) {
                       return argv[0];
                   }
           ;

       mul : mul '*' number
                   lambda (...argv) {
                       return argv[0] * argv[2];
                   }
           |  mul '/' number 
                   lambda (...argv) {
                       return argv[0] / argv[2];
                   }
           | number
                   lambda (...argv) {
                       return argv[0];
                   }  
           ; 
       
       number : r'[0-9]+' 
                   lambda (...argv) {
                       return argv[0].integer(); 
                   } 
           ;
       
       nil : r'[ \t\r\n\]+'
    ;
}
```

이와 같이 구성한 후, my.calc('3+4*2') 와 같이 실행하면 11이 출력된다.

이 부분은 BNF와 파싱에 대한 사전 지식이 있어야 완벽하게 이해할 수 있다. 때문에 parse 구문을 이용하여, EDSL 이나 간단한 프로그래밍 언어를 만드는 방법을 추후에 따로 연재하겠다.

여기서는 bison과 다른 점 위주로 간단히 설명하겠다.

구문안의 스트링과 정규표현식은 터미널을 의미하는데, 오르카는 구문안의 터미널들을 사용하여 입력 스트링에서 토큰들을 알아서 분리하게된다. 문법중 nil : r'\[ \\t\\r\\n\]+' 의 경우, 왼쪽의 nil은 오른쪽의 터미널들은 사용하지 않고 버리겠다는 의미이다. 문법이 매칭되면 오른쪽의 람다함수가 실행되는데, 입력값은 매칭되는 노드의 값들을 argv 로 받게되며 리턴값은 새로 구성되는 논터미널의 값으로 등록된다.

설명의 편의성을 위해 간단한 예제를 사용했는데, 오르카 라이브러리들 중 lisp.orca를 보면 common lisp 이 parse 구문으로 구현되어 있는 것을 확인해 볼 수 있다.

문맥 확장 객체 (Context Extended Object)
------

문맥 확장 객체는 오르카의 언어 중간에서 사용자가 정의한 함수가 해당 구역의 코드를 컴파일하고실행하는 것을 의미한다. 이 구문을 통해서 오르카 언어 내부에 사용자가 정의한 DSL(Domain Specific Language)을 내장할 수 있다.

가장 간단한 예로, 다음의 예를 먼저 보고 설명한다.

```
a = lambda.cpp(msg){
  // this is cpp code
  cout << "hello, " << msg.String() << endl;
};

a('world');
```

위의 코드는 hello, world를 출력하는데, lambda.cpp{ ... } 로 정의된 객체의 내부 코드가 CPP 언어로 되어 있는것에 주의하자. def.name 나 lambda.name 가 선언되면 오르카는 name 모듈에게 statement 코드를 넘겨주고, 추가적으로 현재의 시간정보와 모듈의 유니크한 이름 을 넘겨준다.

즉, cpp(name, timestamp, source_code, pa체rams_name_list) 을 호출한다. cpp 모듈은 name 과 timestamp 정보를 사용하여, 컴파일된 확장 라이브러리가 있는지 혹은 소스코드가 확장라이브러리보다 나 중에 바뀌었는지 확인한 후 필요하면 이를 재컴파일하고 확장라이브러리를 열어서 실행한다.

마치 C언어 내부의 인라인 어셈블리어와 비슷하지만 결정적으로 다른것은, 특정 문법에 고정된 것이 아니라 사용자가 재정의 할 수 있도록 범용적인 구성으로 되어 있고, 연산의 결과가 객체로서 오르카에게 전달되도록 되기 때문에, 인라인 어셈블리어의 남용시 겪게 되는 가독성 저하 및 부수효과도 방지된다.

오르카에서 기본제공되는 문맥확장객체 처리 모듈은 html, json, cpp, lisp, sh 가 있다. 이들의 상세 내역은 모듈 레퍼런스에서 참조할 수 있고, 실제 내부 모습은 오르카 라이브러리 폴더에서 확인할 수 있다. 사용자는 이들의 방식과 유사하게 자신만의, DSL을 오르카 언어 내부에서 사용할 수 있다.

사용자는 별도로 처리하고자 하는 문맥 (html, cpp, etc...) 을 담당하는 모듈을 만들고 그 모듈에서 전달되는 문맥을 처리하면 된다. 
현재 문맥확장객체는 html 에 내장되어 템플릿 처리를 하는 부분에서 가장 잘 쓰이고 있으며, 그 예는 아래의 10분 가이드 문서의 마지막 장에서 확인할 수 있다.

문맥확장 객체를 처리하는 모듈은 아래와 같이 만든다. 설명을 위해 가장 간단한 예로 하겠다.

```
def txt(...argv) under root
{
    print(argv);

    def txt_object
    {
        def template := '';
        return my.template;
    }

    ret =  my.txt_object.clone();
    ret.template = argv[2];
    return ret;
}


def.txt txt_pure
{
    simple text object
}
```
text 문맥을 받아서, 실행하면 해당 텍스트를 그냥 리턴하는 txt 문맥처리 모듈을 만드는 예이다. 위에서 under root 는 해당 객체를 root 아래 등록한는 의미이다. (별도로 txt.orca 로 처리하는게 일반적이나 여기서는 간단한 설명을위해...)

위의 txt_pure 를 실행하면 아래와 같은 내용이 txt 에 전달된다.
argv[0] 는 정의된 오브젝트 이름 (여기서는 txt_pure)
argv[1] 은 파일의 최종 변경시각으로 결과물을 만드는 파서인 경우 재컴파일을 할지 여부를 판단하는데 사용된다. (인터프리터라면 상관없다)
argv[2] 는 처리할 문맥 정보이고
argv[3] 는 파라미터 (여기서는 사용하지 않았다)
argv[4] 는 안에 정의되어 있는 또다른 객체의 위치인데 나중에 설명하겠다.
```
( 'txt_pure',2019-05-04T19:20:06,'
    simple text object
',(  ),{  } )
```

이 정보를 사용하여 txt 모듈은 txt_object 를 clone 한 후 txt_object 의 template 멤버에 전달받은 txt 를 그냥 대입시켰다.
txt_object 는 실행하면 해당 template 을 리턴하는 일만 한다.

아래와 같은 코드를 실행하면 결과가 그 다음과 같다.
```
def.txt txt_pure
{
    simple text object
}

print: '#### txt_pure';
print: my.txt_pure.MEMBERS;
print: my.txt_pure();
```

```
#### txt_pure
{ 'template':'
    simple text object
' }

    simple text object
```


그런데 문맥확장객체는 해당 문맥의 객체안에 다른 객체를 포함할 수 있다. 위의 txt 문맥 안에 오르카 문법의 객체를 또 정의할 수 있다.
아래와 같이 정의하면
```
def.txt txt_hibrid
{
    simple text object

    def object_under_txt
    {
        ret = 'this is orca object under txt\n';
        ret += 'my owners template: %s' % owner.template;
        return ret;
    }
}


print: '#### txt_hibrid';
print: my.txt_hibrid.MEMBERS;
print: my.txt_hibrid();
print: my.txt_hibrid.object_under_txt();
```

아래와 같은 실행결과를 얻는다.
```
#### txt_hibrid
{ 'object_under_txt':<object_under_txt - 0x55996be27cb0>,'template':'
    simple text object







' }

    simple text object








this is orca object under txt
my owners template: 
    simple text object
```


txt_hibrid 객체안에 object_under_txt 를 정의했는데, 실제 최종 객체를 보면 정말 object_under_txt 가 멤버로 존재하고, 실행가능하다는 것을 알 수 있다.

그런데, txt 모듈에서는 외부 객체를 처리하는 코드가 별도로 있지 않았었다.
txt_hibrid 를 실행하면 txt 모듈에는 아래와 같은 파라미터가 전달되는데,
```
( 'txt_hibrid',2019-05-04T19:20:06,'
    simple text object







',(  ),{ 'object_under_txt':3 } )
```

보면 순수 txt 문맥만 전달되고 그 안의 다른 문맥으로 정의되어 있는 (def 로 시작하는) 구문은 빠져 있는 것을 알 수 있다.
이것은 오르카 파서가 별도로 스스로 처리하거나 해당 문맥의 모듈로 넘겨 객체를 만들고 나중에 멤버로 추가해준다. 멤버로 추가할 내역이 가장 마지막 파라미터로 추가될 멤버이름과 해당 멤버가 몇번째 줄에서 정의되어 있는지를 맵으로 전달해 준다.

오르카 객체는 owner, member 로 느슨하게 연결되어 있기 때문에 할 수 있는 방법이다. 이런 방식의 가장 유용한 예가 sonar 와 html 처리이다.





