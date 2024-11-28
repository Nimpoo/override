#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

bool auth(char *s, int a2)
{
	int i;
	int v4;
	int v5;

	s[strcspn(s, "\n")] = 0;
	v5 = strnlen(s, 32);
	if (v5 <= 5)
		return 1;
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
		puts("\x1B[32m.---------------------------.");
		puts("\x1B[31m| !! TAMPERING DETECTED !!  |");
		puts("\x1B[32m'---------------------------'");
		return 1;
	} else {
		v4 = (s[3] ^ 0x1337) + 6221293;
		for (i = 0; i < v5; ++i) {
			if (s[i] <= 31)
				return 1;
			v4 += (v4 ^ (unsigned int)s[i]) % 0x539;
		}
		return a2 != v4;
	}
}
// 80485D0: using guessed type int __cdecl strnlen(_DWORD, _DWORD);

//----- (08048879) --------------------------------------------------------
int main(int argc, char **argv)
{
	int v4;
	char s[28];
	unsigned int v6;

	v6 = __readgsdword(0x14u);
	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(s, 32, stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%d", &v4);
	if (auth(s, v4))
		return 1;
	puts("Authenticated!");
	system("/bin/sh");
	return 0;
}
