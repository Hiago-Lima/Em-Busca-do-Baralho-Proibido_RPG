#include <stdio.h>
#include <string.h>
#include "combat.h"
#include "queue.h"
#include "ui.h"

/* ═══════════════════════════════════════════════════════════════════
 *  player_turn
 *
 *  Exibe o menu, lê a escolha e executa a ação do jogador.
 *  Retorna:
 *     1  →  combate continua
 *    -1  →  jogador fugiu
 * ═══════════════════════════════════════════════════════════════════ */
static int player_turn(Character *player, Enemy *enemy,
                       ActionStack *history)
{
    int choice = ui_player_menu();
    char msg[256];

    switch (choice)
    {

    case 1:
    { /* Atacar */
        int raw = character_calculate_damage(player, 0);
        int dmg = character_take_damage(&enemy->character, raw);
        snprintf(msg, sizeof(msg),
                 "%s ataca %s e causa %d de dano!",
                 player->name, enemy->character.name, dmg);
        ui_log_player(msg);
        stack_push(history, msg);
        break;
    }

    case 2:
    { /* Atacar Forte */
        int raw = character_calculate_damage(player, 1);
        int dmg = character_take_damage(&enemy->character, raw);
        snprintf(msg, sizeof(msg),
                 "%s usa ATAQUE FORTE em %s e causa %d de dano!",
                 player->name, enemy->character.name, dmg);
        ui_log_player(msg);
        stack_push(history, msg);
        break;
    }

    case 3:
    { /* Defender */
        player->status.defense_bonus = 15;
        player->status.turns_defending = 1;
        snprintf(msg, sizeof(msg),
                 "%s assume postura defensiva! Defesa +15 por 1 turno.",
                 player->name);
        ui_log_player(msg);
        stack_push(history, msg);
        break;
    }
    }

    return 1;
}

/* ═══════════════════════════════════════════════════════════════════
 *  enemy_turn
 *
 *  Consulta a FSM para decidir a ação e a executa.
 *  O estado retornado por enemy_think() dita o que o inimigo faz.
 * ═══════════════════════════════════════════════════════════════════ */
static void enemy_turn(Enemy *enemy, Character *player,
                       ActionStack *history)
{
    FSMState state = enemy_think(enemy, player);
    char msg[256];

    switch (state)
    {

    case STATE_ATTACK:
    {
        int raw = character_calculate_damage(&enemy->character, 0);
        int dmg = character_take_damage(player, raw);
        snprintf(msg, sizeof(msg),
                 "%s ataca %s e causa %d de dano!",
                 enemy->character.name, player->name, dmg);
        ui_log_enemy(msg);
        stack_push(history, msg);
        break;
    }

    case STATE_STRONG_ATTACK:
    {
        int raw = character_calculate_damage(&enemy->character, 1);
        int dmg = character_take_damage(player, raw);
        snprintf(msg, sizeof(msg),
                 "%s usa ATAQUE PODEROSO em %s e causa %d de dano!",
                 enemy->character.name, player->name, dmg);
        ui_log_enemy(msg);
        stack_push(history, msg);
        break;
    }

    case STATE_DEFEND:
    {
        enemy->character.status.defense_bonus = 12;
        enemy->character.status.turns_defending = 1;
        snprintf(msg, sizeof(msg),
                 "%s se prepara para defender! Defesa +12.",
                 enemy->character.name);
        ui_log_enemy(msg);
        stack_push(history, msg);
        break;
    }

    default:
        break;
    }
}

/* ═══════════════════════════════════════════════════════════════════
 *  combat_run
 *
 *  Loop principal do combate:
 *
 *  1. Monta a fila ordenada por velocidade
 *  2. A cada iteração:
 *     a. Pega quem age (queue_peek)
 *     b. Processa efeitos temporários (tick)
 *     c. Executa o turno (jogador ou inimigo)
 *     d. Cicla a fila (quem agiu vai pro fim)
 *  3. Para quando alguém morre
 *  4. Retorna o resultado
 * ═══════════════════════════════════════════════════════════════════ */
CombatResult combat_run(Character *player, Enemy *enemy,
                        ActionStack *history)
{
    /* Monta a fila ordenada por velocidade */
    Turn_Queue queue;
    initqueue(&queue);
    insertqueue(&queue, player);
    insertqueue(&queue, &enemy->character);

    /* Registra o início da batalha no histórico */
    char intro[128];
    snprintf(intro, sizeof(intro), "--- %s vs %s ---",
             player->name, enemy->character.name);
    stack_push(history, intro);

    int turn = 1;

    while (character_is_alive(player) &&
           character_is_alive(&enemy->character))
    {

        /* Quem age neste turno */
        Character *actor = queue_peek(&queue);

        /* Redesenha a tela a cada turno */
        ui_clear();
        ui_draw_combat_header(player, &enemy->character, &enemy->fsm);
        printf(ANSI_BOLD "  Turno %d\n\n" ANSI_RESET, turn);

        /* Processa efeitos temporários de quem vai agir */
        character_tick_effects(actor);

        /* Executa o turno */
        if (actor == player)
        {
            int result = player_turn(player, enemy, history);
            if (result == -1)
                return COMBAT_FLED;
        }
        else
        {
            enemy_turn(enemy, player, history);
        }

        /* Quem agiu vai para o fim da fila */
        queue_cycle(&queue);
        turn++;

        ui_pause();
    }

    /* Determina o resultado */
    char result_msg[128];

    if (!character_is_alive(&enemy->character))
    {
        snprintf(result_msg, sizeof(result_msg),
                 "%s foi derrotado!", enemy->character.name);
        ui_log_system(result_msg);
        stack_push(history, result_msg);
        return COMBAT_VICTORY;
    }
    else
    {
        snprintf(result_msg, sizeof(result_msg),
                 "%s foi derrotado...", player->name);
        ui_log_system(result_msg);
        stack_push(history, result_msg);
        return COMBAT_DEFEAT;
    }
}