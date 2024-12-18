# level00

![level00](Ressources/title_screen00.png)

# _Let's keep our good habits :_

```sh
level00@OverRide:~$ ./level00 
***********************************
*            -Level00 -           *
***********************************
Password:Garp >>>> all

Invalid Password!
level00@OverRide:~$ ./level00 D
***********************************
*            -Level00 -           *
***********************************
Password:Kid <<<< all

Invalid Password!
level00@OverRide:~$ 
```

Before decompiling the binary, we can try to make it without de source code for more challenge (you can see the [source code in the `source` file](source.c) and the [decompiled file by `hex-rays`](Ressources/binary_00-hex-rays.png) in the `Ressources` folder). :

```sh
(gdb) disass main
Dump of assembler code for function main:
   0x08048494 <+0>:	push   ebp
   0x08048495 <+1>:	mov    ebp,esp
   0x08048497 <+3>:	and    esp,0xfffffff0
   0x0804849a <+6>:	sub    esp,0x20
   0x0804849d <+9>:	mov    DWORD PTR [esp],0x80485f0
   0x080484a4 <+16>:	call   0x8048390 <puts@plt>
   0x080484a9 <+21>:	mov    DWORD PTR [esp],0x8048614
   0x080484b0 <+28>:	call   0x8048390 <puts@plt>
   0x080484b5 <+33>:	mov    DWORD PTR [esp],0x80485f0
   0x080484bc <+40>:	call   0x8048390 <puts@plt>
   0x080484c1 <+45>:	mov    eax,0x804862c
   0x080484c6 <+50>:	mov    DWORD PTR [esp],eax
   0x080484c9 <+53>:	call   0x8048380 <printf@plt>
   0x080484ce <+58>:	mov    eax,0x8048636
   0x080484d3 <+63>:	lea    edx,[esp+0x1c]
   0x080484d7 <+67>:	mov    DWORD PTR [esp+0x4],edx
   0x080484db <+71>:	mov    DWORD PTR [esp],eax
   0x080484de <+74>:	call   0x80483d0 <__isoc99_scanf@plt>
   0x080484e3 <+79>:	mov    eax,DWORD PTR [esp+0x1c]
   0x080484e7 <+83>:	cmp    eax,0x149c
   0x080484ec <+88>:	jne    0x804850d <main+121>
   0x080484ee <+90>:	mov    DWORD PTR [esp],0x8048639
   0x080484f5 <+97>:	call   0x8048390 <puts@plt>
   0x080484fa <+102>:	mov    DWORD PTR [esp],0x8048649
   0x08048501 <+109>:	call   0x80483a0 <system@plt>
   0x08048506 <+114>:	mov    eax,0x0
   0x0804850b <+119>:	jmp    0x804851e <main+138>
   0x0804850d <+121>:	mov    DWORD PTR [esp],0x8048651
   0x08048514 <+128>:	call   0x8048390 <puts@plt>
   0x08048519 <+133>:	mov    eax,0x1
   0x0804851e <+138>:	leave  
   0x0804851f <+139>:	ret    
End of assembler dump.
(gdb) 
```

We can notice th line `<+83>` : **`cmp`**
- The instruction `cmp` in assembly only compare the two values. If they are equal, the next instruction will be `je` (for `Jump if Equal`) or `jne` (for `Jump if Not Equal`).
- Here, the value `0x149c` is compared to the value stored in the memory address `[esp+0x1c]` (which is the value we entered).
- The next instruction after `cmp` is `jnp 0x804850d <main+121>`, which means the program jumps to the line `<+121>`. At this line, it prints probably "Invalid Password!" with `puts` then finishes the program (finish with a `prologue` if you want the technical term).

> We can check if `0x8048651` is the address of the string "Invalid Password!" :
```sh
(gdb) x/s 0x8048651
0x8048651:	 "\nInvalid Password!"
(gdb) 
```
> Yes ! It is !

## _What we can do ?_

Too simple, see what our input is compared to and change it to the good value : `0x149c`

```sh
(gdb) print 0x149c
$2 = 5276
(gdb) 
```

Our input is compared to `0x149c` and if it is equal, the program will execute the `system` function with the argument `"/bin/sh"`. So we can just enter `5276` as input and we will get a shell. Else, the program will print "Invalid Password!" and return.

> How to convert `hexadecimal` to `decimal` ? <br /> `0x149c` is equal to `0x0000149c`. <br /> c = 12, 12 * 1 = 12 <br /> 9 * 16 = 144 <br /> 4 * 256 = 1024 <br /> 1 * 4096 = 4096 <br /> 12 + 144 + 1024 + 4096 = 5276  <br /> For each digit, we multiply it by 16 to the power of the position of the digit in the number (starting from 0).

# _OKAY, let's do it !_

```sh
level00@OverRide:~$ ./level00 
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ 
```

# EASY FIRST LEVEL

Let's get the flag, and go to the next level :

```sh
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
$ 
level00@OverRide:~$ su level01
Password: 
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/users/level01/level01
level01@OverRide:~$ 
```

# level00 complet !
![yeah](../assets/yeah.gif)
