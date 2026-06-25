#include <stdio.h>
#include "story.h"
#include "ui.h"
#include "ascii.h"

/* ═══════════════════════════════════════════════════════════════════
 *  story_title_screen
 *
 *  Primeira coisa que o jogador vê.
 *  Inspirado no estilo visual de Yu-Gi-Oh.
 * ═══════════════════════════════════════════════════════════════════ */
void story_title_screen(void)
{
    ui_clear();

    printf(ANSI_YELLOW ANSI_BOLD);
    printf("\n\n");
    printf("       //     EM BUSCA DO BARALHO PROIBIDO         //\n");
    printf(ANSI_RESET);

    printf(ANSI_CYAN);
    draw_ascii_art_pegasus();
    printf("\n     Pegasus te desafia a cruzar o Reino dos Duelistas.\n");
    printf("       Tres criaturas se erguem entre voce e o baralho.\n");
    printf("       Apenas o com o coração mais valente vencera!!!.\n");
    printf(ANSI_RESET);

    ui_pause();
}

/* ═══════════════════════════════════════════════════════════════════
 *  ASCII art dos personagens
 *
 *  Exibidos durante a seleção. Estilo simples que funciona em
 *  qualquer terminal sem dependências externas.
 * ═══════════════════════════════════════════════════════════════════ */
static void print_crono(void)
{
    printf(ANSI_BLUE);
    printf("         )  CRONO  (\n");
    draw_ascii_art_crono();
    printf(ANSI_RESET);
}

static void print_marie(void)
{
    printf(ANSI_MAGENTA);
    printf("         \\  MARIE  /\n");
    printf(ANSI_RESET);
}

static void print_lucca(void)
{
    printf(ANSI_GREEN);
    printf("        |   LUCCA   |\n");
}
/* ═══════════════════════════════════════════════════════════════════
 *  story_character_select
 *
 *  Exibe os três personagens com seus atributos e ASCII art.
 *  Inicializa o `player` com os atributos do escolhido.
 *  Retorna o HeroID para que story_intro saiba qual história contar.
 *
 *  Cada herói tem uma especialidade diferente:
 *    Crono → equilibrado, velocidade alta
 *    Marie → defesa alta, mais tanque
 *    Lucca → ataque alto, mais frágil
 * ═══════════════════════════════════════════════════════════════════ */
HeroID story_character_select(Character *player)
{
    ui_clear();

    printf(ANSI_BOLD "\n  === ESCOLHA SEU PERSONAGEM ===\n\n" ANSI_RESET);

    /* Crono */
    print_crono();
    printf(ANSI_BLUE ANSI_BOLD "  1. CRONO\n" ANSI_RESET);
    printf("     HP: 120 | ATK: 20 | DEF: 10 | VEL: 15\n");
    printf("     Guerreiro equilibrado. Age primeiro.\n\n");

    /* Marie */
    print_marie();
    printf(ANSI_MAGENTA ANSI_BOLD "  2. MARIE\n" ANSI_RESET);
    printf("     HP: 140 | ATK: 16 | DEF: 16 | VEL: 11\n");
    printf("     Tanque resistente. Dificil de derrubar.\n\n");

    /* Lucca */
    print_lucca();
    printf(ANSI_GREEN ANSI_BOLD "  3. LUCCA\n" ANSI_RESET);
    printf("     HP: 100 | ATK: 26 | DEF:  8 | VEL: 13\n");
    printf("     Alta ofensiva. Fragil mas devastadora.\n\n");

    printf(ANSI_BOLD "  Escolha: " ANSI_RESET);
    int choice = ui_read_int(1, 3);

    /* Inicializa o personagem com os atributos do escolhido */
    switch (choice)
    {
    case 1:
        character_init(player, "Crono", 120, 20, 10, 15);
        return HERO_CRONO;
    case 2:
        character_init(player, "Marie", 140, 16, 16, 11);
        return HERO_MARIE;
    default:
        character_init(player, "Lucca", 100, 26, 8, 13);
        return HERO_LUCCA;
    }
}

/* ═══════════════════════════════════════════════════════════════════
 *  story_intro
 *
 *  Texto de introdução personalizado por personagem.
 *  Cada herói tem sua motivação para aceitar o desafio de Pegasus.
 * ═══════════════════════════════════════════════════════════════════ */
