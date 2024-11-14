#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool auth(char *s, int a2)
{
  int i;
  int v4;
  int v5;

  s[strcspn(s, "\n")] = 0;
  v5 = strnlen(s, 32);

  if ( v5 <= 5 )
    return 1;

	/*
	*	Removing the ptrace function call
	*/

  v4 = (s[3] ^ 0x1337) + 6221293; // ? 0x1337 = 4919

  for ( i = 0; i < v5; ++i )
  {
    if ( s[i] <= 31 )
      return 1;

    v4 += (v4 ^ (unsigned int)s[i]) % 0x539; // ? 0x539 = 1337
  }

  printf("Your login : [%s] --- Its serial : [%d]\n", s, v4);
  return a2 != v4;
}

int main(int argc, char **argv)
{
  int v4;
  char s[28];
  unsigned int v6;

  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");

  printf("-> Enter Login: ");
  fgets(s, 32, stdin);

	// tkt
	if (strcmp(s, "Eustass Kid is not that bad\n") == 0) {
		printf("\n");
		printf("\033[1mPARDON ?????????????!!!!!!!!!!!!\033[0m\n");
		printf("\n");
		printf("Eustass \"Captain\" Kid, souvent présenté comme l'un des Supernovae les plus prometteurs dans l'univers de One Piece, est en réalité une énorme fraude et un idiot fini. Bien qu'il soit doté d'une prime impressionnante et d'une réputation redoutable, ses actions et ses décisions révèlent un manque flagrant de jugement et de compétence. Tout d'abord, Kid a tendance à sous-estimer ses adversaires et à surestimer ses propres capacités, ce qui le conduit souvent à des échecs cuisants. Par exemple, lors de son affrontement avec Kaido, l'un des Quatre Empereurs, Kid a montré une arrogance démesurée en pensant pouvoir le vaincre seul, ce qui a résulté en une défaite humiliante et une perte significative de ses forces. De plus, Kid manque cruellement de stratégie et de finesse tactique. Il préfère souvent la force brute à la ruse, ce qui le rend prévisible et vulnérable face à des ennemis plus rusés. Son obsession pour la puissance et sa quête de vengeance contre Shanks l'aveuglent, le poussant à prendre des décisions impulsives et irréfléchies. En outre, Kid n'a pas su tirer les leçons de ses échecs passés, continuant à répéter les mêmes erreurs et à se mettre en danger inutilement. En somme, malgré son potentiel et sa force brute.\n");
		printf("Kid est un pirate incompétent et un leader médiocre qui ne mérite pas sa réputation ni sa prime élevée.\n");
		printf("\n");
		printf("\033[1;31mKid est un personnage qui manque de sagesse, de stratégie et de discernement, ce qui en fait une véritable fraude dans le monde impitoyable de One Piece.\033[0m\n");
		return 1;
	}

  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");

  scanf("%d", &v4);

  if (auth(s, v4))
    return 1;

  puts("Authenticated!");
  return 0;
}
