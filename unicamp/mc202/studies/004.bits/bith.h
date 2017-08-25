#ifndef __BITH_H__
#define __BITH_H__

#include <limits.h>

#define BIT_NBSLOTS(X) ( ( X / CHAR_MAX ) + 1 )
#define BIT_BSLOT(X)   ( X / CHAR_MAX )
#define BIT_SLOT(X)    ( X % CHAR_MAX + 1 )
#define BIT_MASK(X)    ( 1 << ( X % CHAR_MAX ) )

#define PRINT_BSLOT(A,X) ( printf("0x%x\n",A[BIT_BSLOT(X)]) )
#define BIT_SET(A,X)     ( A[BIT_BSLOT(X)] |= BIT_MASK(X) )
#define BIT_CLEAR(A,X)   ( A[BIT_BSLOT(X)] &= ~BIT_MASK(X) )
#define BIT_TEST(A,X)    ( A[BIT_BSLOT(X)] & BIT_MASK(X) )

#endif
