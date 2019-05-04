

# 오르카에 대한 10분 홍보

오르카 프로그래밍 언어는 2009년 처음 릴리즈 되었다. 그 당시에도 전체적인 사상과 얼개는 지금과 같았으나 오르카만의 특이점을 끌어내는 대는 부족했었던 것 같다.

한동안 개발이 멈춘 상태에서 위 고민을 해나가던 중, 문맥 확장 객체 (context extended object)를 중심으로 해결책을 찾고자 했고, 이를 통해 웹 개발쪽에 집중하기로 했다. 그 결과로 나온 것이 웹 개발 프로임웍인 sonar 이며 이를 먼저 둘러보고 싶으면 #4 을 보면 된다. 

이 글에서는 #1 에서 언어의 가장 기본적인 특징을 살펴보고 #2 에서는 이를 통해 GUI 프로그램을 매우 직관적이고 빠르게 구현하는 것을 보여주며, #3 에서는 문맥 확장 객체에 대해 간단하게 설명하고 #4에서는 이를 이용한 웹 프로그래밍을 살펴보겠다.

가장 핵심적인 부분만을 추려서 기술할 내용이라, 상세한 내용은 아래의 manual 과 module 설명서를 참조하면 된다.


[튜토리얼](https://github.com/lynix94/orca-lang/blob/master/docs/tutorial_kr.md)

[모듈](https://github.com/lynix94/orca-lang/blob/master/docs/module_kr.md)




# 1. 기본 컨셉 - 객체로의 완전한 일원화
오르카는 파이썬 스타일의 스크립트 언어이며, 파이썬과 C++, go lang 에서 영향을 받았다. 그러나, 기존 언어의 객체-함수간 관계에 어색함을 느껴 새로운 구조로 구현하였다.

오르카에서 모든 객체는 def 로 선언된다. 객체는 실행 코드를 가지고 있을 수 있다. 때문에 별도로 (객체가 아닌) 함수는 없다. 

```
def foo
{
	print('hello, world');
}
```

위는 hello, world 를 찍는 함수이지만 객체이기도 하다. 현재는 멤버가 없는 객체일 뿐이다.



```
def rectangle
{
	def width := 10;
	def height := 20;

	def area()
	{
		return owner.width * owner.height;
	}

	// code of rectangle which describe itself.
	print('Rentangle with w:%d, h:%d, area=%d' % (my.width, my.height, my.area()));
}

my.rectangle();
```

rectangle 객체는 width, height, area 를 멤버로 가지는 객체이다. 이 부분은 별다를게 없으나, width, height, area 들도 모두 독립된 객체들이다. (객체에 강하게 바인딩된 함수나 멤버변수가 아니다)

때문에, area 입장에서는 자신을 소유하고 있는 객체는 owner 로 접근할 수 있다. (this 나 self 가 아니다) 

위 코드를 sample.orca 로 저장하고 orca sample.orca 를 실행하면 아래와 같은 결과가 나온다.
```
$ orca sample.orca
Rentangle with w:10, h:20, area=200
```
위 코드의 마지막 줄은 my.rectangle() 인데 이 부분이 위 내용을 출력했다.
orca 가 한 파일을 컴파일 하면 해당 파일 이름의 객체를 root 밑에 등록한다. sample 객체입장에서는 rectangle 이 멤버객체이고, my.rectangle() 이 sample 객체의 실행코드이다. 즉 파일안의 코드의 앞뒤에 아래와 같은 정의가 표현되어 있다고 생각하면 된다.
```
def sample #file name
{
	# sample code above	
}
```

이와 같은 방식이 기존 OOP에 익숙한 사용자에게는 혼돈스러울 수 있고, 모든 멤버함수들이 별도 객체로 존재하면서 가지는 오버헤드 (객체로서의 문맥저장공간)를 가지는 것도 사실이다.

그러나, 이런 방식이 주는 장점들도 많은데 다른 부분은 튜토리얼을 참조해 보고, 가장 인상적인 장점들 중 하나로 GUI 와 웹 프로그래밍을 먼저 살펴보겠다.


# 2. GUI 프로그래밍



1장을 통해 오르카 객체와 함수는 동일하며, def 로 정의되고 def 안에서 새로운 객체들을 선언하면 member 로 등록되어 계층적인 연관관계를 가지게 된다는 것을 알았다. 이와 같은 방식을 사용하면 많은 상황들을 가장 간단하게 표현할 수 있다.

그에 대한 예로서 다음의 두 GUI 예제를 살펴보겠다. 기존 GTK 나 windows api 의 GUI 프로그램들과 비교해서 본다면 얼마나 직관적이고 간단해 졌는지 알 수 있을 것이다.

먼저 가장 간단한 프로그램이다. 윈도우가 뜨고 - 버튼을 누르면 라벨의 숫자가 1 감소하고 + 버튼을 누르면 1 증가하는 프로그램이다. 실행 모습은 다음 링크로 볼 수 있다.

https://youtu.be/og9MEaWCqHc

아래는 이 프로그램의 코드이다.

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
			my.event['clicked'] = lambda() { 
				find_owner('box').counter.attr['text'] += 1;
			};
		}

		def minus : button
		{
			my.attr['xy'] = (150, 130);
			my.attr['wh'] = (100, 50);
			my.attr['text'] = '-';
			my.event['clicked'] = lambda() { 
				find_owner('box').counter.attr['text'] -= 1;
			};
		}
	}
}


