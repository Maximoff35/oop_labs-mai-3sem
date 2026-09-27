#include "str_ops.h"
#include <iostream>

std::size_t str_len(const char* s) {
    if (s == nullptr) return 0;
    std::size_t count = 0;
    while (s[count] != '\0') count ++;
    return count;
}

void str_copy(char* dst, const char* src) {
    if ((src == nullptr) || (dst == nullptr)) {
        return;
    }
    std::size_t len = str_len(src);
    for (std::size_t i=0; i<=len; i++) {
        dst[i] = src[i];
    }
}

char* str_alloc(const char* src) {
    if (src == nullptr) {
        return nullptr;
    }
    std::size_t src_len = str_len(src);
    char* dst = new char[src_len + 1];
    str_copy(dst, src);
    return dst;
}

void str_delete(char*& s) {
    delete[] s;
    s = nullptr;
}

void str_print(const char* s) {
    if (s == nullptr) return;
    std::cout << s << "\n";
}

char* str_trim(const char* s) {
    if (s == nullptr) return nullptr;
    std::size_t start = 0, len = str_len(s);
    while ((start < len) && ((s[start] == ' ') || (s[start] == '\t') || (s[start] == '\n'))) {
        start++;
    }
    if (start == len) {
        return str_alloc("");
    }

    std::size_t end = len - 1;
    while ((end > start) && ((s[end] == ' ') || (s[end] == '\t') || (s[end] == '\n'))) {
        end--;
    }
    char* dst = new char[end - start + 2];
    for (std::size_t i=0; i<end - start + 1; i++) {
        dst[i] = s[i + start];
    }
    dst[end - start + 1] = '\0';
    return dst;
}

static void swap(char* s, std::size_t i, std::size_t j) {
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
}

static void reverse(char* s, std::size_t i, std::size_t j) {
    while (j > i) {
        swap(s, i, j);
        i++;
        j--;
    }
}

void str_reverse_words(char* s) {
    if ((s == nullptr) || (s[0] == '\0')) return;
    std::size_t s_len = str_len(s);
    reverse(s, 0, s_len - 1);
    std::size_t word_start = 0;
    for (std::size_t j = 0; j <= s_len; j++) {
        if ((s[j] == ' ') || s[j] == '\0') {
            if (j != word_start) {
                reverse(s, word_start, j - 1);
            }
            word_start = j + 1;
        }
    }
}