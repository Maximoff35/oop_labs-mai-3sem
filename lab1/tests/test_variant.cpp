#include <gtest/gtest.h>
#include "str_ops.h"

TEST(StrLen, NormalString) {
    EXPECT_EQ(str_len("Hello"), 5);
}

TEST(StrLen, EmptyString) {
    EXPECT_EQ(str_len(""), 0);
}

TEST(StrLen, NullPtrString) {
    EXPECT_EQ(str_len(nullptr), 0);
}

TEST(StrAlloc, Normal) {
    char* s = str_alloc("Hello");
    EXPECT_STREQ(s, "Hello");
    str_delete(s);
}

TEST(StrDelete, Normal) {
    char* s = str_alloc("Hello");
    str_delete(s);
    EXPECT_EQ(s, nullptr);
}

TEST(StrCopy, Normal) {
    char* s = str_alloc("Hello");
    char* new_s = new char[str_len(s) + 1];
    str_copy(new_s, s);
    EXPECT_STREQ(new_s, s);
    str_delete(s);
    str_delete(new_s);
}

TEST(StrTrim, Normal) {
    char* s = str_trim("   hello   ");
    EXPECT_STREQ(s, "hello");
    str_delete(s);
}

TEST(StrTrim, WithoutSpaces) {
    char* s = str_trim("hello");
    EXPECT_STREQ(s, "hello");
    str_delete(s);
}

TEST(StrTrim, OnlySpaces) {
    char* s = str_trim(" ");
    EXPECT_STREQ(s, "");
    str_delete(s);
}

TEST(StrReverseWords, Normal) {
    char* s = str_alloc("one two three");
    str_reverse_words(s);
    EXPECT_STREQ(s, "three two one");
    str_delete(s);
}

TEST(StrReverseWords, OneWord) {
    char* s = str_alloc("hello");
    str_reverse_words(s);
    EXPECT_STREQ(s, "hello");
    str_delete(s);
}

TEST(StrReverseWords, EmptyString) {
    char* s = str_alloc("");
    str_reverse_words(s);
    EXPECT_STREQ(s, "");
    str_delete(s);
}
