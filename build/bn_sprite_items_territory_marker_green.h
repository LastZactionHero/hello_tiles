#ifndef BN_SPRITE_ITEMS_TERRITORY_MARKER_GREEN_H
#define BN_SPRITE_ITEMS_TERRITORY_MARKER_GREEN_H

#include "bn_sprite_item.h"

//{{BLOCK(territory_marker_green_bn_gfx)

//======================================================================
//
//	territory_marker_green_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles not compressed
//	Total size: 32 + 128 = 160
//
//	Time-stamp: 2024-06-16, 22:57:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TERRITORY_MARKER_GREEN_BN_GFX_H
#define GRIT_TERRITORY_MARKER_GREEN_BN_GFX_H

#define territory_marker_green_bn_gfxTilesLen 128
extern const bn::tile territory_marker_green_bn_gfxTiles[4];

#define territory_marker_green_bn_gfxPalLen 32
extern const bn::color territory_marker_green_bn_gfxPal[16];

#endif // GRIT_TERRITORY_MARKER_GREEN_BN_GFX_H

//}}BLOCK(territory_marker_green_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item territory_marker_green(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(territory_marker_green_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(territory_marker_green_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

