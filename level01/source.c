#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char a_user_name[100];

bool verify_user_name()
{
	puts("verifying username....\n");
	return memcmp(a_user_name, "dat_wil", 7) != 0;
}

bool verify_user_pass(const void *a1)
{
	return memcmp(a1, "admin", 5) != 0;
}

int main(int argc, char **argv)
{
	char s[64];
	bool v5;

	memset(s, 0, sizeof(s));
	v5 = 0;

	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(a_user_name, 256, stdin);
	v5 = verify_user_name();

	if (v5) {
		puts("nope, incorrect username...\n");
	}

	else {
		puts("Enter Password: ");
		fgets(s, 100, stdin);

		v5 = verify_user_pass(s);
		puts("nope, incorrect password...\n");
	}

	return 1;
}
