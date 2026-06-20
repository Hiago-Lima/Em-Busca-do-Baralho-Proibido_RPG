//loop de combate
#ifndef COMBAT_H
#define COMBAT_H

#include "character.h"
#include "enemies.h"
#include "stack.h"

typedef enum {
    COMBAT_VICTORY,  // Jogador venceu 
    COMBAT_DEFEAT,   // Jogador perdeu 
    COMBAT_FLED      // Jogador fugiu  
} CombatResult;


//Executa um combate completo.
 //Acumula o histórico de ações na `history` passada.
 // Retorna o resultado.
CombatResult combat_run(Character *player, Enemy *enemy,
                        ActionStack *history);

#endif // COMBAT_H 