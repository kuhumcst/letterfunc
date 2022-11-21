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
#include "letterfunc.h"
#include <string.h>
#include <assert.h>

#if UNICODE_CAPABLE
#include "letter.h"

bool Turcic = false;

#if 0
bool isAlpha(int kar)
    {
/*    int ind = kar % ARRSIZE;
    if((int)Letter[ind].Unfolded == kar)
        return true;*/

/* From http://www.w3.org/TR/xml11/#NT-NameStartChar:
NameStartChar       ::=       ":" | [A-Z] | "_" | [a-z] | [#xC0-#xD6] 
        | [#xD8-#xF6] | [#xF8-#x2FF] | [#x370-#x37D] | [#x37F-#x1FFF] 
        | [#x200C-#x200D] | [#x2070-#x218F] | [#x2C00-#x2FEF] 
        | [#x3001-#xD7FF] | [#xF900-#xFDCF] | [#xFDF0-#xFFFD] 
        | [#x10000-#xEFFFF]
*/
    // 20090702
    return 'A' <= kar && kar <= 'Z'
        || 'a' <= kar && kar <= 'z'
        || 0xC0 <= kar && kar <= 0xD6
        || 0xD8 <= kar && kar <= 0xF6
        || 0xF8 <= kar && kar <= 0x2FF
        || 0x370 <= kar && kar <= 0x37D
        || 0x37F <= kar && kar <= 0x1FFF
        || 0x200C <= kar && kar <= 0x200D 
        || 0x2070 <= kar && kar <= 0x218F 
        || 0x2C00 <= kar && kar <= 0x2FEF 
        || 0x3001 <= kar && kar <= 0xD7FF 
        || 0xF900 <= kar && kar <= 0xFDCF 
        || 0xFDF0 <= kar && kar <= 0xFFFD
        || 0x10000 <= kar && kar <= 0xEFFFF;
    //return kar > 255; // Assume Unicode positions outside Latin-1 is all alphabetic
    }

bool isAlpha(int a)
    {
    static int start_i = 0;
    int i;
    if(a <= 0)
        return false;
    if((unsigned int)a < Cletters[start_i].L)
        {
        for(i=0;;++i)
            {
            if((unsigned int)a < Cletters[i].L)
                {
                start_i = --i;
                return (unsigned int)(a) <= (unsigned int)(Cletters[i].L + Cletters[i].range);
                }
            }
        }
    else
        {
        for(i=start_i+1;;++i)
            {
            if((unsigned int)a < Cletters[i].L)
                {
                start_i = --i;
                return (unsigned int)(a) <= (unsigned int)(Cletters[i].L + Cletters[i].range);
                }
            }
        }
    return false;// unreachable code
    }
#else
#if 1
bool isAlpha(int ch)
    {
    const char* mrk = gencat(ch);
    return (mrk[0] == 'L' || mrk[0] == 'M');
    }
#else
bool isAlpha(int a)
    {
    unsigned int pivot;
    unsigned int lo;
    unsigned int hi;
    lo = 0;
    pivot = 8;
    hi = lastindex; /* Range starting at lastindex does not consists of letters, so pivot must always stay less than lastindex. */
    assert(pivot < lastindex);
    if(a <= 0)
        return 0;
    while(1)
        {
        assert(pivot < hi);
        if(a < Cletters[pivot].L)
            {
            if(pivot == lo)
                return 0;
            else
                {
                hi = pivot;
                pivot = (pivot + lo) / 2;
                }
            }
        else if(a <= Cletters[pivot].L + Cletters[pivot].range)
            return 1;
        else if(pivot + 1 == hi)
            return 0;
        else
            {
            lo = pivot + 1;
            pivot = (hi + pivot) / 2;
            }

        }
    }
#endif
#endif
#if 0
static int convertLetter(int a,struct ccaseconv * T)
    {
    int i;
    if(a > 0x10FFFF)
        return a;
    for(i=0;;++i)
        {
        if((unsigned int)a < T[i].L)
            {
            if(i == 0)
                return a;
            --i;            
            if  (   /*(unsigned int)*/a <= (int)T[i].L+(int)T[i].range
                &&  (   T[i].inc < 2
                    ||  !((a - T[i].L) & 1)
                    )
                )
                {
                return a + T[i].dif;
                }
            else
                {
                break;
                }
            }
        }
    return a;
    }
#endif
bool isUpper(int kar)
    {
#if 0
    int ind = kar % ARRSIZE;
    return ((int)Letter[ind].Unfolded == kar) && Letter[ind].Unfolded == Letter[ind].Capital;
#else
    return strcmp(gencat(kar), "Ll"); // Anything but lowercase letter is OK
//    return kar == convertLetter(kar,l2u);
#endif
    }

