/**
 * @file bitset.h
 * @author Adam Naghavi (adamnaghavif@gmail.com)
 * @brief A simple bitset implementation in C.
 * @version 0.1
 * @date 2024-06-03
 *
 * @copyright Copyright (c) 2024
 *
 * @warning Do not forget to define BITSET_IMPLEMENTATION before including this header.
 *
 * @note In debug mode, the library will check for NULL pointers and out of bounds indices.
 *
 */

#ifdef __cplusplus
#pragma once
extern "C"
{
#endif

#ifndef BITSET_H
#define BITSET_H

#ifdef __GNUC__
#define bitset_forced_inline __attribute__((always_inline)) static inline
#elif defined(_MSC_VER)
#define bitset_forced_inline __forceinline static
#elif defined(__INTEL_COMPILER)
#define bitset_forced_inline inline __attribute__((always_inline)) static
#else
#define bitset_forced_inline inline static
#endif

#if defined(_DEBUG) || !defined(NDEBUG) || !defined(__OPTIMIZE__)
#define BITSET_DEBUG_MODE 1
#if defined(SIGTRAP)
#define BITSET_DEBUG_BREAK() raise(SIGTRAP)
#else
#define BITSET_DEBUG_BREAK() raise(SIGABRT)
#endif
#else
#define BITSET_DEBUG_MODE 0
#define BITSET_DEBUG_BREAK() ((void)0)
#endif

#include <signal.h>

#if BITSET_DEBUG_MODE
#define BITSET_ASSERT(cond, msg)                         \
    if (!(cond))                                         \
    {                                                    \
        fprintf(stderr, "Validation failed: %s\n", msg); \
        BITSET_DEBUG_BREAK();                            \
    }
#else
#define BITSET_ASSERT(cond, msg) 
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

    /* Declarations */

    /**
     * @brief  Dont forget to define BITSET_IMPLEMENTATION before including this header.
     * 
     */
    typedef struct BitSet BitSet;

    /**
     * @brief Allows for accessing flat arrays as if they were higher dimensional arrays.
     *   Example:
     *   size_t index = linear_index({2, 2}, 2, {1, 1});\n
     *
     * @param num_dims Number of dimensions.
     * @param dims Array of length "num_dims" that contains the dimensions.
     * @param indices Array/vector length of "num_dims" that contains the indices.
     * @return size_t Linear index.
     */
    bitset_forced_inline size_t linear_index(size_t num_dims, const size_t *dims, const size_t *indices);

    /**
     * @brief Returns a vector "indicies" that is the length of "num_dims"
     *
     * @param num_dims Number of dimensions.
     * @param dims Array of length "num_dims" that contains the dimensions.
     * @param index Index to convert to a vector.
     * @param indices Blank array of length "num_dims" to store the result vector.
     * @return Check indices for the result.
     */
    bitset_forced_inline void inverse_linear_index(size_t num_dims, const size_t *dims, size_t index, size_t *indices);

    /**
     * @brief Calculates the number of bytes needed to store the BitSet.
     *
     * @param bs Pointer to BitSet, cannot be NULL.
     * @return void
     *
     * @note Ensure that the BitSet has been properly initialized before calling this function.
     */
    bitset_forced_inline size_t BitSet_get_byte_len(const BitSet *bs);

    /**
     * @brief Do not forget to use BitSet_free.
     *
     * @param bs Pointer to BitSet, cannot be NULL.
     * @param bit_len Number of bits in the BitSet.
     * @return void
     *
     * @note Ensure that BITSET_IMPLEMENTATION is defined before including this header.
     */
    bitset_forced_inline void BitSet_init(BitSet *bs, size_t bit_len);

    /**
     * @brief Free the memory allocated by BitSet_init
     *
     * @param bs Pointer to BitSet, cannot be NULL.
     * @return void
     *
     * @note Ensure that the BitSet has been properly initialized before calling this function.
     */
    bitset_forced_inline void BitSet_free(BitSet *bs);

    /**
     * @brief Copy the contents of "src" to "dest". "Dest" should be uninitialized.
     *
     * @param dest Pointer to uninitialized BitSet, cannot be NULL.
     * @param src Pointer to BitSet, cannot be NULL.
     * @return void
     *
     * @note Ensure that the BitSet has been properly initialized before calling this function.
     */
    bitset_forced_inline void BitSet_copy_construct(BitSet *dest, const BitSet *src);

    /**
     * @brief Sets all bits to 1.
     *
     * @param bs Pointer to BitSet, cannot be NULL.
     * @return void
     *
     * @note Ensure that the BitSet has been properly initialized before calling this function.
     */
    bitset_forced_inline void BitSet_set_all(BitSet *bs);

    /**
     * @brief Sets all bits to 0.
     *
     * @param bs Pointer to BitSet, cannot be NULL.
     * @return void
     *
     * @note Ensure that the BitSet has been properly initialized before calling this function.
     */
    bitset_forced_inline void BitSet_clear_all(BitSet *bs);

    /**
     * @brief Sets bit at "index" to 1.
     *
     * @param bs Pointer to BitSet, cannot be NULL.
     * @param index Bit index.
     * @return void
     *
     * @note Ensure that the BitSet has been properly initialized before calling this function.
     */
    bitset_forced_inline void BitSet_set(BitSet *bs, size_t index);

    /**
     * @brief Sets bit at "index" to 0.
     *
     * @param bs
     * @param index
     * @return void
     *
     * @note Ensure that the BitSet has been properly initialized before calling this function.
     */
    bitset_forced_inline void BitSet_clear(BitSet *bs, size_t index);

    /* returns the value of the bit at "index" */
    /**
     * @brief Get the value of the bit at "index".
     *
     * @param bs Pointer to BitSet, cannot be NULL.
     * @param index Bit index.
     * @return 1 or 0.
     *
     * @note Ensure that the BitSet has been properly initialized before calling this function.
     */
    bitset_forced_inline unsigned int BitSet_get(const BitSet *bs, size_t index);

    /**
     * @brief Flip the value of a specific bit in a BitSet.
     *
     * This function inverts the value of the bit at the specified index in the BitSet.
     * If the bit is 0, it will be set to 1, and if it is 1, it will be set to 0.
     *
     * @param bs Pointer to the BitSet.
     * @param index Index of the bit to flip.
     *
     * @details The function checks if the BitSet pointer is valid and the index is within bounds.
     * Flipping a bit is performed using the XOR operation.
     *
     * @note Ensure that the BitSet has been properly initialized before calling this function.
     *
     * @warning The function does not handle cases where the index is out of bounds.
     */
    bitset_forced_inline void BitSet_flip(BitSet *bs, size_t index);

    /**
     * @brief Perform a bitwise OR operation between two BitSets.
     *
     * This function performs a bitwise OR operation between the destination BitSet and the source BitSet.
     * The result is stored in the destination BitSet.
     *
     * @param dest Pointer to the destination BitSet.
     * @param src Pointer to the source BitSet.
     *
     * @details The function assumes that both BitSets have been properly initialized and have the same bit length.
     * The bitwise OR operation is performed byte by byte.
     *
     * @note Ensure that both BitSets have the same length for meaningful results.
     *
     * @warning The function will use the length of the smaller BitSet if the BitSets have different lengths.
     */
    bitset_forced_inline void BitSet_or(BitSet *dest, const BitSet *src);

    /**
     * @brief Perform a bitwise AND operation between two BitSets.
     *
     * This function performs a bitwise AND operation between the destination BitSet and the source BitSet.
     * The result is stored in the destination BitSet.
     *
     * @param dest Pointer to the destination BitSet.
     * @param src Pointer to the source BitSet.
     *
     * @details The function assumes that both BitSets have been properly initialized and have the same bit length.
     * The bitwise AND operation is performed byte by byte.
     *
     * @note Ensure that both BitSets have the same length for meaningful results.
     *
     * @warning The function will use the length of the smaller BitSet if the BitSets have different lengths.
     */
    bitset_forced_inline void BitSet_and(BitSet *dest, const BitSet *src);

    /**
     * @brief Perform a bitwise XOR operation between two BitSets.
     *
     * This function performs a bitwise XOR operation between the destination BitSet and the source BitSet.
     * The result is stored in the destination BitSet.
     *
     * @param dest Pointer to the destination BitSet.
     * @param src Pointer to the source BitSet.
     *
     * @details The function assumes that both BitSets have been properly initialized and have the same bit length.
     * The bitwise XOR operation is performed byte by byte.
     *
     * @note Ensure that both BitSets have the same length for meaningful results.
     *
     * @warning The function will use the length of the smaller BitSet if the BitSets have different lengths.
     */
    bitset_forced_inline void BitSet_xor(BitSet *dest, const BitSet *src);

    /**
     * @brief Perform a bitwise NOT operation on a BitSet.
     *
     * This function inverts all bits in the BitSet. Each bit is flipped from 0 to 1 or from 1 to 0.
     *
     * @param bs Pointer to the BitSet.
     *
     * @details The function assumes that the BitSet has been properly initialized.
     * The bitwise NOT operation is performed byte by byte.
     *
     * @note Ensure that the BitSet has been properly initialized before calling this function.
     *
     * @warning The function will use the length of the smaller BitSet if the BitSets have different lengths.
     */
    bitset_forced_inline void BitSet_not(BitSet *bs);

    /**
     * @brief Check if two BitSets are equal.
     *
     * This function compares two BitSets and returns 1 if they are equal, and 0 otherwise.
     *
     * @param bs1 Pointer to the first BitSet.
     * @param bs2 Pointer to the second BitSet.
     *
     * @return 1 if the BitSets are equal, 0 otherwise.
     *
     * @details The function checks if both BitSets have the same length and compares their bits byte by byte.
     *
     * @note Ensure that both BitSets have been properly initialized before calling this function.
     *
     * @warning The function will use the length of the smaller BitSet if the BitSets have different lengths.
     */
    bitset_forced_inline int BitSet_equals(const BitSet *bs1, const BitSet *bs2);

    /**
     * @brief Print the BitSet.
     *
     * This function prints the BitSet to the standard output.
     *
     * @param bs Pointer to the BitSet.
     * @param newline Number of bits to print per line.
     *
     * @details The function prints each bit in the BitSet. After printing the specified number of bits,
     * it prints a newline character.
     *
     * @note Ensure that the BitSet has been properly initialized before calling this function.
     */
    bitset_forced_inline void BitSet_print(const BitSet *bs, int newline);

    /*  Implementation */

#ifdef BITSET_IMPLEMENTATION

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

    #undef bitset_forced_inline

#endif /* BITSET_IMPLEMENTATION */

#if defined(BITSET_CPP_WRAPPER) && defined(__cplusplus) && defined(BITSET_IMPLEMENTATION)

    struct BitSetWrapper
    {
        BitSet bs;
        BitSetWrapper() = delete;
        BitSetWrapper(size_t bit_len)
        {
            BitSet_init(&bs, bit_len);
        }
        ~BitSetWrapper()
        {
            BitSet_free(&bs);
        }
        BitSetWrapper(const BitSetWrapper &other)
        {
            BitSet_copy_construct(&bs, &other.bs);
        }
        BitSetWrapper &operator=(const BitSetWrapper &other)
        {
            BitSet_copy_construct(&bs, &other.bs);
            return *this;
        }
        void set(size_t index)
        {
            BitSet_set(&bs, index);
        }
        void clear(size_t index)
        {
            BitSet_clear(&bs, index);
        }
        unsigned int get(size_t index)
        {
            return BitSet_get(&bs, index);
        }
        void flip(size_t index)
        {
            BitSet_flip(&bs, index);
        }
        void set_all()
        {
            BitSet_set_all(&bs);
        }
        void clear_all()
        {
            BitSet_clear_all(&bs);
        }
        void or_op(const BitSetWrapper &other)
        {
            BitSet_or(&bs, &other.bs);
        }
        void and_op(const BitSetWrapper &other)
        {
            BitSet_and(&bs, &other.bs);
        }
        void xor_op(const BitSetWrapper &other)
        {
            BitSet_xor(&bs, &other.bs);
        }
        void not_op()
        {
            BitSet_not(&bs);
        }
        int equals(const BitSetWrapper &other)
        {
            return BitSet_equals(&bs, &other.bs);
        }
        void print(int newline)
        {
            BitSet_print(&bs, newline);
        }
    };

#endif /* BITSET_CPP_WRAPPER */

#endif /* BITSET_H */

#ifdef __cplusplus
} /* extern "C" */
#endif
