# Запуск и демонстрация лабораторной работы №1 «MyString»

## 1. Состав проекта

Основные файлы лабораторной работы находятся в корне проекта:

- `MyString.h` — объявление класса `MyString`;
- `MyString.cpp` — реализация класса;
- `MyString_wrapper.cpp` — Python-обёртка на основе `pybind11`;
- `mystring_h_path.txt` — путь к заголовочному файлу для автоматической проверки;
- `.gitignore` — исключения для артефактов сборки;
- `lab_tests/lab1_mystring_test-master` — предоставленные автотесты.

Все приведённые ниже команды необходимо выполнять из корневой директории проекта:

```text
C:\Work Space\OOP\1
```

## 2. Необходимые компоненты

Для полной демонстрации нужны:

1. Microsoft Visual Studio с компонентом «Разработка классических приложений на C++».
2. Компилятор MSVC (`cl.exe`).
3. Python 3.14.
4. Python-пакеты `pybind11` и `pytest`.

Компилятор `clang++` нужен только для дополнительной проверки требования о совместимости с Clang. В установленной Visual Studio он уже находится по адресу:

```text
C:\Work Space\Microsoft Visual Studio\Product\VC\Tools\Llvm\x64\bin\clang++.exe
```

## 3. Открытие консоли Visual Studio

Для сборки через MSVC рекомендуется использовать специальную консоль Visual Studio:

1. Открыть меню «Пуск».
2. Найти папку установленной Visual Studio.
3. Запустить `x64 Native Tools Command Prompt for VS`.
4. Перейти в директорию проекта:

```bat
cd /d "C:\Work Space\OOP\1"
```

Проверить доступность компилятора:

```bat
cl
```

Если вывод содержит версию Microsoft C/C++ Compiler, окружение настроено правильно.

## 4. Сборка C++-автотестов через MSVC

В консоли `x64 Native Tools Command Prompt for VS` выполнить:

```bat
cl /nologo /std:c++17 /EHsc /DIMYSTRING=\"MyString.h\" /I. /I"lab_tests\lab1_mystring_test-master" "lab_tests\lab1_mystring_test-master\main.cpp" "lab_tests\lab1_mystring_test-master\tests\test_logger.cpp" "MyString.cpp" /Fe:"mystring_tests.exe"
```

Назначение основных параметров:

- `/std:c++17` — использование стандарта C++17 согласно техническому заданию;
- `/EHsc` — включение стандартной обработки исключений C++;
- `/DIMYSTRING=\"MyString.h\"` — передача автотестам пути к заголовочному файлу;
- `/I.` — добавление корня проекта в пути поиска заголовков;
- `/Fe` — имя создаваемого исполняемого файла.

После успешной сборки появится файл `mystring_tests.exe`.

## 5. Запуск C++-автотестов

Выполнить:

```bat
mystring_tests.exe
```

Будут последовательно проверены:

- конструкторы и копирование;
- методы `c_str`, `size`, `capacity` и `empty`;
- `insert`, `append`, `erase` и `replace`;
- `substr` и `find`;
- операторы присваивания и конкатенации;
- операторы сравнения;
- оператор индексации;
- сохранение и уменьшение `capacity`;
- исключения при недопустимых индексах.

Успешный тест выводит строку с пометкой `Success`. В полностью успешном запуске строки с пометкой `Error` отсутствуют.

## 6. Проверка с предупреждениями компилятора

Для дополнительной проверки качества кода можно включить высокий уровень предупреждений MSVC:

```bat
cl /nologo /std:c++17 /EHsc /W4 /permissive- /DIMYSTRING=\"MyString.h\" /I. /I"lab_tests\lab1_mystring_test-master" "lab_tests\lab1_mystring_test-master\main.cpp" "lab_tests\lab1_mystring_test-master\tests\test_logger.cpp" "MyString.cpp" /Fe:"mystring_tests.exe"
```

Предупреждения о неиспользуемых переменных и параметрах могут исходить из предоставленных файлов автотестов. Файл `MyString.cpp` собирается без предупреждений.

## 7. Проверка памяти с AddressSanitizer

MSVC позволяет проверить обращения к динамической памяти с помощью AddressSanitizer:

```bat
cl /nologo /std:c++17 /EHsc /Zi /fsanitize=address /DIMYSTRING=\"MyString.h\" /I. /I"lab_tests\lab1_mystring_test-master" "lab_tests\lab1_mystring_test-master\main.cpp" "lab_tests\lab1_mystring_test-master\tests\test_logger.cpp" "MyString.cpp" /Fe:"mystring_tests_asan.exe" /link /DEBUG
```

Запуск проверки:

```bat
mystring_tests_asan.exe
```

При корректной работе выполняются обычные тесты и не появляются сообщения `AddressSanitizer: error`. Это проверяет выходы за границы буфера, использование освобождённой памяти и другие ошибки работы с памятью.

## 8. Проверка сборки через clang++

Этот шаг демонстрирует выполнение прямого требования технического задания о поддержке `clang++`.

В обычном PowerShell из корня проекта выполнить:

```powershell
@'
-std=c++17
-DIMYSTRING=\"MyString.h\"
-I.
-Ilab_tests/lab1_mystring_test-master
lab_tests/lab1_mystring_test-master/main.cpp
lab_tests/lab1_mystring_test-master/tests/test_logger.cpp
MyString.cpp
-o
mystring_clang_tests.exe
'@ | Set-Content -Encoding ASCII clang_test.rsp
```

Затем собрать тесты:

```powershell
& "C:\Work Space\Microsoft Visual Studio\Product\VC\Tools\Llvm\x64\bin\clang++.exe" '@clang_test.rsp'
```

Запустить:

```powershell
.\mystring_clang_tests.exe
```

