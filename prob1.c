#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book Book;
struct book{
	char *title;
	char *author;
	Book *next;
};

Book *addBook(char *rawCsv){

	Book *b = (Book*)calloc(1,sizeof(Book));
	char *token = NULL;
	token = strtok(rawCsv, ",");
	b->title = strdup(token);

	
	token = strtok(NULL, ",");
	b->author = strdup(token);

	return b;
	
	
}


void traverse(Book *b) {
	if (b != NULL) {
		
		printf("%s\n",b->title );
		traverse(b->next);
	}
}

void findBooks(char *authorname, Book *b1){
	Book *head1, *temp1, *sameAuthorBooks;
	head1 = temp1 = NULL;
	while(b1 != NULL){
		
		if(strcmp(authorname, (b1->author))==0){
			sameAuthorBooks = (Book*)calloc(1,sizeof(Book));
			sameAuthorBooks -> title = strdup(b1->title);
		
			if(head1 ==NULL){
				head1 = sameAuthorBooks; 
				temp1 = head1;
			}
			else{
				temp1->next = sameAuthorBooks;
				temp1 = temp1->next;
			}
		}
				b1 = b1->next;
	}
	temp1 = head1;
	traverse(temp1);
	while (head1 != NULL)
    {
       temp1 = head1;
       head1 = head1->next;
	   free(temp1->title);
	   free(temp1);
       
    }
	
		
}




int main(int argc, char **argv){
	char buffer[128] = {0};
	FILE * fp = NULL; 
	fp = fopen(argv[1], "r");
	Book *current, *head;
	current = NULL;
	head = NULL;
	while(!feof(fp)){	
		fgets(buffer, 128, fp);
		buffer[strlen(buffer)-1] = 0;
		if (head == NULL) {
			head = addBook(buffer);
			current = head;
		
			
		} else {
			current->next = addBook(buffer);
			current = current->next;
		
		}
		
	}
	current = head;
	printf("Enter author: ");
	fgets(buffer, 128, stdin);
	buffer[strlen(buffer)-1] = 0;
	findBooks(buffer, current);
	fclose(fp);
	while (head != NULL)
    {
       current = head;
       head= head->next;
	   free(current->title);
	   free(current->author);
	   free(current);
       
    }
	
	
	

	return 0;
}
