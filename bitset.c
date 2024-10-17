#include "bitset.h"
#ifdef __cplusplus
extern "C"
{
#endif
    struct BitSet
    {
        uint8_t *bits;
        /* length in bits */
        size_t bit_len;
    };

    bitset_forced_inline size_t linear_index(size_t num_dims, const size_t *dims, const size_t *indices)
    {
        size_t index = 0;
        size_t multiplier = 1;
        for (size_t i = num_dims; i-- > 0;)
        {
            index += indices[i] * multiplier;
            multiplier *= dims[i];
        }
        return index;
    }

    bitset_forced_inline void inverse_linear_index(size_t num_dims, const size_t *dims, size_t index, size_t *indices)
    {
        for (size_t i = 0; i < num_dims; ++i)
        {
            size_t dim_index = num_dims - 1 - i;
            indices[dim_index] = index % dims[dim_index];
            index /= dims[dim_index];
        }
    }

    bitset_forced_inline size_t BitSet_get_byte_len(const BitSet *bs)
    {
        BITSET_ASSERT(bs, "BitSet_get_byte_len: BitSet is NULL");
        return (bs->bit_len + 7) / 8;
    }

    bitset_forced_inline void BitSet_init(BitSet *bs, size_t bit_len)
    {
        BITSET_ASSERT(bs, "BitSet_init: BitSet is NULL");
        bs->bit_len = bit_len;
        bs->bits = (uint8_t *)calloc(BitSet_get_byte_len(bs), sizeof(uint8_t));
        BITSET_ASSERT(bs->bits != NULL, "BitSet_init: Memory allocation failed");
    }

    bitset_forced_inline void BitSet_set_all(BitSet *bs)
    {
        BITSET_ASSERT(bs, "BitSet_set_all: BitSet is NULL");
        size_t byte_len = BitSet_get_byte_len(bs);
        for (size_t i = 0; i < byte_len; i++)
        {
            bs->bits[i] = 0xFF;
        }
    }

    bitset_forced_inline void BitSet_clear_all(BitSet *bs)
    {
        BITSET_ASSERT(bs, "BitSet_clear_all: BitSet is NULL");
        size_t byte_len = BitSet_get_byte_len(bs);
        for (size_t i = 0; i < byte_len; i++)
        {
            bs->bits[i] = 0;
        }
    }

    bitset_forced_inline void BitSet_set(BitSet *bs, size_t index)
    {
        BITSET_ASSERT(bs, "BitSet_set: BitSet is NULL");
        BITSET_ASSERT(index < bs->bit_len, "BitSet_set: Index out of bounds");
        bs->bits[index / 8] |= 1 << (index % 8);
    }

    bitset_forced_inline void BitSet_clear(BitSet *bs, size_t index)
    {
        BITSET_ASSERT(bs, "BitSet_clear: BitSet is NULL");
        BITSET_ASSERT(index < bs->bit_len, "BitSet_clear: Index out of bounds");
        bs->bits[index / 8] &= ~(1 << (index % 8));
    }

    bitset_forced_inline unsigned int BitSet_get(const BitSet *bs, size_t index)
    {
        BITSET_ASSERT(bs, "BitSet_get: BitSet is NULL");
        BITSET_ASSERT(index < bs->bit_len, "BitSet_get: Index out of bounds");
        return (bs->bits[index / 8] >> (index % 8)) & 1;
    }

    bitset_forced_inline void BitSet_flip(BitSet *bs, size_t index)
    {
        BITSET_ASSERT(bs, "BitSet_flip: BitSet is NULL");
        BITSET_ASSERT(index < bs->bit_len, "BitSet_flip: Index out of bounds");
        bs->bits[index / 8] ^= 1 << (index % 8);
    }

    bitset_forced_inline void BitSet_free(BitSet *bs)
    {
        BITSET_ASSERT(bs, "BitSet_free: BitSet is NULL");
        free(bs->bits);
        bs->bits = NULL;
        bs->bit_len = 0;
    }

    bitset_forced_inline void BitSet_copy_construct(BitSet *dest, const BitSet *src)
    {
        BITSET_ASSERT(dest && src, "BitSet_copy_construct: BitSet is NULL");
        /*
        Expecting dest to be uninitialized
        if (dest->bits != NULL)
        {
            free(dest->bits);
        }
        */
        size_t byte_len = BitSet_get_byte_len(src);
        dest->bits = (uint8_t *)malloc(byte_len * sizeof(uint8_t));
        BITSET_ASSERT(dest->bits != NULL, "BitSet_copy_construct: Memory allocation failed");
        dest->bit_len = src->bit_len;
        for (size_t i = 0; i < byte_len; i++)
        {
            dest->bits[i] = src->bits[i];
        }
    }

    bitset_forced_inline void BitSet_or(BitSet *dest, const BitSet *src)
    {
        BITSET_ASSERT(dest && src, "BitSet_or: BitSet is NULL");
        size_t byte_len = BitSet_get_byte_len(dest->bit_len < src->bit_len ? dest : src);
        for (size_t i = 0; i < byte_len; i++)
        {
            dest->bits[i] |= src->bits[i];
        }
    }

    bitset_forced_inline void BitSet_and(BitSet *dest, const BitSet *src)
    {
        BITSET_ASSERT(dest && src, "BitSet_and: BitSet is NULL");
        size_t byte_len = BitSet_get_byte_len(dest->bit_len < src->bit_len ? dest : src);
        for (size_t i = 0; i < byte_len; i++)
        {
            dest->bits[i] &= src->bits[i];
        }
    }

    bitset_forced_inline void BitSet_xor(BitSet *dest, const BitSet *src)
    {
        BITSET_ASSERT(dest && src, "BitSet_xor: BitSet is NULL");
        size_t byte_len = BitSet_get_byte_len(dest->bit_len < src->bit_len ? dest : src);
        for (size_t i = 0; i < byte_len; i++)
        {
            dest->bits[i] ^= src->bits[i];
        }
    }

    bitset_forced_inline void BitSet_not(BitSet *bs)
    {
        BITSET_ASSERT(bs, "BitSet_not: BitSet is NULL");
        size_t byte_len = BitSet_get_byte_len(bs);
        for (size_t i = 0; i < byte_len; i++)
        {
            bs->bits[i] = ~bs->bits[i];
        }
    }

    bitset_forced_inline int BitSet_equals(const BitSet *bs1, const BitSet *bs2)
    {
        BITSET_ASSERT(bs1 && bs2, "BitSet_equals: BitSet is NULL");
        if (bs1->bit_len != bs2->bit_len)
        {
            return 0;
        }
        size_t byte_len = BitSet_get_byte_len(bs1);
        for (size_t i = 0; i < byte_len; i++)
        {
            if (bs1->bits[i] != bs2->bits[i])
            {
                return 0;
            }
        }
        return 1;
    }

    bitset_forced_inline void BitSet_print(const BitSet *bs, int newline)
    {
        BITSET_ASSERT(bs, "BitSet_print: BitSet is NULL");
        for (size_t i = 0; i < bs->bit_len; i++)
        {
            printf("%d", BitSet_get(bs, i));
            if ((i + 1) % newline == 0)
            {
                printf("\n");
            }
        }
        printf("\n");
    }
#ifdef __cplusplus
}
#endif