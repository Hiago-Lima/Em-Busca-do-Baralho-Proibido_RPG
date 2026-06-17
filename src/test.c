// testes
#include "character.h"
#include "stack.h"
#include <stdio.h>
int main()
{
    Character c;
    ActionStack s;
    char msg[256];
    character_init(&c, "Teste", 100, 20, 10, 5);
    printf("Name: %s\nHP: %d/%d\nATK: %d\nDEF: %d\nSPD: %d\n",
           c.name, c.hp, c.hp_max, c.atk, c.def, c.spd);
    int damage = character_calculate_damage(&c, 1);
    printf("Damage calculated (strong attack): %d\n", damage);
    int taken = character_take_damage(&c, damage);
    printf("Damage taken: %d\nHP after damage: %d\n", taken, c.hp);
    stack_init(&s);
    printf("pilha vazia? %d\n", stack_is_empty(&s)); // espera 1
    stack_push(&s, "Primeira ação");
    stack_push(&s, "Segunda ação");
    stack_push(&s, "terceira op");
    while (!stack_is_empty(&s))
    {
        if (stack_pop(&s, msg))
        {
            printf("Popped: %s\n", msg);
        }
    }
    return 0;
}