#include <stdio.h>

#define STACK_SIZE 10
#define STACK_EMPTY - 1

typedef enum bool
{
    FALSE = 0,
    TRUE = 1
}
bool;

// Stack structure
typedef struct stack
{
    int stack_array[STACK_SIZE];
    int top;
    void( * push)(struct stack * my_stack, int value);
    void( * pop)(struct stack * my_stack);
    int( * peek)(struct stack * my_stack);
    bool( * is_empty)(struct stack * my_stack);
}
stack_t;

// Push on stack function
void push(struct stack * my_stack, int value)
{
    if (my_stack -> top == STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow!\n");
        return;
    } else {
        my_stack -> stack_array[++(my_stack -> top)] = value;
    }
}

// Pop from stack function
void pop(struct stack * my_stack)
{
    if (my_stack -> top == STACK_EMPTY) {
        fprintf(stderr, "Stack is already empty!\n");
        return;
    } else {
        (my_stack -> top) --;
    }
}

// Peek at the top
int peek(struct stack * my_stack)
{
    if (my_stack -> top == STACK_EMPTY) {
        fprintf(stderr, "Stack is empty!\n");
        return STACK_EMPTY;
    }
    return my_stack -> stack_array[my_stack -> top];
}

// Check if the stack exists
bool is_empty(struct stack * my_stack)
{
    if (my_stack -> top == STACK_EMPTY)
        return TRUE;
    return FALSE;
}

int main(void)
{
    // Initialise stack
    stack_t my_stack;
    my_stack.top = STACK_EMPTY;
    my_stack.pop = & pop;
    my_stack.push = & push;
    my_stack.is_empty = & is_empty;
    my_stack.peek = & peek;

    // Push elements to the stack
    for (int i = 0; i < 5; i++) {
        my_stack.push( & my_stack, i);
    }

    // Pop some elements
    for (int i = 0; i < 2; i++) {
        my_stack.pop( & my_stack);
    }

    // Display result
    printf("Expected output: 0 1 2\n");
    printf("Output: ");
    for (int i = 0; i <= my_stack.top; i++)
        printf("%d ", my_stack.stack_array[i]);

    // Display the top
    printf("\nTop level %d\n", my_stack.peek( & my_stack));

    // Clear the stack
    while (!(is_empty( & my_stack)))
        my_stack.pop( & my_stack);

    return 0;
}
