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
#include "bn_regular_bg_map_cell_info.h"

#include "bn_blending_actions.h"

#include "common_info.h"

#include "bn_bg_palette_items_grass_tileset_palette.h"
#include "bn_regular_bg_tiles_items_grass_tileset.h"

#include "./tile_map.h"

#define GRID_SIZE_COLS 32
#define GRID_SIZE_ROWS 32
#define GRID_CELLS_COUNT GRID_SIZE_COLS *GRID_SIZE_ROWS

#define MAP_ROWS 20
#define MAP_COLS 30

#define TILE_UNDEFINED 1000

namespace
{

    struct Point
    {
        int x; // col
        int y; // row
    };

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

        void draw(Point viewport_center)
        {
            for (int col_idx = 0; col_idx < GRID_SIZE_COLS; col_idx++)
            {
                for (int row_idx = 0; row_idx < GRID_SIZE_ROWS; row_idx++)
                {
                    bn::regular_bg_map_cell &current_cell = cells[map_item.cell_index(col_idx, row_idx)];
                    bn::regular_bg_map_cell_info current_cell_info(current_cell);

                    int tile_idx = TILE_UNDEFINED;

                    Point viewport_cell = {
                        col_idx - GRID_SIZE_COLS / 2 + viewport_center.x,
                        row_idx - GRID_SIZE_ROWS / 2 + viewport_center.y};

                    int tile_map_idx = viewport_cell.y * MAP_COLS + viewport_cell.x;
                    if (viewport_cell.y < MAP_ROWS &&
                        viewport_cell.x < MAP_COLS &&
                        viewport_cell.y >= 0 &&
                        viewport_cell.x >= 0)
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

// Start at the center of the map
Point viewport_center = {MAP_COLS / 2, MAP_ROWS / 2};

enum MoveDirection
{
    MOVE_NONE,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN
};

bool validate_viewport_move(Point new_point)
{
    // Center of viewport must still contain the map.
    if (new_point.x < 0 ||
        new_point.y < 0 ||
        new_point.x > MAP_COLS ||
        new_point.y > MAP_ROWS)
    {
        return false;
    }
    return true;
}

Point move_viewport(Point original_point, MoveDirection direction)
{
    Point new_point = original_point;
    switch (direction)
    {
    case MOVE_LEFT:
        new_point = {--new_point.x, new_point.y};
        break;
    case MOVE_RIGHT:
        new_point = {++new_point.x, new_point.y};
        break;
    case MOVE_UP:
        new_point = {new_point.x, --new_point.y};
        break;
    case MOVE_DOWN:
        new_point = {new_point.x, ++new_point.y};
        break;
    default:
        break;
    }
    if (validate_viewport_move(new_point))
    {
        return new_point;
    }
    return original_point;
}

int main()
{
    bn::core::init();

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

    bg_map_ptr->draw(viewport_center);
    bg_map.reload_cells_ref();

    while (true)
    {
        MoveDirection direction = MOVE_NONE;
        if (bn::keypad::left_pressed())
        {
            direction = MOVE_LEFT;
        }
        else if (bn::keypad::right_pressed())
        {
            direction = MOVE_RIGHT;
        }
        else if (bn::keypad::down_pressed())
        {
            direction = MOVE_DOWN;
        }
        else if (bn::keypad::up_pressed())
        {
            direction = MOVE_UP;
        }
        if (direction != MOVE_NONE)
        {
            viewport_center = move_viewport(viewport_center, direction);
            bg_map_ptr->draw(viewport_center);
            bg_map.reload_cells_ref();
        }

        bn::core::update();
    }
}