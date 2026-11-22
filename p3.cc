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

    Dynarray(const Dynarray& inpt)
      : Dynarray(inpt.size_)
    {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = inpt.data_[i];
        }
    }

    Dynarray& operator=(const Dynarray& inpt)
    {
        if (this != &inpt) {
            Dynarray copy(inpt);
            *this = std::move(copy);
        }
        return *this;
    }

    Dynarray(Dynarray&& inpt) noexcept
      : size_(inpt.size_)
      , data_(inpt.data_)
    {
        inpt.size_ = 0;
        inpt.data_ = nullptr;
    }

    Dynarray& operator=(Dynarray&& inpt) noexcept
    {
        if (this != &inpt) {
            delete[] data_;

            size_ = inpt.size_;
            data_ = inpt.data_;

            inpt.size_ = 0;
            inpt.data_ = nullptr;
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

    bool operator<(const Dynarray& inpt) const
    {
        return std::lexicographical_compare(
            data_, data_ + size(), inpt.data_, inpt.data_ + inpt.size());
    }

    bool operator==(const Dynarray& inpt) const
    {
        return std::equal(data_, data_ + size(), inpt.data_, inpt.data_ + inpt.size());
    }

    bool operator<=(const Dynarray& inpt) const { return !(inpt < *this); }

    bool operator!=(const Dynarray& inpt) const { return !(*this == inpt); }

    bool operator>(const Dynarray& inpt) const { return !(*this <= inpt); }

    bool operator>=(const Dynarray& inpt) const { return !(*this < inpt); }
};

std::ostream&
operator<<(std::ostream& out, const Dynarray& inpt)
{
    out << '[';

    for (Dynarray::size_type i = 0; i < inpt.size(); i++) {
        if (i > 0)
            out << ", ";

        out << inpt[i];
    }

    out << ']';

    return out;
}

#endif