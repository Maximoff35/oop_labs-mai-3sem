#include <iostream>
#include <limits>
#include "str_ops.h"

void print_menu() {
    std::cout << "\n\n=== MENU ===\n";
    std::cout << "1. Enter string\n";
    std::cout << "2. Print string\n";
    std::cout << "3. String length\n";
    std::cout << "4. Copy to buffer and print\n";
    std::cout << "5. Trim whitespace from edges\n";
    std::cout << "6. Reverse word order\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    char* s = nullptr;
    int choice = -1;

    do {
        print_menu();
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
            std::cout << "Invalid input\n";
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: {
                char buffer[1024];
                std::cout << "Enter string: ";
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(),
                    '\n'
                );
                std::cin.getline(buffer, 1024);

                if ((std::cin.fail())) {
                    std::cin.clear();
                    std::cin.ignore(
                        std::numeric_limits<std::streamsize>::max(),
                        '\n'
                    );
                    std::cout << "Invalid input\n";
                    break;
                }

                str_delete(s);
                s = str_alloc(buffer);
                break;
            }
            case 2: {
                if (s == nullptr) {
                    std::cout << "String is not entered\n";
                } else {
                    str_print(s);
                }
                break;
            }
            case 3: {
                if (s == nullptr) {
                    std::cout << "String is not entered\n";
                } else {
                    std::cout << "String length: " << str_len(s) << '\n';
                }
                break;
            }
            case 4: {
                if (s == nullptr) {
                    std::cout << "String is not entered\n";
                } else {
                    std::size_t len = str_len(s);
                    char* copy = new char[len + 1];
                    str_copy(copy, s);
                    std::cout << "Copy: ";
                    str_print(copy);
                    str_delete(copy);
                }
                break;
            }
            case 5: {
                if (s == nullptr) {
                    std::cout << "String is not entered\n";
                } else {
                    char* trimmed = str_trim(s);
                    str_delete(s);
                    s = trimmed;
                    std::cout << "Result: ";
                    str_print(s);
                }
                break;
            }
            case 6: {
                if (s == nullptr) {
                    std::cout << "String is not entered\n";
                } else {
                    str_reverse_words(s);
                    std::cout << "Result: ";
                    str_print(s);
                }
                break;
            }
            case 0: {
                break;
            }
            default: {
                std::cout << "Unknown menu option\n";
            }
        }

    } while (choice != 0);

    str_delete(s);

    return 0;
}

