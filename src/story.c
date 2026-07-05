#include <stdio.h>
#include "story.h"
#include "ui.h"
#include "ascii.h"

//  Primeira coisa que o jogador ve ao iniciar o jogo. Exibe o título, a arte ASCII e uma breve introdução.
void story_title_screen(void)
{
    ui_clear();

    printf(ANSI_YELLOW ANSI_BOLD);
    printf("\n\n");
    printf(ANSI_BOLD "                  ##               EM BUSCA DO BARALHO PROIBIDO               ##\n\n");
    printf(ANSI_RESET);

    printf(ANSI_CYAN);
    draw_castle(); // acoplei a intro com a imagem do castelo, para dar mais impacto visual
    printf(ANSI_RESET);

    ui_pause();
}

/*  story_character_select

  Exibe os três personagens com seus atributos e ASCII art.
  Inicializa o `player` com os atributos do escolhido.
  Retorna o HeroID para que story_intro saiba qual história contar.

  Cada herói tem uma especialidade diferente:
    Seiya → equilibrado, velocidade alta
    Shun → defesa alta, mais tanque
    Shiryu → ataque alto, mais frágil
*/
HeroID story_character_select(Character *player)
{
    ui_clear();

    printf(ANSI_BOLD "\n  === ESCOLHA SEU PERSONAGEM ===\n\n" ANSI_RESET);
    // todos as ascii da glr
    draw_trio();
    // seiya
    printf("\n");
    printf(ANSI_BLUE ANSI_BOLD "  1. SEIYA\n" ANSI_RESET);
    printf("     HP: 150 | ATK: 25 | DEF: 10 | VEL: 15\n");
    printf("     O obstinado Cavaleiro de Pegaso que se move num piscar de olhos, sempre pronto para superar qualquer barreira pela justica e por Atena.\n");

    // shun

    printf(ANSI_MAGENTA ANSI_BOLD "  2. SHUN\n" ANSI_RESET);
    printf("     HP: 180 | ATK: 20 | DEF: 16 | VEL: 11\n");
    printf("     O pacifista Cavaleiro de Andromeda que ergue uma barreira intransponivel ao seu redor, mas prefere sempre a via da diplomacia e da protecao.\n");

    // shiryu
    printf(ANSI_GREEN ANSI_BOLD "  3. SHIRYU\n" ANSI_RESET);
    printf("     HP: 120 | ATK: 30 | DEF:  8 | VEL: 13\n");
    printf("     O honrado Cavaleiro de Dragao, cuja sabedoria e lealdade guiam um impacto devastador capaz de reverter o fluxo das maiores mares.\n\n");

    printf(ANSI_BOLD "  Escolha: " ANSI_RESET);
    int choice = ui_read_int(1, 3);

    // Inicializa o personagem com os atributos do escolhido
    switch (choice)
    {
    case 1:
        character_init(player, "Seiya", 150, 25, 10, 15);
        return HERO_SEIYA;
    case 2:
        character_init(player, "Shun", 180, 20, 16, 11);
        return HERO_SHUN;
    default:
        character_init(player, "Shiryu", 120, 30, 8, 13);
        return HERO_SHIRYU;
    }
}

/*
    story_intro
    Texto de introdução personalizado por personagem.
    Cada herói tem sua motivação para aceitar o desafio de Pegasus.
 */