my.main.make();
my.main.show()
```

gtk 의 사전 정의된 위젯들을 상속받아 객체들이 정의되는데, 가장 바깥쪽에는 main 객체가 있다. main 객체 안에는 그룹을 만들기 위한 box 객체가 있고 (html 의 div 를 생각하면 된다), 그 안에 label 인 counter 와, plus, minus 버튼이 있다.

각 객체의 코드들은 윈도우가 만들어 질 때 (my.main.make()) 실행되면서 각 객체를 초기화 한다.



먼저 main window 는 아래와 같이 좌표(xy)와 크기(wh) 를 설정한다.

```

def main : window
{
	my.attr['xy'] = (50, 20);
	my.attr['wh'] = (300, 200);
```



카운터는 box 안에서의 상대좌표를 아래와 같이 설정하고, 초기 라벨의 텍스트를 0으로 설정한다.

```
		def counter : label
		{
			my.attr['xy'] = (40, 50);
			my.attr['text'] = 0;
		}
```



plus 버튼은 비슷하게 box 안에서의 상대좌표를 설정하고, 버튼이 눌리는 이벤트가 실행됐을때의 액션을 추가로 설정한다.

아래 코드의 액션을 보면  find_owner 함수로 이름이 'box'인 상위 객체를 찾은 다음 그 객체의 멤버들 중 counter 를 찾은 후 text 속성을 1 증가시킨다. minus 버튼도 비슷하게 동작한다.

```
		def plus : button
		{
			my.attr['xy'] = (150, 30);
			my.attr['wh'] = (100, 50);
			my.attr['text'] = '+';
			my.event['clicked'] = lambda() { 
				find_owner('box').counter.attr['text'] += 1;
			};
		}
```



이 코드를 보면 프로그램안의 위젯들의 배치와 코드상의 객체들의 배치가 같음을 알 수 있다. 그리고 특정 위젯에서 이벤트가 발생했을 때 타 위젯의 변화를 가져오는 동작을, 해당 위젯을 표현하고 있는 객체를 찾아서 속성을 직접 변경하는 식으로 동작하고 있다.


다음은 아주 간단한 텍스트 에디터이다. 이번에도 main window 안에 정렬을 위한 box 가 있고 box 안에 menu 와 scroll 객체인 hs 가 있고 hs 는 안에 에디터 객체를 가지고 있다. 앞서의 예제와 마찬가지로, 직관적인 텍스트 에디터의 배치와 코드상의 객체 배치가 일치한다.

```
using gui;
using gui.window;
using gui.vbox;
using gui.label;
using gui.menubar;
using gui.text;
using gui.scroll;
using gui.dialog;
using util.find_owner;

def main : window
{
	my.attr['wh'] = (800, 600);

	def box : vbox
	{
		def menu : menubar
		{
			file = [ 'open', lambda(){ 
								name = dialog.fileopen(find_owner('main'));
								str= os.read(name);
								find_owner('box').hs.edit.attr['text'] = str;
							},
					'save', lambda(){ 
								str= find_owner('box').hs.edit.attr['text'];
								name = dialog.filesave(find_owner('main'));
								os.write(name, str);
							},
					'exit', lambda(){ 
								find_owner('main').quit(); 
							}
					];

			my.push_back('file', file);
		}

		def hs : scroll # this make scroll bar outside of edit member
		{
			def edit : text # this make edit window
			{
			}
		}
	}
}

my.main.make();
my.main.show();
```





main window 의 크기는 my.attr['wh'] 로 넓이, 높이가 800, 600 으로 설정되었다.

menu 객체는 file 에 메뉴를 구성하여 자기자신에게 등록하는 일을 한다. 각 메뉴는 이름과 동작을 하는 람다함수의 쌍으로 되어 있다. open, save, exit 가 그것이다. open 을 눌렀을때는 미리 정의된 filopen dialog 를 열고 그 결과를 name 변수에 받는다. 이 name 이 fileopen 다이알로그로 선택된 파일 이름이다. 이제 os.read 로 이 파일을 읽은 후 이름이 'box' 인 상위의 객체를 찾은 후 그 객체로부터 hs.edit 로 참조해 내려온 후 attr['text'] 을 str 로 변경한다.

```
			file = [ 'open', lambda(){ 
								name = dialog.fileopen(find_owner('main'));
								str= os.read(name);
								find_owner('box').hs.edit.attr['text'] = str;
							},
```

save 의 경우는 마찬가지로 edit 객체의 'text' attr (실제 윈도우의 텍스트 데이터가 들어있음) 를 가져와서 파일로 쓰는일을 하고, exit 의 경우는 main 객체를 찾은 후 quit() 을 호출해 프로그램을 종료한다.

```
					'save', lambda(){ 
								str= find_owner('box').hs.edit.attr['text'];
								name = dialog.filesave(find_owner('main'));
								os.write(name, str);
							},
					'exit', lambda(){ 
								find_owner('main').quit(); 
							}
					];
```

이 코드의 간단한 동작은 아래 링크로 확인 가능하다.


https://youtu.be/qwcmxUXFNP0



아래 링크는 앞의 두 예제들에 대한 보다 자세한 설명이다. 시간이 되면 참고바란다.

https://youtu.be/VsmmITn2dbw


# 3. context extended object

이제 orca 로 web 프로그래밍을 하는 부분을 설명할 예정이나, 그 전에 문맥 확장 객체에 대해서 사전 설명이 필요하다. 문맥 확장 객체(context extended object) 는 오르카의 또다른 가장 큰 특징으로, 오르카 객체를 정의하면서 그 객체를 컴파일 하는 모듈을 지정할 수 있게 된다.

객체를 정의할때 def.html 로 시작하면 { } 안의 구문은 오르카 문법으로 컴파일하지 않고 html 모듈에게 객체 생성을 위탁한다. 
아래와 같이 코드를 작성 후 실행하면,

```
# test_html.orca
using html;

def.html html_object
{
	<html>
	<body>
		<p> test html </p>	
	</body>
	</html>
}


print(my.html_object);
print(my.html_object());
```


아래와 같은 결과가 나온다. 
html_object 안의 내용은 텍스트로 html 모듈에 전해져서 실행을 하면 html 구문이 
```
$ orca test_html
html_object - 0xd79280>

    <html>
    <body>
        <p> test html </p>
    </body>
    </html>
```

이 문맥 확장 객체는 오르카 초기부터 있었으나 유용성은 크지 않았다. 당시에는 lisp 나 cpp 를 오르카 코드안에서 사용하려는 목적뿐이었다.
그런데, 웹 프로그래밍의 템플릿 처리를 수월하게 하기 위해 고민하면서 새 개념을 하나 추가하면서 유용성이 커졌다.

문맥확장 객체안에서 def 로 선언된 객체가 있으면 (def 이면) 오르카가 직접 파싱하고, def.NAME 으로 선언되어 있는 또다른 문맥확장 객체이면 해당 모듈이 파싱하여 객체를 합성하는 것이다. 이 방식으로 하면 def.html 은 순수 html 텍스트만 파싱하고, 그 안의 오르카 문법(이나 타 문맥의 문법) 으로 되어 있는 멤버들은 스스로 하지 않고 파싱된 결과를 사용할 수 있게 된다.

간단한 예는 다음과 같다.

```
using html

def.html html_object
{
    <html>
    <body>
		%{made_by_orca_object}
    </body>
    </html>

	def made_by_orca_object
	{
		return 'embedding result by orca object';
	}
}

print('#1: ', my.html_object);
print('#2: ', my.html_object.MEMBERS);
print('#3: ', my.html_object());
```


```
$ orca test.orca

#1: <html_object - 0x185d6b0>
#2: { '__head':'','__id':'html_object','__position':{ 'made_by_orca_object':7 },'__tail':'','__template':'
    <html>
    <body>
        %{made_by_orca_object}
    </body>
    </html>





','init':<init - 0x185d980>,'made_by_orca_object':<made_by_orca_object - 0x1856560> }
#3: 
    <html>
    <body>
        embedding result by orca object
    </body>
    </html>
```

실행 결과를 보면 html_object 는 별도의 오르카 객체로 생성된 것임을 알 수 있다. html 모듈이 생성해서 리턴한 것이다.
그다음 html_object 의 멤버를 출력해보면 내장된 (html 모듈이 만든) 멤버들되에, made_by_orca_object 라는 오르카 객체가 포함되어 있는것을 알 수 있다. 이것은 오르카 문법으로 되어 있는 객체로 오르카 파서가 컴파일해서 객체로 만들어 html_object 에 멤버로 추가시켜준 것이다. 앞서 설명했듯이 이 과정은 자동으로 일어나며 html 모듈은 def made_by_orca_object {...} 부분은 신경쓰지 않고 다음과 같은 영역만을 전달받아 작업한다. 잘라서 주는 것은 오르카 메인 파서가 실행한다.

```
# html 모듈이 실제 전달받아 처리하는 부분
    <html>
    <body>
		%{made_by_orca_object}
    </body>
    </html>
```

이제 마지막 #3 을 보자, html_object 를 실행시키면 이 오브젝트는 __template 으로 부터 포멧스트링 처리를 한 결과를 텍스트로 리턴한다. map type format (%{made_by_orca_object} 부분) 은 포멧 스트링을 오르카에서 확장한 것으로 자세한 내용은 튜토리얼을 참고하자.

여튼 html_object 는 템플릿 내에 %{made_by_orca_object} 가 있는것을 확인하고 멤버들 중 같은 이름인 made_by_orca_object 객체를 호출한 후 그 결과값으로 해당 포멧을 변경해 준다.

이 방식은 기존 텍스트 템플릿을 process response 단에서 별도의 view 처리객체가 절차적인 방식으로 구성하지 않고, html 객체가 자신에게 필요한 로직을 내장할 수 있게 된다. 예제이기 때문에 간단한 내용만을 담았는데, 이를 이용한 예는 다음 장에서 더 살펴보겠다.


여담으로, 문맥 확장객체의 가장 흥미로운 것 중 하나는 cpp 모듈이다. 아래와 같이 def.cpp 로 객체를 생성하면 {} 안에 cpp 코드를 넣을 수 있다.
파라미터 타입은 orcaData 인데, cpp 의 복사 생성자가 구현되어 있어 별도 형변환 없이 파라미터를 받고 리턴할 수 있다.

예제는 단순이 두 정수를 합치는 것이지만 좀 더 복잡한 c 코드나 외부의 c 함수를 호출할 수 있다.

```
# test_cpp.orca

def.cpp sum(a, b)
{
	orcaData result = a + b;
	printf("# %d + %d = %d\n", a.Integer(), b.Integer(), result.Integer());

	return result;
}


ret = my.sum(10, 20);
print(ret);
```

실행 결과는 아래와 같다. 실행결과의 첫출은 해당 cpp 코드를 빌드하여 오르카 객체로 만드는 부분으로 최초 한번만 실행된다.
```
$ orca test_cpp
cpp external module compile: g++ -fPIC -shared -o ./liborca_sum.so ./sum.cpp -I${ORCA_HOME}/include/orca -L${ORCA_HOME}/lib -lorca
# 10 + 20 = 30
30
```

같은 방식으로 def.python, def.ruby 도 구성할 수 있다. 오르카의 또다른 목표중 하나는 허브 랭기지이다.


# 4. html과 sonar 를 이용한 웹 프로그래밍

이제 오르카를 통한 웹 프로그래밍을 살표보겠다. 이 문서에서 가장 강조하고 싶은 포인트이나 사전 개념이 필요하여 돌아왔다. 앞에서 GUI 를 오르카 객체의 표현 방식으로 표현하는 것을 보았는데, 오르카 초기에는 웹의 html 도 같은 방식으로 DOM 과 객체를 매핑시켜 프로그래밍 하는 방식을 고려했었다. 

그러나 DOM 은 GUI의 위젯과 다른 점이 많았다. 위젯은 최소한의 숫자로 실제 보이는 최소한의 객체만 필요한 반면에 DOM은 여러가지 이유로 이보다 훨씬 복잡하게 구성되며 특정 tag 의 depth 및 경로가 개발 단계에서 자주 변경된다.

때문에, 이를 우회하여 context extenstion object 를 사용하여 html 은 html 문법으로 바로 다루고, 논리적인 프로그래밍 처리가 필요한 부분은 오르카 객체를 추가하는 방식으로 접근했다.
context object 는 html 모듈을 사용했다.

추가로, 오르카에서는 sonar 라는 웹 개발 프레임웍을 제공한다. python 의 django를 참조하였으나 html 템플릿 처리는 앞서 언급한 문맥확장객체를 사용한다.

sonar 의 기본 구동 방법은 다음 링크를 참조할 수 있다.

https://github.com/lynix94/orca-lang/blob/master/docs/about_sonar_kr.md

sonar 구동방법은 앞의 링크로 대신하고 구현된 코드들을 바로 살펴보기로 하다.
코드 예제 별로 실행결과를 링크했으니 같이 확인해 볼 수 있다.

소나 예제코드는 github 의 다음 링크에서도 볼 수 있다.

https://github.com/lynix94/sonar-example

먼저 첫번째 예제이다.
예제 페이지의 전체코드는 다음 링크와 같고, 

https://github.com/lynix94/sonar-example/blob/master/ex1.orca/index.orca.html

그 동작하는 모습은 아래와 같다.

https://youtu.be/VLD-mqbRKAw

 간단하게 해당 부분만 잘라서 보면 아래와 같다.
중간의 hello, %{name} 과 def name 부분은 앞장의 문맥확장 객체에서 설명한 대로 html 로 생성한 페이지 객체가 런타임에 구성할 내역이다. 참고로 def name 을 호출하면서 url request 를 파라미터로 전달하기 때문에 hello, orca. hello, workld 와 같은 식으로 런타임에 구성할 수 있다.

```
<div style="float:left; width:50%;">
using html;
using sonar;

<a href="/ex1?name=orca">about orca</a><br>
...

<h4>generated by object</h4>

hello, %{name}

def name(req)
{
	return req.get['name'];
}
<br>
```


코드를 보면 아래와 같이 embed_whale 객체가 있는데, 

```
<h4>object embedding</h4>
def embed_whale(req)
{
	switch req.get['name'] {
	case 'orca':
		return '<a href="https://en.wikipedia.org/wiki/Killer_whale">The killer whale or orca (Orcinus orca) is a toothed whale belonging to the oceanic dolphin family, of which it is the largest member.</a>';

	case 'humpback':
		return '<a href="https://en.wikipedia.org/wiki/Humpback_whale">The humpback whale (Megaptera novaeangliae) is a species of baleen whale. One of the larger rorqual species, adults range in length from 1216 m (3952 ft) and weigh around 2530 metric tons (2833 short tons).</a>';

	case 'blue':
		return '<a href="https://en.wikipedia.org/wiki/Blue_whale">The blue whale (Balaenoptera musculus) is a marine mammal belonging to the baleen whale parvorder, Mysticeti. At up to 29.9 metres (98 ft) in length and with a maximum recorded weight of 173 tonnes (190 short tons), it is the largest animal known to have ever existed.</a>';

	default:
		return '';
	}
}

<br><br><br><a href="/">back to main</a>
</div>
```

request 에서 오는 url 파라미터에 따라서 embed_whale 은 파라미터의 고래 정보 (orca, humpback, blue) 에 맞는 것을 골라서 리턴해주고 이것이 최종 html 결과에 반영된다. 이러한 방식은 기존의 웹프레임워크들 (장고나 플라스크)과 접근 방식이 다른데, 기존 방식은 템플릿은 스트링이고 이 템플릿내의 정해놓은 규칙에 맞게 별도의 로직에서 변경작업을 진행해 준다. 즉, View 와 Logic 이 따로 놀게 됨으로써 관계있는 것들끼리 묶여있어야 하는 객체의 조건에 맞지 않다. 다시말해 처리방식이 절차적이다.

 반면 오르카의 html 객체는 하나의 표현을 처리하기 위한 객체로서 view 와 view 만의 logic 을 같이 묶어놓을 수 있다. 기존 MVC 모델은 M, V, C 가 각각 구분되는 것이 좋다 했는데, Model 이 구분되는 것은 당연하지만 View 와 Control 의 구분은 재고할 필요가 있다. Control 중 특정 View 에만 종속적인 것은 분리가 되서 따로 관리되는게 효율적이지 않을 수 있다. (단순하게 할수 있으면 단순하게 하는게 좋다) 


다음은 html 안에 아이템의 목록을 동적으로 생성하는 예제이다. 
페이지 코드는 다음과 같으며

https://github.com/lynix94/sonar-example/blob/master/ex2.orca/index.orca.html

동작 영상은 아래와 같다.

https://youtu.be/5yXVhJ3SCqM


전체 코드 중 고래 목록을 생성하는 부분은 아래와 같다.
embed_ 로 시작하는 객체는 html 안의 그 위치에 실행 결과가 추가된다. 파라미터로 밭은 request 객체로 상황에 맞는 내용을 생성할 수 있으나 여기서는 고정 내용을 생성한다.

```
<div style="float:left; width:50%;">
using html;
using sonar;


<h4>whale list</h4>
def embed_whale_list(req)
{
	ret = '<div id="table">';

	for k, v in req.whale_map {
		ret += '<div class="row">';
		ret += '<span class="cell col1">%s</span><span class="cell col2"><pre>%s</pre></span>' % (k, v);
		ret += '</div>';
	}
	ret += '</div>';
	return ret;
}

<br><br><br><a href="/">back to main</a>
</div>
```






다음은 세번째 예제로 form 을 구성한 모습이다.

전체 코드는 아래와 같다.


https://github.com/lynix94/sonar-example/blob/master/ex3.orca/index.orca.html

동작 모습은 아래와 같다.

https://youtu.be/un_InSHbRcQ



```
<h3>leave message</h3>

def embed_input_form(req) : form
{
	def name := form.input.text('name');
	def pw := form.input.password('password');
	def message := form.input.textarea('message', 10, 40);
	def submit := form.input.submit('add');

	#form_result = .fill_and_get(req.post); # if you want keep input use this line instead below
	form_result = .fill_and_get({'name':'anonymous'});

	return .render('/ex3', form_result);
}

<h4>messages</h4>
def embed_message_board(req)
{
	def messages := [];

	# add new message if exists
	if req.post.has_key('name') {
		name = req.post['name'];
		message = req.post['message'];
		if name.length() > 0 && message.length() > 0 {
			.messages.push_back((name, message));
		}
	}

	# render messages as table
	ret = '<div id="table">';
	for msg in .messages {
		ret += '<div class="row">';
		ret += '<span class="cell col1">%s</span><span class="cell col2"><pre>%s</pre></span>' % (msg[0], msg[1]);
		ret += '</div>';
	}
	ret += '</div>';
	
	return ret;
}

```



다음은 orm 모듈을 이용하여 포스트 내용을 저장하고, 포스트 생성, 조회를 수행하는 간단한 예제이다.

코드는 아래와 같다.

메인페이지: https://github.com/lynix94/sonar-example/blob/master/ex4.orca/index.orca.html

본문읽기: https://github.com/lynix94/sonar-example/blob/master/ex4.orca/read.orca.html

새 포스트 작성: https://github.com/lynix94/sonar-example/blob/master/ex4.orca/write.orca.html

모델: https://github.com/lynix94/sonar-example/blob/master/ex4.orca/models.orca

동작 모습은아래와 갈다.

https://youtu.be/lm1NXO0tf5A






```
<h4>messages</h4>
def embed_board(req)
{
	# add new message if exists
	if req.post.has_key('name') {
		name = req.post['name'];
		subject = req.post['subject'];
		message = req.post['message'];

		if name.length() == 0 {
			name = 'anonymous';
		}

		if subject.length() > 0 {
			new_post = models.post.new();
			new_post.name = name;
			new_post.subject = subject;
			new_post.message = message;
			new_post.save();
		}
	}

	# render messages as table
	ret = '<div id="table">';
	ret += '<div class="row">';
	ret += '<span class="cell col1">id</span><span class="cell col2">subject</span><span class="cell col3">name</span>';
	ret += '</div>';

	post_iter = models.post.orderby(models.post.id).result();
	for post in post_iter {
		ret += '<div class="row">';
		ret += '<span class="cell col1">%d</span><span class="cell col2"><a href="ex4_read?id=%d">%s</a></span><span class="cell col3">%s</span>' % (post.id, post.id, post.subject, post.name);
		ret += '</div>';
	}

	ret += '</div>';
	return ret;
}
```

```
<div style="float:left; width:50%;">
using html;
using html.form;

<h3>leave message</h3>

def embed_input_form(req) : form
{
	def name := form.input.text('name');
	def subject := form.input.text('subject');
	def message := form.input.textarea('message', 10, 40);
	def submit := form.input.submit('post');

	form_result = .fill_and_get({'name':'anonymous'});
	return .render('/ex4', form_result);
}

</div>
```
```
<div style="float:left; width:50%;">
using html;
using ex4.models;

def embed_board(req)
{
	if req.get.has_key('id') == false {
		return '';
	}

	id = req.get['id'].integer();
	post = models.post.where(models.post.id == id).result();
	p = post();

	ret = '<div class="row">';
	ret += '<span class="cell col1">%s</span><span class="cell col2">%s</span>' % (p.name, p.subject);
	ret += '</div>';
	ret += '<pre>%s<pre>' % (p.message.replace('\\r\\n', '\r\n'));

	return ret;
}

<br>
<a href="/ex4">back</a>

</div>
```




다섯번째 예제는 네번째와 동일한데 html tag 객체를 사용하는 것으로 코드만 참조해 보면 된다. orca 의 scope object 를 사용하여 태그를 가독성있게 생성하는 예이다.
html.tag 는 추가로 자바 스크립트를 가독성있게 내장할 수 있는 기능이 있는데 다음 예제를 보면 된다.
페이지 링크는 아래와 같다.

https://github.com/lynix94/sonar-example/blob/master/ex5.orca/index.orca.html


여섯번째 예제는 소나에서의 자바스크립트 처리에 대한 내용이다.
페이지 코드는 아래와 같다.

https://github.com/lynix94/sonar-example/blob/master/ex6.orca/index.orca.html

동작 모습은 아래와 갈다.

https://youtu.be/-6uRAqPw7Dk


일반적인 자바스크립트의 사용예와 같이 html 코드상에 추가할 수 있고 html.jquery 를 사용해서 객체로 분리하여 추가할 수 있다.
다음은 그 예인데, html.jquery 문맥확장 객체로 자바 스크립트를 정의했다. embed_click_to_hide 내의 코드는 자바스크립트 (jquery) 로 되어 있다. 
이 객체는 실행하면 해당 내용을 스트링으로 반환한다. 물론 이 객체도 다른 오르카 객체를 내부에 정의할 수 있고, 사용할 수 있다.
```
<p id="id_2">Click me to hide.</p>
def.html.jquery embed_click_to_hide
{
	<script>
	$(document).ready(function(){
	  $("#id_2").click(function(){
		$(this).hide();
	  });
	});
	</script>
}
```

위의 예제는 자바스크립트를 명시적인 객체로 정의해서 관리할 수 있는것을 보여주었는데, 여기에 그치지 않고 tag 의 이벤트에 삽입할 수있다.
아래는 그 예이다.

id_3 라는 p tag 를 정의하고, 이 id 에 event 를 할당한다. 이벤트는 'click' 일 때, my.hide_script 를 실행하게 된다.
hide_script 는 jquery 스크립트로서 전달된 $(this) 를 감추는 코드로 되어 있다.
앞의 예와 가독성 면에서 뛰어나고, 실제 태그와 그것과 연관된 jquery 가 같은 객체에 정의되고 같이 관리된다.
```
<pre>
#3. Third example use event() of html.tag object.
</pre>

def embed_tag
{
	tag = html.tag.clone();
	tag.output = strings.builder();

	def.html.jquery hide_script
	{
		$(this).hide();
	}

	tag.p.id('id_3').event('click', my.hide_script) {
		tag.output += "Click me to hide";
	}

	return tag.output.string();
}
<br><br>
```

오르카는 lambda 객체를 지원하고, lambda 객체도 문맥확장객체로 정의할 수 있기 때문에 위의 예제는 아래와 같이 더 간략하게 쓸 수 있다.
동일한 기능이지만 $(this).hide() 가 event 내로 들어가서 가독성이 더 좋은 모습이다.
```
<pre>
#4. This example is same with above but use lambda object
</pre>

def embed_tag_with_lambda
{
	tag = html.tag.clone();
	tag.output = strings.builder();

	tag.p.id('id_4').event('click', lambda.html.jquery { $(this).hide(); }) {
		tag.output += "Click me to hide";
	}

	return tag.output.string();
}
```


이제 오르카에서의 script 사용예를 보았으니 이를 응용하여 앞의 게시판 예제를 ajax 지원 예제로 만들어보자.
페이지 코드는 아래와 같으며,

https://github.com/lynix94/sonar-example/blob/master/ex7.orca/index.orca.html

동작하는 모습은 아래와 같다.

https://youtu.be/vS8zuJmN50s

게시글을 클릭하면 해당 게시글의 본문이 ajax 로 요청하여 태그에 추가되고,
게시글을 쓰면 최근 목록에 바로 추가되는 내용이다.

먼저 request 를 처음 처리하는 prepare 에서 req 의 URL 파라미터를 검사하여 ajax_read_response 나 ajax_write_response 를 호출하여, ajax 인 경우 페이지를 리턴하지 않고 해당 함수의 결과를 리턴한다. 이로써 ajax 응답을 처리할 수 있다.

```
def prepare(req)
{
	if req.get.has_key('ajax') {
		return ..ajax_read_response(req);
	}
	elif req.post.has_key('ajax') {
		return ..ajax_write_response(req);
	}
}

def ajax_read_response(req)
{
	if req.get.has_key('id') == false {
		return '';
	}

	id = req.get['id'].integer();
	post = models.post.where(models.post.id == id).result();
	p = post();
	
	return '<pre>%s</pre>' % p.message.replace('\\r\\n', '\r\n');
}

def ajax_write_response(req)
{
	new_post = models.post.new();
	new_post.name = req.post['name'];
	new_post.subject = req.post['subject'];
	new_post.message = req.post['message'];
	new_post.save();
	
	post_iter = models.post.orderby_desc(models.post.id).limit(1).result();
	p = post_iter();

	ret = '<div id="%d" class="row"><span class="cell col1">%d</span><span class="cell col2">%s</span><span class="cell col3">%s</span></div>' % (p.id, p.id, p.subject, p.name);
	ret += '<pre>%s</pre>' % p.message.replace('\\r\\n', '\r\n');
	return ret;
}
```


폼을 기존 예제에서 변경하여,  submit 에 두번째 파라미터를 주어 클릭되었을때 실행될 함수를 지정해 준다.
submit_handler 가 호출되어 ajax 로 폼 데이터를 post 로 요청하게 되고, 이는 앞서 살펴본 prepare 단에서 검사하여 ajax_write_response 의 응답을 받는다.
ajax_write_response 는 orm 으로 해당 게시글을 DB에 저장한 후, 게시글 제목을 div 태그로 생성하여 리턴해준다.
이러면 submit_handler 는 success 인 경우 이 리턴값을 .title 클래스 태그 다음에 추가하여 게시글 목록이 바로 갱신되도록 한다.

```
<h4>posts</h4>
def embed_input_form(req) : form
{
	def name := form.input.text('name');
	def subject := form.input.text('subject');
	def message := form.input.textarea('message', 10, 40);
	def submit := form.input.submit('add', my.submit_handler);

	def.html.jquery submit_handler
	{
		var formData = $('form').serialize() + '&ajax';
		$.ajax({
			cache:false,
			url:"/ex7",
			type:'POST',
			data:formData,
			success:function(data) {
				$(".title").after(data);
			},
		});
	}

	// code start
	form_result = .fill_and_get({'name':'anonymous'});
	return .render('/ex7', form_result);
}
```

게시글을 읽는 부분도 아래와 같이 변경되었다.
게시글 id 에 event 를 등록하여 해당 게시글이 클릭되었을때 click_hander 를 호출하도록 한다.
click_handler 는 ajax 로 해당 게시글의 ID를 요청하여 ajax_read_handler 의 응답을 받고, 이 응답값을 해당 게시글의 아래에 추가하여 화면 전체갱신 없이 해당 게시글의 목록이 나타나도록 한다.
```
def embed_board(req)
{
	...
	
	tag.div.id('table') {
		...

		post_iter = models.post.orderby_desc(models.post.id).result();
		for post in post_iter {
			tag.div.id(post.id.string()).class('row').event('click', my.click_handler) {
				...
			}
		}
	}

	def.html.jquery click_handler
	{
		var clicked  = $(this);
		$.get('/ex7?ajax&id=' + $(this).attr('id'), function(data, status) {
			clicked.after(data);
		});
	}

	return tag.output.string();
}
```

이 sonar 예제에 대한 더 상세한 강의는 다음 링크로 볼 수 있다.

https://youtu.be/AjS3p9NYQT4

여기까지 오르카의 특징을 간략하게 살펴보았다. 더 자세한 사항은 tutorial, module library 를 참조해도 되고,
Youtube 에 강좌를 추가할 예정이니 이를 참조하기 바란다. (계속 추가할 예정이니 구독해 주시면 더 좋겠다)

버그 리포팅, Pull Request 및 어느 타입의 공헌도 모두 환영하며 보다 자세한 사항은 아래 링크를 참조하여 문의 주시기 바란다.

project page:		https://github.com/lynix94/orca-lang  
facebook page:		https://www.facebook.com/orcalang  
youtube:		https://www.youtube.com/channel/UC0bUKWj0aoWgbh9KaqJu8gw  
email:			kiyeul.lee@gmail.com  
linked-in:		https://www.linkedin.com/in/kiyeul-lee  





