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
#ifndef UTF8_H
#define UTF8_H

#include "letterfunc.h"
#include <stddef.h>
#if UNICODE_CAPABLE
bool isAllUpper(const char * s,size_t len);
bool isUpperUTF8(const char * s);
//int UnicodeToUtf8(int w,char * s,int len);
int UnicodeToUtf8(unsigned int w,char * s,size_t len);
int Utf8ToUnicode(int * w,const char * s,size_t len);
void AllToUpper(char * s);
const char * allToLowerUTF8(const char * s);
// Simple case folding, used for simple "case insensitive" comparison.
// Allocates enough memory to hold the returned value.
// This memory is deallocated the next time allToLowerUTF8 is called, so
// do not delete!
//void AllToLowerUTF8(char * s);
// Simple case folding, used for simple "case insensitive" comparison.
// Overwrites s!
//void NToLowerUTF8(char * s,const char * stop);
// Like AllToLowerUTF8. Last converted character is the last character
// starting before stop. Zero byte is written after last converted character.
// Overwrites s!


const char * changeCase(const char * s,bool low,size_t & length);
// The returned value must be copied to its destination before the next call
// to changeCase. 'length' is the number of bytes before the final '\0' in the
// returned value. On entry, if length is set to a positive number, case is
// only converted for the first 'length' bytes; the remaining bytes are
// skipped.

const char* CapitalizeAndLowercase(const char* s);
// Capitalizes first character and lowercases the rest.
// The returned value must be copied to its destination before the next call
// to CapitalizeAndLowercase. 

const char * adaptCase(const char * ll, const char * rr, size_t & length);
// Adapt the casing of ll to the casing of rr, starting from the first
// character in ll and rr, continuing for as long as the current character in
// ll is equal to the current character of rr, when converted to the same case.
// The returned value must be copied to its destination before the next call
// to adaptCase. 'length' is the number of bytes before the final '\0' in the
// returned value. On entry, if length is set to a positive number, case is
// only converted for the first 'length' bytes; the remaining bytes are
// skipped.
int strCaseCmp(const char *s, const char *p);
int strCaseCmpN(const char *s, const char *p,ptrdiff_t & is,ptrdiff_t & ip);
//Like strCaseCmp. Returns indices into s and p where s and/or p ended or where they became dissimilar.
int strCmpN(const char *s, const char *p,ptrdiff_t & is,ptrdiff_t & ip);
//Like strCaseCmp, but case-sensitive. Returns indices into s and p where s and/or p ended or where they became dissimilar.
int UTF8char(const char * s,bool & UTF8); 
    // Sets UTF8 to false if s isn't UTF8
    // returns character (starting at) s
int getUTF8char(const char *& s,bool & UTF8); 
    // Same as UTF8char, but also post-increments s!
//const char * Inc(const char *& s);
//size_t Inc(const char * s);
int copyUTF8char(const char * source,char * dest);
    // Copies one character from source to destination.
    // Returns number of bytes copied. (max 6)
    // Makes no check of validity of UTF-8!
size_t skipUTF8char(const char * s);
    // Makes no check of validity of UTF-8!
extern bool globUTF8;
#endif

#endif