void story_intro(HeroID hero)
{
    ui_clear();

    printf(ANSI_YELLOW ANSI_BOLD "\n  [ PROLOGO ]\n\n" ANSI_RESET);

    switch (hero)
    {
    case HERO_SEIYA:
        printf("  O reino estava em paz quando Pegasus apareceu.\n\n");
        printf("  \"Seiya...\" sua voz ecoou pelo salao.\n");
        printf("  \"Dizem que voce e o mais forte dos guerreiros de Atena.\n");
        printf("   Prove isso. Chegue ate o fim do meu reino\n");
        printf("   e o Baralho Proibido sera seu.\"\n\n");
        printf("  Seiya vestiu sua Armadura e saiu em busca do desafio.\n");
        printf("  Nao era uma escolha. Era um destino.\n");
        break;

    case HERO_SHUN:
        printf("  Shun conhecia as lendas do Baralho Proibido.\n\n");
        printf("  Pegasus surgiu diante dele com um sorriso.\n");
        printf("  \"Ah, a famoso Shun. Sua corrente eh lendaria.\n");
        printf("   Mas sera que resistira aos Monstros de Duelo\n");
        printf("   do meu reino?\"\n\n");
        printf("  Shun ergueu suas correntes.\n");
        printf("  Nenhuma criatura o derrubaria.\n");
        break;

    case HERO_SHIRYU:
        printf("  Shiryu havia estudado o Baralho Proibido por anos.\n\n");
        printf("  \"Interessante...\" disse Pegasus, ajustando o olho do milenio.\n");
        printf("  \"Voce enfrenta cada desafio com coragem, Shiryu.\n");
        printf("   Vamos ver se sua determinacao vai resistir\n");
        printf("   ao caos do meu reino.\"\n\n");
        printf("  Shiryu sorriu. Ele ja havia decidido sua jornada.\n");
        break;
    }

    ui_pause();
}

/*
   story_phase_intro
   Texto de transição antes de cada combate.
   Apresenta o inimigo com um pouco de drama.
*/
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
        ui_pause();
        printf(ANSI_RED);
        printf(ANSI_BOLD "  Ele com seu tremendo poder que destroi seus inimigos com um unico golpe do seu machado.\n");
        draw_ascii_ox();
        printf(ANSI_RESET);
        break;

    case 1:
        printf(ANSI_MAGENTA);
        printf("  Uma nevoa roxa toma o corredor.\n\n");
        printf("  Risadas ecoam pelas paredes de pedra.\n");
        printf("  Uma figura encurvada emerge da escuridao.\n\n");
        printf("  O MAGO NEGRO ergue seu cajado.\n");
        ui_pause();
        printf(ANSI_MAGENTA);
        printf(ANSI_BOLD "  O mago definitivo em termos de ataque e defesa.\n");
        draw_ascii_mage();
        printf(ANSI_RESET);
        break;

    case 2:
        printf(ANSI_CYAN);
        printf("  O teto racha.\n\n");
        printf("  Uma sombra imensa cobre tudo.\n");
        printf("  Asas brancas se abrem bloqueando a luz.\n\n");
        printf("  O DRAGAO BRANCO DE OLHOS AZUIS.\n");
        ui_pause();
        printf(ANSI_CYAN);
        printf(ANSI_BOLD "  Este dragao lendario eh uma poderosa maquina de destruicao. Praticamente invencivel, muito poucos enfrentaram esta magnifica criatura e viveram para contar a historia.\n");
        draw_ascii_dragon();
        printf(ANSI_RESET);
        break;
    }

    ui_pause();
}

/*
   story_victory
   Tela final de vitória.
   Desempilha e exibe todo o histórico da batalha
   do mais recente ao mais antigo.
*/
void story_victory(ActionStack *history)
{
    ui_clear();

    printf(ANSI_YELLOW ANSI_BOLD);
    printf("\n  ############################################\n");
    printf("  #         PARABENS, DUELISTA!              #\n");
    printf("  #                                          #\n");
    printf("  #   O Baralho Proibido e seu.              #\n");
    printf("  #   Pegasus inclina a cabeca em respeito.  #\n");
    printf("  ############################################\n");
    printf(ANSI_RESET);

    // Exibe o log completo desempilhando
    printf(ANSI_BOLD "\n  [ LOG COMPLETO DA JORNADA ]\n\n" ANSI_RESET);

    char msg[256];
    int index = 1;
    while (!stack_is_empty(history))
    {
        stack_pop(history, msg);
        printf(ANSI_CYAN "  %3d. " ANSI_RESET "%s\n", index++, msg);
    }

    printf("\n");
    ui_pause();
}

//  story_game_over

void story_game_over(void)
{
    ui_clear();

    printf(ANSI_RED ANSI_BOLD);
    printf("\n  ############################################\n");
    printf("  #              GAME OVER                   #\n");
    printf("  #                                          #\n");
    printf("  #   Sua jornada termina aqui, duelista.    #\n");
    printf("  #   O Baralho Proibido permanece intocado. #\n");
    printf("  ############################################\n");
    printf(ANSI_RESET);

    ui_pause();
}