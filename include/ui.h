// Interface visual com cores ANSI e formatação de texto
// perfumaria
#ifndef UI_H
#define UI_H

#include "character.h"
#include "fsm.h"

// Códigos ANSI
#define ANSI_RESET "\033[0m"
#define ANSI_BOLD "\033[1m"
#define ANSI_RED "\033[91m"
#define ANSI_GREEN "\033[92m"
#define ANSI_YELLOW "\033[93m"
#define ANSI_BLUE "\033[94m"
#define ANSI_MAGENTA "\033[95m"
#define ANSI_CYAN "\033[96m"
#define ANSI_GRAY "\033[90m"

// Limpa o terminal
void ui_clear(void);

// Aguarda o jogador pressionar ENTER
void ui_pause(void);

// Lê um inteiro do usuário entre min e max
int ui_read_int(int min, int max);

// Desenha o painel de combate com HP dos dois personagens
void ui_draw_combat_header(const Character *player,
                           const Character *enemy,
                           const FSM *enemy_fsm);

// Exibe o menu de ações e retorna a escolha (1-3)
int ui_player_menu(void);

// Funções de log colorido
void ui_log_player(const char *msg); /* azul  */
void ui_log_enemy(const char *msg);  /* vermelho */
void ui_log_system(const char *msg); /* ciano */

#endif