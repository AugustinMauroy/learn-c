#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool isletter(char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isNotLetter(char c){
	return (c < 'a' || c > 'z') && (c < 'A' || c > 'Z');
}

int main(void){
	char phrase[100];

	printf("Enter a phrase: ");
	fgets(phrase, 100, stdin);

	int start_word = 0;
	int end_word = 0;
	int count = 0;
	bool isWord = false;

	while(phrase[end_word] != '\0'){
		if(isletter(phrase[end_word])){
			if(!isWord){
				isWord = true;
				start_word = end_word;
			}
			count++;
		}else if(isWord){
			printf("Word: ");
			for(int i = start_word; i < end_word; i++){
				printf("%c", phrase[i]);
			}
			printf("\nLength: \033[0;32m%d\033[0m\n", count);
			count = 0;
			isWord = false;
		}
		end_word++;
	}

	return EXIT_SUCCESS;
}
