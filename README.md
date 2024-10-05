# `huff`

A tool to compress and uncompress text files.
This tool is my implementation of the huffman tree data structure dedicated to compress files.

# Installation

1. Clone the reposotiry

```sh
git clone https://github.com/omardoescode/Huffman-Compression.git
cd Huffman-Compression
```

2. Build the project

```sh
make # or make all clean
```

# Usage

```sh
./huff <text_file_to_compress> -c <output_file>

./huff <compressed> -u <uncompressed_file_output>
```

# Implementaion

This tool uses **bit packing** as the main compression algorithm.
First we start be generating codes that correspond each unique symbol in the text file. These codes will be replaced later in the compressed file. These codes will be packed and written to the compressed file.

## Huffman tree

To ensure minimum size, we have to assign the shortest codes to the elements with higher frequences. To solve this problem, We use huffman tree.

More info regarding huffman trees is to be found [here](https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/Huffman.html)

Now, we need to store this tree in the header. To do this in minimum storage, Serialiazation is used. The method used is not standard, but rather developed by me, even if it looks like some of others.

## Tree serialization

To serialize the tree:

    0 is placed for internal nodes.
    1 is placed for leaves, followed by the information about the element stored in the leaf.
    We store the number of bytes used for the element, denoted as C. The maximum value of C is log2(sizeof(wchar_t)).
    This maximum value is also saved in the compressed file header to accommodate any potential differences in size_t for wchar_t across machines.
    Following this, C bytes that correspond to the leaf element are stored.

## Bit packing

After serialization, The **bit packing** packing algorithm is used to pack the codes generated earlier into the compressed file. More is to be found [here](https://kinematicsoup.com/news/2016/9/6/data-compression-bit-packing-101)

## Library interpositioning

This is a technique that involves intercepting the calls to library functions and replacing them with others. This usually means adding a wrapper around that library function and print information for debugging. This technique is used for debugging compresstion and uncompression bit by bit.

# Notes

This tool works well only large text files and might actually maginfy the file if the text file is so small
