#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>

char *set_msg(int64_t a1);
int set_username(int64_t a1);

int secret_backdoor()
{
	char s[128];

	fgets(s, 128, stdin);
	return system(s);
}

int handle_msg()
{
	char v1[140];
	int64_t v2;
	int64_t v3;
	int64_t v4;
	int64_t v5;
	int64_t v6;
	int v7;

	v2 = 0LL;
	v3 = 0LL;
	v4 = 0LL;
	v5 = 0LL;
	v6 = 0LL;
	v7 = 140;
	set_username((int64_t)v1);
	set_msg((int64_t)v1);
	return puts(">: Msg sent!");
}

char *set_msg(int64_t a1)
{
	char s[1024];

	memset(s, 0, sizeof(s));
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(s, 1024, stdin);
	return strncpy((char *)a1, s, *(int *)(a1 + 180));
}

int set_username(int64_t a1)
{
	char s[140];
	int i;

	memset(s, 0, 0x80uLL);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(s, 128, stdin);
	for ( i = 0; i <= 40 && s[i]; ++i )
		*(unsigned char *)(a1 + i + 140) = s[i];
	return printf(">: Welcome, %s", (const char *)(a1 + 140));
}

int main(int argc, char **argv)
{
	puts(
		"--------------------------------------------\n"
		"|   ~Welcome to l33t-m$n ~    v1337        |\n"
		"--------------------------------------------");
	handle_msg();
	return 0;
}
