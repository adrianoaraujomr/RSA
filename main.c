#include "nano_rsa.h"

int main(int argc,char* argv[]){
	int *aux;
	unsigned int *enc;
	char *dec;
	char message[18] = "Lady Maria";
	Key private,public;
	unsigned int ascii = 256,xua = 1,xuaa = 1;
	int i;

	generate_keys(&public,&private);

//	gets(message);
	printf("%s [%lu]\n",message,sizeof(message));
//	for(i = 1;i < public.c;i++){
//		xuaa = xua;
//		xua = xua * ascii;
//		printf("[%d] : %d\n",i,xua);
//		if(xua < xuaa) break;
//	}
//	test(&private,&public,message,10);

	enc = encrypt(&public,message,strlen(message));
	dec = decrypt(&private,enc,strlen(message));

	for(i = 0;i < strlen(message);i++) printf("%u",enc[i]);
	printf("\n");
	printf("%s\n",dec);

	return 0;
}
