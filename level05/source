#include <stdio.h>

int main(int argc, char **argv)
{
	char s[100];
	unsigned int i;

	i = 0;
	fgets(s, 100, stdin);
	for (i = 0; i < strlen(s); ++i) {
		if (s[i] > 64 && s[i] <= 90)
			s[i] = s[i] ^ 0x20u;
	}
	printf(s);
	exit(0);
}
