#ifndef BN_BG_PALETTE_ITEMS_NEIGHBORHOOD_PALETTE_H
#define BN_BG_PALETTE_ITEMS_NEIGHBORHOOD_PALETTE_H

#include "bn_bg_palette_item.h"

//{{BLOCK(neighborhood_palette_bn_gfx)

//======================================================================
//
//	neighborhood_palette_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	Total size: 32 = 32
//
//	Time-stamp: 2024-07-08, 15:42:10
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_NEIGHBORHOOD_PALETTE_BN_GFX_H
#define GRIT_NEIGHBORHOOD_PALETTE_BN_GFX_H

#define neighborhood_palette_bn_gfxPalLen 32
extern const bn::color neighborhood_palette_bn_gfxPal[64];

#endif // GRIT_NEIGHBORHOOD_PALETTE_BN_GFX_H

//}}BLOCK(neighborhood_palette_bn_gfx)

namespace bn::bg_palette_items
{
    constexpr inline bg_palette_item neighborhood_palette(span<const color>(neighborhood_palette_bn_gfxPal, 64), 
            bpp_mode::BPP_4, compression_type::NONE);
}

#endif

