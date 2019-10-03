### using orca by docker image

orca pre built docker image exists.

get docker image like below.

```
docker pull lynix94/orca-lang:latest
```

run below command to enable x11 redirection
```
xhost +local:docker
```

Run docker image like below (add below options to use gtk display)

```
docker run -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=unix$DISPLAY -it orca-lang:latest bash
```


orca home is /orca and source code of orca is in /orca-lang

You can type 'orca' to run interepeter.
or you can run test files in /orca-lang/tests like below

```
lynix@lynix-ThinkPad-X390:~/lab/orca$ docker run -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=unix$DISPLAY -it orca-lang:latest bash
root@de0b8acc27e8:/# orca
$ print('hello, orca from docker');
hello, orca from docker
$ ^C
root@de0b8acc27e8:/# 
root@de0b8acc27e8:/# cd orca-lang/tests
root@de0b8acc27e8:/orca-lang/tests# orca test
### Test: test_arith start
add
sub
mul
div
mod
mix
22
assign op
real test
add
sub
mul
div
mix
22.5
...

```




