#ifndef BN_SPRITE_ITEMS_TERRITORY_MARKER_RED_H
#define BN_SPRITE_ITEMS_TERRITORY_MARKER_RED_H

#include "bn_sprite_item.h"

//{{BLOCK(territory_marker_red_bn_gfx)

//======================================================================
//
//	territory_marker_red_bn_gfx, 16x16@8, 
//	+ palette 48 entries, not compressed
//	+ 4 tiles not compressed
//	Total size: 96 + 256 = 352
//
//	Time-stamp: 2024-06-16, 22:57:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TERRITORY_MARKER_RED_BN_GFX_H
#define GRIT_TERRITORY_MARKER_RED_BN_GFX_H

#define territory_marker_red_bn_gfxTilesLen 256
extern const bn::tile territory_marker_red_bn_gfxTiles[8];

#define territory_marker_red_bn_gfxPalLen 96
extern const bn::color territory_marker_red_bn_gfxPal[48];

#endif // GRIT_TERRITORY_MARKER_RED_BN_GFX_H

//}}BLOCK(territory_marker_red_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item territory_marker_red(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(territory_marker_red_bn_gfxTiles, 8), bpp_mode::BPP_8, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(territory_marker_red_bn_gfxPal, 48), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

