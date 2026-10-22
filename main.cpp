#include <iostream>
#include "my_string.h"

int main() {
    String s("AAABCC");
    std::cout << "Исходная строка: " << s << std::endl;

    String compressed = s.rle_compress();
    std::cout << "После rle_compress(): " << compressed << std::endl;

    compressed.rle_decompress();
    std::cout << "После rle_decompress(): " << compressed << std::endl;

    return 0;
}
