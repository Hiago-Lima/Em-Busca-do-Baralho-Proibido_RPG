#include <stdio.h>
#include <string.h>
#include "ui.h"

/* ═══════════════════════════════════════════════════════════════════
 *  ui_clear
 *
 *  \033[2J  →  apaga todo o conteúdo da tela
 *  \033[H   →  move o cursor para o canto superior esquerdo
 * ═══════════════════════════════════════════════════════════════════ */
void ui_clear(void)
{
    printf("\033[2J\033[H");
    fflush(stdout);
}

/* ═══════════════════════════════════════════════════════════════════
 *  ui_pause
 *
 *  Consome tudo que está no buffer de entrada até achar um '\n'.
 *  Isso evita que ENTERs anteriores passem direto pela pausa.
 * ═══════════════════════════════════════════════════════════════════ */
void ui_pause(void)
{
    printf(ANSI_CYAN "\n  [ ENTER para continuar... ]" ANSI_RESET);
    fflush(stdout);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* ═══════════════════════════════════════════════════════════════════
 *  ui_read_int
 *
 *  Lê uma linha inteira com fgets (mais seguro que scanf).
 *  Tenta extrair um inteiro com sscanf.
 *  Repete até receber um valor válido dentro do intervalo [min, max].
 * ═══════════════════════════════════════════════════════════════════ */
int ui_read_int(int min, int max)
{
    char buf[32];
    int val;

    while (1)
    {
        if (fgets(buf, sizeof(buf), stdin))
        {
            if (sscanf(buf, "%d", &val) == 1 && val >= min && val <= max)
                return val;
        }
        printf(ANSI_YELLOW "  Opcao invalida. Digite entre %d e %d: " ANSI_RESET, min, max);
    }
}

/* ═══════════════════════════════════════════════════════════════════
 *  ui_draw_hp_bar  (função interna — não está no .h)
 *
 *  Desenha uma barra visual de HP: [████░░░░]
 *  A cor muda conforme o HP:
 *    > 60%  →  verde
 *    > 30%  →  amarelo
 *    ≤ 30%  →  vermelho
 *
 *  Usamos os caracteres Unicode:
 *    \xe2\x96\x88  →  █  (bloco cheio)
 *    \xe2\x96\x91  →  ░  (bloco vazio)
 * ═══════════════════════════════════════════════════════════════════ */
static void ui_draw_hp_bar(int hp, int hp_max, int width)
{
    int filled = (hp_max > 0) ? (hp * width / hp_max) : 0;
    float pct = (hp_max > 0) ? (float)hp / (float)hp_max : 0.0f;

    const char *color;
    if (pct > 0.60f)
        color = ANSI_GREEN;
    else if (pct > 0.30f)
        color = ANSI_YELLOW;
    else
        color = ANSI_RED;

    printf("[%s", color);
    for (int i = 0; i < width; i++)
    {
        if (i < filled)
            printf("\xe2\x96\x88"); /* █ */
        else
            printf("\xe2\x96\x91"); /* ░ */
    }
    printf(ANSI_RESET "]");
}

/* ═══════════════════════════════════════════════════════════════════
 *  ui_draw_combat_header
 *
 *  Exibe o painel principal do combate a cada turno:
 *
 *  ╔══════════════════════════════════╗
 *  ║   EM BUSCA DO BARALHO PROIBIDO  ║
 *  ╚══════════════════════════════════╝
 *  Crono            HP:  80/120  [████████░░░░]
 *  ──────────────────────────────────────
 *  Touro Guerreiro  HP: 100/120  [████████████]
 *  Estado da IA: [ ATACAR ]
 * ═══════════════════════════════════════════════════════════════════ */
void ui_draw_combat_header(const Character *player,
                           const Character *enemy,
                           const FSM *enemy_fsm)
{
    printf(ANSI_BOLD
           "╔══════════════════════════════════════╗\n"
           "║    EM BUSCA DO BARALHO PROIBIDO      ║\n"
           "╚══════════════════════════════════════╝\n" ANSI_RESET);

    /* Linha do jogador */
    printf(ANSI_BLUE ANSI_BOLD "  %-20s" ANSI_RESET, player->name);
    printf(" HP: %3d/%-3d  ", player->hp, player->hp_max);
    ui_draw_hp_bar(player->hp, player->hp_max, 12);

    /* Mostra se está defendendo */
    if (player->status.defense_bonus > 0)
        printf(ANSI_CYAN "  [DEFENDENDO]" ANSI_RESET);
    printf("\n");

    printf("  ──────────────────────────────────────\n");

    /* Linha do inimigo */
    printf(ANSI_RED ANSI_BOLD "  %-20s" ANSI_RESET, enemy->name);
    printf(" HP: %3d/%-3d  ", enemy->hp, enemy->hp_max);
    ui_draw_hp_bar(enemy->hp, enemy->hp_max, 12);
    printf("\n");

    /* Estado atual da FSM */
    printf("  Estado do inimigo: " ANSI_BOLD ANSI_MAGENTA "[ %s ]" ANSI_RESET "\n",
           fsm_current_label(enemy_fsm));

    printf("  ══════════════════════════════════════\n\n");
}

/* ═══════════════════════════════════════════════════════════════════
 *  ui_player_menu
 *
 *  Exibe as 3 opções do jogador e retorna a escolha.
 *  Simplificado — sem itens conforme decidimos.
 * ═══════════════════════════════════════════════════════════════════ */
int ui_player_menu(void)
{
    printf(ANSI_BLUE ANSI_BOLD "  >> SUA VEZ <<\n\n" ANSI_RESET);
    printf("  1. Atacar\n");
    printf("  2. Atacar Forte\n");
    printf("  3. Defender\n\n");
    printf(ANSI_BLUE "  Escolha: " ANSI_RESET);

    return ui_read_int(1, 3);
}

/* ═══════════════════════════════════════════════════════════════════
 *  Funções de log colorido
 *
 *  Cada tipo de evento tem sua cor:
 *    jogador  →  azul
 *    inimigo  →  vermelho
 *    sistema  →  ciano (transições, avisos)
 * ═══════════════════════════════════════════════════════════════════ */
void ui_log_player(const char *msg)
{
    printf(ANSI_BLUE "  [JOGADOR] %s" ANSI_RESET "\n", msg);
}

void ui_log_enemy(const char *msg)
{
    printf(ANSI_RED "  [INIMIGO] %s" ANSI_RESET "\n", msg);
}

void ui_log_system(const char *msg)
{
    printf(ANSI_CYAN "  >> %s" ANSI_RESET "\n", msg);
}