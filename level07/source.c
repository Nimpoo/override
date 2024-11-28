#include <stdbool.h>
#include <stdio.h>

int clear_stdin()
{
	int result;

	do
		result = getchar();
	while ((unsigned char)result != 10 && (unsigned char)result != 0xFF);

	return result;
}

int get_unum()
{
	int number;

	fflush(stdout);
	scanf("%d", &number);
	clear_stdin();
	return number;
}

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

int read_number(int *a1)
{
	int unum;

	printf(" Index: ");
	unum = get_unum();
	printf(" Number at data[%u] is %u\n", unum, a1[4 * unum]);

	return 0;
}

int main(int argc, const char **argv, const char **envp)
{
	unsigned char v6[400];
	int number;
	char s[20];
	unsigned int v13;

	v13 = __readgsdword(0x14u);
	number = 0;
	bzero(s, 20);
	memset(v6, 0, sizeof(v6));

	while (*argv) {
		memset((void *)*argv, 0, strlen(*argv));
		++argv;
	}

	while (*envp) {
		memset((void *)*envp, 0, strlen(*envp));
		++envp;
	}

	puts(
		"----------------------------------------------------\n"
		"  Welcome to wil's crappy number storage service!   \n"
		"----------------------------------------------------\n"
		" Commands:                                          \n"
		"    store - store a number into the data storage    \n"
		"    read  - read a number from the data storage     \n"
		"    quit  - exit the program                        \n"
		"----------------------------------------------------\n"
		"   wil has reserved some storage :>                 \n"
		"----------------------------------------------------\n"
	);

	while (true) {
		printf("Input command: ");
		number = 1;
		fgets(s, 20, stdin);
		s[strlen(s) - 1] = 0;

		if (!memcmp(s, "store", 5u))
			number = store_number(v6);

		else if (!memcmp(s, "read", 4u))
			number = read_number(v6);

		else if (!memcmp(s, "quit", 4u))
			return 0;

		if (number)
			printf(" Failed to do %s command\n", s);
		else
			printf(" Completed %s command successfully\n", s);

		bzero(s, 20);
	}
}
