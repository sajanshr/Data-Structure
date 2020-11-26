#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum priority{
	Low,
	Medium,
	High
};
typedef struct bug BUG;
struct bug{
	char *description;
	enum priority p;
	BUG *next;
};
BUG *push(BUG *head){
	BUG *new = calloc(1,sizeof(BUG));
	char buffer[128] = {0};
	printf("Description: ");
	fgets(buffer, 128, stdin);
	buffer[strlen(buffer)-1] = 0;
	new->description = strdup(buffer);
	printf("Priority(0,1,2): ");
	fgets(buffer, 128, stdin);
	buffer[strlen(buffer)-1] = 0;
	new->p = atoi(buffer);
	new -> next = head;
	return new;
	
}
void print_menu(){
	printf("\n1.Report bug\n");
	printf("2.View current bug\n");
	printf("3.Quit\n");
}

BUG *pop(BUG **head){
	BUG *result = NULL;
	if (*head != NULL) {
		result = *head;
		*head = (*head)->next;
	}

	return result;
}
void free_BUG(BUG *n) {
    while (n != NULL) {
       free(n->description);
	   n = n->next;
	   free(n);
       
    }
}


int main(){
	BUG *head = NULL;
	int userInput =0;
	while(userInput!=3){
		print_menu();
		scanf("%d",&userInput);
		getchar();
		if(userInput==1){
			if(head==NULL){
				head = push(NULL);
			}
			else{
				head = push(head);
			}
		}
		else if(userInput==2){
			if(head==NULL){
				printf("Empty List!\n");
			}
			else{
				printf("Description: %s\n", head->description);
				printf("Priority(0,1,2): %d", head->p);
				printf("\n1.Mark as fixed\n");
				printf("2.Go back\n");
				scanf("%d", &userInput);
				if(userInput==1){
					BUG * result = pop(&head);
					printf("%s is marked as fixed\n", result->description);
					free(result->description);
					free(result);
				}
			}	
			
		}
		else if(userInput==3){
			break;
		}
	}
	free_BUG(head);
	
	
}