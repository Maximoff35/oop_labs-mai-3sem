# Лабораторная работа №1

Вариант 14.

Программа работает с динамическими C-строками (`char*`).  
`std::string`, контейнеры STL и умные указатели не используются, память выделяется и освобождается вручную через `new[]` и `delete[]`.

## Что реализовано

Основные функции для работы со строками:

- `str_alloc` — создание динамической копии строки;
- `str_len` — вычисление длины строки;
- `str_copy` — копирование строки в буфер;
- `str_delete` — освобождение памяти;
- `str_print` — вывод строки.

Функции варианта 14:

- `str_trim` — удаление пробельных символов по краям строки;
- `str_reverse_words` — разворот порядка слов без разворота самих слов.

Пример:

```text
one two three
```

после `str_reverse_words`:

```text
three two one
```

## Структура проекта

```text
lab1/
├── CMakeLists.txt
├── README.md
├── include/
│   └── str_ops.h
├── src/
│   ├── main.cpp
│   └── str_ops.cpp
└── tests/
    └── test_variant.cpp
```

## Сборка

Проект собирается через CMake.

```powershell
cmake -S . -B build
cmake --build build
```

## Запуск программы

```powershell
.\build\lab1.exe
```

Меню программы:

```text
1. Enter string
2. Print string
3. String length
4. Copy to buffer and print
5. Trim whitespace from edges
6. Reverse word order
0. Exit
```

## Тесты

Для тестирования используется Google Test.

Запуск тестов напрямую:

```powershell
.\build\lab1_tests.exe
```

Или через CTest:

```powershell
ctest --test-dir build --output-on-failure
```

В тестах проверяются основные операции со строками, пустые строки, `nullptr`, удаление пробелов по краям и разворот порядка слов.
