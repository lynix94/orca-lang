Orca Programming Language Tutorial
==================================

written by Lee, Ki-Yeul (kiyeul.lee@gmail.com)  


Table of Contents
=================

0.  [What's this](#what's-this)
1.  [start](#start)
2.  [Data types](#data-types)
    1.  [local variable](#local-variable)
    2.  [integer](#integer)
    3.  [real number](#float)
    4.  [string](#string)
    5.  [regular expression](#regular-expression)
    6.  [list](#list)
    7.  [tuple](#tuple)
    8.  [map](#map)
    9.  [set builder form list](#set-builder-form-list)
    10.  [iterator](#iterator)
3.  [control statement](#control-statement)
    1.  [if](#if)
    2.  [while](#while)
    3.  [do while](#do_while)
    4.  [for](#for)
    5.  [switch](#switch)
    6.  [select](#select)
    7.  [scope object](#scope)
    8.  [parallel do](#parallel-do)
    9.  [parallel call](#parallel-call)
    10.  [parallel for](#parallel-for)
    11.  [decode statement](#decode-statement)
        1.  [string match](#string-match)
        2.  [regular expression match](#regular-expression-match)
        3.  [list match](#list-match)
        4.  [decode function](#decode-function)
4.  [function and object](#function-and-object)
    1.  [function](#function)
    2.  [object](#object)
        1.  [object define](#object-define)
        2.  [simple notation of my, owner](#simple-notation-of-my,-owner)
        3.  [special character member](#special-character-member))
        4.  [one time initializer](#one-time-initializer))
        5.  [name'string' object](#name'string'-object)
    3.  [inherit](#inherit)
    4.  [using](#using)
    5.  [virtual member](#virtual-member)
        1.  [TYPE](#TYPE)
        2.  [TYPENAME](#TYPENAME)
        3.  [STATIC_MEMBERS](#STATIC_MEMBERS)
        4.  [MEMBERS](#MEMBERS)
        5.  [PARENTS](#PARENTS)
        6.  [ID](#ID)
    6.  [excpetion](#exception)
    7.  [lambda](#lambda)
    8.  [operator overloading](#operator-overloading)
	9.  [channel object](#channel-object)
	10.  [folder object](#folder-object)
5.  [special object](#special-object)
    1.  [native object](#native-object)
    2.  [parse object](#parse-object)
    3.  [context extended object](#context-extended-object)

What's this
===========

This document is "simple" manual for orca programming language. You can get more information about orca by run and reading test vectors in orca project. (run it by ./orca tests/test.orca)

If you have any question, mail me (kiyeul.lee at gmail) or leave comment on sourceforge or Korean community board.

start
=====

Let's start traditional example. If you type like below,

```
shell> ./orca
```

Interpreter will be come out in console. Of course it is possible type like "./orca test.orca" or "./orca test" to compile & run source file directly. And type like below in the prompt of interpreter.

```
$ print('hello, world');
hello, world
```

It print 'hello, world' constant string. Funny thing is.. above statements could be written like this.

```
print: 'hello, world';
```

Because function\_name ( parameter\_list ) is same as function\_name : parameter\_list

in orca.

This expression is named 'simple call statement' its purpose is not only typing but also improving readability in lambda programming. ex, if there is "for\_each (items, lambda\_function)" function which apply lambda_function to all items of first parameter. Normal notation is like below,

```
for_each(list_a, lambda(...argv) { print(argv[0]);} );
```

This expression could not be read easily. But if we use simple call statement, it could be written like below

```
for_each: list_a, lambda(...argv) {
  print(argv[0]);
};
```

If lambda function is bigger, it should be more useful.

Data types
==========

local variable
--------------

Variables in function are managed as local variables. (It's located in Local stack of VM and reenterentable)

```
$ a = 10;
$ print: a;
10
$ a = 'hello';
$ print: a;
hello
```

First line in above code, set a as 10 and prints it. Then reset a as 'hello' and prints it again.

orca is dynamic type language. A type of a variable is changeable.

integer
-------

Orca supports integer data types and its basic operation. And It supports big number so upper limit is not existed.

```
$ print: 10000000000000000000000 * 33333333333333333333333333333;
333333333333333333333333333330000000000000000000000 
```

Integer has its internal member functions string() and float(). string() converts integer to string and float() convers integer to real number. string() can has format string as parameter.

```
$ print: 1.string();
1
$ print: 10.string('%010d');
0000000010
$ print: 30.float();
30
$
```

And you can write hexadecimal or Binary Integer by special prefix. 0x on hexadecimal and 0b

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

real number
-----------

It supports real number. precision is same as "double" in C/C++.

```
$ print: 1.0 / 3.0;
0.333333
```

Real number has its internal member functions string() and integer() which convert real number as string or integer.

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

string
------

String separator could be both of ' and ", and it supports escape character. And it supports, """ and ''' like python. both of them has same meaning but ''' recognize ${} expression but """ translate all as text itself.

String can contain expression in it (like ruby) It's form is ${ expression } Below is one example.

```
$ name = 'james';
$ print: 'hello, ${name}';
hello, james
```

String has \[\] operator.

```
$ 'hello, world'[0];
h
$ 'hello, world'[-1];
d
```

Minus index means access string backward.

```
$ 'hello, world'[0:5];
hello
```

Above one is an example of slicing operator, It makes new string which copied from 'from:to' range of original one.

```
$ 'hello, world'[2:0];
le
```

If from is bigger than to, it is reversed automatically.

```
$ 'hello, world'[0:5+];
hello,
```

If right part is '+]' (not '\]'), it takes last 'to' index item. So, if you reverse all string, you can try like this.

```
$ 'hello, world' [-1:0+];
dlrow, olleh
```

String supports operator + and *

\+ means string concatenation.
```
$ print: 'hello, ', + 'world';
hello, world

$ print: '3 + 4 = ' + 7
3 + 4 = 7
```

\* means repeat string n times.

```
$ print: "5 times" * 5;
5 times5 times5 times5 times5 times 
```

Currently, String provides length, find, find\_all, strip, lstrip, rstrip, integer, replace interfaces. And, at 0.4 release it supports hash, starts\_with, ends\_with, chomp, push\_back interfaces. Below simple examples may be enough for understanding. length() returns length of string.

```
$ print: "hello, world".length();
12
```

find() returns index which parameter string is found.

```
$ print: 'hello, world'.find('world');
7
```

find_all() find all positions and make result list of them.

```
$ print: 'hello, world'.find_all('o');
[ 4,8 ]
```

First parameter of find and find_all interface could be regular expression which will be described next chapter. And second, third parameters are acceptable which mean start, end index. string(), lstrip() and rstrip() interface work like below.

```
$ print: '"', '    hello,    '.rstrip() + '  world   '.strip() + ' ! '.lstrip(), '"';
"    hello,world! "

$ print: "123".integer() + 100;
223
```

integer() make string to integer.

```
$ print: '30.8'.float();
30.8
$ print: '30e14'.float();
3e+15
$           
```

float() make string to real number.

```
$ print: "hello, world".replace("world", "earth");
Hello, earth
```

first argument of replace could be regular expression. second and third arguments are range of replacement (string start, end index) hash(mod) make simple hash value (integer type). Its max value is INT_MAX but if there is mod value as parameter modulo result is return.

```
$ a = 'hello, world!';
$ print: a.hash();
1193
$ print: a.hash(100);
93
```

split(by, n) divides string by parameter and makes list which have been divided results. 'by' could be string or regular expression. n limits maximum count of split.

```
$ a = 'aaaa-bbbb-cccc-dddd';
$ print: a.splint('-');
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

string also provides starts\_with, ends\_with interface. Its naming is oriented from Java. but parameter could be regular expression.

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
$ 
```

lower() return string as lowercase upper() return string as uppercase.

```
$ 'Hello, World!'.upper();
HELLO, WORLD!
$ 'Hello, World!'.lower();
hello, world!
```

char(idx) interface return character of string at index of idx. But char(idx) return character code as number at index of idx

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

String constants can be rewritten with hexadecimal or binary string format. by just add h or b before string constants.

```
$ print: h'3031323334';
01234
$ print: b'01110011';
s
$ print: b'01110011 01110100';
st
```

string supports python style format string. It's made by overriding the % operator.

```
$ 'i: %d, f: %f, e: %e, s: %s' % (100, 12.34, 12.34, 'hello, world!');
i: 100, f: 12.340000, e: 1.234000e+01, s: hello, world!
```

Orca extends format string by using map type format. This spec is used in html module. If %{NAME} is in format string orca think last parameter is map and replace format by its 'NAME' value. 

So, below example prints 'hello, orca'.

```
print: 'hello, %{name}' % ({'name':'orca'});
```

map type format can be used with other format types. but map type format parameter should be passed only one and should be last. like below.

```
print: 'format i: %d, name: %{name}, f: %f, age: %{age}' % (10, 12.34, {'name':'orca', 'age':20});
```

above example prints for format i: 10, name: orca, f: 12.340000, age: 20



regular expression
------------------

To define regular expression, just attach r before constant string. r'\[0-9\]+' means regular expression for numbers.

Regular expression that orca provides is made by boost::regex library. So, you can get detail specification from boost regex docs. In this documents, just simple usages are mentioned. There are match, find and replace operations in regular expression.

First, match operation could be done like this.

```
str = '123abc456def';
if str == r'[0-9a-z]+' {
    print: 'matched';
}
```

Above example will print 'matched'. Match operation could be done by ==, != operator. In above str, if find interface is called like this.

```
$ print: str.find(r'[a-z]+[0-9+');
( 'abc456',3,9 )
```

Matched string('abc456'), start index, end index is come out.

```
$ print: str.find_all(r'[0-9]+[a-z]+');
[ ( '123abc', 0, 6), ( '456def', 6, 12) ]
```

Find_all finds all matched results and start, end index. And it makes list from founded results.

```
$ print: str.find_all(r'([0-9]+)[a-z]+');
[ ( ( '123abc',0,6 ),( '123',0,3 ) ),( ( '456def',6,12 ),( '456',6,9 ) ) ]
```

Subgroup is supported. if some part of regular expression is parented, that parts are found and added in tuples. You can detail spec. of subgroup in boost::regex docs.

Finally, replace operation is done like this.

```
$ print: str.replace(r'[0-9]+', '{{$0}}');
{{123}}abc{{456}}def
```

orca regular expression is done by same interfaces which are used in string object (==, !=, find, find_all, replace). And returns list & tuples directly (don't use additional match objects) It's simple & useful :)

list
----

List is sequence of items which are added or removed later.

```
$ a = [1,2,3,4,5];
$ print: a, ' ', a[0], ' ', a[-1];
[1,2,3,4,5] 1, 5
```

Of course, assignment and nested lists are possible.

```
$ a[1] = ['abc', 3];
$ print: a;
[1, ['abc', 3], 3, 4, 5]
$ print: a[1][0];
abc
```

Slicing is supported. slicing method is same as method of string.

list have internal member functions push\_front, pop\_front, push\_back and pop\_back  
push_front insert item to front of list  
pop_front remove item of list head  
push_back insert item to back of list  
pop_back remove item from back  
These four functions return modified list itself  

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

tuple() make new tuple which have same item of list.

```
$ a = [1..10];
$ print: a, a.tuple();
[ 1,2,3,4,5,6,7,8,9,10 ]( 1,2,3,4,5,6,7,8,9,10 )
```

size() return list length empty() returns true if list is empty. clear() clear list.

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

iter() is value based iterator. this interface return iterator which return value of list. piter(), first(), last() and end() are position based iterator. these specs are common on tuple and map.


iter() means first item of iterator and it return next value if next() is called. if it moves to end of list, then it raises orca.iter.end exception

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

 

piter returns an iterator whose position is previous of first item (if it calls next() it return first item position), first() returns the position of first item, last() returns the position of last item. end() means invalid position like c++ stl end. position iterators are can be check as equal or not. If position iterator is called, it returns the value of current position. And if it is called with parameter, It change the value of current position. These aspects are more useful than value based iterator. 
  

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

find(value) function find position which have value and return its iterator.

```
$ list = [1,2,3];
$ i = list.find(2);
$ print: i();
2
$ i.prev();
$ print: i();
1
```

list iterator have insert(), remove() interface. insert() insert new item in front of itself. remove() remove item which itself had pointed.

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

list and iterator have timestamp in it. So, if there is change in container (list, tuple and map). its old iterators are invalidated. So, if these iterators are used, exception occurs. list has sort interface which sort its internal items. If you call this interface without parameter, Default comparison is worked and items are sorted in increase order. If you pass compare function when you call sort, Sort use it as '<' operator.

```
$ a = [1,3,2,4,2];
[ 1,3,2,4,2 ]
$ a.sort();
[ 1,2,2,3,4 ]
$ print: a;
[ 1,2,2,3,4 ]
$ 
$ a.sort(lambda(...argv) { return argv[0] >= argv[1]; });
[ 4,3,2,2,1 ]
```

In above example, User pass >= lambda function as parameter so sorting has done with descending order.

tuple
-----

Tuple is almost same as list. but it has more efficient in random access. (It is made by vector in C++/STL) But interface of tuple is same as list.

```
$ a = ( 1, 3, 4 );
$ print: a,' ',a[1];
( 1, 3, 4 ) 3
```

tuple has its internal function push\_back and pop\_back. push\_back insert new item to back of tuple. pop\_front remove item from back

```
$ a = (1,2,3);
$ print: a.push_back(100);
( 1,2,3,100 )
$ print: a.pop_back();
( 1,2,3 )
```

list() make new list which have same items of tuple. length() return length of tuple empty() return true if tuple is empty. clear() initializes tuple.

```
$ a = (1..10);
$ print: a, a.list();
( 1,2,3,4,5,6,7,8,9,10 )\[ 1,2,3,4,5,6,7,8,9,10 \]
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


tuple provides iter(), piter(), first(), last(), end(), find() interfaces but insert() and remove() are not supported.

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



map
---

Map is key-value container like dictionary in ruby and python. or map in STL.

```
$ a = { "harry":100, "tom":20 };
$ print: a["harry"];
100
```

Map provides keys, values interfaces which returns list of keys or values. But maybe it will be changed as virtual object which points keys (or values) in map (like python 3.0) length() return length of map which means count of items. empty() return true if map is empty. clear() initializes map.

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

has\_key(val) return true if there are key value of 'val'. erase\_key(val) erase item whose key is 'val'

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

map also provides iter(), piter(), first(), last(), end() interface. map is sorted collection so if you iterate by next() you can get sorted result.

map is composed by key and value so you can get it directly with iter2() interface.

The return type is (key, value) tuple if you call iterator. If you want to get key or value use key() or value() interface.

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

Calling iterator with parameter means change the value of current position. In map it changes the value (not key of course) of map.

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


find() return iterator which points item that has same key value.

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

map also provides lower\_bound and upper\_bound. They are similar like find. find return end() if there are no item has same key but lower\_bound and upper\_bound return position could be inserted.

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

keys() return list which have keys of map. values() return list which have values of map.

```
$ a = { 1:'value 1', 'two':2, 'key3':[1,2,3] };
$ print: a.keys();
[ 1,'key3','two' ]
$ print: a.values();
[ 'value 1',[ 1,2,3 ],2 ]
```





set builder form list
---------------------

### Set builder form list will be deprecated. and list comprehension will be introduced instead for more readability

orca supports set builder form which is build up by lazy evaluation. Original set builder form which generates even number from between 1 and 10 is like this

\[x|x<-n, 1But it have to get some changes as programming notation. First n is not defined orca so source generator could be written as x<-1~10 directly. and to notify SBF (not normal list) '%' is placed in front of list.

So above SBF is written like this in orca.

```
$ print: %[x|x<- 1~10, x%2 == 0];
[2,4,6,8,10]
```

Let's see more detail..

```
%[x|x<- 1~10, x%2==0] have three part
```

First x before | is functional part. Which is final expression of generated inputs by right part. If we change SBF as %\[x-1|x<-1~10, x%2 == 0\], it prints odd number. Next x<-1~10 is generation part, it generates number between 1 and 10. Similarly, x <- -10~ generates number greater than -10 (it means unbounded number will generates, it's possible because of lazy evaluation) x<- ~100 generates numbers which is less than 100. Not only integer range form, List item or iterator object or other SBF list could be used. As an example,

%\[x|x<-\[1..10\], x%2 == 0\] makes same result. x<- (list object) means "all items in object". In this case it's a list constant but variables are also possible like x <- b. But this type of definition make list at one in run time, so it has initial overhead. As an example, if you define like this range form.

```
$ a = %[x|x<-1~100000000];
$ print: a[10];
11
```

It returns quickly but,

```
$ a = %[x|x<-[1..100000000]];
$ print: a[10];
```

In this case, it requires just 11th item but list definition in SBF make all list at one time so it resumes much time and memory. So, range form, another SBF and iterator object is more effective in lazy evaluation. And last part is condition. x%2 == 0 which check to all items. This part should be a boolean expression and could be multiple.

```
$ print: %[x|x<-1~10, x%2 == 0, x%3 == 0]
```

prints out \[6\]. first condition x%2 selects 2,4,6,8,10 and second condition x%3 select only 6. Generation part also could be multiple. See the below code.

```
$ print: %[(x,y)|x<-1~5, y<-3~5];
[ ( 1,3 ),( 1,4 ),( 1,5 ),( 2,3 ),( 2,4 ),( 2,5 ),( 3,3 ),( 3,4 ),( 3,5 ),( 4,3 ),( 4,4 ),( 4,5 ),( 5,3 ),( 5,4 ),( 5,5 ) ]
```

When x generates 1~5, y generates 3~5 each. You can add condition to this.

```
$ print: %[(x,y)|x<-1~5, y<-3~5, x==y];
[ ( 3,3 ),( 4,4 ),( 5,5 ) ]
$
```

It selects what x == y. so final result is like above.

Let's see more useful example that find prime number. First, define factor which returns exact divisors.

```
$ def factor(n)
* {
*   return %[x|x<-1~n, n%x==0];
* }
* 

$ print: .factor(100);
[ 1,2,4,5,10,20,25,50,100 ]
```

And second, define prime which prints out prime numbers between 1 and n like below,

```
def prime(n)
{
  return %[x|x<-1~n, ..factor(x) == [1, x]];
}
```

This function get n and calculate factors between 1 and n. Then check it has only 2 items (1 and itself) It is definition of prime number itself. Let's test it

```
$ print: .prime(100);
[ 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97 ]
$ 
```

It works well :) And then see another famous functional programming example. Quick sort.

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

Decode function qsort gets list and if list is empty just return. If list is not empty, cut off first item and assign it to x (this is pivot). Then reorder remaining items so that all the items with values less than pivot come before the pivot. while others come after the pivot. and recursively do qsort to moved item groups.

This is same as quick sort definition exactly.

range generator of Set builder form could be other data types (floating number or etc) Integer is decreased number so It has default increase/decrease step. (number 1) But, Floating number (and other data types) is not decreased number so, user add increase/decrease step on generator

You can write generator with step like this form. x <- START ~ END : STEP If START and END are integer type, STEP could be omitted and It's implicit value is 1.

below SBF generator floating number from 0 to 10 by 0.1 step.

```
$ a = %[x|x<- 0 ~ 10 : 0.1];
[ 0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5,5.1,5.2,5.3,5.4,5.5,5.6,5.7,5.8,5.9,6,6.1,6.2,6.3,6.4,6.5,6.6,6.7,6.8,6.9,7,7.1,7.2,7.3,7.4,7.5,7.6,7.7,7.8,7.9,8,8.1,8.2,8.3,8.4,8.5,8.6,8.7,8.8,8.9,9,9.1,9.2,9.3,9.4,9.5,9.6,9.7,9.8,9.9,10 ]
```

If set builder form list's length is infinite, orca prints it like below,

```
$ a = %[x|x<-1~];
[ 1,2,3,4,5,6,7,8,9,10, ... ]
```

In that case (infinite) size() interface return -1.

```
$ print: a.size()
-1
```

iterator
--------

Iterators of container have similar interface with STL. Rules of current implementation are like below.

*   If you want to move next item, call next() and it change its position and return itself or its value.
*   If you want to move prev item, call prev() and it change its position and return itself or its value.
*   If result of next and prev is out of range, next, prev raise orca.iter.end exception.
*   If you want value of item which iterator points out. call iterator. (like, value = it(); )
*   If you want change value of item which iterator points out. call iterator with parameters ( like, it(3) )
*   Iterator have operator\_eq, operator\_neq so they could be compared. (==, !=)
*   map iterator have operator_lt so it could be compared ( ==, !=, <, <=, >, >=)
*   If you access invalid iterator, orca.iter exception occurs.

And here are additional rules of container.

*   You can get iterator which points out first position by calling first()
*   next(), prev() can get integer parameter. next(2) means next(), next().
*   You can get iterator which points out last item by calling last().
*   You can get iterator which points out next of last position, call end() (real last position is end().before())
*   You can find item and get it's iterator by calling find()
*   If you want erase item. call erase() interface of iterator (but tuple iterator doesn¡¯t support)
*   If you want insert new item call insert() interface of iterator (but tuple and map doesn¡¯t support)
*   If order of container is changed, old iterators are invalid and exception occurs if they are referred.

control statement
=================

if
----

Structure of if statement is

if bool\_expression { statement\_list }

And it could exist that additional elif and else clauses.

while
-----

Structure of while statement is

while boolean\_expression { statement\_list }

This is worked like C/C++ while

```
a = sum = 0;
while a < 10 {
  sum  += a;
  a+=1;
}
```

Above example is sum all of 0 to 9.

do while
--------

Structure of do while statement is

do { stement\_list } while boolean\_expression

```
a = sum = 0;
do {
  sum += a;
  a += 1;
} while a < 10;
```

Above example makes same result (of while example)

for
---

The structure of for statement is

for a in b { statement_list }

b could be list, tuple and map. And iterator object and set builder form list are possible as b. a will be assigned all items in b in order, and statement_lists are excuted. Let's look at example.

```
sum = 0;
for a in [1..10] {
  sum += a;
}
```

Above example sums up 1 to 10. \[1..10\] generate list \[1,2,3,4,5,6,7,8,9,10\] and each item is assigned to a in order. And sum += a is executed every time. Iterator object could be used, iterator object is that have next() interface. Simple example is below

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

A switch statement is similar with other languages. It checks parameter and select same case. Below example prints 20.

Unlike C/C++, break is not required but fallthrough can be used to execute next case at same time.


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
The switch statement select case if result of == operator is true. So, in below example, regex and string can be same if string is matched to regex. So, this prints alphabet_only.

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
select statements get inspiration from go lang. It can wait channel, fd, timer and other kinds of channel objects. 
We will see about channel object later, Orca handle channel as object which have ->, <- operator. So, every object can be used on select statement if it has -> and <- operator.

Below is an example which use list and tuple.

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

a and b are empty so default is printed. default on select statement is selected if there is no possible channel out object.

Below is more complex example. lambda object pushes 100, 200, 300 to tuple b on every 0.1 second.

Select statement wait a or b until there are possible data to them. So, it gets item from tuple b and push it to result list.

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


Result is like below. We use tuple so -> operator return last item (tuple only support pop_back not pop_front) so 300, 200, 100 are pushed to result.

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

In this chapter we only saw the list, tuple but general channel object, socket, file and timer, ticker can be used.

You can see other examples on test_select.orca, test_timer.orca from test vectors.



scope object
------------

If object has scope\_start(0, scope\_end() interface, it could be used as scope statement. The structure of scope statement is like below

```
object {
  statement_list
}
```

In this case, before statement\_list is executed, object."{"() is called automatically. And after the execution of statement\_list is done object."}"() is called. And if there is exception throwing or return in statement\_list, object."}"() is called automatically.

As an example, If you make a mutex lock on some code area.

```
usign ipc;

def scope_mutex
{
    def mtx;

    def new {
        clone owner;
        ..mtx = new ipc.mutex;
    }

    def scope_start {
        ..mtx.lock();
    }

    def scope_end {
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

If you run fun(),

```
mtx."{"();
foo();
bar();
mtx."}"();
```

Will be executed in order. if there is exception throwing from foo(). bar() is not executed but mtx."}"() is called automatically. And in below case, mtx."}"() is called also.

```
mtx {
  foo();
  return;
}
```

This statement could be used to all pairing cases. likes making CS, resource open/close, timer start/end.. etc





parallel do
-----------

orca provides thread module for parallel processing already. But parallel programming by using thread API requires special caution in design level. If you change sequential program to parallel program, maybe main logic flow should be changed.

So, orca provides parallel statements for supporting easy parallel programming.

```
b = foo(a);
user_log ('result of foo: ${b}');
bar(b);
```

Think about above code, main logic executes foo and assign it's result to b. Then it call bar using b (which is result of foo()) In this case, bar(b) is depend on foo(a). so it must be sequential.  
But, bar(b) is not depend on result of user\_log('result of foo: ${b}'); So user\_log could be parallel executed. 

```
b = foo(a);
parallel do {
  user_log('result of foo: ${b}');
}
bar(b);
```

If you change code like above, Main thread runs just

```
b=foo(a);
bar(b);
```

And when foo(a) is done, additional sub thread is created and run statements in parallel do block. This is very useful and easy because sub thread in parallel do statements can access local variables of main thread. So, if you want make some block to be parallelized, just let them into parallel do statements. Then main thread will skip that parts.  
Here is another example

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
```

without parallel do: 999 ms, 599 us with parallel do: 399 us Like above, with parallel do, main thread is not blocked by time.sleep(1.0) So it can run down to sw.lap() more fast.

I recommend parallel do statements to IO bound job. Especially logging, async communication and etc. But in case of CPU bound job, maybe parallel for statement (which is in next chapter) is more useful.

parallel call
-----------
You can call function with parallel. If so, function is executed parallel.

Below is an example.

```
using time;

def foo
{
	time.sleep(1.0);
	print: "I'm foo";
}


parallel my.foo();
print: "maybe this will be shown faster";

```



parallel for
------------

parallel for a in input_list
{
  statement_list;
}

The grammar of parallel for statement is like above. And similar to for statement, all items in input\_list (list, set builder form, iterator object are could be as input\_list) is assigned to a then statement_list is executed. But execution is not sequential but parallel. Let's see simple example

```
parallel for a in [1,2,3,4,5]
{
  foo(a);
}
```

Above code call foo(1), foo(2), foo(3), foo(4) and foo(5) in same time logically. But for optimization, max thread num in same time is number of CPU core. In dual core system, 2 threads are made and execute all input list in same time. And in quad core system, 4 threads are made and do them all. Like parallel do statement, this sub threads can access local variables in main thread. So, if you want parallelize for statement. just add "parallel" in front of that. (but logic in satement_list should be independent) Unlike parallel do statement, main logic wait until all sub thread is done. And beware that there is assigning overhead, So it is not recommended to use parallel for statement to very simple work.

Here is another example

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

Above code is run under quad core system. It shows that total run time is shorten to 1/4.

You can add additional by, per option to parallel statement. for example,

```
parallel for a in [1..100] by 3 per 30: 
  print: a; 
```

above code means that run 3 threads with 30 items in one time. So, working ranges are set as \[1..30\],\[31..60\],\[61..90\],\[91..100\] and 3 threads are invoked with these working ranges.

by and per option are could be omitted. in this case, default value of by is cpu num in current machine and default value of per is 1. But, If there is one CPU in machine, default value of by is 2 (because It's possible user use blocking IPC on his/her code)

Normal expression is possible as value of by, per. You can use system module for balancing threads.

```
a = [1..1000]; 
parallel for i in a by (cpu = system.cpu_n() * 2) per (a.size() / cpu) { 
  print: i; 
} 
```

Above code select adaptive thread number in run time.

decode statement
----------------

This statement is similar to pattern matching in Earlang. But there is some more advanced feature in it.

Basically, its grammar is like below

```
decode A
{
  case pattern_list: statement_list
  case pattern_list: statement_list
  case pattern_list: statement_list
  ...
}
```

A is compared to pattern\_lists in order. If A is matched to one of left side pattern\_lists then right side statement\_list is executed. List, vector, list type object (SBF, iterator) and string could be placed in A. And pattern\_list could be composed by string, regular expression and list.

Let's examine it in each case

### string match

```
decode 'orca'
{
  case 'orca': print('orca, matched');
  case 'python': print('python, matched');
}
```

This code print 'orca, matched'. It seems like to see simple switch statement.

And here is more complex example.

```
decode str
{
  case 'send:', %to, ':', %msg: ..send(to, msg);
  case 'connect:', %to: ..connect(to);
  case %fail: ..error(fail);
}
```

Think about simple chatting server protocol. First pattern list is for send message format.

If client send to server 'send:tom:hello, tom', then it matched to first pattern list, Then 'tom' is assigned to to and 'hello, tom' is assigned to msg. And finally, ..send(to, msg) is run. If client send to server 'connect:tom', it matched to second pattern list. Then ..connect('tom') is called.  
Last pattern is for 'default' it matched to all input case so it must be last pattern.(because matching is done by order of pattern list)  
If there is unknown input string, it matched to %fail and its value assigned to fail variable then ..error(fail) is called.

### regular expression match

Regex could make more convenient and flexible pattern matching.

```
decode str
{
	case 'id:', r'[a-zA-Z][a-zA-Z_0-9]*', ', number:', r'[0-9]+': print('matched!!');
	case %fail: print('failed..');
}
```

Above code print 'matched!!' in case of 'id:lynix, number:103'. It print 'failed..' in case of 'id:3aa, number:10' or 'id:lynix, number:10a'. If you want to know real value which is matched to regex. Change above to like this,

```
decode str
{
	case 'id:', %id=r'[a-zA-Z][a-zA-Z_0-9]*', ', number:', %number=r'[0-9]+': print('matched!!, id=${id}, number=${number}');
	case %fail: print('failed..');
}
```

Then if str is 'id:lynix, number:103' then "matched!!', id=lynix, number=103" is come out.

### list match

List matching is also possible,

```
decode [1,2,3,4,5]
{
	case [1, 2], %mid, [4, 5]: print(mid);
}
```

Above code prints \[3\]. Traditional list matching process is head:tail matching. So, orca supports this also.

```
decode [1,2,3,4,5]
{
  case []: print('empty');
  case %head[%tail]: print('head: ${head}, tail: ${tail}');
}
```

This code prints head: 1, tail: \[2,3,4,5\]

### decode function

Like the many examples of LISP, list pattern matching is done recursively. Let's see below example.

```
def print_list(a)
{
	decode a
    {
		case []: print('done');
		case %head[%tail]: {
			print: head;
			print_list(tail);
		}
    }
}

.print_list([1,2,3,4,5]);
```

This code print out.

```
1
2
3
4
5
done
```

But this code is so complex, So you can use def.decode for conveniance. Below code is same as above example.

```
def.decode print_list(a)
{
  case []: print('done');
  case %head[%tail]: {
		print: head;
		print_list(tail);
  }
}
```

Like this, orca can process string easily and without side effects like functional programming.

And decode supports user defined function as match value from 0.4 release. It's simple upgrade but very useful. If you see module xml and json in lib directory of orca, you can find It's very useful to decoding nested string.  
as a simple example If there is string like below,  
str = " \[1, \[2\], 3 \] "  

If you want read it and convers it to list. (don¡¯t think about eval(), just decode string)

If you parse it by decode statement (old version) programmer may try it like this,

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

In this case, programmer want string "1, \[2\], 3" is assigned to body. but, "1, \[2" is assigned (because decode match first occurrence) so match is failed.  
So, If you use user defined match function like below,

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

decode statement call match.bracket with "1, \[2\], 3\]" as parameter. and match.bracket function matches valid scope of \[ and \]. And match.bracket matches string "1, \[2\], 3" and assign it to body. and match is success.  
and action code is called. and tolist(body) is called and second rule is matched so head is "1" and tail is "\[2\], 3"  
and finally, list \[1, \[2\], 3\] is return.  
like this orca can traits nested string very easily. 

# 

function and object
===================

function
--------

Function is just runnable object.

You can define function like below.

```
def name {
  statement_list
}
```

As an example, function that sum up two parameters is like below,

```
def add(a, b) {
    return a + b;
}

print: my.add(10, 20);
```

This prints 30 If you want variable arguments,

```
def sum_all(...argv) {
    sum = 0;
    for a in argv {
        sum += a;
	}

    return sum;
}

print: my.sum_all(1,2,3);
6
```

You can define it like above. ...argv means variable arguments. And those are inserted in argv list. ... must be end of parameter list. That means that def (a, ...b, c) is illegal but def (a, b, ...c) is correct.

object
------

### object definition

Previous function definition is just one object which is runnable. And now, let's define object which have member variables.

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

Above example prints out 0, 1, 0.

Let's see more detail again. First, we define counter object by "def counter" and in its area, we define its member variable c, member function inc, dec and describe counter's code (my.c = 0)

In this defines, all of counter, c, inc, dec are independent whole object. They just have relations to others. and by that they can access each other.

In the position of inc and dec, counter means their "owner". So, if they access to counter's member c, have to do that by owner.c += 1 or owner.c -= 1  
In the position of counter inc, dec and c is "my" member. so It can access them in his scope by my.* like code which is include in it "my.c = 0"  
(think about "self" of python)

This code will be written in python like below,

```
class counter:
  def __init__(self):
    self.c = 0;

  def inc(self):
    self.c += 1;

  def dec(self):
    self.c -= 1;
```

But this simple definition has many pre-defined rules inside. In position of inc, self means not inc but counter. so, inc and counter is binded strongly. inc is just member function and counter are just member container.  
But in all of orca, inc, dec, c and counter are just object.

And inc and counter is loosely binded. so inc could be member function of other objects later. (if its owner is changed) It's more minimal and atomic to object orient concept in my thought. Think about another example.

If programmer design thread API which will launch new thread. He must choose function or class as it's parameter in design time. But in orca, both of them are possible like this,

```
def foo {
    print: "hello, thread";
}

thread.run(my.foo);

def foo {
    # some init code here
    ...

    my.run();
    return;

    def run {

    }

    def blah {

    }
}

thread.run(my.foo);
```

So in same API, foo could be a simple function or class which have its member.

### simple notation of my, owner

There is simple notation for owner and my, Those are .. and . (.. for owner, . for my) So above one could be written as

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

### special character member

When you refer member of object. You type like this form. object.member. As an example, io.print means refer print member of io object.

In this form, member name doesn't includes special characters. If member name has special characters in it. You should access it with string constant form.

Like below form. (cf. If you want to access it with variables io.members\[var_name\] is possible)

```
def foo
{
  def "+"(rhs)
    {
      ...
    }
}
```

As an example, operator module has below members.

```
$ operator.members;
{ '!=':!=,'%':%,'&&':&&,'*':*,'+':+,'-':-,'/':/,'<':<,'<=':<=,'==':==,'>':>,'>=':>=,'||':||, }
$ operator.'+'(3,4);
7
```

### one time initializer

You can define foo object which get parameter and add to its internal list member like below,

```
def foo(a)
{
	def item;

	if my.item == nil: 
		my.item = [];

	my.item.push_back(a);
}
```

In above code, you should check my.item's type in run time. But you can use one time initializer to initialize my.item in module loading time.

one time initializer is written like this,

```
def name := expression
```

expression's result value is assigned to name member when module is loaded. This assignment done only one time and It's not done on runtime.

So, above example can be rewritten like below,

```
def foo(a)
{
	def item := [];
	my.item.push_back(a);
}
```

### name'string' object

With a date example, If you want to get days between 2011-04-03 and 2010-01-01.

```
$ using date;
$ print: date.clone('2011-04-03') - date.clone('2010-01-01');
457
```

You can type like above. But in many cases, object\_name.clone('string') expression is bothering to type and decrease readability. So, there is another way to express it. object\_name'string' has equal meaning to object_name.clone('string') So above example could be rewritten like this, $ date'2011-04-03' - date'2010-01-01'; 457

inherit
-------

Inheritance definition is like below,

```
def derived : base { ... }
```

Like this, you can list up parents of derived on right side of colon. If you want to make new object, use clone internal interface.

```
a = b.clone(10);
```

This make new b object and assign it to a; And if b has an init member in it, after make new b object, b.init(10) is called automatically.

using
-----

using keyword loads module.

If there is sample.orca file in current folder or folders in ORCA_PATH environment variable. If programmer want to use that file. Type like this,

```
$ using sample;
```

Then orca find 'sample.orca' (or 'sample') and compile it and insert that into 'root' If user want to call object foo which is defined in sample.orca

```
$ root.sample.foo();
```

Or already sample is in namespace

```
$ sample.foo();
```

Is possible too. If you using like this,

```
$ using sample.foo;
$ foo();
```

Then sample.foo is in namespace.

virtual member
--------------

Orca objects have its default virtual members. If these members are not defined explicit, it works pre-defined way.

below are virtual members and It's meaning. virtual members are represented with upper case letters.

### TYPE

type type is data which explain object type. You can use this for type traits. If you refer this as member of variable, It returns object type.

first, you can check data type of object like this.

```
a = 1;
a.TYPE== 2.TYPE; 
```

above code check 1 and 2 has same type. 1 and 2 are same integer so it returns true.

```
a.TYPE == 2.TYPE;
```
or
```
a.TYPE == type.int;
```

has same results.

```
a.TYPE != 2.TYPE
```

and above codes return false. < operator between TYPES  means inheritance.

```
a.TYPE < b.TYPE
```
above code return true if a inherits b. if not, it returns false. 



object < object.TYPE means instance.

```
a < b.TYPE
```
if a is instance of b, It returns true.

### TYPENAME

TYPENAME return type of data as string

```S
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

this returns static members of object as map interface object. map interface object means that It's not a map but It supports some map interfaces.

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

if you run above codes.

```
{ 'bar':nil }
{ 'bar':nil,'new_member':1 }
{ 'bar':nil,'new_member':1 }
1
```

are printed. This STATIC_MEMBERS is worked like map but if you change It(static\_member object)'s contents original static members in object foo is changed.

STATIC_MEMBERS provides has\_key, erase_key, keys, values, begin, last, end, find interfaces. begin, last, end and find return iterator of static members.

### MEMBERS

STATIC_MEMBERS return only static members of object. But MEMBERS returns all static, non-static members other aspects are same as STATIC_MEMBERS

### PARENTS

PARENTS virtual member returns parents list of an object as list interface object. It provides push\_back, pop\_back, push\_front, pop\_front, begin, end, last, find interface.

### ID

ID return unique number of object If it¡¯s remained in heap memory.

```
$   print: 1.ID;
0

$    print: 'str'.ID;
167178248

$    print: io.ID;
166676848
```

exception
---------

orca can throw exception and its syntax is similar to other languages. But throwed parameter is not object but path name.

thorw io.error.disconnected Like above communication module thows io.error.disconnected.  
But io.error.disconnected is not real object but just string path name. If you want to catch exception.  
You can write explicit catch like "catch io.error.disconnect" or implicit catch like "catch io.error" or "catch io" So below code is possible

```
try {
    ...
    throw io.diconn;
    ...
    throw io.timeout;
    ...
    throw app.input.invalid;
    ...
}
catch io.timeout {
    print: "timeout";
}
catch io.disconn {
    print: "disconnected";
}
catch io {
    print: "general io exception";
}
catch app {
    print: "application exception";
}
catch {
    print: "unknown exception";
}
finally {
    print: "finally is always called ";
}
```

orca choose path name (not object), so programmer make new exception type easily. But you must be careful to mistyping.  
Type throw iio.error.disconnected make unwanted result.

Hmm.. but someday, only registered paths are possible for prevent mistyping.  
Other parameters are delivered as object to catch code Like this,

```
try {
    throw app.test <- 10, "test";
}
catch app -> num, msg {
    print: num, msg;
}
```

lambda
------

orca supports lambda function. The grammar of lambda function is like this

```
lambda() { statment_list }
```

This code block has no name but it's same as normal orca object entirely. It could have member objects and its owner is who define it. Below are code in test_lambda.orca

```
def for_each(list, functor) {
    for a in list {
        functor(a);
    }
}

my.for_each([1..10], lambda(...argv){ print(argv[0]); });
```



below is same with above statement

```
my.for_each: [1..10], lambda (...argv) {
    print: argv[0];
};
```

As said before, lambda is object so

```
$ a = lambda() { print: "foo"; };
$ a();
foo
```

It's possible assign, clone and any other operation for object.






operator overloading
--------------------

Operator overloading is described with famous example for complex operation. Below code is in test_operator.orca

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

'+', '-', '*', '/', '<', '==' is overloading function and parameter is It's arguments that be placed in right side of operator.

If you define '==' and '<', orca do '<=', '>', '>=' and '!=' automatically by using combination of '==' and '<'. and orca provides '.', '.$', '.=' as new overloading operators.

first, "."('b') is called if a.b is referred but a has no member named 'b'.

```
def day_of_month
{
	def "."(name)
	{
		decode(name)
		{
		'January' -> return 31;
		'February' -> return 28;
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

like above, expression p.Apill finally called .attr('April')

.=('b', 3) is called if a.b = 3 referred but a has no member named 'b'

.$ is something different. If this function is not defined, only . is called. but If this function is defined, 
If expresion a.b.c is reffered, a.'.'('b') is called because b is not last path of path expression(a.b.c, c is last) and If expression a.b is reffred, a.'.$'('b') is called because b is last path of path expression(a.b) This is used for remote access, You can see useful usage of this in remotec.orca and remoted.orca.

And you can override indexing operators. "\[\]" and "\[\]=" are those.

If obj has \[\] and \[\]= overriding operator,

a = obj\[b\] calls a = obj."\[\]"(b) and obj\[b\] = c calls obj."\[\]"(b, c)

These operators make object like map or list interface.

overloaded operator acts when object is at left hands side. but, If object is at right hands side and LHS object has no overriding operator, RHS object's operator is called.

With an example, If obj has overriding + operator, obj + 1 calls obj.'+'(1) and 1 + obj calls obj.'+'(1)

And if obj\_b has + operator, obj + obj\_b calls obj.'+'(obj\_b) but obj\_b + obj calls obj_b.'+'(obj). Operator of LHS works first.

And there is one more thing to consider about this. + and * satisfy commutative law but - and / don't.

So, obj - 1 calls obj.'-'(1) is ok and 1 - obj should not call obj.'-'(1). In this case, 1 - obj calls obj.'-rev'(1) and 1 / obj calls obj.'/rev'(1).


channel object
--------

The orca has ->, <- operators. This operator calls -> or <- member of object if they are defined. -> is channel out and it pop data from object if possible and set to right side variable. A list and a tuple have predefined channel operator. In case of list, first item is popped (pop_front) but in case of tuple, last item is popped (pop_back) because tuple doesn't support pop_front.


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

<- is channel in operator which push data to object from right side variable.

Below is an channel in example

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


But channel is not a push, pop interface. If select statement wait channel object by channel out, The orca vm check channel object by size() interface (So channel object must have size member it it's used at select statement) then wait if it is empty. Then if other thread push data to that channel object by channel in. The orca vm notify to pending thread to get data.

So, you can use above list, tuple as sync queue. See select statements for more detail information.

And channel in has one more specific aspect. If orca vm get <- from object and that <- member is nil, vm don't evaluate right side of statement and skip to next statement.

The C/C++ can use #ifdef if user want to remove debug message code. but other language use log like below,

```
log(INFO, "result of foo: %s", foo());
```

If user increase log level to ERROR, above message will be ignored but ignoring means just printing. Parameters are evaluated so foo() is executed anyway. This means unwanted overhead and side-effect if foo() change variables.


The log library of orca uses channel in. For an example,

```
using log;
log.tcp(false);
  
log <- 'log print';
log.tcp <- 'log.tcp print';
log.tcp.socket <- 'log.tcp.socket print';
log.udp <- 'log.udp print';
```
log is turn on implicitly. but log.tcp is turn off explicitly. So only 'log print' and 'log.udp print' are printed. log.tcp and log.tcp.* are skipped by orca VM so right side of statement is not evaluated. So, there is no overhead and side-effect.



folder object
------

The modularizing is required if code size is bigger. In case of python if folder has __init__.py in it. It's assumed as module. In case of golang package notation is used as module define.

The Orca use folder name for modularizing. If folder name has prefix of .orca, this folder become an orca object. And files in this folder become members of this folder object. If this folder object needs execution code. You can make CODE.orca in this folder and CODE.orca become an execution code of folder object. (remind virtual member is named with CAPITAL)

Let's see example. make simple.orca folder and write orca files in this folder like below.

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


The result of execution is like below. It prints its name, member and result of member execution.

```
~$ orca sample.orca
I'm sample
My members: { 'bar':<bar - 0x1f20f50>,'foo':<foo - 0x1f220a0> }
I'm bar
I'm foo
```

You can see other examples in the lib folder of orca. Many libraries are built as folder object in it.







special object
==============

native object
-------------

orca is made by C++/boost so It's very easy to make native extension module. In the orca project files, find and see orcaFile.h which is describe file module.

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

Almost all interpreter languages support to make native extension call. But like above, it's simple and easy because there is C++ orcaFile class which represents file module in orca.

This is internal source code. So, if you want build up dynamic library add additional code to use it runtime. If you make extension module and name it as sample.dll or libsample.so, add get\_sample in it with prototype extern "C" void* get\_sample().

And in this function, make your object and return it as type of orcaObject*

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

This code is sample dll source which is included in orca project. get_sample returns new orcaObject* sample.

object sample's execution is built by operator(). It gets two integer parameters and sum up and return (by pushing it to stack frame)

If you add another object into this module try like orcaFile.h in case of native code. or try like orcaIO.h if you add real orcaObject into it. Here is that part of orcaIO.h

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

parse object
------------

Orca has LALR(1) parser generator in it. So, if you use it, you can make your own syntax parser very easily.

basic operation is same as BNF notation of bison (or yacc). But It contains its lexical analyzer in it.

below example is simple calculator examlple

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
   
       nil : r'[ \t\r\n]+'
	;
}
```

if you run my.calc('3+4*2'), It returns 11

This part requires knowledge about BNF & parsing process to understand all. so, I'll describe other articles about that. In this tutorial let's see different facts with bison.

strings and regular expressions in object are terminals. Orca get token from input stream by using above terminals. in grammar nil : r'\[ \\t\\r\\n\]+', left nil means don't use right terminal. (ignore right side terminal) if grammar is matched, lambda object of right side is called. Input parameters are argv list which is composed by return values of matched nodes.

This is simple example, So, if you want another complex one, See the lib/lisp.orca. lisp.orca is common lisp module which is made by parse statement.

context extended object
---------------------------------

Context extension object handle statements that user defines in orca source file. handle means It get it's text code and compile and make result object itself.

by this, Orca can contain domain specipic language in its source code.

for a simple example, let's see below,

```
a = lambda.cpp(msg) {
  // this is cpp code
  cout << "hello, " << msg.String() << endl;
};

a('world');
```

this code prints 'hello, world'. and internal codes in lambda.cpp { ... } is written by C++ language. If def.name or lambda.name is appear, Orca call name module and pass statement code, timestamp of source code and unique name. That means orca call cpp(name, timestamp, source_code, parameter_name_list)

cpp module check name and timestamp. If there is no dynamic extension library or source\_datetime is newer than dynamic library, cpp module recompile statement and save it as name.so And finally, open that dynamic library and get result object.

This is similar to inline assembly in C language. but It's different because This can be used for other languages or context which user want to handle. And another difference is result of this is independent object, so It doesn't harm readability.

Default supported context extended object module libraries in orca are html, json, cpp, lang.lisp and lang.sh. You can see these in lib folder and understand how it works.


The module which make context extended module is made like below.
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
Above is a simple module which make txt object which just return txt. under root means location of object (Normally, make txt as txt.orca file)
If orca read txt_pure it passes below argv to txt module like below.
argv[0] is an object name. (txt_pure in this case)
argv[1] is a last modified time of file to recompile in case of parser which make result (An interpreter don’t need to mind it)
argv[2] is a context body.
argv[3] is a names of parameters. (don’t use here)
argv[4] is a location info of other context module inside. Let’s see it later.
```
( 'txt_pure',2019-05-04T19:20:06,'
    simple text object
',(  ),{  } )
```
The txt module make txt_object as a result object with these parameters. It clones txt_object and just set context body to template member of txt_object.
txt_object return template when it is called.
Below code make next result. 
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

And Context extended object can contain another object definition in it. So, you can define pure orca object in the text context of above.
If you define like below,
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

It makes below result.
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

The example define object_under_txt in Txt_hibrid. The result object really has that as a member and can execute it.

But txt module has no code to handle external object as you know.
Below parameters are passed to txt module if txt_hibrid is parsed.
```
( 'txt_hibrid',2019-05-04T19:20:06,'
    simple text object







',(  ),{ 'object_under_txt':3 } )
```

Only pure txt context body is passed as argv[2]. Another object definition (which is start with def) is omitted and is not passwd to txt module.
That definition is handled by orca parser. The orca parser make object by itself or pass that to another context extended module maker. And insert that result object to txt_hibrid object as a member. Now you can see the last parameter’s meaning. That is a list of member name and its line in the txt context body.
This is can be made because objects of orca are loosely bind. One of the most useful usage of this is html processing of sonar.

