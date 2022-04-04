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
#ifndef LETTERFUNC_H
#define LETTERFUNC_H

#define UNICODE_CAPABLE 1

#if UNICODE_CAPABLE

extern bool Turcic; // if true, upperEquivalent('i') = 'İ' and lowerEquivalent('I') = 'ı'

class folded
    {
    private:
        unsigned int * w;
        int i;
        bool inFull;
    protected:
        virtual int c() = 0;
        virtual int cinc() = 0;
    public:
        folded():w(0),i(-1),inFull(false){}
        virtual ~folded(){}
        int Cinc(); // full case folding of w
        int CincSimple();
    };


bool isAlpha(int kar);
bool isUpper(int kar); // True for any character that isn't lowercase
bool isLower(int kar); // True for any character that isn't uppercase
/*
   Non-letters such as numbers are both lower- and uppercase!
   To positively check that a character c is uppercase and not lowercase,
   use !isLower(c). Vice versa for lowercase.
 */
unsigned int lowerEquivalent(int kar);
unsigned int upperEquivalent(int kar);
//bool isAllUpper(const char * s,int len);
int strCaseCmp(const wchar_t *s, const char *p);
int strLeftCaseCmp(const wchar_t* s, const char* p);
int strCmp(const wchar_t* s, const char* p);
//int strCaseCmp(const char *s, const char *p);
//int UTF8char(const char * s,bool & UTF8); 
    // Sets UTF8 to false if s isn't UTF8
    // returns character (starting at) s
//int getUTF8char(const char *& s,bool & UTF8); 
    // Same as UTF8char, but also increments s!
//const char * Inc(const char *& s);
#endif

#endif
