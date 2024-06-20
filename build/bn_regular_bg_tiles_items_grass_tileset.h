#ifndef BN_REGULAR_BG_TILES_ITEMS_GRASS_TILESET_H
#define BN_REGULAR_BG_TILES_ITEMS_GRASS_TILESET_H

#include "bn_regular_bg_tiles_item.h"

//{{BLOCK(grass_tileset_bn_gfx)

//======================================================================
//
//	grass_tileset_bn_gfx, 176x112@4, 
//	+ 308 tiles not compressed
//	Total size: 9856 = 9856
//
//	Time-stamp: 2024-06-20, 04:20:22
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GRASS_TILESET_BN_GFX_H
#define GRIT_GRASS_TILESET_BN_GFX_H

#define grass_tileset_bn_gfxTilesLen 9856
extern const bn::tile grass_tileset_bn_gfxTiles[308];

#endif // GRIT_GRASS_TILESET_BN_GFX_H

//}}BLOCK(grass_tileset_bn_gfx)

namespace bn::regular_bg_tiles_items
{
    constexpr inline regular_bg_tiles_item grass_tileset(
            span<const tile>(grass_tileset_bn_gfxTiles, 308), bpp_mode::BPP_4, compression_type::NONE);
}

#endif

