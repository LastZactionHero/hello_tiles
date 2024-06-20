/*
 * Copyright (c) 2020-2023 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_memory.h"
#include "bn_bg_tiles.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_map_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_map_cell_info.h"

#include "bn_blending_actions.h"
#include "bn_blending_fade_alpha.h"
#include "bn_sprite_text_generator.h"
#include "bn_blending_fade_alpha_hbe_ptr.h"
#include "bn_blending_transparency_attributes.h"
#include "bn_blending_transparency_attributes_hbe_ptr.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"

#include "bn_bg_palette_items_palette.h"
#include "bn_regular_bg_tiles_items_tm_territory_markers.h"

#include "bn_regular_bg_items_territory_map.h"

#define TM_TERRITORY_MARKER_CAT_NONE_TILE_INDEX 0
#define TM_TERRITORY_MARKER_CAT_PLAYER_TILE_INDEX 1
#define TM_TERRITORY_MARKER_CAT_A_TILE_INDEX 2

#define GRID_SIZE_COLS 32
#define GRID_SIZE_ROWS 32
#define GRID_CELLS_COUNT GRID_SIZE_COLS *GRID_SIZE_ROWS

#define GRID_VISIBLE_COL_MIN 1
#define GRID_VISIBLE_COL_MAX GRID_SIZE_COLS - GRID_VISIBLE_COL_MIN
#define GRID_VISIBLE_ROW_MIN 6
#define GRID_VISIBLE_ROW_MAX GRID_SIZE_COLS - GRID_VISIBLE_ROW_MIN

namespace
{

    int tile_map[600] = {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5,
                          22, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          44, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 49,
                          110, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 115};

    enum Cats
    {
        CAT_NONE,
        CAT_PLAYER,
        CAT_A,
    };

    Cats territory_ownership[GRID_CELLS_COUNT];

    struct bg_map
    {
        static constexpr int columns = GRID_SIZE_COLS;
        static constexpr int rows = GRID_SIZE_ROWS;

        alignas(int) bn::regular_bg_map_cell cells[GRID_CELLS_COUNT];
        bn::regular_bg_map_item map_item;

        bg_map() : map_item(cells[0], bn::size(bg_map::columns, bg_map::rows))
        {
            reset();
        }

        void draw()
        {
            for (int row_idx = GRID_VISIBLE_ROW_MIN; row_idx < GRID_VISIBLE_ROW_MAX; row_idx++)
            {
                for (int col_idx = GRID_VISIBLE_COL_MIN; col_idx < GRID_VISIBLE_COL_MAX; col_idx++)
                {
                    bn::regular_bg_map_cell &current_cell = cells[map_item.cell_index(col_idx, row_idx)];
                    bn::regular_bg_map_cell_info current_cell_info(current_cell);

                    Cats controlling_cat = territory_ownership[row_idx * GRID_SIZE_COLS + col_idx];
                    int tile_idx = TM_TERRITORY_MARKER_CAT_NONE_TILE_INDEX;
                    if (controlling_cat == CAT_PLAYER)
                    {
                        tile_idx = TM_TERRITORY_MARKER_CAT_PLAYER_TILE_INDEX;
                    }
                    else if (controlling_cat == CAT_A)
                    {
                        tile_idx = TM_TERRITORY_MARKER_CAT_A_TILE_INDEX;
                    }

                    current_cell_info.set_tile_index(tile_idx);
                    current_cell_info.set_palette_id(0);
                    current_cell_info.set_horizontal_flip(false);
                    current_cell = current_cell_info.cell();
                }
            }
        }

        void reset()
        {
            bn::memory::clear(GRID_CELLS_COUNT, cells[0]);
        }

    private:
    };
}

void claim_territory(int row, int col, Cats cat)
{
    territory_ownership[row * GRID_SIZE_COLS + col] = cat;
}

int main()
{
    bn::core::init();

    for (int i = 0; i < GRID_CELLS_COUNT; i++)
    {
        territory_ownership[i] = CAT_NONE;
    }
    claim_territory(12, 12, CAT_PLAYER);

    claim_territory(7, 10, CAT_A);
    claim_territory(8, 10, CAT_A);
    claim_territory(7, 11, CAT_A);
    claim_territory(8, 11, CAT_A);
    claim_territory(9, 11, CAT_A);

    claim_territory(15, 14, CAT_A);
    claim_territory(15, 15, CAT_A);
    claim_territory(15, 16, CAT_A);
    claim_territory(16, 14, CAT_A);
    claim_territory(16, 15, CAT_A);
    claim_territory(16, 16, CAT_A);

    bn::bg_tiles::set_allow_offset(false);

    bn::regular_bg_ptr territory_map_bg = bn::regular_bg_items::territory_map.create_bg(0, 0);

    bn::unique_ptr<bg_map> bg_map_ptr(new bg_map());
    bn::regular_bg_item bg_item(
        bn::regular_bg_tiles_items::tm_territory_markers,
        bn::bg_palette_items::palette,
        bg_map_ptr->map_item);
    bn::regular_bg_ptr bg = bg_item.create_bg(0, 0);
    bn::regular_bg_map_ptr bg_map = bg.map();

    bn::bg_tiles::set_allow_offset(true);
    bg.set_blending_enabled(true);
    bn::blending::set_transparency_alpha(0.25);

    bg_map_ptr->draw();
    bg_map.reload_cells_ref();

    while (true)
    {
        bn::core::update();
    }
}