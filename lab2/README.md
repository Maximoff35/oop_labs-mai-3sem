# Лабораторная работа №2

Вариант 17. Семейство C — `Matrix`.

Программа реализует класс матрицы с динамическим одномерным массивом `double*`. Элементы хранятся построчно; индекс элемента `(r, c)` вычисляется как `r * cols_ + c`.  
`std::string`, `std::vector`, `std::array` и умные указатели не используются. Память выделяется и освобождается вручную через `new[]` и `delete[]`.

## Что реализовано

Основные возможности класса `Matrix`:

- конструктор с заданными размерами и значением элементов;
- деструктор и управление памятью по принципу RAII;
- конструкторы копирования и перемещения (правило пяти);
- присваивание через идиому copy-and-swap;
- `swap` — обмен ресурсами двух матриц;
- `rows`, `cols` — получение размеров;
- `get`, `set` — чтение и изменение элементов с проверкой индексов;
- `add` — сложение матриц;
- `mul` — умножение матриц;
- `print` — вывод матрицы в поток.

Метод варианта 17:

- `sum` — сумма всех элементов матрицы.

Пример:

```text
1 2
3 4
```

Результат `sum()`:

```text
10
```

## Структура проекта

```text
lab2/
├── CMakeLists.txt
├── README.md
├── include/
│   └── matrix.h
├── src/
│   ├── main.cpp
│   └── matrix.cpp
└── tests/
    └── test_variant.cpp
```

## Сборка

Проект собирается через CMake с использованием стандарта C++20. При первой конфигурации CMake загружает Google Test через FetchContent; для этого нужен доступ к GitHub.

```powershell
cmake -S . -B build
cmake --build build
```

## Запуск программы

```powershell
.\build\lab2.exe
```

`main.cpp` демонстрирует создание матриц, изменение элементов, копирование, перемещение и присваивание, а также вычисление суммы.

## Тесты

Для тестирования используется Google Test (18 тестов).

Запуск тестов напрямую:

```powershell
.\build\lab2_tests.exe
```

Или через CTest:

```powershell
ctest --test-dir build --output-on-failure
```

В тестах проверяются создание матриц, пустые матрицы, чтение и изменение элементов, некорректные индексы, `sum`, глубокое копирование, перемещение, присваивание, самоприсваивание и `swap`.

## Проверка памяти

Для проверки обращений к памяти используется AddressSanitizer со сборкой Clang в MSYS2 CLANG64:

```bash
cmake -S . -B build-asan -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_CXX_FLAGS="-fsanitize=address -fno-omit-frame-pointer" \
  -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address"
cmake --build build-asan
ctest --test-dir build-asan --output-on-failure
```

Проверка AddressSanitizer не гарантирует обнаружение всех утечек памяти на Windows.