bool isLower(int kar)
    {
#if 0
    int ind = kar % ARRSIZE;
    return ((int)Letter[ind].Unfolded == kar) && Letter[ind].Unfolded == Letter[ind].Simple;// && Letter[ind].Capital != 0;
#else
    return strcmp(gencat(kar), "Lu"); // Anything but uppercase letter is OK
//    return kar == convertLetter(kar,u2l);
#endif
    }
/*
static int toUpperUnicode(int a)
    {
    return convertLetter(a,l2u);
    }
static int toLowerUnicode(int a)
    {
    return convertLetter(a,u2l);
    }
*/


unsigned int lowerEquivalent(int kar)
    {
    if(kar == 'I' && !Turcic)
        return 'i';
    return toLowerUnicode(kar);
//    return convertLetter(kar,u2l);
/*
    int ind = kar % ARRSIZE;
    return ((int)Letter[ind].Unfolded == kar) && (Letter[ind].Simple) ? Letter[ind].Simple : kar;
*/
    }

unsigned int upperEquivalent(int kar)
    {
    if(kar == 'i' && !Turcic)
        return 'I';
    return toUpperUnicode(kar);
//    return convertLetter(kar,l2u);
/*
    int ind = kar % ARRSIZE;
    return ((int)Letter[ind].Unfolded == kar) && (Letter[ind].Capital) ? Letter[ind].Capital : kar;
*/
    }

int folded::Cinc()
    {
    if(inFull)
        {
        if(i > 2 || w[i] == 0)
            inFull = false;
        else
            return w[i++];
        }
    int kar = cinc();
    int ind = kar % ARRSIZE;
    if((int)Letter[ind].Unfolded == kar)
        {
        tri * Tri = Letter[ind].Full;
        if(  Tri 
          && (w = Tri->w)[1] /* If the second element is zero, we have
                               a Turkic form, not a fully folded form. */
          )
            {
            inFull = true;
            i = 1;
            return w[0];
            }
        return Letter[ind].Simple;
        }
    return kar;
    }

int folded::CincSimple()
    {
    if (inFull)
        {
        if (i > 2 || w[i] == 0)
            inFull = false;
        else
            return w[i++];
        }
    int kar = cinc();
    int ind = kar % ARRSIZE;
    if ((int)Letter[ind].Unfolded == kar)
        {
        return Letter[ind].Simple;
        }
    return kar;
    }

class charfolded:public folded // ISO
    {
    private:
        const char * s;
    protected:
    public:
        virtual int c()
            {
            return *s;
            }
        virtual int cinc()
            {
            return *s++;
            }
    public:
        charfolded(const char * s):s(s)
            {
            }
        virtual ~charfolded()
            {
            }
    };

class wcharfolded:public folded // UTF16
    {
    private:
        const wchar_t * s;
    protected:
    public:
        virtual int c()
            {
            return *s;
            }
        virtual int cinc()
            {
            return *s++;
            }
    public:
        wcharfolded(const wchar_t * s):s(s)
            {
            }
        virtual ~wcharfolded()
            {
            }
    };

int strCaseCmp(const wchar_t *s, const char *p)
/* s and p: case insensitive */
    {
    wcharfolded S(s);
    charfolded P(p);
    int iS,iP;
    
    for(;;)
        {
        iS = S.Cinc();
        iP = P.Cinc();
        if(iS)
            {
            if(iP)
                {
                if(iS != iP)
                    return iS - iP;
                }
            else
                return 1;
            }
        else
            {
            if(iP)
                return -1;
            else
                return 0;
            }
        }
    }

int strLeftCaseCmp(const wchar_t* s, const char* p)
/* s: case insensitive, p: case sensitive */
    {
    wcharfolded S(s);
    charfolded P(p);
    int iS, iP, IS;

    for (;;)
        {
        IS = S.c();
        iS = S.CincSimple();
        iP = P.cinc();
        if (iS)
            {
            if (iP)
                {
                if (iS != iP && IS != iP)
                    return iS - iP;
                }
            else
                return 1;
            }
        else
            {
            if (iP)
                return -1;
            else
                return 0;
            }
        }
    }

int strCmp(const wchar_t* s, const char* p)
    {
    wcharfolded S(s);
    charfolded P(p);
    int iS, iP;

    for (;;)
        {
        iS = S.cinc();
        iP = P.cinc();
        if (iS)
            {
            if (iP)
                {
                if (iS != iP)
                    return iS - iP;
                }
            else
                return 1;
            }
        else
            {
            if (iP)
                return -1;
            else
                return 0;
            }
        }
    }

#endif
