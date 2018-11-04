///\file scalarMult.c
///\brief Function intMult is used to multiply the matrix with an integer
///Created by Preda Iulian
#include "functions.h"

///\fn void intMult(int len, int mat[1001000][3], int fact)
///\brief multiply the matrix with an integer
///\param mat represents the matrix
///\param it is an iterator
void intMult(int len, int mat[1001000][3], int fact){
    ///the only thing we need to do here is to multiply the value of the
    ///current element by fact
    int it;
    for( it = 1; it <= len; it ++){
        mat[it][2] *= fact;
    }
}
