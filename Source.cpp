#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
	int ani;
	char nume[50];

	printf("Introduceti numele: ");
	fgets(nume, sizeof(char), stdin);

	printf("Introduceti ani: ");
	scanf("%i", &ani);

	printf("Numele tau este %s si ai %i ani.", nume, ani);

	return 0;
}