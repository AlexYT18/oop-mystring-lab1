#include "MyString.h"

#include <iostream>
#include <windows.h>

__declspec(noinline) void debug_target(MyString& value)
{
    std::cout << "Before debugger modification: size=" << value.size()
              << ", capacity=" << value.capacity() << ", value=["
              << value.c_str() << "]\n";

    if (IsDebuggerPresent())
    {
        DebugBreak();
    }

    std::cout << "After debugger modification: size=" << value.size()
              << ", capacity=" << value.capacity() << ", value=["
              << value.c_str() << "]\n";
}

int main()
{
    MyString value(128, '.');
    debug_target(value);
    return 0;
}
