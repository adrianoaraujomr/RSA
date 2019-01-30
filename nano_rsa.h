#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

typedef struct rsa_key{
	unsigned int n;
	unsigned int c;
} Key;

void generate_keys(Key* public,Key* private);
unsigned int *encrypt(Key *public,char* message,int nro_chars);
char *decrypt(Key *private,unsigned int* message,int nro_chars);
int *test(Key *private,Key *public,char* message,int nro_chars);
