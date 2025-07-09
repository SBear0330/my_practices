#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    struct node *prev;
    struct node *next;
    int data;

}node;

node *HEAD;
node *TAIL;

#define FIRST_ENTRY HEAD->next
#define LAST_ENTRY TAIL->prev

node *create_node(int data) {
    node *new_node = malloc(sizeof(node));

    if (new_node == NULL) {
        fprintf(stderr, "failed to make new node.\n");
        exit(EXIT_FAILURE);
    }

    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->data = data;

    return new_node;
}

void list_init() {
    HEAD = create_node(0);
    TAIL = create_node(0);

    HEAD->next = TAIL;
    TAIL->prev = HEAD;

}

bool list_empty() {return (FIRST_ENTRY == TAIL && LAST_ENTRY == HEAD);}

void insert_first(node *cur) {
    cur->next = FIRST_ENTRY;
    cur->prev = HEAD;
    FIRST_ENTRY->prev = cur;
    FIRST_ENTRY = cur;
    
}

void insert_last(node *cur) {
    cur->prev = LAST_ENTRY;
    cur->next = TAIL;
    LAST_ENTRY->next = cur;
    LAST_ENTRY = cur;

}

void del_first() {
    node *temp = FIRST_ENTRY;

    HEAD->next = FIRST_ENTRY->next;
    temp->next->prev = HEAD;

    free(temp);

}

void del_last() {
    node *temp = LAST_ENTRY;

    temp->prev->next = TAIL;
    TAIL->prev = LAST_ENTRY->prev;

    free(temp);

}

void print_entries() {
    if (list_empty()) {
        printf("None.\n");

        return;
    }

    int count = 0;
    for(node *cur = FIRST_ENTRY; cur != TAIL; cur = cur->next) {
        count++;
        printf("[%d] %d\n", count, cur->data);
    }
}

void free_list() {
    node *temp = NULL;

    for(node *cur = HEAD; cur != TAIL->next; cur = temp) {
        temp = cur->next;
        free(cur);
    }

}

int main(int argv, char *args[]) {
    list_init();

    int option = 0;
    
    while (1) {
        printf("============\n");
        printf("select what you want:\n");
        printf("[1] view entries in list\n");
        printf("[2] add an entry to list\n");
        printf("[3] delete an entry from list\n");
        printf("else terminates.\n");
        printf("> ");

        if (scanf("%d", &option) != EOF) {

            if (option == 1) print_entries();

            else if (option == 2) {

                int data = 0;
                printf("enter the data value: ");

                if (scanf("%d", &data) != EOF) {

                    node *new_node = create_node(data);
                    int add_dir = 0;

                    printf("where to add? [1] front [2] back: ");

                    if (scanf("%d", &add_dir) != EOF) {

                        if (add_dir == 1) insert_first(new_node);

                        else if (add_dir == 2) insert_last(new_node);

                        else printf("wrong input.\n");

                    }
                }
                else {

                    printf("wrong input.\n");
                    break;

                }
            }
            else if (option == 3) {

                if (!list_empty()) {

                    printf("where to pop? [1] front [2] back: ");
                    int add_dir = 0;

                    if (scanf("%d", &add_dir) != EOF) {

                        if (add_dir == 1) del_first();

                        else if (add_dir == 2) del_last();

                        else printf("wrong input.\n");

                    }

                }

                else printf("list is empty now.\n");
                
            }
                        
        }
        
    }
    
    free_list();
    
    return 0;
}