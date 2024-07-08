#ifndef BN_REGULAR_BG_TILES_ITEMS_NEIGHBORHOOD_TILESET_H
#define BN_REGULAR_BG_TILES_ITEMS_NEIGHBORHOOD_TILESET_H

#include "bn_regular_bg_tiles_item.h"

//{{BLOCK(neighborhood_tileset_bn_gfx)

//======================================================================
//
//	neighborhood_tileset_bn_gfx, 256x256@4, 
//	+ 1024 tiles not compressed
//	Total size: 32768 = 32768
//
//	Time-stamp: 2024-07-08, 15:42:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_NEIGHBORHOOD_TILESET_BN_GFX_H
#define GRIT_NEIGHBORHOOD_TILESET_BN_GFX_H

#define neighborhood_tileset_bn_gfxTilesLen 32768
extern const bn::tile neighborhood_tileset_bn_gfxTiles[1024];

#endif // GRIT_NEIGHBORHOOD_TILESET_BN_GFX_H

//}}BLOCK(neighborhood_tileset_bn_gfx)

namespace bn::regular_bg_tiles_items
{
    constexpr inline regular_bg_tiles_item neighborhood_tileset(
            span<const tile>(neighborhood_tileset_bn_gfxTiles, 1024), bpp_mode::BPP_4, compression_type::NONE);
}

#endif

