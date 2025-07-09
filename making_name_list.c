#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024
#define INIT_CAPACITY 2
#define QUIT_REQ "quit"

void flush_buf(char* buf, size_t size) { memset(buf, 0, size); }

int is_quit_entered(char* input) { return !strcmp(input, QUIT_REQ); }

char* get_user_input(char* buf) {
    if(fgets(buf, BUF_SIZE, stdin) == NULL) return NULL;

    buf[strcspn(buf, "\n")] = '\0';
    return buf;
}

char* move_input_from_buf_to_namestring(char* buf) {
    char* new_name = (char*)malloc(strlen(buf) + 1);

    if (new_name != NULL) {
        strcpy(new_name, buf);
        flush_buf(buf, BUF_SIZE);
        
        return new_name;
    }
    fprintf(stderr, "no space for new name!\n");
    exit(EXIT_FAILURE);
}

void print_list(const char** list, size_t size) {
    if (list != NULL) for (int i = 0; i < size; i++) printf("%s\n", list[i]);
    else {
        fprintf(stderr, "names list has problem\n");
        exit(EXIT_FAILURE);
    }
}

void free_list(char** list, size_t size) {
    for (int i = 0; i < size; i++) free(list[i]);
    free(list);
}

int main() {
    char buf[BUF_SIZE] = "";
    int count = 0;
    int capacity = INIT_CAPACITY;

    char** names = (char**)malloc(sizeof(char*) * INIT_CAPACITY);
    if (names == NULL) {
        fprintf(stderr, "name list allocation failed!\n");
        return 1;
    }

    while(1) {
    
        if (get_user_input(buf) != NULL) { // 입력을 받는다

            if (is_quit_entered(buf)) break; // quit이면 loop를 종료한다
            else {                         // 그 외의 경우, buf의 내용을 이름으로 간주하여 이름 리스트에 추가한다
                
                char* name = move_input_from_buf_to_namestring(buf);

                if (capacity == count) {
                    char** temp_ptr = realloc(names, sizeof(char*) * (2 * capacity));
                
                    if (temp_ptr != NULL) {
                        capacity *= 2;
                        names = temp_ptr;
                        // printf("successfully extended namelist: %d to %d\n", capacity/2, capacity);
                    }
                }
                names[count++] = name;
                // test print to find reason of names extending abort
                // for(int i = 0; i < capacity; i++) {
                //         if (names[i] == NULL) printf("[%d] NULL\n", i);
                //         else printf("[%d] %s\n", i, names[i]);
                //     }
            }
        }
        else fprintf(stderr, "input error\n");
    }

    print_list(names, count);
    free_list(names, count);

    return 0;
}

