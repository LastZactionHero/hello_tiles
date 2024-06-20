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

// #include "bn_bg_palette_items_palette.h"
// #include "bn_regular_bg_tiles_items_tm_territory_markers.h"

#include "bn_bg_palette_items_grass_tileset_palette.h"
#include "bn_regular_bg_tiles_items_grass_tileset.h"

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

#define MAP_ROWS 20
#define MAP_COLS 30

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

        void draw(int viewport_center_row, int viewport_center_col)
        {
            for (int col_idx = 0; col_idx < GRID_SIZE_COLS; col_idx++)
            {
                for (int row_idx = 0; row_idx < GRID_SIZE_ROWS; row_idx++)
                {
                    bn::regular_bg_map_cell &current_cell = cells[map_item.cell_index(col_idx, row_idx)];
                    bn::regular_bg_map_cell_info current_cell_info(current_cell);

                    int tile_idx = 1000; // Undefined

                    int viewport_row_idx = row_idx - GRID_SIZE_ROWS / 2 + viewport_center_row;
                    int viewport_col_idx = col_idx - GRID_SIZE_COLS / 2 + viewport_center_col;

                    int tile_map_idx = viewport_row_idx * MAP_COLS + viewport_col_idx;
                    if (viewport_row_idx < MAP_ROWS && viewport_col_idx < MAP_COLS && viewport_row_idx >= 0 && viewport_col_idx >= 0)
                    {
                        tile_idx = tile_map[tile_map_idx];
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

// void claim_territory(int row, int col, Cats cat)
// {
//     territory_ownership[row * GRID_SIZE_COLS + col] = cat;
// }

int viewport_center_row = MAP_ROWS / 2;
int viewport_center_col = MAP_COLS / 2;

int main()
{
    bn::core::init();

    // for (int i = 0; i < GRID_CELLS_COUNT; i++)
    // {
    //     territory_ownership[i] = CAT_NONE;
    // }
    // claim_territory(12, 12, CAT_PLAYER);

    // claim_territory(7, 10, CAT_A);
    // claim_territory(8, 10, CAT_A);
    // claim_territory(7, 11, CAT_A);
    // claim_territory(8, 11, CAT_A);
    // claim_territory(9, 11, CAT_A);

    // claim_territory(15, 14, CAT_A);
    // claim_territory(15, 15, CAT_A);
    // claim_territory(15, 16, CAT_A);
    // claim_territory(16, 14, CAT_A);
    // claim_territory(16, 15, CAT_A);
    // claim_territory(16, 16, CAT_A);

    bn::bg_tiles::set_allow_offset(false);


    bn::unique_ptr<bg_map> bg_map_ptr(new bg_map());
    bn::regular_bg_item bg_item(
        bn::regular_bg_tiles_items::grass_tileset,
        bn::bg_palette_items::grass_tileset_palette,
        bg_map_ptr->map_item);
    bn::regular_bg_ptr bg = bg_item.create_bg(0, 0);
    bn::regular_bg_map_ptr bg_map = bg.map();

    bn::bg_tiles::set_allow_offset(true);
    bg.set_blending_enabled(true);
    bn::blending::set_transparency_alpha(1.0);

    bg_map_ptr->draw(viewport_center_row, viewport_center_col);
    bg_map.reload_cells_ref();

    while (true)
    {
        bool viewport_update = false;

        if(bn::keypad::left_pressed()) {
            viewport_center_col--;
            viewport_update = true;
        } else if(bn::keypad::right_pressed()) {
            viewport_center_col++;
            viewport_update = true;
        } else if(bn::keypad::down_pressed()) {
            viewport_center_row++;
            viewport_update = true;
        } else if(bn::keypad::up_pressed()) {
            viewport_center_row--;
            viewport_update = true;
        }
        if(viewport_update) {
            bg_map_ptr->draw(viewport_center_row, viewport_center_col);
            bg_map.reload_cells_ref();
        }

        bn::core::update();
    }
}