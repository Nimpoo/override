#include <stdio.h>

int clear_stdin()
{
  int result;

  do
    result = getchar();
  while ( (char)result != 10 && (char)result != 0xFF );
  return result;
}

int get_unum()
{
  int v1[3];

  v1[0] = 0;
  fflush(stdout);
  __isoc99_scanf("%u", v1);
  clear_stdin();
  return v1[0];
}

void prog_timeout()
{
  int v0;

  v0 = sys_exit(1);
}

int decrypt(char a1)
{
  unsigned int i;
  unsigned int v3;
  char v4[29];

  *(int *)&v4[17] = __readgsdword(0x14u);
  strcpy(v4, "Q}|u`sfg~sf{}|a3");
  v3 = strlen(v4);
  for ( i = 0; i < v3; ++i )
    v4[i] ^= a1;
  if ( !strcmp(v4, "Congratulations!") )
    return system("/bin/sh");
  else
    return puts("\nInvalid Password");
}

int test(int a1, int a2)
{
  int result;
  char v3;

  switch ( a2 - a1 )
  {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
      result = decrypt(a2 - a1);
      break;
    default:
      v3 = rand();
      result = decrypt(v3);
      break;
  }
  return result;
}

int main(int argc, char **argv)
{
  unsigned int v3;
  int savedregs;

  v3 = time(0);
  srand(v3);

  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");

  printf("Password:");
  __isoc99_scanf("%d", &savedregs);

  test(savedregs, 322424845);

  return 0;
}
