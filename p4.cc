#ifndef SMART_POINTERS_HPP
#define SMART_POINTERS_HPP 1

#include <cstddef>
#include <utility>

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
            reset(other.release());
        }
        return *this;
    }

    ~UniquePtr() { delete ptr_; }

    T& operator*() { return *ptr_; }
    const T& operator*() const { return *ptr_; }

    T* operator->() { return ptr_; }
    const T* operator->() const { return ptr_; }

    explicit operator bool() const { return ptr_ != nullptr; }

    T* get() const { return ptr_; }

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

    ~SharedPtr()
    {
        if (count_ != nullptr && --(*count_) == 0) {
            delete ptr_;
            delete count_;
        }
    }

    SharedPtr(T* ptr)
      : ptr_(ptr)
    {
        if (ptr_ != nullptr) {
            try {
                count_ = new std::size_t{ 1 };
            } catch (...) {
                delete ptr_;
                throw;
            }
        }
    }

    SharedPtr(const SharedPtr& other)
      : ptr_(other.ptr_)
      , count_(other.count_)
    {
        if (count_ != nullptr)
            ++(*count_);
    }

    SharedPtr& operator=(const SharedPtr& other)
    {
        SharedPtr copy(other);
        return *this = std::move(copy);
    }

    SharedPtr(SharedPtr&& other) noexcept
      : ptr_(other.ptr_)
      , count_(other.count_)
    {
        other.ptr_ = nullptr;
        other.count_ = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept
    {
        if (this != &other) {
            SharedPtr replacement(std::move(other));
            std::swap(ptr_, replacement.ptr_);
            std::swap(count_, replacement.count_);
        }
        return *this;
    }

    T& operator*() { return *ptr_; }
    const T& operator*() const { return *ptr_; }

    T* operator->() { return ptr_; }
    const T* operator->() const { return ptr_; }

    explicit operator bool() const { return ptr_ != nullptr; }

    T* get() const { return ptr_; }

    std::size_t use_count() const { return count_ == nullptr ? 0 : *count_; }
};

#endif
