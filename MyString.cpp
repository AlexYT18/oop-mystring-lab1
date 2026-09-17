#include "MyString.h"

#include <cstring>
#include <ostream>
#include <stdexcept>

namespace
{
std::size_t CheckedValue(int value, const char* argument_name)
{
    if (value < 0)
    {
        throw std::out_of_range(argument_name);
    }
    return static_cast<std::size_t>(value);
}

std::size_t CStringLength(const char* source)
{
    if (source == nullptr)
    {
        throw std::invalid_argument("source must not be null");
    }
    return std::strlen(source);
}

void CheckSourceRange(std::size_t source_size, std::size_t source_index,
                      std::size_t source_count)
{
    if (source_index > source_size || source_count > source_size - source_index)
    {
        throw std::out_of_range("source range is out of bounds");
    }
}
}

const std::size_t MyString::npos = static_cast<std::size_t>(-1);

MyString::MyString()
    : data_(nullptr), size_(0), capacity_(0)
{
}

MyString::MyString(const char* source)
    : data_(nullptr), size_(0), capacity_(0)
{
    assign(source, CStringLength(source));
}

MyString::MyString(const std::string& source)
    : data_(nullptr), size_(0), capacity_(0)
{
    assign(source.data(), source.size());
}

MyString::MyString(const MyString& source)
    : data_(nullptr), size_(0), capacity_(0)
{
    assign(source.c_str(), source.size());
}

MyString::MyString(const char* source, int count)
    : data_(nullptr), size_(0), capacity_(0)
{
    std::size_t source_size = CStringLength(source);
    std::size_t checked_count = CheckedValue(count, "count must not be negative");
    CheckSourceRange(source_size, 0, checked_count);
    assign(source, checked_count);
}

MyString::MyString(const std::string& source, int count)
    : data_(nullptr), size_(0), capacity_(0)
{
    std::size_t checked_count = CheckedValue(count, "count must not be negative");
    CheckSourceRange(source.size(), 0, checked_count);
    assign(source.data(), checked_count);
}

MyString::MyString(const MyString& source, int count)
    : data_(nullptr), size_(0), capacity_(0)
{
    std::size_t checked_count = CheckedValue(count, "count must not be negative");
    CheckSourceRange(source.size(), 0, checked_count);
    assign(source.c_str(), checked_count);
}

MyString::MyString(int count, char ch)
    : data_(nullptr), size_(0), capacity_(0)
{
    std::size_t checked_count = CheckedValue(count, "count must not be negative");
    if (checked_count == 0)
    {
        return;
    }

    ensure_capacity(checked_count + 1);
    std::memset(data_, ch, checked_count);
    size_ = checked_count;
    data_[size_] = '\0';
}

MyString::~MyString()
{
    delete[] data_;
}

MyString& MyString::operator=(const char* source)
{
    assign(source, CStringLength(source));
    return *this;
}

MyString& MyString::operator=(const std::string& source)
{
    assign(source.data(), source.size());
    return *this;
}

MyString& MyString::operator=(const MyString& source)
{
    if (this != &source)
    {
        assign(source.c_str(), source.size());
    }
    return *this;
}

MyString& MyString::operator=(char ch)
{
    assign(&ch, 1);
    return *this;
}

void MyString::clear()
{
    size_ = 0;
    if (data_ != nullptr)
    {
        data_[0] = '\0';
    }
}

