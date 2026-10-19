# Инструкция по демонстрации

1. Выполнить `powershell -ExecutionPolicy Bypass -File additional_task3/build_release.ps1`.
2. Открыть `additional_task3/build/debug_target.exe` в IDA Pro или Visual Studio.
3. Запустить программу под отладчиком.
4. Остановиться на `DebugBreak()` внутри `debug_target`.
5. Объект `MyString value` имеет поля:
   - `data_` — указатель на буфер;
   - `size_` — длина строки;
   - `capacity_` — размер буфера.
6. Буфер заранее рассчитан на 128 символов. Записать в него строку:

   `A picture is worth a thousand words.`

7. Установить `size_` равным `36`; `capacity_` оставить равным `129`.
8. Продолжить выполнение и зафиксировать строку `After debugger modification`.
9. В IDA открыть Exports DLL и сравнить имена перегруженных методов `append`, `insert` или `replace`.

Если отладчик не останавливается на `DebugBreak`, поставить breakpoint на функцию
`debug_target` и выполнить остановку перед второй строкой вывода.
