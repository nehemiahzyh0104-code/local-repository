#ifndef DYNARRAY_HPP
#define DYNARRAY_HPP 1

#include <cstddef>
#include <stdexcept>

#ifndef P2_CC_INCLUDED
#define P2_CC_INCLUDED

#include <cstddef>
#include <stdexcept>
#include <utility>

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
};

#endif
#endif
