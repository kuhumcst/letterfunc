/*
LETTERFUNC - Unicode support

Copyright (C) 2012  Center for Sprogteknologi, University of Copenhagen

This file is part of LETTERFUNC.

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
#ifndef LETTER_H
#define LETTER_H

#if 1
#include "casefolding.h"

#else
#define ARRSIZE 12311

/*
Based on CaseFolding-15.0.0.txt

Structures created with CaseFolding.bra
*/
struct tri { unsigned int w[3]; };
struct quat { unsigned int Unfolded; unsigned int Simple; unsigned int Capital; struct tri* Full; };
extern struct quat Letter[ARRSIZE];
#endif

#if 1
#include "unicaseconv.h"
#else
/*
Based on UnicodeData.txt (2022-08-03 17:00)
(Does not convert final sigma to non-final sigma)

Structures created with CaseFolding.bra
*/
struct ccaseconv { unsigned int L : 21; int range : 11; unsigned int inc : 2; int dif : 20; };
extern struct ccaseconv l2u[];
extern struct ccaseconv u2l[];
#endif

#if 1
#include "unichartypes.h"
#else
extern unsigned int lastindex;
struct cletter { unsigned int L : 21; unsigned int range : 11; };
extern struct cletter Cletters[];
#endif
#endif
