#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 255

// Cesar encryption
char* CesarCript(char* string, int key, int len)
{ 
    char *Out = (char*)malloc(sizeof(char) * len);
    for (int i = 0; i < len; i++)
    {
        *(Out + i) = *(string + i) + key;
    }
    return Out;
}

char* CesarDecript(char* string, int key, int len)
{
    char *Out = (char*)malloc(sizeof(char) * len);
    for (int i = 0; i < len; i++)
    {
        *(Out + i) = *(string + i) - key;
    }
    return Out;
}

// Column encryption
char* ColCriptDecript(char* string, int key, int len, int encrypt){
    // as the code is veeery similar for encode / decode, there is single function
    char *Out = (char*)malloc(sizeof(char) * len);
    int inCol = (len / key);
    if (len % key > 0) inCol++;
    int ii = 0;
    for (int i = 0; i < len; i++)
    {
        int ind = ii / key + inCol * (ii % key); // calculating position of character in non-encoded string
        ii++;
        if (ind >= len) // a little trick to allow encode / decode a string with {len % key != 0}
        {
            i--;
            continue;
        }
        if (encrypt)
            *(Out + i) = *(string + ind);
        else
            *(Out + ind) = *(string + i);
    }
    return Out;
}

// Utilities
int GetCharLen(char* string);
void printChar(char* string, int len);

//--------------------------------------------//
int main(int argc, char **argv)
{
    char static word[MAX_SIZE] = {NULL};
    int key = 0;
    printf("Enter the word: ");
    gets(&word);
    printf("Enter encription key for cesar encryption: ");
    scanf("%d",&key);
    int len = GetCharLen(&word);
    // Cesar show 
    char *encripted = CesarCript(&word, key, len);
    printf("Encrypted by Cesar: ");
    printChar(encripted, len);
    char *decripted = CesarDecript(encripted, key, len);
    printf("Decrypted by Cesar: ");
    printChar(decripted, len);
    
    printf("Enter encription key for column encryption: ");
    scanf("%d",&key);
    // column show
    char *ColEncripted = ColCriptDecript(&word, key, len, 1);
    printf("Encrypted by Column: ");
    printChar(ColEncripted, len);
    char *ColDecripted = ColCriptDecript(ColEncripted, key, len, 0);
    printf("Decrypted by Column: ");
    printChar(ColDecripted, len);
    
	return 0;
}

int GetCharLen(char* string)
{
    for(int i = 0; i < MAX_SIZE; i++ )
        if (*(string + i) == NULL)
            return i;
    return MAX_SIZE;
}

void printChar(char* string, int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("%c",*(string+i));
    }
    printf("\n");
}
