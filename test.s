++++ start ++++
Function: func1
ret type: char
arg list:
int a1
char a2
--
vari list:
int a
char b
--
state list:
Session: s1
Assign:
b = -1  
Assign:
a = a 1 + b -  
Goto: s1
Return:a b 3 * +  
================
Function: main
ret type: int
arg list:
int a
char b
--
vari list:
int c
int d
char e
char* f
--
state list:
------
Function call:
name: func1
arg pass list:
c d +  
e  
------
Return:0  
================
++++  end  ++++
