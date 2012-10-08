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

#ifndef ISOFUNC_H
#define ISOFUNC_H

#include <stddef.h> // gcc size_t
#include "letterfunc.h"

// ISO-8859-1 (Latin1) functions for handling upper/lower case 

extern const unsigned char * UpperEquivalentISO;

#define isUpperISO(s) (UpperEquivalentISO[(int)(*s & 0xFF)] == (int)(*s & 0xFF))

void toUpperISO(char * s);
bool isAllUpperISO(const char * s,size_t len);
void AllToUpperISO(char * s);


#endif
