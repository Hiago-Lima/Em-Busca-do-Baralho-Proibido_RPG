// Fluxo completo utilizando td
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "character.h"
#include "stack.h"
#include "enemies.h"
#include "combat.h"
#include "story.h"

int main(void)
{
    /* Semente aleatória — garante variação diferente a cada execução */
    srand((unsigned int)time(NULL));

    /* Variáveis principais do jogo */
    Character player;
    ActionStack history;
    stack_init(&history);

    /* ── Narrativa inicial ──────────────────────────────────────── */
    story_title_screen();
    HeroID hero = story_character_select(&player);
    story_intro(hero);

    /* ── FASE 1: Touro Guerreiro ────────────────────────────────── */
    story_phase_intro(0);
    Enemy bull;
    enemy_create_bull(&bull);

    CombatResult r1 = combat_run(&player, &bull, &history);
    fsm_destroy(&bull.fsm);

    if (r1 == COMBAT_DEFEAT)
    {
        story_game_over();
        return 0;
    }

    /* ── FASE 2: Mago Negro ─────────────────────────────────────── */
    story_phase_intro(1);
    Enemy mage;
    enemy_create_dark_mage(&mage);

    CombatResult r2 = combat_run(&player, &mage, &history);
    fsm_destroy(&mage.fsm);

    if (r2 == COMBAT_DEFEAT)
    {
        story_game_over();
        return 0;
    }

    /* ── FASE 3: Dragão Branco de Olhos Azuis ───────────────────── */
    story_phase_intro(2);
    Enemy dragon;
    enemy_create_blue_eyes(&dragon);

    CombatResult r3 = combat_run(&player, &dragon, &history);
    fsm_destroy(&dragon.fsm);

    if (r3 == COMBAT_DEFEAT)
    {
        story_game_over();
        return 0;
    }

    /* ── Vitória final ──────────────────────────────────────────── */
    story_victory(&history);

    return 0;
}