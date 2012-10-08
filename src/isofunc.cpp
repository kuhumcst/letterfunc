/*
LETTERFUNC - Unicode functions: I/O, string comparison, change casing

Copyright (C) 2012  Center for Sprogteknologi, University of Copenhagen

This file is part of CST's Language Technology Tools.

LETTERFUNC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

LETTERFUNC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LETTERFUNC; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include "isofunc.h"
#include <string.h>

static const unsigned char upperEquivalent_ISO8859_1[256] =
    {
    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  /*   0 -  15 */ /* 00 - 0F */
    16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  /*  16 -  31 */ /* 10 - 1F */
    ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', /*  31 -  47 */ /* 20 - 2F */
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',  /*  48 -  63 */ /* 30 - 3F */

    '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',  /*  64 -  79 */ /* 40 - 4F */
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', /*  80 -  95 */ /* 50 - 5F */
    '`', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',  /*  96 - 111 */ /* 60 - 6F */
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '{', '|', '}', '~', 127,  /* 112 - 127 */ /* 70 - 7F */

    128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,  /* 128 - 143 */ /* 80 - 8F */
    144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 138, 155, 140, 157, 142, 159,  /* 144 - 159 */ /* 90 - 9F */
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,  /* 160 - 175 */ /* A0 - AF */
    176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,  /* 176 - 191 */ /* B0 - BF */

    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,  /* 192 - 207 */ /* C0 - CF */
    208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,  /* 208 - 223 */ /* D0 - DF */
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,  /* 224 - 239 */ /* E0 - EF */
    208, 209, 210, 211, 212, 213, 214, 247, 216, 217, 218, 219, 220, 221, 222, 159   /* 240 - 255 */ /* F0 - FF */
    };

const unsigned char * UpperEquivalentISO = upperEquivalent_ISO8859_1;

void AllToUpperISO(char * s)
    {
    if(UpperEquivalentISO)
        {
        while(*s)
            {
            *s = (char)UpperEquivalentISO[*s & 0xFF];
            ++s;
            }
        }
    }

void toUpperISO(char * s)
    {
    if(UpperEquivalentISO)
        *s = (char)UpperEquivalentISO[*s & 0xFF];
    }

bool isAllUpperISO(const char * s,size_t len)
    {
    if(!UpperEquivalentISO)
        return false;
    else
        {
        if(len > 0)
            {
            while(*s && len-- > 0)
                {
                int S = *s & 0xFF;
                if(UpperEquivalentISO[S] != S)
                    return false;
                ++s;
                }
            }
        else
            {
            while(*s)
                {
                int S = *s & 0xFF;
                if(UpperEquivalentISO[S] != S)
                    return false;
                ++s;
                }
            }
        return true;
        }
    }

