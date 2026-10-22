#include <gtest/gtest.h>
#include "my_string.h"

TEST(StringTest, DefaultConstructor) {
    String s;
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(s.capacity(), 1);
    EXPECT_STREQ(s.c_str(), "");
}

TEST(StringTest, CStringConstructor) {
    String s1("A");
    EXPECT_EQ(s1.size(), 1);
    EXPECT_STREQ(s1.c_str(), "A");

    String s2("hello");
    EXPECT_EQ(s2.size(), 5);
    EXPECT_STREQ(s2.c_str(), "hello");
}

TEST(StringTest, CopyConstructor) {
    String s1("test");
    String s2(s1);
    EXPECT_TRUE(s1 == s2);
    EXPECT_NE(s1.c_str(), s2.c_str()); 
}

TEST(StringTest, MoveConstructor) {
    String s1("move");
    String s2(std::move(s1));
    EXPECT_STREQ(s2.c_str(), "move");
    EXPECT_EQ(s1.size(), 0);
}

TEST(StringTest, AssignmentOperator) {
    String s1("first");
    String s2("second");
    s2 = s1;
    EXPECT_STREQ(s2.c_str(), "first");

    s1 = s1; 
    EXPECT_STREQ(s1.c_str(), "first");
}

TEST(StringTest, PushBackAndCapacity) {
    String s;
    s.push_back('a');
    EXPECT_EQ(s.capacity(), 1);
    s.push_back('b');
    EXPECT_EQ(s.capacity(), 2);
    s.push_back('c');
    EXPECT_EQ(s.capacity(), 4);
    EXPECT_STREQ(s.c_str(), "abc");
}

TEST(StringTest, AppendString) {
    String s1("hello");
    String s2(" world");
    s1.append(s2);
    EXPECT_STREQ(s1.c_str(), "hello world");

    String empty;
    s1.append(empty);
    EXPECT_STREQ(s1.c_str(), "hello world");
}

TEST(StringTest, EqualityOperator) {
    String s1("abc");
    String s2("abc");
    String s3("abd");
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3);
}

TEST(StringTest, RleCompressBasic) {
    String s("AAABCC");
    String res = s.rle_compress();
    EXPECT_STREQ(res.c_str(), "A3B1C2");
}

TEST(StringTest, RleDecompressBasic) {
    String s("A3B1C2");
    s.rle_decompress();
    EXPECT_STREQ(s.c_str(), "AAABCC");
}

TEST(StringTest, RleEmptyString) {
    String empty;
    String comp = empty.rle_compress();
    EXPECT_STREQ(comp.c_str(), "");
    
    comp.rle_decompress();
    EXPECT_STREQ(comp.c_str(), "");
}

TEST(StringTest, RleDecompressDoubleDigit) {
    String s("A10");
    s.rle_decompress();
    EXPECT_STREQ(s.c_str(), "AAAAAAAAAA");
}
