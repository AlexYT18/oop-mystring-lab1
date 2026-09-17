#include <pybind11/pybind11.h>

#include "MyString.h"

namespace py = pybind11;

PYBIND11_MODULE(mystring, module)
{
    py::class_<MyString>(module, "MyString")
        .def(py::init<>())
        .def(py::init<const char*>())
        .def(py::init<const char*, int>())
        .def(py::init<int, char>())
        .def(py::init<const MyString&>())
        .def("c_str", [](const MyString& value) {
            return std::string(value.c_str(), value.size());
        })
        .def("size", &MyString::size)
        .def("capacity", &MyString::capacity)
        .def("empty", &MyString::empty)
        .def("clear", &MyString::clear)
        .def("shrink_to_fit", &MyString::shrink_to_fit)
        .def("insert", static_cast<MyString& (MyString::*)(int, int, char)>(&MyString::insert),
             py::return_value_policy::reference_internal)
        .def("insert", static_cast<MyString& (MyString::*)(int, const char*)>(&MyString::insert),
             py::return_value_policy::reference_internal)
        .def("insert", static_cast<MyString& (MyString::*)(int, const char*, int)>(&MyString::insert),
             py::return_value_policy::reference_internal)
        .def("insert", static_cast<MyString& (MyString::*)(int, const char*, int, int)>(&MyString::insert),
             py::return_value_policy::reference_internal)
        .def("append", static_cast<MyString& (MyString::*)(int, char)>(&MyString::append),
             py::return_value_policy::reference_internal)
        .def("append", static_cast<MyString& (MyString::*)(const char*)>(&MyString::append),
             py::return_value_policy::reference_internal)
        .def("append", static_cast<MyString& (MyString::*)(const MyString&)>(&MyString::append),
             py::return_value_policy::reference_internal)
        .def("append", static_cast<MyString& (MyString::*)(const char*, int)>(&MyString::append),
             py::return_value_policy::reference_internal)
        .def("append", static_cast<MyString& (MyString::*)(const char*, int, int)>(&MyString::append),
             py::return_value_policy::reference_internal)
        .def("erase", &MyString::erase, py::return_value_policy::reference_internal)
        .def("replace", static_cast<MyString& (MyString::*)(int, int, const char*)>(&MyString::replace),
             py::return_value_policy::reference_internal)
        .def("replace", static_cast<MyString& (MyString::*)(int, int, const char*, int)>(&MyString::replace),
             py::return_value_policy::reference_internal)
        .def("replace", static_cast<MyString& (MyString::*)(int, int, const char*, int, int)>(&MyString::replace),
             py::return_value_policy::reference_internal)
        .def("substr", static_cast<MyString (MyString::*)(int) const>(&MyString::substr))
        .def("substr", static_cast<MyString (MyString::*)(int, int) const>(&MyString::substr))
        .def("find", static_cast<std::size_t (MyString::*)(const char*) const>(&MyString::find))
        .def("find", static_cast<std::size_t (MyString::*)(const char*, int) const>(&MyString::find))
        .def("compare", &MyString::compare)
        .def("__len__", &MyString::size)
        .def("__str__", [](const MyString& value) {
            return std::string(value.c_str(), value.size());
        })
        .def("__add__", static_cast<MyString (MyString::*)(const MyString&) const>(&MyString::operator+), py::is_operator())
        .def("__add__", static_cast<MyString (MyString::*)(const char*) const>(&MyString::operator+), py::is_operator())
        .def("__iadd__", static_cast<MyString& (MyString::*)(const MyString&)>(&MyString::operator+=),
             py::return_value_policy::reference_internal, py::is_operator())
        .def("__iadd__", static_cast<MyString& (MyString::*)(const char*)>(&MyString::operator+=),
             py::return_value_policy::reference_internal, py::is_operator())
        .def("__eq__", &MyString::operator==, py::is_operator())
        .def("__ne__", &MyString::operator!=, py::is_operator())
        .def("__lt__", &MyString::operator<, py::is_operator())
        .def("__le__", &MyString::operator<=, py::is_operator())
        .def("__gt__", &MyString::operator>, py::is_operator())
        .def("__ge__", &MyString::operator>=, py::is_operator());
}
