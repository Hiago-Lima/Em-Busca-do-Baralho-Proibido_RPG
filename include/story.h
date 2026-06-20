//Narrativa e seleção dos bonecos
#ifndef STORY_H
#define STORY_H

#include "character.h"
#include "stack.h"

typedef enum {
    HERO_CRONO = 0,
    HERO_MARIE,
    HERO_LUCCA
} HeroID;

//Exibe a tela de título e aguarda ENTER 
void story_title_screen(void);

// Exibe a seleção de personagem, inicializa o jogador e retorna qual herói foi escolhido 
HeroID story_character_select(Character *player);

// Exibe o texto de introdução após escolher o personagem 
void story_intro(HeroID hero);

// Exibe a transição antes de cada fase phase: 0 = Touro, 1 = Mago, 2 = Dragão 
void story_phase_intro(int phase);

// Exibe a tela de vitória final com o log completo da batalha 
void story_victory(ActionStack *history);

// Exibe a tela de game over 
void story_game_over(void);

#endif // STORY_H 