/**
 * @file main.c
 * @author Adam Naghavi
 * @brief Test the bitset implementation.
 * @version 0.1
 * @date 2024-06-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#define BITSET_IMPLEMENTATION
#include "bitset.h"
#include <stdlib.h>
#include <stdio.h>


int main(void)
{
    BitSet bs;
    BitSet_init(&bs, 100);
    srand(0);
    // for (size_t i = 0; i < 100; i++)
    // {
    //     if (rand() % 2)
    //     {
    //         BitSet_set(&bs, i);
    //     }
    // }
    size_t dims[] = {2,2};
    size_t num_dims = sizeof(dims) / sizeof(dims[0]);
    size_t vec[] = {1,1};
    BitSet_set(&bs, linear_index(num_dims,dims,vec));
    BitSet_print(&bs,10);
    putc('\n', stdout);
    BitSet bs2;
    BitSet_copy_construct(&bs2, &bs);
    BitSet_print(&bs2,10);

    BitSet_free(&bs);
    BitSet_free(&bs2);

    return 0;
}