void story_intro(HeroID hero)
{
    ui_clear();

    printf(ANSI_YELLOW ANSI_BOLD "\n  [ PROLOGO ]\n\n" ANSI_RESET);

    switch (hero)
    {
    case HERO_CRONO:
        printf("  O reino estava em paz quando Pegasus apareceu.\n\n");
        printf("  \"Crono...\" sua voz ecoou pelo salao.\n");
        printf("  \"Dizem que voce e o mais forte desta era.\n");
        printf("   Prove isso. Chegue ate o fim do meu reino\n");
        printf("   e o Baralho Proibido sera seu.\"\n\n");
        printf("  Crono apertou a empunhadura da espada.\n");
        printf("  Nao era uma escolha. Era um destino.\n");
        break;

    case HERO_MARIE:
        printf("  Marie conhecia as lendas do Baralho Proibido.\n\n");
        printf("  Pegasus surgiu diante dela com um sorriso.\n");
        printf("  \"Ah, a famosa Marie. Sua defesa e lendaria.\n");
        printf("   Mas sera que resistira aos guardioes\n");
        printf("   do meu reino?\"\n\n");
        printf("  Marie ergueu o escudo sem hesitar.\n");
        printf("  Nenhum guardiao a derrubaria.\n");
        break;

    case HERO_LUCCA:
        printf("  Lucca havia estudado o Baralho Proibido por anos.\n\n");
        printf("  \"Interessante...\" disse Pegasus, ajustando o monculo.\n");
        printf("  \"Uma cientista. Voce calcula cada movimento.\n");
        printf("   Vamos ver se seus calculos resistem\n");
        printf("   ao caos do meu reino.\"\n\n");
        printf("  Lucca sorriu. Ela ja havia calculado tudo.\n");
        break;
    }

    ui_pause();
}

/* ═══════════════════════════════════════════════════════════════════
 *  story_phase_intro
 *
 *  Texto de transição antes de cada combate.
 *  Apresenta o inimigo com um pouco de drama.
 * ═══════════════════════════════════════════════════════════════════ */
void story_phase_intro(int phase)
{
    ui_clear();

    printf(ANSI_YELLOW ANSI_BOLD "\n  [ FASE %d ]\n\n" ANSI_RESET, phase + 1);

    switch (phase)
    {
    case 0:
        printf(ANSI_RED);
        printf("  O chao treme.\n\n");
        printf("  Das sombras surge uma figura colossal.\n");
        printf("  Chifres apontados para o ceu. Olhos de brasa.\n\n");
        printf("  O TOURO GUERREIRO barra seu caminho.\n");
        printf("  Ele nao negocia. Ele apenas ataca.\n");
        printf(ANSI_RESET);
        break;

    case 1:
        printf(ANSI_MAGENTA);
        printf("  Uma nevoa roxa toma o corredor.\n\n");
        printf("  Risadas ecoam pelas paredes de pedra.\n");
        printf("  Uma figura encurvada emerge da escuridao.\n\n");
        printf("  O MAGO NEGRO ergue seu cajado.\n");
        printf("  Astuto. Paciente. Perigoso.\n");
        printf(ANSI_RESET);
        break;

    case 2:
        printf(ANSI_CYAN);
        printf("  O teto racha.\n\n");
        printf("  Uma sombra imensa cobre tudo.\n");
        printf("  Asas brancas se abrem bloqueando a luz.\n\n");
        printf("  O DRAGAO BRANCO DE OLHOS AZUIS.\n");
        printf("  O guardiao final do Baralho Proibido.\n");
        printf("  Nao ha retreat. E agora ou nunca.\n");
        printf(ANSI_RESET);
        break;
    }

    ui_pause();
}

/* ═══════════════════════════════════════════════════════════════════
 *  story_victory
 *
 *  Tela final de vitória.
 *  Desempilha e exibe todo o histórico da batalha
 *  do mais recente ao mais antigo.
 * ═══════════════════════════════════════════════════════════════════ */
void story_victory(ActionStack *history)
{
    ui_clear();

    printf(ANSI_YELLOW ANSI_BOLD);
    printf("\n╔══════════════════════════════════════════╗\n");
    printf("  ║         PARABENS, DUELISTA!              ║\n");
    printf("  ║                                          ║\n");
    printf("  ║   O Baralho Proibido e seu.              ║\n");
    printf("  ║   Pegasus inclina a cabeca em respeito.  ║\n");
    printf("  ╚══════════════════════════════════════════╝\n");
    printf(ANSI_RESET);

    /* Exibe o log completo desempilhando */
    printf(ANSI_BOLD "\n  [ LOG COMPLETO DA JORNADA ]\n\n" ANSI_RESET);

    char msg[256];
    int index = 1;
    while (!stack_is_empty(history))
    {
        stack_pop(history, msg);
        printf(ANSI_CYAN "  %3d. " ANSI_RESET "%s\n", index++, msg);
    }

    printf("\n");
}

/* ═══════════════════════════════════════════════════════════════════
 *  story_game_over
 * ═══════════════════════════════════════════════════════════════════ */
void story_game_over(void)
{
    ui_clear();

    printf(ANSI_RED ANSI_BOLD);
    printf("\n╔══════════════════════════════════════════╗\n");
    printf("  ║              GAME OVER                   ║\n");
    printf("  ║                                          ║\n");
    printf("  ║   Sua jornada termina aqui, duelista.    ║\n");
    printf("  ║   O Baralho Proibido permanece intocado. ║\n");
    printf("  ╚══════════════════════════════════════════╝\n");
    printf(ANSI_RESET);

    ui_pause();
}