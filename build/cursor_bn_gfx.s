
@{{BLOCK(cursor_bn_gfx)

@=======================================================================
@
@	cursor_bn_gfx, 8x8@4, 
@	+ palette 16 entries, not compressed
@	+ 1 tiles not compressed
@	Total size: 32 + 32 = 64
@
@	Time-stamp: 2024-06-16, 22:57:54
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global cursor_bn_gfxTiles		@ 32 unsigned chars
	.hidden cursor_bn_gfxTiles
cursor_bn_gfxTiles:
	.word 0x00055500,0x05555550,0x52111115,0x05555555,0x00053500,0x00054500,0x00054500,0x00055500

	.section .rodata
	.align	2
	.global cursor_bn_gfxPal		@ 32 unsigned chars
	.hidden cursor_bn_gfxPal
cursor_bn_gfxPal:
	.hword 0x03E0,0x4E75,0x7FFF,0x1890,0x10F8,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(cursor_bn_gfx)
