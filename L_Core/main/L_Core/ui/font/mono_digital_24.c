/*******************************************************************************
 * Size: 24 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef MONO_DIGITAL_24
#define MONO_DIGITAL_24 1
#endif

#if MONO_DIGITAL_24

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x7f, 0xfd, 0x7f, 0xcf,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+0023 "#" */
    0x0, 0x1b, 0xd, 0x99, 0x3c, 0x99, 0xb3, 0x27,
    0x93, 0x36, 0x1b, 0x0, 0x0,

    /* U+0024 "$" */
    0x0, 0x6, 0x3, 0x1f, 0xf7, 0xf6, 0x63, 0x31,
    0x98, 0xcc, 0x60, 0x3f, 0xcf, 0xf0, 0x18, 0x6c,
    0x36, 0x1b, 0xd, 0xbf, 0xff, 0xa1, 0x80, 0xc0,
    0x0,

    /* U+0025 "%" */
    0xe8, 0xcf, 0x1b, 0x67, 0x78, 0xcb, 0xb8, 0x6,
    0x0, 0xc0, 0x10, 0x8, 0x3, 0x0, 0x60, 0x1d,
    0xd3, 0x1e, 0xe6, 0xd8, 0xf3, 0x17,

    /* U+0026 "&" */
    0x7d, 0xf, 0xc6, 0x31, 0x8c, 0x63, 0x10, 0x47,
    0xf3, 0xfe, 0xc1, 0xb0, 0x6c, 0x1b, 0x6, 0xc0,
    0x9f, 0xef, 0xfc, 0x6, 0x0, 0x80,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x39, 0xec, 0x30, 0xc3, 0xc, 0x20, 0x83, 0xc,
    0x30, 0xc3, 0x7, 0x8e,

    /* U+0029 ")" */
    0x71, 0xe0, 0xc3, 0xc, 0x30, 0xc1, 0x4, 0x30,
    0xc3, 0xc, 0x37, 0x9c,

    /* U+002A "*" */
    0x18, 0x18, 0xff, 0x7e, 0x7e, 0xff, 0x18, 0x18,

    /* U+002B "+" */
    0x0, 0x18, 0x18, 0x7e, 0x7e, 0x18, 0x18, 0x0,

    /* U+002C "," */
    0xff,

    /* U+002D "-" */
    0xff, 0xfc,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x1, 0x81, 0xc0, 0xc0, 0xe0, 0x60, 0x70, 0x30,
    0x18, 0x10, 0x18, 0xc, 0xe, 0x6, 0x7, 0x3,
    0x1, 0x80,

    /* U+0030 "0" */
    0xfe, 0xbf, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x1, 0x80, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xff, 0xfd,

    /* U+0031 "1" */
    0x7f, 0xfd, 0x7f, 0xfd,

    /* U+0032 "2" */
    0xfe, 0xbf, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6,
    0xff, 0xff, 0x60, 0x30, 0x18, 0xc, 0x6, 0x1,
    0xf9, 0xfe,

    /* U+0033 "3" */
    0xfe, 0xff, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6,
    0xff, 0x7f, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xf,
    0xff, 0xfd,

    /* U+0034 "4" */
    0x1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0x7f, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xc,
    0x6, 0x3,

    /* U+0035 "5" */
    0xff, 0x3f, 0x30, 0x18, 0xc, 0x6, 0x3, 0x1,
    0xfe, 0x7f, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xd,
    0xff, 0xfd,

    /* U+0036 "6" */
    0xff, 0x3f, 0x30, 0x18, 0xc, 0x6, 0x3, 0x1,
    0xfe, 0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xff, 0xfd,

    /* U+0037 "7" */
    0xfe, 0xbf, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x1, 0x0, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xc,
    0x6, 0x3,

    /* U+0038 "8" */
    0xfe, 0xbf, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xff, 0xfd,

    /* U+0039 "9" */
    0xfe, 0xbf, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0x7f, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xd,
    0xff, 0xfd,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0xf0, 0x0, 0x3, 0xfc,

    /* U+003C "<" */
    0xc, 0x63, 0x18, 0x1, 0x83, 0x6, 0xc,

    /* U+003D "=" */
    0xff, 0xfc, 0x7, 0xff, 0xe0,

    /* U+003E ">" */
    0xc1, 0x83, 0x6, 0x4, 0x73, 0x18, 0xc0,

    /* U+003F "?" */
    0xfe, 0xbf, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6,
    0xff, 0xff, 0x60, 0x30, 0x18, 0x0, 0x0, 0x3,
    0x1, 0x80,

    /* U+0040 "@" */
    0xfe, 0xbf, 0xf0, 0x7b, 0xfc, 0xfe, 0xcf, 0x67,
    0x21, 0x90, 0xec, 0xf6, 0x79, 0xfd, 0xee, 0x1,
    0xf9, 0xfc,

    /* U+0041 "A" */
    0xfe, 0xbf, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf,
    0x7, 0x83,

    /* U+0042 "B" */
    0xfe, 0x3f, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xfd, 0xfc,

    /* U+0043 "C" */
    0xff, 0x3f, 0xb0, 0x18, 0xc, 0x6, 0x3, 0x1,
    0x0, 0x80, 0x60, 0x30, 0x18, 0xc, 0x6, 0x1,
    0xfd, 0xfe,

    /* U+0044 "D" */
    0xfe, 0x3f, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x1, 0x80, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xfd, 0xfc,

    /* U+0045 "E" */
    0xff, 0x3f, 0xb0, 0x18, 0xc, 0x6, 0x3, 0x1,
    0xfe, 0xff, 0x60, 0x30, 0x18, 0xc, 0x6, 0x1,
    0xfd, 0xfe,

    /* U+0046 "F" */
    0xff, 0x3f, 0xb0, 0x18, 0xc, 0x6, 0x3, 0x1,
    0xfe, 0xff, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80,

    /* U+0047 "G" */
    0xff, 0x3f, 0x30, 0x18, 0xc, 0x6, 0x3, 0x1,
    0xe, 0x87, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xff, 0xfd,

    /* U+0048 "H" */
    0x81, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf,
    0x7, 0x83,

    /* U+0049 "I" */
    0x7f, 0xfd, 0x7f, 0xfc,

    /* U+004A "J" */
    0x1, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6,
    0x1, 0x80, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xff, 0xfd,

    /* U+004B "K" */
    0x81, 0x61, 0xb1, 0x99, 0x8d, 0x87, 0xc3, 0xc1,
    0xfe, 0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf,
    0x7, 0x83,

    /* U+004C "L" */
    0xc0, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3, 0x1,
    0x0, 0x80, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3,
    0xff, 0x7f,

    /* U+004D "M" */
    0xff, 0x5f, 0xfc, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xce, 0x31, 0x80, 0x70, 0x3c, 0xf, 0x3, 0xc0,
    0xf0, 0x3c, 0xf, 0x3,

    /* U+004E "N" */
    0xc1, 0xf8, 0xfc, 0x7b, 0x3c, 0xde, 0x3e, 0x2,
    0x0, 0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf,
    0x6,

    /* U+004F "O" */
    0x3e, 0x3f, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x1, 0x80, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xfc, 0x7c,

    /* U+0050 "P" */
    0xfe, 0x3f, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0xff, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80,

    /* U+0051 "Q" */
    0xfe, 0xbf, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x1, 0x80, 0xe0, 0xf0, 0x78, 0x3c, 0x7e, 0x39,
    0xff, 0xfb,

    /* U+0052 "R" */
    0xfe, 0xbf, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0xff, 0x78, 0x3e, 0x1b, 0xc, 0xc6, 0x33,
    0xd, 0x2,

    /* U+0053 "S" */
    0xff, 0xbf, 0xb0, 0x18, 0xc, 0x6, 0x3, 0x1,
    0xfe, 0x7f, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xd,
    0xff, 0xfd,

    /* U+0054 "T" */
    0x7f, 0x9f, 0xe0, 0xc0, 0x30, 0xc, 0x3, 0x0,
    0xc0, 0x30, 0x0, 0x3, 0x0, 0xc0, 0x30, 0xc,
    0x3, 0x0, 0xc0, 0x30,

    /* U+0055 "U" */
    0x81, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x1, 0x80, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xff, 0xfd,

    /* U+0056 "V" */
    0x0, 0x60, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x1, 0x80, 0xe0, 0xf0, 0x6c, 0x63, 0x61, 0xb0,
    0x50, 0x0,

    /* U+0057 "W" */
    0x0, 0x30, 0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3c,
    0xe, 0x1, 0x8c, 0x73, 0x3c, 0xcf, 0x33, 0xcc,
    0xf3, 0x37, 0xff, 0xfd,

    /* U+0058 "X" */
    0xc1, 0xe1, 0xf8, 0xcc, 0xe7, 0x61, 0xf0, 0xf0,
    0x38, 0x1c, 0x1e, 0xf, 0x8e, 0xc6, 0x77, 0x1b,
    0xf, 0x83,

    /* U+0059 "Y" */
    0x1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0x7f, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xd,
    0xff, 0xfd,

    /* U+005A "Z" */
    0x7f, 0xbf, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18,
    0x8, 0x8, 0xc, 0x6, 0x6, 0x3, 0x3, 0x1,
    0xfc, 0xbe,

    /* U+005B "[" */
    0xfb, 0xb1, 0x8c, 0x63, 0x10, 0x86, 0x31, 0x8c,
    0x61, 0xdf,

    /* U+005C "\\" */
    0xc0, 0x60, 0x38, 0xc, 0x7, 0x1, 0x80, 0xc0,
    0x20, 0xc, 0x6, 0x3, 0x80, 0xc0, 0x70, 0x18,
    0xe, 0x3,

    /* U+005D "]" */
    0xeb, 0xc6, 0x31, 0x8c, 0x61, 0x8, 0xc6, 0x31,
    0x8d, 0xfd,

    /* U+005E "^" */
    0x0, 0xa, 0xd, 0x8c, 0x6c, 0x1c, 0x4,

    /* U+005F "_" */
    0xff, 0x7f, 0xc0,

    /* U+0060 "`" */
    0xc6, 0x31,

    /* U+0061 "a" */
    0xfe, 0xbf, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf,
    0x7, 0x83,

    /* U+0062 "b" */
    0xfe, 0x3f, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xfd, 0xfc,

    /* U+0063 "c" */
    0xff, 0x3f, 0xb0, 0x18, 0xc, 0x6, 0x3, 0x1,
    0x0, 0x80, 0x60, 0x30, 0x18, 0xc, 0x6, 0x1,
    0xfd, 0xfe,

    /* U+0064 "d" */
    0xfe, 0x3f, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x1, 0x80, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xfd, 0xfc,

    /* U+0065 "e" */
    0xff, 0x3f, 0xb0, 0x18, 0xc, 0x6, 0x3, 0x1,
    0xfe, 0xff, 0x60, 0x30, 0x18, 0xc, 0x6, 0x1,
    0xfd, 0xfe,

    /* U+0066 "f" */
    0xff, 0x3f, 0xb0, 0x18, 0xc, 0x6, 0x3, 0x1,
    0xfe, 0xff, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80,

    /* U+0067 "g" */
    0xff, 0x3f, 0x30, 0x18, 0xc, 0x6, 0x3, 0x1,
    0xe, 0x87, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xff, 0xfd,

    /* U+0068 "h" */
    0x81, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf,
    0x7, 0x83,

    /* U+0069 "i" */
    0x7f, 0xfd, 0x7f, 0xfc,

    /* U+006A "j" */
    0x1, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6,
    0x1, 0x80, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xff, 0xfd,

    /* U+006B "k" */
    0x81, 0x61, 0xb1, 0x99, 0x8d, 0x87, 0xc3, 0xc1,
    0xfe, 0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf,
    0x7, 0x83,

    /* U+006C "l" */
    0xc0, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3, 0x1,
    0x0, 0x80, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3,
    0xff, 0x7f,

    /* U+006D "m" */
    0xff, 0x5f, 0xfc, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xce, 0x31, 0x80, 0x70, 0x3c, 0xf, 0x3, 0xc0,
    0xf0, 0x3c, 0xf, 0x3,

    /* U+006E "n" */
    0xc1, 0xf8, 0xfc, 0x7b, 0x3c, 0xde, 0x3e, 0x2,
    0x0, 0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf,
    0x6,

    /* U+006F "o" */
    0x3e, 0x3f, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x1, 0x80, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xfc, 0x7c,

    /* U+0070 "p" */
    0xfe, 0x3f, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0xff, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80,

    /* U+0071 "q" */
    0xfe, 0xbf, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x1, 0x80, 0xe0, 0xf0, 0x78, 0x3c, 0x7e, 0x39,
    0xff, 0xfb,

    /* U+0072 "r" */
    0xfe, 0xbf, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0xff, 0x78, 0x3e, 0x1b, 0xc, 0xc6, 0x33,
    0xd, 0x2,

    /* U+0073 "s" */
    0xff, 0xbf, 0xb0, 0x18, 0xc, 0x6, 0x3, 0x1,
    0xfe, 0x7f, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xd,
    0xff, 0xfd,

    /* U+0074 "t" */
    0x7f, 0x9f, 0xe0, 0xc0, 0x30, 0xc, 0x3, 0x0,
    0xc0, 0x30, 0x0, 0x3, 0x0, 0xc0, 0x30, 0xc,
    0x3, 0x0, 0xc0, 0x30,

    /* U+0075 "u" */
    0x81, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x1, 0x80, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xd,
    0xff, 0xfd,

    /* U+0076 "v" */
    0x0, 0x60, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x1, 0x80, 0xe0, 0xf0, 0x6c, 0x63, 0x61, 0xb0,
    0x50, 0x0,

    /* U+0077 "w" */
    0x0, 0x30, 0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3c,
    0xe, 0x1, 0x8c, 0x73, 0x3c, 0xcf, 0x33, 0xcc,
    0xf3, 0x37, 0xff, 0xfd,

    /* U+0078 "x" */
    0xc1, 0xe1, 0xf8, 0xcc, 0xe7, 0x61, 0xf0, 0xf0,
    0x38, 0x1c, 0x1e, 0xf, 0x8e, 0xc6, 0x77, 0x1b,
    0xf, 0x83,

    /* U+0079 "y" */
    0x1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xff, 0x7f, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xd,
    0xff, 0xfd,

    /* U+007A "z" */
    0x7f, 0xbf, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18,
    0x8, 0x8, 0xc, 0x6, 0x6, 0x3, 0x3, 0x1,
    0xfc, 0xbe,

    /* U+007B "{" */
    0x1f, 0xe, 0x18, 0x18, 0x18, 0x18, 0x18, 0x68,
    0x68, 0x18, 0x18, 0x18, 0x18, 0x18, 0xe, 0x1f,

    /* U+007C "|" */
    0x7f, 0xff, 0xff, 0xfd,

    /* U+007D "}" */
    0xf8, 0x70, 0x18, 0x18, 0x18, 0x18, 0x18, 0x16,
    0x16, 0x18, 0x18, 0x18, 0x18, 0x18, 0x70, 0xf8,

    /* U+007E "~" */
    0x20, 0x18, 0x37, 0x79, 0xf0, 0x60
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 175, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 175, .box_w = 2, .box_h = 16, .ofs_x = 5, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 175, .box_w = 5, .box_h = 4, .ofs_x = 3, .ofs_y = 12},
    {.bitmap_index = 8, .adv_w = 175, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 21, .adv_w = 175, .box_w = 9, .box_h = 22, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 46, .adv_w = 175, .box_w = 11, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 175, .box_w = 10, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 90, .adv_w = 175, .box_w = 2, .box_h = 4, .ofs_x = 5, .ofs_y = 12},
    {.bitmap_index = 91, .adv_w = 175, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 175, .box_w = 6, .box_h = 16, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 175, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 123, .adv_w = 175, .box_w = 8, .box_h = 8, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 131, .adv_w = 175, .box_w = 2, .box_h = 4, .ofs_x = 5, .ofs_y = -2},
    {.bitmap_index = 132, .adv_w = 175, .box_w = 7, .box_h = 2, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 134, .adv_w = 175, .box_w = 2, .box_h = 2, .ofs_x = 5, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 175, .box_w = 2, .box_h = 16, .ofs_x = 8, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 265, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 175, .box_w = 2, .box_h = 9, .ofs_x = 5, .ofs_y = 4},
    {.bitmap_index = 322, .adv_w = 175, .box_w = 2, .box_h = 15, .ofs_x = 5, .ofs_y = -2},
    {.bitmap_index = 326, .adv_w = 175, .box_w = 6, .box_h = 9, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 333, .adv_w = 175, .box_w = 7, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 338, .adv_w = 175, .box_w = 6, .box_h = 9, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 345, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 435, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 489, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 175, .box_w = 2, .box_h = 16, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 583, .adv_w = 175, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 603, .adv_w = 175, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 692, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 710, .adv_w = 175, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 730, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 748, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 766, .adv_w = 175, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 822, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 175, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 850, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 868, .adv_w = 175, .box_w = 5, .box_h = 16, .ofs_x = 5, .ofs_y = 0},
    {.bitmap_index = 878, .adv_w = 175, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 885, .adv_w = 175, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 888, .adv_w = 175, .box_w = 4, .box_h = 4, .ofs_x = 3, .ofs_y = 12},
    {.bitmap_index = 890, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 908, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 926, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 944, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 962, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 980, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 998, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1016, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1034, .adv_w = 175, .box_w = 2, .box_h = 16, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 1038, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1056, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1074, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1092, .adv_w = 175, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1112, .adv_w = 175, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1129, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1147, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1165, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1183, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1201, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1219, .adv_w = 175, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1239, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1257, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1275, .adv_w = 175, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1295, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1313, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1331, .adv_w = 175, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1349, .adv_w = 175, .box_w = 8, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1365, .adv_w = 175, .box_w = 2, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1369, .adv_w = 175, .box_w = 8, .box_h = 16, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1385, .adv_w = 175, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 7}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
lv_font_t mono_digital_24 = {
#else
lv_font_t mono_digital_24 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 22,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if MONO_DIGITAL_24*/
