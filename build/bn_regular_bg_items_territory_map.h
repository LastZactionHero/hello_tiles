#ifndef BN_REGULAR_BG_ITEMS_TERRITORY_MAP_H
#define BN_REGULAR_BG_ITEMS_TERRITORY_MAP_H

#include "bn_regular_bg_item.h"

//{{BLOCK(territory_map_bn_gfx)

//======================================================================
//
//	territory_map_bn_gfx, 256x256@8, 
//	+ palette 64 entries, not compressed
//	+ 115 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 128 + 7360 + 2048 = 9536
//
//	Time-stamp: 2024-06-16, 22:57:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TERRITORY_MAP_BN_GFX_H
#define GRIT_TERRITORY_MAP_BN_GFX_H

#define territory_map_bn_gfxTilesLen 7360
extern const bn::tile territory_map_bn_gfxTiles[230];

#define territory_map_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell territory_map_bn_gfxMap[1024];

#define territory_map_bn_gfxPalLen 128
extern const bn::color territory_map_bn_gfxPal[64];

#endif // GRIT_TERRITORY_MAP_BN_GFX_H

//}}BLOCK(territory_map_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item territory_map(
            regular_bg_tiles_item(span<const tile>(territory_map_bn_gfxTiles, 230), bpp_mode::BPP_8, compression_type::NONE), 
            bg_palette_item(span<const color>(territory_map_bn_gfxPal, 64), bpp_mode::BPP_8, compression_type::NONE),
            regular_bg_map_item(territory_map_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

