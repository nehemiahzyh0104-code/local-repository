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
};

#endif
#endif
