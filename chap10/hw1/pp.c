#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        perror("malloc");
        exit(1);
    }
    new_node->data = data;
    new_node->next = *top;
    *top = new_node;
}

int pop(struct node **top) {
    if (*top == NULL) {
        fprintf(stderr, "Error: Stack underflow\n");
        return -1;
    }
    struct node *temp = *top;
    int popped_data = temp->data;
    *top = (*top)->next;
    free(temp);
    return popped_data;
}

void print_stack(struct node *top) {
    printf("Print stack\n");
    if (top == NULL) {
        printf("(empty)\n");
        return;
    }
    struct node *current = top;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int is_valid_integer(const char *str) {
    if (*str == '\0') return 0;
    if (*str == '-' || *str == '+') str++;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int main() {
    struct node *top = NULL;
    char input[20];

    printf("./pp\n");
    while (1) {
        scanf("%s", input);
        if (is_valid_integer(input)) {
            push(&top, atoi(input));
        } else {
            print_stack(top);
            break;
        }
    }

    while (top != NULL) {
        pop(&top);
    }

    return 0;
}

