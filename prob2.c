#include<stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct book Book;
struct book{
	char *title;
	char *author;
	Book *next;
};

void enqueue(Book *newbook,Book **head) {
	if(*head == NULL){
		*head = newbook;
		return;
	}
	Book *temp = *head;
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp -> next = newbook;
}

void printMenu(){
	printf("1. Add Book\n");
	printf("2. View Book\n");
	printf("3. Quit\n");
}

Book *dequeue(Book **head){
	Book *result = NULL;
	if(*head != NULL){
		result = *head;
		(*head) = (*head)->next;
	}
	return result;
}
void free_Book(Book *n) {
    while (n != NULL) {
       free(n->title);
	   free(n->author);
	   n = n->next;
	   free(n);
       
    }
}


int main(){
	Book *head = NULL;
	int userInput = 0;
	char buffer[128] = {0};
	while(userInput != 3){
		printMenu();
		scanf("%d", &userInput);
		getchar();
		if(userInput == 1){
			Book *books = malloc(sizeof(Book));
			printf("Enter the Book Title: ");
			fgets(buffer, 128, stdin);
			buffer[strlen(buffer)-1] = 0;
			(books -> title) = strdup(buffer);
			printf("Enter the Book Author: ");
			fgets(buffer, 128, stdin);
			buffer[strlen(buffer)-1] = 0;
			(books-> author) = strdup(buffer);
			
			enqueue(books, &head);
		}
		else if(userInput == 2){
			if(head == NULL){
				printf("Empty List!\n");
			}
			else{
				printf("%s by %s\n", head->title, head->author);
				printf("1. Mark as Read\n");
				printf("2. Go back \n");
				scanf("%d", &userInput);
				getchar();
				if(userInput == 1){
					Book *resultbook = dequeue(&head);
					printf("%s is mark as Read\n ", resultbook->title);
					free(resultbook->title);
					free(resultbook->author);
					
					free(resultbook);
				}
			
			}	
			
		}
		else if(userInput == 3){
			break;
		}
	
	}
	free_Book(head);
	return 0;
}