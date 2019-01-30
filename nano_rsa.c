#include "nano_rsa.h"

int is_prime(unsigned int p){
	unsigned int i;

	for(i = 2;i < p;i++){
		if((p % i) == 0) return 0;
	}

	return 1;
}

unsigned int nearst_prime(unsigned int p){
	
	while(1){
		if(is_prime(p)) return p;
		else p--;
	}

}

unsigned int mdc(unsigned int a,unsigned int b){
// Euclides algorithm
	if(b == 0) return a;
	else return mdc(b,a%b);
}

void generate_keys(Key* public,Key* private){
	unsigned int p,q;

	srand(time(NULL));
	p = (rand() % 100) + 3;
	q = (rand() % 200) + 5;

	p = nearst_prime(p);
	q = nearst_prime(q);
	if(p == q) q = nearst_prime(q - 1);

	printf("p  : %d\nq  : %d\n",p,q);

	unsigned int n;
	unsigned int on;

	n  = p*q;
	on = (p-1)*(q-1);

	printf("n  : %d\non : %d\n",n,on);
	
	unsigned int e;

	do
		e = rand() % (on - 2) + 2;
	while(mdc(e,on) != 1);

	printf("e  : %d [%d]\n",e,mdc(e,on));

	unsigned int d;
//Check if $d is less than $on
	d = 1;
	while(((e%on)*(d%on))%on != 1 || d == e) d++;


//	unsigned int k;
//	k = 6;
//
//	d = (k*on + 1)/e;

	printf("d  : %u [%u|%u]\n",d,(e*d)%on,1%on);

	public->n  = n;
	private->n = n;

	public->c  = e;
	private->c = d;
}

unsigned int squaring_algorithm(unsigned int x,unsigned int n){
	unsigned int aux = 1;

	if(n == 1) return x;
	if(n % 2 == 0) squaring_algorithm(x*x,n/2);
	else squaring_algorithm(x*x,(n - 1)/2);

//-------------------------------------------------------------------------------------------------
	while(n != 1){
		x = x*x;

		if(n % 2 == 0) n = n/2;
		else n = (n - 1)/2;
	}

}


unsigned int *encrypt(Key *public,char* message,int nro_chars){
	unsigned int i,j;
	unsigned int *encrypt_text;	

	encrypt_text = (unsigned int *) malloc(sizeof(unsigned int)*nro_chars);
	for(i = 0;i < nro_chars;i++){
		unsigned int aux;
		long unsigned int lim1;

		aux = message[i]%public->n;
		lim1 = public->c % (public->n - 1);
		for(j = 1;j < lim1;j++) {
			aux *= (message[i]%public->n);
			aux = aux % public->n;
		}

		encrypt_text[i] = aux;
	}	

	for(i = 0;i < nro_chars;i++) printf("%u",encrypt_text[i]);
	printf("\n");

	return encrypt_text;
}

char *decrypt(Key *private,unsigned int* message,int nro_chars){
	unsigned int i,j;
	char *dencrypt_text;	

	dencrypt_text = (char *) malloc(sizeof(char)*nro_chars);
	for(i = 0;i < nro_chars;i++){
		unsigned int aux;
		long unsigned int lim2;

		aux = message[i]%private->n;
		lim2 = private->c % (private->n - 1);

		for(j = 1;j < lim2;j++) {
			aux *= (message[i]%private->n);
			aux = aux % private->n;
		}

		dencrypt_text[i] = aux;
	}	

	
	for(i = 0;i < nro_chars;i++) printf("%c",dencrypt_text[i]);
	printf("\n");

	return dencrypt_text;
}

int *test(Key *private,Key *public,char* message,int nro_chars){
	long unsigned int i,j;
	long unsigned int *encrypt_text;	

	encrypt_text = (long unsigned int *) malloc(sizeof(long unsigned int)*nro_chars);
	for(i = 0;i < nro_chars;i++){
		long unsigned int aux;
		long unsigned int lim1,lim2;

		aux = message[i]%public->n;

		lim1 = public->c % (public->n - 1);
	//	printf("%d -> %d\n",public->c,lim1);
		for(j = 1;j < lim1;j++) {
			aux *= (message[i]%public->n);
			aux = aux % public->n;
		}

		encrypt_text[i] = aux;

		aux = encrypt_text[i]%private->n;

		lim2 = private->c % (private->n - 1);
	//	printf("%d -> %d\n",private->c,lim2);
		for(j = 1;j < lim2;j++) {
			aux *= (encrypt_text[i]%private->n);
			aux = aux % private->n;
		}

	//	printf("%c(%d) [%lu] [%d]\n",message[i],message[i],encrypt_text[i],aux);
	}	

//	for(i = 0;i < nro_chars;i++) printf("%d",encrypt_text[i]);
//	printf("\n");
	return encrypt_text;
}
