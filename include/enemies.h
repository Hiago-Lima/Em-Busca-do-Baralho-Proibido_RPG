//inimigos e seus comportamentos
#ifndef ENEMIES_H
#define ENEMIES_H

#include "character.h"
#include "fsm.h"

// Um inimigo é um personagem + sua FSM 
typedef struct {
    Character character;
    FSM       fsm; 
} Enemy;

// Cria o Touro Guerreiro — agressivo, ataca forte rapidamente 
void enemy_create_bull(Enemy *e);

// Cria o Mago Negro — defensivo, recua quando HP baixo 
void enemy_create_dark_mage(Enemy *e);

// Cria o Dragão Branco — boss com 3 fases baseadas em HP 
void enemy_create_blue_eyes(Enemy *e);
    
// Consulta a FSM e retorna o estado decidido para este turno
FSMState enemy_think(Enemy *e, const Character *player);

#endif /* ENEMIES_H */