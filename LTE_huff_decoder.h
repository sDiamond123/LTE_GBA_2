#include "LTE_glyphs.h"

#ifndef HUFF_SIZE
#define HUFF_SIZE   127 // size of a huffman tree
#define HUFF_ROOT   HUFF_SIZE - 1

//huffman tree
extern const unsigned char HUFF_TREE[HUFF_SIZE];

struct huff_branch{
    char left;
    char right;
    char parent;
};
#endif

struct huff_branch * make_huff_tree();
