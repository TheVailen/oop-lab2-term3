#include "my_string.h"
#include <cstdio>

String::String() {
    size_ = 0;
    capacity_ = 1;
    data_ = new char[capacity_ + 1];
    data_[0] = '\0';
}

String::String(const char* str) {
    size_ = 0;
    capacity_ = 1;
    data_ = nullptr;

    if (str == nullptr) {
        data_ = new char[capacity_ + 1];
        data_[0] = '\0';
        return;
    }

    while (str[size_] != '\0') {
        size_++;
    }

    if (size_ > 0) {
        capacity_ = size_;
    } else {
        capacity_ = 1;
    }

    data_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = str[i];
    }
    data_[size_] = '\0';
}

String::~String() {
    delete[] data_;
}

String::String(const String& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new char[capacity_ + 1];
    
    for (size_t i = 0; i <= size_; ++i) {
        data_[i] = other.data_[i];
    }
}

String::String(String&& other) noexcept {
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

void String::swap(String& other) noexcept {
    char* tmp_data = data_; 
    data_ = other.data_; 
    other.data_ = tmp_data;
    
    size_t tmp_size = size_; 
    size_ = other.size_; 
    other.size_ = tmp_size;
    
    size_t tmp_cap = capacity_; 
    capacity_ = other.capacity_; 
    other.capacity_ = tmp_cap;
}

String& String::operator=(String other) {
    this->swap(other);
    return *this;
}

void String::push_back(char c) {
    if (size_ == capacity_) {
        size_t new_capacity;
        if (capacity_ == 0) {
            new_capacity = 1;
        } else {
            new_capacity = capacity_ * 2;
        }
        
        char* new_data = new char[new_capacity + 1];
        
        if (data_ != nullptr) {
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
        }
        
        data_ = new_data;
        capacity_ = new_capacity;
    }
    data_[size_] = c;
    size_++;
    data_[size_] = '\0';
}

void String::append(const String& other) {
    for (size_t i = 0; i < other.size_; ++i) {
        push_back(other.data_[i]);
    }
}

size_t String::size() const {
    return size_;
}

size_t String::capacity() const {
    return capacity_;
}

const char* String::c_str() const {
    if (data_ != nullptr) {
        return data_;
    }
    return "";
}

bool String::operator==(const String& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

String String::rle_compress() const {
    String result;
    if (size_ == 0 || data_ == nullptr) {
        return result;
    }

    size_t count = 1;
    for (size_t i = 1; i <= size_; ++i) {
        if (i < size_ && data_[i] == data_[i - 1]) {
            count++;
        } else {
            result.push_back(data_[i - 1]);
            
            char buf[32];
            snprintf(buf, sizeof(buf), "%zu", count);
            for (int j = 0; buf[j] != '\0'; ++j) {
                result.push_back(buf[j]);
            }
            
            count = 1;
        }
    }
    return result;
}

void String::rle_decompress() {
    if (size_ == 0 || data_ == nullptr) {
        return;
    }
    
    String result;
    size_t i = 0;
    
    while (i < size_) {
        char c = data_[i];
        i++;
        
        size_t count = 0;
        while (i < size_ && data_[i] >= '0' && data_[i] <= '9') {
            count = count * 10 + (data_[i] - '0');
            i++;
        }
        
        for (size_t j = 0; j < count; ++j) {
            result.push_back(c);
        }
    }
    
    this->swap(result);
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.c_str();
    return os;
}