void MyString::shrink_to_fit()
{
    std::size_t required_capacity = size_ == 0 && capacity_ == 0 ? 0 : size_ + 1;
    if (capacity_ == required_capacity)
    {
        return;
    }

    char* new_data = required_capacity == 0 ? nullptr : new char[required_capacity];
    if (new_data != nullptr)
    {
        if (size_ != 0)
        {
            std::memcpy(new_data, data_, size_);
        }
        new_data[size_] = '\0';
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = required_capacity;
}

const char* MyString::c_str() const
{
    return data_ == nullptr ? "" : data_;
}

std::size_t MyString::size() const
{
    return size_;
}

std::size_t MyString::capacity() const
{
    return capacity_;
}

bool MyString::empty() const
{
    return size_ == 0;
}

MyString& MyString::insert(int index, int count, char ch)
{
    std::size_t checked_index = CheckedValue(index, "index must not be negative");
    std::size_t checked_count = CheckedValue(count, "count must not be negative");
    if (checked_index > size_)
    {
        throw std::out_of_range("index is out of bounds");
    }
    if (checked_count == 0)
    {
        return *this;
    }

    char* repeated = new char[checked_count];
    std::memset(repeated, ch, checked_count);
    try
    {
        splice(checked_index, 0, repeated, checked_count, 0, checked_count);
    }
    catch (...)
    {
        delete[] repeated;
        throw;
    }
    delete[] repeated;
    return *this;
}

MyString& MyString::insert(int index, const char* source)
{
    return insert(index, source, 0, static_cast<int>(CStringLength(source)));
}

MyString& MyString::insert(int index, const std::string& source)
{
    return insert(index, source, 0, static_cast<int>(source.size()));
}

MyString& MyString::insert(int index, const MyString& source)
{
    return insert(index, source, 0, static_cast<int>(source.size()));
}

MyString& MyString::insert(int index, const char* source, int count)
{
    return insert(index, source, 0, count);
}

MyString& MyString::insert(int index, const std::string& source, int count)
{
    return insert(index, source, 0, count);
}

MyString& MyString::insert(int index, const MyString& source, int count)
{
    return insert(index, source, 0, count);
}

MyString& MyString::insert(int index, const char* source, int source_index, int count)
{
    std::size_t source_size = CStringLength(source);
    splice(CheckedValue(index, "index must not be negative"), 0, source, source_size,
           CheckedValue(source_index, "source index must not be negative"),
           CheckedValue(count, "count must not be negative"));
    return *this;
}

MyString& MyString::insert(int index, const std::string& source, int source_index, int count)
{
    splice(CheckedValue(index, "index must not be negative"), 0, source.data(), source.size(),
           CheckedValue(source_index, "source index must not be negative"),
           CheckedValue(count, "count must not be negative"));
    return *this;
}

MyString& MyString::insert(int index, const MyString& source, int source_index, int count)
{
    splice(CheckedValue(index, "index must not be negative"), 0, source.c_str(), source.size(),
           CheckedValue(source_index, "source index must not be negative"),
           CheckedValue(count, "count must not be negative"));
    return *this;
}

MyString& MyString::append(int count, char ch)
{
    return insert(static_cast<int>(size_), count, ch);
}

MyString& MyString::append(const char* source)
{
    return insert(static_cast<int>(size_), source);
}

MyString& MyString::append(const std::string& source)
{
    return insert(static_cast<int>(size_), source);
}

MyString& MyString::append(const MyString& source)
{
    return insert(static_cast<int>(size_), source);
}

MyString& MyString::append(const char* source, int count)
{
    return insert(static_cast<int>(size_), source, count);
}

MyString& MyString::append(const std::string& source, int count)
{
    return insert(static_cast<int>(size_), source, count);
}

MyString& MyString::append(const MyString& source, int count)
{
    return insert(static_cast<int>(size_), source, count);
}

MyString& MyString::append(const char* source, int source_index, int count)
{
    return insert(static_cast<int>(size_), source, source_index, count);
}

MyString& MyString::append(const std::string& source, int source_index, int count)
{
    return insert(static_cast<int>(size_), source, source_index, count);
}

MyString& MyString::append(const MyString& source, int source_index, int count)
{
    return insert(static_cast<int>(size_), source, source_index, count);
}

MyString& MyString::erase(int index, int count)
{
    std::size_t checked_index = CheckedValue(index, "index must not be negative");
    std::size_t checked_count = CheckedValue(count, "count must not be negative");
    splice(checked_index, checked_count, "", 0, 0, 0);
    return *this;
}

MyString& MyString::replace(int index, int count, const char* source)
{
    return replace(index, count, source, 0, static_cast<int>(CStringLength(source)));
}

MyString& MyString::replace(int index, int count, const std::string& source)
{
    return replace(index, count, source, 0, static_cast<int>(source.size()));
}

MyString& MyString::replace(int index, int count, const MyString& source)
{
    return replace(index, count, source, 0, static_cast<int>(source.size()));
}

MyString& MyString::replace(int index, int count, const char* source, int source_count)
{
    return replace(index, count, source, 0, source_count);
}

MyString& MyString::replace(int index, int count, const std::string& source, int source_count)
{
    return replace(index, count, source, 0, source_count);
}

MyString& MyString::replace(int index, int count, const MyString& source, int source_count)
{
    return replace(index, count, source, 0, source_count);
}

MyString& MyString::replace(int index, int count, const char* source, int source_index, int source_count)
{
    std::size_t source_size = CStringLength(source);
    splice(CheckedValue(index, "index must not be negative"),
           CheckedValue(count, "count must not be negative"), source, source_size,
           CheckedValue(source_index, "source index must not be negative"),
           CheckedValue(source_count, "source count must not be negative"));
    return *this;
}

MyString& MyString::replace(int index, int count, const std::string& source,
                            int source_index, int source_count)
{
    splice(CheckedValue(index, "index must not be negative"),
           CheckedValue(count, "count must not be negative"), source.data(), source.size(),
           CheckedValue(source_index, "source index must not be negative"),
           CheckedValue(source_count, "source count must not be negative"));
    return *this;
}

MyString& MyString::replace(int index, int count, const MyString& source,
                            int source_index, int source_count)
{
    splice(CheckedValue(index, "index must not be negative"),
           CheckedValue(count, "count must not be negative"), source.c_str(), source.size(),
           CheckedValue(source_index, "source index must not be negative"),
           CheckedValue(source_count, "source count must not be negative"));
    return *this;
}

MyString MyString::substr(int index) const
{
    std::size_t checked_index = CheckedValue(index, "index must not be negative");
    if (checked_index > size_)
    {
        throw std::out_of_range("index is out of bounds");
    }
    return MyString(c_str() + checked_index, static_cast<int>(size_ - checked_index));
}

MyString MyString::substr(int index, int count) const
{
    std::size_t checked_index = CheckedValue(index, "index must not be negative");
    std::size_t checked_count = CheckedValue(count, "count must not be negative");
    if (checked_index > size_)
    {
        throw std::out_of_range("index is out of bounds");
    }
    if (checked_count > size_ - checked_index)
    {
        checked_count = size_ - checked_index;
    }
    return MyString(c_str() + checked_index, static_cast<int>(checked_count));
}

MyString MyString::operator+(const char* source) const
{
    MyString result(*this);
    result.append(source);
    return result;
}

MyString MyString::operator+(const std::string& source) const
{
    MyString result(*this);
    result.append(source);
    return result;
}

MyString MyString::operator+(const MyString& source) const
{
    MyString result(*this);
    result.append(source);
    return result;
}

MyString& MyString::operator+=(const char* source)
{
    return append(source);
}

MyString& MyString::operator+=(const std::string& source)
{
    return append(source);
}

MyString& MyString::operator+=(const MyString& source)
{
    return append(source);
}

char& MyString::operator[](int index)
{
    std::size_t checked_index = CheckedValue(index, "index must not be negative");
    if (checked_index >= size_)
    {
        throw std::out_of_range("index is out of bounds");
    }
    return data_[checked_index];
}

const char& MyString::operator[](int index) const
{
    std::size_t checked_index = CheckedValue(index, "index must not be negative");
    if (checked_index >= size_)
    {
        throw std::out_of_range("index is out of bounds");
    }
    return data_[checked_index];
}

int MyString::compare(const MyString& source) const
{
    std::size_t common_size = size_ < source.size_ ? size_ : source.size_;
    int comparison = common_size == 0 ? 0 : std::memcmp(c_str(), source.c_str(), common_size);
    if (comparison < 0)
    {
        return -1;
    }
    if (comparison > 0)
    {
        return 1;
    }
    if (size_ < source.size_)
    {
        return -1;
    }
    if (size_ > source.size_)
    {
        return 1;
    }
    return 0;
}

bool MyString::operator==(const MyString& source) const
{
    return compare(source) == 0;
}

bool MyString::operator!=(const MyString& source) const
{
    return compare(source) != 0;
}

bool MyString::operator<(const MyString& source) const
{
    return compare(source) < 0;
}

bool MyString::operator<=(const MyString& source) const
{
    return compare(source) <= 0;
}

bool MyString::operator>(const MyString& source) const
{
    return compare(source) > 0;
}

bool MyString::operator>=(const MyString& source) const
{
    return compare(source) >= 0;
}

std::size_t MyString::find(const char* source) const
{
    return find(source, 0);
}

std::size_t MyString::find(const std::string& source) const
{
    return find(source, 0);
}

std::size_t MyString::find(const MyString& source) const
{
    return find(source, 0);
}

std::size_t MyString::find(const char* source, int index) const
{
    std::size_t source_size = CStringLength(source);
    return find_data(source, source_size, CheckedValue(index, "index must not be negative"));
}

std::size_t MyString::find(const std::string& source, int index) const
{
    return find_data(source.data(), source.size(),
                     CheckedValue(index, "index must not be negative"));
}

std::size_t MyString::find(const MyString& source, int index) const
{
    return find_data(source.c_str(), source.size(),
                     CheckedValue(index, "index must not be negative"));
}

void MyString::ensure_capacity(std::size_t required_capacity)
{
    if (required_capacity <= capacity_)
    {
        return;
    }

    char* new_data = new char[required_capacity];
    if (size_ != 0)
    {
        std::memcpy(new_data, data_, size_);
    }
    new_data[size_] = '\0';
    delete[] data_;
    data_ = new_data;
    capacity_ = required_capacity;
}

void MyString::assign(const char* source, std::size_t source_size)
{
    if (source == nullptr && source_size != 0)
    {
        throw std::invalid_argument("source must not be null");
    }

    char* source_copy = source_size == 0 ? nullptr : new char[source_size];
    if (source_size != 0)
    {
        std::memcpy(source_copy, source, source_size);
    }

    try
    {
        if (source_size != 0)
        {
            ensure_capacity(source_size + 1);
            std::memcpy(data_, source_copy, source_size);
        }
        size_ = source_size;
        if (data_ != nullptr)
        {
            data_[size_] = '\0';
        }
    }
    catch (...)
    {
        delete[] source_copy;
        throw;
    }
    delete[] source_copy;
}

void MyString::splice(std::size_t index, std::size_t erase_count,
                      const char* source, std::size_t source_size,
                      std::size_t source_index, std::size_t source_count)
{
    if (index > size_)
    {
        throw std::out_of_range("index is out of bounds");
    }
    if (source == nullptr && source_size != 0)
    {
        throw std::invalid_argument("source must not be null");
    }
    CheckSourceRange(source_size, source_index, source_count);
    if (erase_count > size_ - index)
    {
        erase_count = size_ - index;
    }

    char* source_copy = source_count == 0 ? nullptr : new char[source_count];
    if (source_count != 0)
    {
        std::memcpy(source_copy, source + source_index, source_count);
    }

    std::size_t new_size = size_ - erase_count + source_count;
    try
    {
        if (new_size != 0)
        {
            ensure_capacity(new_size + 1);
        }
        std::size_t tail_size = size_ - index - erase_count;
        if (tail_size != 0)
        {
            std::memmove(data_ + index + source_count,
                         data_ + index + erase_count, tail_size);
        }
        if (source_count != 0)
        {
            std::memcpy(data_ + index, source_copy, source_count);
        }
        size_ = new_size;
        if (data_ != nullptr)
        {
            data_[size_] = '\0';
        }
    }
    catch (...)
    {
        delete[] source_copy;
        throw;
    }
    delete[] source_copy;
}

std::size_t MyString::find_data(const char* source, std::size_t source_size,
                                std::size_t index) const
{
    if (index > size_)
    {
        throw std::out_of_range("index is out of bounds");
    }
    if (source_size == 0)
    {
        return index;
    }
    if (source_size > size_ - index)
    {
        return npos;
    }

    for (std::size_t current = index; current <= size_ - source_size; ++current)
    {
        if (std::memcmp(data_ + current, source, source_size) == 0)
        {
            return current;
        }
    }
    return npos;
}

std::ostream& operator<<(std::ostream& stream, const MyString& value)
{
    stream.write(value.c_str(), static_cast<std::streamsize>(value.size()));
    return stream;
}
