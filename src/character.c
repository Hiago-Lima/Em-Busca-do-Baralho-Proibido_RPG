#include <string.h>
#include <stdlib.h>
#include "character.h"

void character_init(Character *c, const char *name,
                    int hp, int attack, int defense, int speed)
{
    strncpy(c->name, name, NAME_SIZE - 1); // strncpy copia com segurança a string, mas nao garante que o \0 vai ser passado
    c->name[NAME_SIZE - 1] = '\0';         // por isso q passamos ele bem aq
    c->hp = hp;
    c->hp_max = hp;
    c->atk = attack;
    c->def = defense;
    c->spd = speed;
    c->status.defense_bonus = 0;
    c->status.turns_defending = 0;
}

int character_take_damage(Character *c, int raw_damage)
{
    int total_defense = c->def + c->status.defense_bonus;
    int damage = raw_damage - total_defense;
    if (damage < 1)
        damage = 1;
    c->hp -= damage;
    if (c->hp < 0)
        c->hp = 0;
    return damage;
}

void character_tick_effects(Character *c)
{
    if (c->status.turns_defending > 0)
    {
        c->status.turns_defending--;
        if (c->status.turns_defending == 0)
            c->status.defense_bonus = 0;
    }
}

int character_is_alive(const Character *c)
{
    return c->hp > 0;
}

int character_calculate_damage(const Character *attacker, int strong)
{
    int base = attacker->atk;
    if (strong)
        base = (int)(base * 1.6f);
    int variation = (rand() % 5) - 2;
    return base + variation;
}