

# 10 minutes introduction about orca programming language

The orca programming language had been released 2009 first. Basic concepts were same but killing advantages were not enough at that time. I think. 

Additional development has been paused many years, but one day I thought the idea about context extended object and using that on web programming. The result of this idea is the web development framework sonar. 

This document explains basic aspects of orca on #1. in #2, show the GUI programming easily with this aspect. #3 explains about context extended object briefly and #4 introduces the web development framework sonar. 

This document explains briefly, So I recommend below two documents later.

[Tutorial](https://github.com/lynix94/orca-lang/blob/master/docs/tutorial_kr.md)

[Module reference](https://github.com/lynix94/orca-lang/blob/master/docs/module_kr.md)


#1. Basic concept - unified object define

The Orca is python style language, and get inspiration from python, C++ and go lang. But, re-invent object-function relation because I feel some inconvenience about that.

In the orca, everything is defined by def keyword. And an object can have its execution code also. So there is no function which is not an object.

```
def foo
{
	print('hello, world');
}
```

Above code is simple function which print 'hello, world' but also an object which has no member now.



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

The rectangle object has members width, height and area. This is similar with other languages but width, height and area are also an independent object. That means they are not a strong binded function or object.

So, the area object can access it's owner rectangle by 'owner' then access to width and height by owner.width, owner.height.

An execution result of this code is like below if you save this code as sample.orca.
```
$ orca sample.orca
Rentangle with w:10, h:20, area=200
```
The last line of code 'my.rectangle()' prints above message.

If the orca parses some file, the orca makes that file as an object and registers it under root. In the sample object side, rectangle is a member object. so my.rectangle() call rectangle execution code. Orca assume file as object so you can assume below codes are added to file implicitly.

```
def sample #file name
{
	# sample code above	
}
```

This kind of approach in orca can cause confusing to user who is familiar with other OOPs. And there is some overhead (context memory & processing as an object) because every function are an independent object.

But there are many advantages also. You can see those in tutorial but now Let's see some of them by GUI & Web programming.



#2. GUI programming

Previous chapter explains basic concepts of orca. Everything be defined by def and all object have relation with owner & my like tree. This scheme can design many things more easily. 

As an example, Let's see two simple GUI program. If you already have experience about GTK or windows API programming. Maybe be surprised about its simplicity. 

First example is simple GUI button example. Label counter decrease by 1 if you press - button and + button increase label counter.

You can see a demo by below link.

https://youtu.be/og9MEaWCqHc

Below is the code of this program.

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

All Object inherit pre-defined GTK widgets (window, fixed, label and button). The most outer object is main object. And box object which is member of main is for grouping other widgets in it (like div of html). A counter label object and plus, minus button objects are in it.

The execution codes of each objects are used when window is created. (by my.main.make()) to initialize each widgets. 

The main window set its axis (xy) and area (wh) by below codes.
```

def main : window
{
	my.attr['xy'] = (50, 20);
	my.attr['wh'] = (300, 200);
	...
```

The counter object set its relative axis and set its initial text as 0 by below codes.
```
		def counter : label
		{
			my.attr['xy'] = (40, 50);
			my.attr['text'] = 0;
		}
```

The plus button object sets its axis and registers event when it clicked. event action code is set by lambda object like below codes.

find_owner('box') is defined under util module and it find owner whose name is 'box'. So it returns the box object of this program and find_owner('box').counter means the counter label object. then finally it increases counter's text attribute.

The minus button works same opposite way.

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

In this code, widgets view relations and objects relations are same. And event handler (lambda function in this case) change other widget's attribute (text in this case) after find it by using this relation.

Next sample is simple text editor. A box object is in the main window for grouping. A menu object, hs scroll object are in this box object. The hs object include edit object which is used for editor field.

Objects are arranged like previous example (same with its real view relation)



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

The main window's size is set as 800 x 600 by my.attr['wh'].
The menu inherits menubar gtk object. and it's initial code registers file menu in it. file menu has three menu items open, save and exit. and those are represented as name and lambda object pair.

If you chose 'open' from menu lambda function of 'open' menu item will be called. It uses dialog gtk widget to choses file from os. Then read chosen file and set text of box.hs.edit by that file's contents. (box is get by util.find_owner like previous example)
```
			file = [ 'open', lambda(){ 
								name = dialog.fileopen(find_owner('main'));
								str= os.read(name);
								find_owner('box').hs.edit.attr['text'] = str;
							},
```

save is similar but save text of box.hs.edit to chosen file.
exit quit main window and program.
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

You can see the demo of this program by below link.

https://youtu.be/qwcmxUXFNP0



Below link is a more detail lecture about above 2 exmaples.

https://youtu.be/e3TYmBNrhZ8



#3. context extended object

Now I'd like to explain orca web programming. but concepts of context extended object should be explained first. The context extended object is another main aspect of orca programming language. It enables other context module make orca object by its rule and way.

If object is defined by def.html, Codes in { } are passed to html module (with timestamp, name and other information) and html module make orca object by its way.

If you make code like below,
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

The result of above is like below.
The html module makes html_object which have its html text in it. and this object return html code if it is called.

```
$ orca test_html
<html_object - 0xd79280>

    <html>
    <body>
        <p> test html </p>
    </body>
    </html>
```

This context extended object has invented early years of orca. But It has been used to parse lisp or CPP code in orca (like inline assembly)

But now, simple idea is introduced. context extended code can include an orca define code or other context extended object defines. And orca parser passes those objects to exact modules (or parse itself if pure orca object) and bind them automatically

And this aspect is useful to process html template processing.


simple example is below.

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

result 1 shows that html_object is an orca object which is made by html module.
result 2 shows members of html_object. internal members (like __head, __id etc) are made by html module. But made_by_orca_object module is an orca object which is made by orca parser and it inserted to html_object. The html module only gets below codes (except pure made_by_orca_object define)

```
# html module process below codes only
    <html>
    <body>
		%{made_by_orca_object}
    </body>
    </html>
```

result 3 shows the execution result of html_object. html_object process formats in __template format string. In this case, format is %{made_by_orca_objects} this type of format is called dictionary format which is invented in orca. (Read tutorial if you want to get more info)
The html module replaces this with its member whose name is same.

This method doesn't need another view processing function (or class) like other web framework. And html object can contain required logic as it's member. 

Next chapter will show more complex examples.

By the way, context extended object's another useful example is a CPP module. You can add pure CPP code in {} if you define object by def.cpp. Parameters which CPP code get are orcaData type. That type support automatic type conversion so you can use them without casting. (orca programming language is made by C++)


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

Result is like below. Compiling message at first line is auto generating & compile by orca. And that step is done only the first time. (And rebuild again if source code is changed)
```
$ orca test_cpp
cpp external module compile: g++ -fPIC -shared -o ./liborca_sum.so ./sum.cpp -I${ORCA_HOME}/include/orca -L${ORCA_HOME}/lib -lorca
# 10 + 20 = 30
30
```

Some days later def.python, def.ruby will be introduced. Another main goal of orca is hub language.



# 4. Web programming with html and sonar

Let's see orca web programming from now on. It's the major part in this document but needs some concepts to understand so we traverse previous 3 chapters. We already saw GUI programming with orca object in #2. At the first time when I develop orca. I consider the same approach to html programming, Match a DOM with an orca object.

But DOM is differed with GUI widget. widgets in GUI program have its role & actions in it. but DOMS in html are more complex so it's hard to apply same method.

To solve this problem, orca handle html as html text itself by context extended object and process logic in html page by pure (or other) orca object.

And orca provides web development framework Sonar. It referenced the django of python but process html template by html module.


The document about the basic usage of sonar is below link.

https://github.com/lynix94/orca-lang/blob/master/docs/about_sonar_kr.md

Then let's see the sonar example code & execution result video clip here.

The sonar example is located in a below github link.

https://github.com/lynix94/sonar-example

First example is simple page rendering.

The code of this page is a below link.

https://github.com/lynix94/sonar-example/blob/master/ex1.orca/index.orca.html

The demo video clip is a below link.

https://youtu.be/VLD-mqbRKAw



The main code of this is below,

hello, %{name} and def name {} object will be processed runtime to make result html. By the way, Sonar call name object with url request parameter so it can return orca, humpback or blue.

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


There is embed_whale object in code.

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

The embed_whale object check url parameter from req and chose the result depend on whale. (orca, humpback, blue) then it's interested result html.

This method is differed with other web frameworks (like django, flask). They are based on template string processing. Template is just string and are another view controller read it and change it. But orca can group these related objects. 



Next example ex2 is about generating list dynamically.

The page code is a below link,

https://github.com/lynix94/sonar-example/blob/master/ex2.orca/index.orca.html

The  video demo clip is a below link,

https://youtu.be/5yXVhJ3SCqM

Code parts which generate whale list is below,
embed_ prefix means embed return of object to html at that position. embed_wale_list generate list dynamically but this example generates static list. (which are in req.whale_map)


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



ex3 is a simple form processing.


The page code is a below link.

https://github.com/lynix94/sonar-example/blob/master/ex3.orca/index.orca.html

The video demo clip is a below link.

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



ex4 is about orm & simple message board.

The page codes are below links.

main page: https://github.com/lynix94/sonar-example/blob/master/ex4.orca/index.orca.html

message read: https://github.com/lynix94/sonar-example/blob/master/ex4.orca/read.orca.html

new post: https://github.com/lynix94/sonar-example/blob/master/ex4.orca/write.orca.html

model: https://github.com/lynix94/sonar-example/blob/master/ex4.orca/models.orca


The video demo clip is a below link.

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



ex5 is same with ex4 but use html.tag object to generate html tag. 
This html.tag is useful at script handling on next example.

The page code is a below link,

https://github.com/lynix94/sonar-example/blob/master/ex6.orca/index.orca.html


ex6 is about java script handling at sonar.

The page code is a below link,

https://github.com/lynix94/sonar-example/blob/master/ex6.orca/index.orca.html

The video demo clip is a below link,

https://youtu.be/-6uRAqPw7Dk

You can add java script on html text directly or can separate script to html.jquery object.
Below is an example. define hiding script code as def.html.jquery context extended object. This object return string in its block. You can other additional objects in it and use it of course. (like def.html context extended object)

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

Above example show orca can manage javascript as object. But that's not all. Orca can add that in tag object as event.
Below is an example about this.

p tag id_3 is defined and (by chaining) event 'click' is registered to this tag object. An event handler is my.hide_script.
hide_script is a jquery script which hide $(this)

Below is more readable then above example. and relate script is located to target tag and they will be managed together.

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

Orca support lambda object. And lambda object also support context extended object. So you can rewrite above example like below.
It's same but event handler code is located in tag object.
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

Finally, we can see the ajax message board example ex7.

The Page code is a below link,

https://github.com/lynix94/sonar-example/blob/master/ex7.orca/index.orca.html

The video demo clip is a below link,

https://youtu.be/vS8zuJmN50s

In this example, A selected message body is inserted to message list if you click one.
A new message is appended if you make one and submit.

First, prepare check request if there is ajax parameter or not. If exists, prepare call ajax_read_response in case of GET. Or call ajax_write_response in case of POST. By this way, Sonar handle ajax request.

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

The embed_input_form is changed to handle ajax by pass 2nd parameter to submit. It means object to executed if it clicked.

The submin_handler is called and send form data to the sonar by POST. then this will get ajax_write_response result.  The ajax_write_reponse save message to DB by orm module. then return new message as partial html tag.

Then submit_handler add this new message to next of .title class tag.

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

A reading parts of code is also changed like below.

The page register event to id of message when html is generated. So the click_handler is called when that message is clicked.

The click_handler request message contents with ajax parameter. And the sonar call ajax_read_handler and return result of that object. Then the click_handler append this message to the page.
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

You can see the full detail explaination by below clip.

https://youtu.be/AblG8c7t5qQ



We traversed basic aspects of the orca programming language briefly. You can read tutorial.md, module.md for more detail information. And can see more video clips on youtube. (I'll add more clips periodically so I recommend to subscribe if you want)

Any kinds of contribution like bug reporting or pull request are welcome. 
Don't hesitate to contact or ask about the orca by below links.

Thanks for reading. :)

project page:	https://github.com/lynix94/orca-lang
facebook page:	https://www.facebook.com/orcalang
youtube:		https://www.youtube.com/channel/UC0bUKWj0aoWgbh9KaqJu8gw
email:			kiyeul.lee@gmail.com
linked-in:		https://www.linkedin.com/in/kiyeul-lee






