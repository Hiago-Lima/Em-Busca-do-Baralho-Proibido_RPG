// dados e regras dos personagens
#ifndef CHARACTER_H
#define CHARACTER_H
#define NAME_SIZE 30
typedef struct
{
    int defense_bonus;   // bonus de defesa, usado para calcular o dano recebido
    int turns_defending; // quantos turnos o personagem está defendendo
} StatusEffect;
typedef struct
{
    char name[NAME_SIZE];
    int hp;
    int hp_max;
    int atk;
    int def;
    int spd;
    StatusEffect status;
} Character;

void character_init(Character *c, const char *name, int hp, int atk, int def, int spd); // copia os parametros, durante a execução o character ja vai existir por sí, ai inicializa aq

int character_take_damage(Character *c, int damage);                   // dano tomado
int character_calculate_damage(const Character *attacker, int strong); // dano causado, o strong é um multiplicador de dano, usado para ataques fortes
void character_tick_effects(Character *c);                             // efeito da defesa, ao defender aumenta a def um pouco
int character_is_alive(const Character *c);                            // verifica se o personagem ainda está vivo, ou seja, se o hp é maior que 0

#endif // CHARACTER_H
