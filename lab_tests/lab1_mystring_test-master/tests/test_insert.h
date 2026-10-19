#ifndef TEST_INSERT_H
#define TEST_INSERT_H

#include IMYSTRING
#include "test_logger.h"
#include <string>

// $env:PYTHONPATH = "$PWD\build"
void test_insert_methods() {
    logger(info, "INSERT METHODS TESTING");
    std::string test_name;
	//TEST 1
    test_name = "TEST 1 - INSERT WHEN CAPACITY IS FULL";
    MyString str12("hellohellohellohellohellohellohellohellohello");
    bool cap12 = str12.capacity() == str12.size() + 1;
    str12.insert(3, "hellohello");
    !strcmp(str12.c_str(), "helhellohellolohellohellohellohellohellohellohellohello") && cap12 && str12.size() == 55 && str12.capacity() == 56 ? logger(success, test_name) : logger(error, test_name);
	//TEST 2
    test_name = "TEST 2 - INSERT STRING INTO ITSELF WHEN CAPACITY IS FULL";
    MyString str2("hellohellohellohellohellohellohellohellohello");
    bool cap2 = str2.capacity() == str2.size() + 1;
    str2.insert(3, str2);
    !strcmp(str2.c_str(), "helhellohellohellohellohellohellohellohellohellolohellohellohellohellohellohellohellohello") && cap2 && str2.size() == 90 && str2.capacity() == 91 ? logger(success, test_name) : logger(error, test_name);
}
#endif
