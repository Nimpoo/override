int main(int argc, char **argv)
{
	int v4;

	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	puts("***********************************");

	printf("Password:");
	__isoc99_scanf("%d", &v4);

	if (v4 == 5276) {
		puts("\nAuthenticated!");
		system("/bin/sh");
		return 0;
	}

	else {
		puts("\nInvalid Password!");
		return 1;
	}
}
