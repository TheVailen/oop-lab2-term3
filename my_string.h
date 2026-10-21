#pragma once

#include <cstddef>
#include <iostream>

class String {
private:
    char* data_;
    size_t size_;
    size_t capacity_;

public:
    String();
    String(const char* str);
    ~String();
    String(const String& other);
    String(String&& other) noexcept;
    String& operator=(String other);

    void swap(String& other) noexcept;

    void push_back(char c);
    void append(const String& other);
    
    size_t size() const;
    size_t capacity() const;
    const char* c_str() const;

    bool operator==(const String& other) const;

    String rle_compress() const;
    void rle_decompress();
};

std::ostream& operator<<(std::ostream& os, const String& str);