#ifndef BN_REGULAR_BG_TILES_ITEMS_TM_TERRITORY_MARKERS_H
#define BN_REGULAR_BG_TILES_ITEMS_TM_TERRITORY_MARKERS_H

#include "bn_regular_bg_tiles_item.h"

//{{BLOCK(tm_territory_markers_bn_gfx)

//======================================================================
//
//	tm_territory_markers_bn_gfx, 80x8@4, 
//	+ 10 tiles not compressed
//	Total size: 320 = 320
//
//	Time-stamp: 2024-06-20, 04:20:22
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TM_TERRITORY_MARKERS_BN_GFX_H
#define GRIT_TM_TERRITORY_MARKERS_BN_GFX_H

#define tm_territory_markers_bn_gfxTilesLen 320
extern const bn::tile tm_territory_markers_bn_gfxTiles[10];

#endif // GRIT_TM_TERRITORY_MARKERS_BN_GFX_H

//}}BLOCK(tm_territory_markers_bn_gfx)

namespace bn::regular_bg_tiles_items
{
    constexpr inline regular_bg_tiles_item tm_territory_markers(
            span<const tile>(tm_territory_markers_bn_gfxTiles, 10), bpp_mode::BPP_4, compression_type::NONE);
}

#endif

