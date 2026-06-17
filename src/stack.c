#include <string.h>
#include "stack.h"

void stack_init(ActionStack *s)
{
    s->top = -1;
}
void stack_push(ActionStack *s, const char *msg)
{
    if (s->top >= STACK_MAX - 1)
        return;
    s->top++;
    strncpy(s->entries[s->top], msg, STACK_MSG_LEN - 1);
    s->entries[s->top][STACK_MSG_LEN - 1] = '\0';
    return;
}
int stack_pop(ActionStack *s, char *out)
{
    if (s->top < 0)
        return 0;
    strncpy(out, s->entries[s->top], STACK_MSG_LEN);
    s->top--;
    return 1;
}
int stack_is_empty(const ActionStack *s)
{
    return s->top < 0;
}