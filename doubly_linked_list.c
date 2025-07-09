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
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->data = data;

    return new_node;
}

node *list_init() {
    HEAD = create_node(0);
    TAIL = create_node(0);

    HEAD->next = TAIL;
    TAIL->prev = HEAD;

    return HEAD;
}

bool list_empty() {return (FIRST_ENTRY == TAIL && LAST_ENTRY == HEAD);}

node *insert_first(node *cur) {
    cur->next = FIRST_ENTRY;
    cur->prev = HEAD;
    FIRST_ENTRY->prev = cur;
    FIRST_ENTRY = cur;
    
    return HEAD;
}

node *insert_last(node *cur) {
    cur->prev = LAST_ENTRY;
    cur->next = TAIL;
    LAST_ENTRY->next = cur;
    LAST_ENTRY = cur;

    return HEAD;
}

void print_entries() {
    int count = 0;
    for(node *cur = FIRST_ENTRY; cur != TAIL; cur = cur->next) {
        count++;
        printf("[%d] %d\n", count, cur->data);
    }
}

int main(int argv, char *args[]) {
    list_init();

    int option = 0;
    
    while (1) {
        printf("select what you want:\n");
        printf("[1] view entries in list\n");
        printf("[2] add an entry to list\n");
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

                    }
                }
                else {

                    printf("wrong input.\n");
                    break;

                }
            }      
        }

        
        
    }
    
    return 0;
}