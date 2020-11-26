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
	printf("[DEBUG] %s\n", rawCsv);
	Book *b = (Book*)calloc(1,sizeof(Book));
	char *token = NULL;
	token = strtok(rawCsv, ",");
	b->title = strdup(token);
	//b->title = token;
	
	token = strtok(NULL, ",");
	b->author = strdup(token);
	//b->author = token;
	return b;
	
	
}
void freeList(Book* head2)
{
   Book* tmp;

   while (head2 != NULL)
    {
       tmp = head2;
       head2 = head2->next;
       free(tmp);
    }

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
			//printf("%s\n", b1->title);
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
       
    }
	
	freeList(head1);
		
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
			//printf("[DEBUG] %s\n", current->title);
			//printf("[DEBUG] %s\n", current->author);
			
		} else {
			current->next = addBook(buffer);
			current = current->next;
			//printf("[DEBUG] %s\n", current->title);
			//printf("[DEBUG] %s\n", current->author);
		}
		
	}
	current = head;
	//traverse(current);
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
       
    }
	freeList(head);
	
	

	return 0;
}