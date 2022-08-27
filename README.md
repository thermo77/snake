# Ncurses Snake

![gameplay](./gameplay.gif)


A simple snake game written in C that uses the ncurses library. Control the snake using the WASD keys and eat the randomly spawning food to get bigger and increase your score. 


# Installation


**Arch**
```
$ sudo pacman -S build-essential
```
```
$ sudo pacman -S ncurses
```
```
$ gcc -lncurses main.c
```


**Debian Based**
```
$ sudo apt-get install build-essential
```
```
$ sudo apt-get install libncurses5-dev libncursesw5-dev
```
``` 
$ gcc -lncurses main.c
```


**Fedora**
```
$ sudo yum install gcc
```
```
$ sudo dnf install ncurses-devel
```
```
$ gcc -lncurses main.c
```
