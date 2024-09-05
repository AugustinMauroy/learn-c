#include <stdio.h>
#include <stdlib.h>

int str_len(char *str){
    int i = 0;
    while (str[i] != '\0')i++;
    return i;
}

// version using pointer arithmetic
/*
int str_len(char *str){
       int c=0;
    while(*p!='\0')
    {
        c++;
        *str++;
    }
    return(c);
}
*/

int count_space(char *str){
	int i = 0;
	int count = 0;
	while(str[i] != '\0'){
		if(str[i] == ' '){
			count++;
		}
		i++;
	}
	return count;
};

int main(void){
	char phrase[100];
  printf("Enter a phrase: ");
  fgets(phrase, 100, stdin);
  //printf("The length of the phrase is: %d\n", str_len(phrase));
  
	// i need to be declared
	// outside of the scope of the for loop
	int i;
	for(i = 0; phrase[i] != '\0'; i++);
	i--;
	phrase[i] = '\0'; // to chot off the newline character
 	printf("The length of the phrase is: %d\n", i);
	printf("The number of spaces in the phrase is: %d\n", count_space(phrase));

	return EXIT_SUCCESS;
}
