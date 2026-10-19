#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <cstddef>
#include <iosfwd>
#include <iterator>
#include <stdexcept>
#include <string>

class MyStringConversionError : public std::invalid_argument
{
public:
    explicit MyStringConversionError(const char* message);
};

class MyString
{
public:
    using iterator = char*;
    using const_iterator = const char*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static const std::size_t npos;

    MyString();
    MyString(const char* source);
    MyString(const std::string& source);
    MyString(const MyString& source);
    MyString(MyString&& source) noexcept;
    MyString(int value);
    MyString(double value);
    MyString(const char* source, int count);
    MyString(const std::string& source, int count);
    MyString(const MyString& source, int count);
    MyString(int count, char ch);
    ~MyString();

    MyString& operator=(const char* source);
    MyString& operator=(const std::string& source);
    MyString& operator=(const MyString& source);
    MyString& operator=(MyString&& source) noexcept;
    MyString& operator=(char ch);

    void clear();
    void shrink_to_fit();

    const char* c_str() const;
    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator rcbegin() const noexcept;
    const_reverse_iterator rcend() const noexcept;

    MyString& insert(int index, int count, char ch);
    MyString& insert(int index, const char* source);
    MyString& insert(int index, const std::string& source);
    MyString& insert(int index, const MyString& source);
    MyString& insert(int index, const char* source, int count);
    MyString& insert(int index, const std::string& source, int count);
    MyString& insert(int index, const MyString& source, int count);
    MyString& insert(int index, const char* source, int source_index, int count);
    MyString& insert(int index, const std::string& source, int source_index, int count);
    MyString& insert(int index, const MyString& source, int source_index, int count);

    MyString& insert(iterator position, int count, char ch);
    MyString& insert(iterator position, const char* source);
    MyString& insert(iterator position, const std::string& source);
    MyString& insert(iterator position, const MyString& source);
    MyString& insert(iterator position, const char* source, int count);
    MyString& insert(iterator position, const std::string& source, int count);
    MyString& insert(iterator position, const MyString& source, int count);
    MyString& insert(iterator position, const char* source, int source_index, int count);
    MyString& insert(iterator position, const std::string& source,
                     int source_index, int count);
    MyString& insert(iterator position, const MyString& source,
                     int source_index, int count);

    MyString& append(int count, char ch);
    MyString& append(const char* source);
    MyString& append(const std::string& source);
    MyString& append(const MyString& source);
    MyString& append(const char* source, int count);
    MyString& append(const std::string& source, int count);
    MyString& append(const MyString& source, int count);
    MyString& append(const char* source, int source_index, int count);
    MyString& append(const std::string& source, int source_index, int count);
    MyString& append(const MyString& source, int source_index, int count);

    MyString& erase(int index, int count);
    MyString& erase(iterator position, int count);

    MyString& replace(int index, int count, const char* source);
    MyString& replace(int index, int count, const std::string& source);
    MyString& replace(int index, int count, const MyString& source);
    MyString& replace(int index, int count, const char* source, int source_count);
    MyString& replace(int index, int count, const std::string& source, int source_count);
    MyString& replace(int index, int count, const MyString& source, int source_count);
    MyString& replace(int index, int count, const char* source, int source_index, int source_count);
    MyString& replace(int index, int count, const std::string& source, int source_index, int source_count);
    MyString& replace(int index, int count, const MyString& source, int source_index, int source_count);

    MyString& replace(iterator position, int count, const char* source);
    MyString& replace(iterator position, int count, const std::string& source);
    MyString& replace(iterator position, int count, const MyString& source);
    MyString& replace(iterator position, int count, const char* source, int source_count);
    MyString& replace(iterator position, int count, const std::string& source,
                      int source_count);
    MyString& replace(iterator position, int count, const MyString& source,
                      int source_count);
    MyString& replace(iterator position, int count, const char* source,
                      int source_index, int source_count);
    MyString& replace(iterator position, int count, const std::string& source,
                      int source_index, int source_count);
    MyString& replace(iterator position, int count, const MyString& source,
                      int source_index, int source_count);

    MyString substr(int index) const;
    MyString substr(int index, int count) const;
    MyString substr(const_iterator position) const;
    MyString substr(const_iterator position, int count) const;

    MyString operator+(const char* source) const;
    MyString operator+(const std::string& source) const;
    MyString operator+(const MyString& source) const;
    MyString& operator+=(const char* source);
    MyString& operator+=(const std::string& source);
    MyString& operator+=(const MyString& source);

    char& operator[](int index);
    const char& operator[](int index) const;
    char& at(int index);
    const char& at(int index) const;

    int to_int() const;
    float to_float() const;

    int compare(const MyString& source) const;
    bool operator==(const MyString& source) const;
    bool operator!=(const MyString& source) const;
    bool operator<(const MyString& source) const;
    bool operator<=(const MyString& source) const;
    bool operator>(const MyString& source) const;
    bool operator>=(const MyString& source) const;

    std::size_t find(const char* source) const;
    std::size_t find(const std::string& source) const;
    std::size_t find(const MyString& source) const;
    std::size_t find(const char* source, int index) const;
    std::size_t find(const std::string& source, int index) const;
    std::size_t find(const MyString& source, int index) const;
    std::size_t find(const char* source, const_iterator position) const;
    std::size_t find(const std::string& source, const_iterator position) const;
    std::size_t find(const MyString& source, const_iterator position) const;

private:
    char* data_;
    std::size_t size_;
    std::size_t capacity_;

    void ensure_capacity(std::size_t required_capacity);
    void assign(const char* source, std::size_t source_size);
    std::size_t iterator_index(const_iterator position) const;
    std::size_t find_data(const char* source, std::size_t source_size,
                          std::size_t index) const;
};

std::ostream& operator<<(std::ostream& stream, const MyString& value);
std::ofstream& operator<<(std::ofstream& stream, const MyString& value);
std::ifstream& operator>>(std::ifstream& stream, MyString& value);

#endif // _MYSTRING_H_