После демонстрации временный файл параметров можно удалить:

```powershell
Remove-Item clang_test.rsp
```

Если Visual Studio установлена в другую директорию, путь к `clang++.exe` необходимо заменить на фактический.

## 9. Подготовка Python

Проверить установленную версию Python:

```bat
py --version
```

Ожидаемый результат в текущем окружении:

```text
Python 3.14.7
```

Установить зависимости для сборки и тестирования обёртки:

```bat
py -m pip install pybind11 pytest
```

Проверить установку:

```bat
py -m pip show pybind11
py -m pip show pytest
```

## 10. Сборка Python-обёртки через MSVC

Следующие команды необходимо выполнять в `x64 Native Tools Command Prompt for VS` из корня проекта.

Сначала получить используемые Python пути:

```bat
py -c "import sys; print(sys.base_prefix)"
py -c "import sysconfig; print(sysconfig.get_path('include'))"
py -c "import pybind11; print(pybind11.get_include())"
py -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))"
```

Для текущей установки Python 3.14 команда сборки имеет следующий вид:

```bat
cl /nologo /std:c++17 /EHsc /LD "MyString.cpp" "MyString_wrapper.cpp" /I"C:\Users\v1136\AppData\Local\Python\pythoncore-3.14-64\Include" /I"C:\Users\v1136\AppData\Local\Python\pythoncore-3.14-64\Lib\site-packages\pybind11\include" /link /LIBPATH:"C:\Users\v1136\AppData\Local\Python\pythoncore-3.14-64\libs" /OUT:"mystring.cp314-win_amd64.pyd"
```

В результате в корне проекта появится модуль:

```text
mystring.cp314-win_amd64.pyd
```

Имя после `mystring` зависит от версии и архитектуры Python. Его точное окончание показывает команда:

```bat
py -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))"
```

При использовании другой версии Python необходимо заменить пути к `Include`, `site-packages` и `libs`, а также окончание имени `.pyd`.

## 11. Быстрая ручная демонстрация Python-обёртки

После сборки `.pyd` запустить Python:

```bat
py
```

В интерактивном интерпретаторе выполнить:

```python
from mystring import MyString

text = MyString("Hello")
text.append(" world")
print(text.c_str())
print("size:", text.size())
print("capacity:", text.capacity())

text.insert(5, ",")
print(text.c_str())

part = text.substr(7, 5)
print(part.c_str())

print("world index:", text.find("world"))
print("comparison:", MyString("apple") < MyString("banana"))
```

Ожидаемый смысловой результат:

```text
Hello world
size: 11
capacity: 12
Hello, world
world
world index: 7
comparison: True
```

Для выхода из интерпретатора:

```python
exit()
```

## 12. Запуск Python-автотестов

После сборки файла `.pyd` выполнить из корня проекта:

```bat
py -m pytest "lab_tests\lab1_mystring_test-master\wrapper_test" -v
```

Ожидаемый итог:

```text
13 passed
```

Тесты проверяют конструкторы, свойства строки, основные методы, операторы, сравнение, поиск и корректность изменения `capacity` через Python.

## 13. Рекомендуемый порядок демонстрации преподавателю

1. Показать `MyString.h`: публичный интерфейс и закрытые поля `data_`, `size_`, `capacity_`.
2. Показать `MyString.cpp`: выделение памяти через `new[]`, освобождение через `delete[]`, методы `assign`, `ensure_capacity` и `splice`.
3. Обратить внимание, что `clear`, `erase` и сокращающий `replace` не уменьшают `capacity`.
4. Показать, что уменьшение памяти выполняется только методом `shrink_to_fit`.
5. Показать проверки аргументов и генерацию `std::out_of_range` и `std::invalid_argument`.
6. Собрать и запустить C++-автотесты.
7. При необходимости запустить вариант с AddressSanitizer.
8. Показать `MyString_wrapper.cpp` и объяснить экспорт класса через `pybind11`.
9. Собрать Python-модуль `.pyd`.
10. Выполнить короткий ручной пример в Python.
11. Запустить Python-автотесты и показать результат `13 passed`.

## 14. Очистка файлов сборки

После демонстрации можно удалить созданные артефакты:

```bat
del /Q *.obj *.exe *.pyd *.lib *.exp *.pdb *.ilk 2>nul
```

Исходные файлы `MyString.h`, `MyString.cpp`, `MyString_wrapper.cpp` и `mystring_h_path.txt` удалять не нужно.

## 15. Краткий вариант полного запуска

В `x64 Native Tools Command Prompt for VS`:

```bat
cd /d "C:\Work Space\OOP\1"
cl /nologo /std:c++17 /EHsc /DIMYSTRING=\"MyString.h\" /I. /I"lab_tests\lab1_mystring_test-master" "lab_tests\lab1_mystring_test-master\main.cpp" "lab_tests\lab1_mystring_test-master\tests\test_logger.cpp" "MyString.cpp" /Fe:"mystring_tests.exe"
mystring_tests.exe
cl /nologo /std:c++17 /EHsc /LD "MyString.cpp" "MyString_wrapper.cpp" /I"C:\Users\v1136\AppData\Local\Python\pythoncore-3.14-64\Include" /I"C:\Users\v1136\AppData\Local\Python\pythoncore-3.14-64\Lib\site-packages\pybind11\include" /link /LIBPATH:"C:\Users\v1136\AppData\Local\Python\pythoncore-3.14-64\libs" /OUT:"mystring.cp314-win_amd64.pyd"
py -m pytest "lab_tests\lab1_mystring_test-master\wrapper_test" -v
```

Успешная демонстрация завершается прохождением всех C++-тестов без `Error` и сообщением `13 passed` от `pytest`.
