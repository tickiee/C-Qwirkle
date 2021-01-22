
#ifndef ASSIGN1_TILECODES_H
#define ASSIGN1_TILECODES_H

// Colours
#define RED    'R'
#define ORANGE 'O'
#define YELLOW 'Y'
#define GREEN  'G'
#define BLUE   'B'
#define PURPLE 'P'

/* Colour codes to colour any text */
#define NORCOLOUR  "\x1B[0m"
#define REDCOLOUR  "\x1B[38;5;160m"
#define ORANGECOLOUR  "\x1B[38;5;202m"
#define YELLOWCOLOUR  "\x1B[38;5;214m"
#define GREENCOLOUR  "\x1B[38;5;112m"
#define BLUECOLOUR  "\x1B[38;5;105m"
#define PURPLECOLOUR  "\x1B[38;5;165m"

#define F_RED(x) (REDCOLOUR + x + NORCOLOUR)
#define F_ORANGE(x) (ORANGECOLOUR + x + NORCOLOUR)
#define F_YELLOW(x) (YELLOWCOLOUR + x + NORCOLOUR)
#define F_GREEN(x) (GREENCOLOUR + x + NORCOLOUR)
#define F_BLUE(x) (BLUECOLOUR + x + NORCOLOUR)
#define F_PURPLE(x) (PURPLECOLOUR + x + NORCOLOUR)

// Shapes
#define CIRCLE    1
#define STAR_4    2
#define DIAMOND   3
#define SQUARE    4
#define STAR_6    5
#define CLOVER    6

// Array Size
#define ARRAYSIZE 6

#endif // ASSIGN1_TILECODES_H
