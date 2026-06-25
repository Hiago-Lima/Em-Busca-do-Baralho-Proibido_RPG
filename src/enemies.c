#include "enemies.h"

//  CONDIÇÕES — funções usadas nas arestas do grafo  Cada uma recebe o contexto e retorna 1 (dispara) ou 0(não)

static int cond_always(const FSMContext *ctx)
{
    (void)ctx;
    return 1;
}

static int cond_self_hp_below_30(const FSMContext *ctx)
{
    return ctx->self->hp * 100 / ctx->self->hp_max < 30;
}

static int cond_self_hp_below_15(const FSMContext *ctx)
{
    return ctx->self->hp * 100 / ctx->self->hp_max < 15;
}

static int cond_self_hp_below_60(const FSMContext *ctx)
{
    return ctx->self->hp * 100 / ctx->self->hp_max < 60;
}

static int cond_self_hp_above_50(const FSMContext *ctx)
{
    return ctx->self->hp * 100 / ctx->self->hp_max >= 50;
}

static int cond_player_hp_below_50(const FSMContext *ctx)
{
    return ctx->player->hp * 100 / ctx->player->hp_max < 50;
}
// todas são funções baseadas na vidado inimigo e do jogador, que recebem o contexto (inimigo e jogador) e retornam 1 ou 0 dependendo da condição. Essas funções são usadas para determinar as transições entre os estados da FSM dos inimigos.

void enemy_create_bull(Enemy *e)
{
    character_init(&e->character, "Touro Guerreiro", 170, 22, 8, 12);
    fsm_init(&e->fsm, STATE_ATTACK);

    /* De ATACAR */
    fsm_add_edge(&e->fsm, STATE_ATTACK, STATE_DEFEND,
                 cond_self_hp_below_15, 10);
    fsm_add_edge(&e->fsm, STATE_ATTACK, STATE_STRONG_ATTACK,
                 cond_player_hp_below_50, 5);
    fsm_add_edge(&e->fsm, STATE_ATTACK, STATE_ATTACK,
                 cond_always, 1);

    /* De ATAQUE FORTE */
    fsm_add_edge(&e->fsm, STATE_STRONG_ATTACK, STATE_DEFEND,
                 cond_self_hp_below_15, 10);
    fsm_add_edge(&e->fsm, STATE_STRONG_ATTACK, STATE_STRONG_ATTACK,
                 cond_always, 1);
}

void enemy_create_dark_mage(Enemy *e)
{
    character_init(&e->character, "Mago Negro", 250, 18, 14, 10);
    fsm_init(&e->fsm, STATE_ATTACK);

    /* De ATACAR */
    fsm_add_edge(&e->fsm, STATE_ATTACK, STATE_DEFEND,
                 cond_self_hp_below_30, 10);
    fsm_add_edge(&e->fsm, STATE_ATTACK, STATE_STRONG_ATTACK,
                 cond_player_hp_below_50, 5);
    fsm_add_edge(&e->fsm, STATE_ATTACK, STATE_ATTACK,
                 cond_always, 1);

    /* De DEFENDER — pode voltar a atacar se se recuperar */
    fsm_add_edge(&e->fsm, STATE_DEFEND, STATE_ATTACK,
                 cond_self_hp_above_50, 5);
    fsm_add_edge(&e->fsm, STATE_DEFEND, STATE_DEFEND,
                 cond_always, 1);
}

void enemy_create_blue_eyes(Enemy *e)
{
    character_init(&e->character, "Dragao Branco de Olhos Azuis", 300, 28, 15, 8);
    fsm_init(&e->fsm, STATE_DEFEND);

    // De DEFENDER
    fsm_add_edge(&e->fsm, STATE_DEFEND, STATE_ATTACK,
                 cond_self_hp_below_60, 20);
    fsm_add_edge(&e->fsm, STATE_DEFEND, STATE_ATTACK,
                 cond_always, 1);

    // De ATACAR
    fsm_add_edge(&e->fsm, STATE_ATTACK, STATE_STRONG_ATTACK,
                 cond_self_hp_below_15, 20); /* fase 3 */
    fsm_add_edge(&e->fsm, STATE_ATTACK, STATE_STRONG_ATTACK,
                 cond_self_hp_below_30, 10); /* oportunidade */
    fsm_add_edge(&e->fsm, STATE_ATTACK, STATE_ATTACK,
                 cond_always, 1);

    // De ATAQUE FORTE — fase 3: nunca sai daqui
    fsm_add_edge(&e->fsm, STATE_STRONG_ATTACK, STATE_STRONG_ATTACK,
                 cond_always, 1);
}

//  enemy_think
//  Chamada a cada turno do inimigo pelo combat.c.
//  Monta o contexto e atualiza a FSM.
//  Retorna o estado decidido — combat.c usa para executar a ação.
FSMState enemy_think(Enemy *e, const Character *player)
{
    FSMContext ctx = {&e->character, player};
    return fsm_update(&e->fsm, &ctx);
}