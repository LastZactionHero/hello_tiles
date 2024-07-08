#ifndef BN_BG_PALETTE_ITEMS_GRASS_TILESET_PALETTE_H
#define BN_BG_PALETTE_ITEMS_GRASS_TILESET_PALETTE_H

#include "bn_bg_palette_item.h"

//{{BLOCK(grass_tileset_palette_bn_gfx)

//======================================================================
//
//	grass_tileset_palette_bn_gfx, 8x8@8, 
//	+ palette 64 entries, not compressed
//	Total size: 128 = 128
//
//	Time-stamp: 2024-06-22, 23:32:01
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GRASS_TILESET_PALETTE_BN_GFX_H
#define GRIT_GRASS_TILESET_PALETTE_BN_GFX_H

#define grass_tileset_palette_bn_gfxPalLen 128
extern const bn::color grass_tileset_palette_bn_gfxPal[64];

#endif // GRIT_GRASS_TILESET_PALETTE_BN_GFX_H

//}}BLOCK(grass_tileset_palette_bn_gfx)

namespace bn::bg_palette_items
{
    constexpr inline bg_palette_item grass_tileset_palette(span<const color>(grass_tileset_palette_bn_gfxPal, 64), 
            bpp_mode::BPP_4, compression_type::NONE);
}

#endif

