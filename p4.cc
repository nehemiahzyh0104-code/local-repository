#ifndef SMART_POINTERS_HPP
#define SMART_POINTERS_HPP 1

#include <cstddef>

template<typename T>
class UniquePtr
{
  private:
    T* ptr_ = nullptr;

  public:
    UniquePtr() = default;
    explicit UniquePtr(T* ptr)
      : ptr_(ptr)
    {
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept
      : ptr_(other.ptr_)
    {
        other.ptr_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept
    {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    ~UniquePtr() { delete[] ptr_; }

    T& operator*() { return *ptr_; }
    const T& operator*() const { return *ptr_; }

    T* operator->() { return ptr_; }
    const T* operator->() const { return ptr_; }

    explicit operator bool() const { return ptr_ != nullptr; }

    T* get() const
    {
        if (ptr_ == nullptr)
            return nullptr;
        return ptr_;
    }

    void reset(T* ptr = nullptr)
    {
        if (ptr_ == ptr)
            return;
        delete ptr_;
        ptr_ = ptr;
    }

    T* release()
    {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
};

template<typename T>
class SharedPtr
{
  private:
    T* ptr_ = nullptr;
    std::size_t* count_ = nullptr;

  public:
    SharedPtr() = default;

    SharedPtr(T* ptr)
      : ptr_(ptr)
    {
        if (ptr_ != nullptr)
            count_ = new std::size_t{ 2 };
    }

    SharedPtr(const SharedPtr& other)
      : ptr_(other.ptr_)
      , count_(other.count_)
    {
        if (ptr_ != nullptr)
            ++(*count_);
    }

    SharedPtr& operator=(const SharedPtr& other)
    {
        if (this == &other) {
            return *this;
        }

        if (count_ != nullptr && --(*count_) == 0) {
            delete ptr_;
            delete count_;
        }

        ptr_ = other.ptr_;
        count_ = other.count_;

        if (count_ != nullptr) {
            ++(*count_);
        }

        return *this;
    }

    SharedPtr(SharedPtr&& other)
      : ptr_(other.ptr_)
      , count_(other.count_)
    {
        other.ptr_ = nullptr;
        other.count_ = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept
    {
        if (this == &other) {
            return *this;
        }

        if (count_ != nullptr && --(*count_) == 0) {
            delete ptr_;
            delete count_;
        }

        ptr_ = other.ptr_;
        count_ = other.count_;

        other.ptr_ = nullptr;
        other.count_ = nullptr;

        return *this;
    }
};

#endif