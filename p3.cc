#include <ostream>
#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <algorithm>
#include <cstddef>
#include <ostream>
#include <stdexcept>

class Dynarray
{
  private:
    std::size_t size_ = 0;
    int* data_ = nullptr;

  public:
    Dynarray() = default;

    explicit Dynarray(std::size_t n)
      : size_(n)
      , data_(n == 0 ? nullptr : new int[n]{})
    {
    }

    Dynarray(std::size_t n, int x)
      : Dynarray(n)
    {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = x;
        }
    }

    Dynarray(const int* begin, const int* end)
      : Dynarray(begin == end ? 0 : static_cast<std::size_t>(end - begin))
    {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = begin[i];
        }
    }

    ~Dynarray() { delete[] data_; }

    Dynarray(const Dynarray& other)
      : Dynarray(other.size_)
    {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Dynarray& operator=(const Dynarray& other)
    {
        if (this != &other) {
            Dynarray copy(other);
            *this = std::move(copy);
        }
        return *this;
    }

    Dynarray(Dynarray&& other) noexcept
      : size_(other.size_)
      , data_(other.data_)
    {
        other.size_ = 0;
        other.data_ = nullptr;
    }

    Dynarray& operator=(Dynarray&& other) noexcept
    {
        if (this != &other) {
            delete[] data_;

            size_ = other.size_;
            data_ = other.data_;

            other.size_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    std::size_t size() const { return size_; }

    bool empty() const { return size_ == 0; }

    int& at(std::size_t i)
    {
        if (i >= size_) {
            throw std::out_of_range{ "Dynarray index out of range!" };
        }
        return data_[i];
    }

    const int& at(std::size_t i) const
    {
        if (i >= size_) {
            throw std::out_of_range{ "Dynarray index out of range!" };
        }
        return data_[i];
    }

    /*----------------------------------------------------------------*/

    using size_type = std::size_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using const_pointer = const int*;
    using const_reference = const int&;

    int& operator[](std::size_t i) { return data_[i]; }

    const int& operator[](std::size_t i) const { return data_[i]; }

    /*------------------------------------------*/

    bool operator<(const Dynarray& other) const
    {
        if (empty() || other.empty())
            return empty() && !other.empty();

        return std::lexicographical_compare(
            data_, data_ + size(), other.data_, other.data_ + other.size());
    }

    bool operator==(const Dynarray& other) const
    {
        if (size() != other.size()) {
            return false;
        }
        return empty() || std::equal(data_, data_ + size(), other.data_);
    }

    bool operator!=(const Dynarray& other) const { return !(*this == other); }

    bool operator<=(const Dynarray& other) const { return *this == other || *this < other; }

    bool operator>(const Dynarray& other) const { return !(*this <= other); }

    bool operator>=(const Dynarray& other) const { return !(*this < other); }
};

std::ostream&
operator<<(std::ostream& out, const Dynarray& inpt)
{
    out << '[';

    for (Dynarray::size_type i = 0; i < inpt.size(); i++) {
        if (i > 0)
            out << ',';

        out << inpt[i];
    }

    out << ']';

    return out;
}

#endif