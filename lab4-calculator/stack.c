#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct node {
    void *data;
    struct node *next;
};

struct stack {
    struct node *top;
    size_t size;
};

void ptr_stack_push(struct stack *stack, void *value);
void *ptr_stack_pop(struct stack *stack);

struct stack *stack_new()
{
    struct stack *stack = malloc(sizeof *stack);
    stack->top = NULL;
    stack->size = 0;

    return stack;
}

void stack_free(struct stack *stack)
{
    while (!stack_isempty(stack)) {
        ptr_stack_pop(stack);
    }
    free(stack);
}

#define DEFINE_STACK_PUSH(TYPE, NAME)                   \
void NAME##_stack_push(struct stack *stack, TYPE value) \
{                                                       \
    TYPE *ptr = malloc(sizeof *ptr);                    \
    *ptr = value;                                       \
    ptr_stack_push(stack, ptr);                         \
}
DEFINE_STACK_PUSH(double, double);
DEFINE_STACK_PUSH(char, char);

void ptr_stack_push(struct stack *stack, void *value)
{
    /* Create new node */
    struct node *top_new = malloc(sizeof *top_new);
    top_new->data = value;
    top_new->next = stack->top;

    /* Point top to new node */
    stack->top = top_new;
    stack->size++;
}

#define DEFINE_STACK_POP(TYPE, NAME)        \
TYPE NAME##_stack_pop(struct stack *stack)  \
{                                           \
    TYPE *ptr = ptr_stack_pop(stack);       \
    TYPE value = *ptr;                      \
    free(ptr);                              \
    return value;                           \
}
DEFINE_STACK_POP(double, double);
DEFINE_STACK_POP(char, char);

void *ptr_stack_pop(struct stack *stack)
{
    /* Precondition: stack must not be empty */
    assert(!stack_isempty(stack));

    /* Get value of top element */
    struct node *top_old = stack->top;
    void *value = top_old->data;

    /* Point top to next in list */
    stack->top = top_old->next;
    stack->size--;

    free(top_old);
    return value;
}

_Bool stack_isempty(struct stack *stack)
{
    return stack->top == NULL;
}

size_t stack_size(struct stack *stack)
{
    return stack->size;
}
