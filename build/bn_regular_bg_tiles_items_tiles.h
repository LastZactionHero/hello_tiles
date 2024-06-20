#ifndef BN_REGULAR_BG_TILES_ITEMS_TILES_H
#define BN_REGULAR_BG_TILES_ITEMS_TILES_H

#include "bn_regular_bg_tiles_item.h"

//{{BLOCK(tiles_bn_gfx)

//======================================================================
//
//	tiles_bn_gfx, 56x8@4, 
//	+ 7 tiles not compressed
//	Total size: 224 = 224
//
//	Time-stamp: 2024-06-16, 22:57:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TILES_BN_GFX_H
#define GRIT_TILES_BN_GFX_H

#define tiles_bn_gfxTilesLen 224
extern const bn::tile tiles_bn_gfxTiles[7];

#endif // GRIT_TILES_BN_GFX_H

//}}BLOCK(tiles_bn_gfx)

namespace bn::regular_bg_tiles_items
{
    constexpr inline regular_bg_tiles_item tiles(
            span<const tile>(tiles_bn_gfxTiles, 7), bpp_mode::BPP_4, compression_type::NONE);
}

#endif

