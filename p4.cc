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

    UniquePtr(UniquePtr&& inpt) noexcept
      : ptr_(inpt.ptr_)
    {
        inpt.ptr_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& inpt) noexcept
    {
        if (this != &inpt) {
            reset(inpt.release());
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

    void release_ownership() noexcept
    {
        T* ptr = std::exchange(ptr_, nullptr);
        std::size_t* count = std::exchange(count_, nullptr);
        if (count != nullptr && --(*count) == 0) {
            delete ptr;
            delete count;
        }
    }

  public:
    SharedPtr() = default;

    ~SharedPtr() { release_ownership(); }

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

    SharedPtr(const SharedPtr& inpt)
      : ptr_(inpt.ptr_)
      , count_(inpt.count_)
    {
        if (count_ != nullptr)
            ++(*count_);
    }

    SharedPtr& operator=(const SharedPtr& inpt)
    {
        if (this == &inpt) {
            return *this;
        }
        SharedPtr copy(inpt);
        return *this = std::move(copy);
    }

    SharedPtr(SharedPtr&& inpt) noexcept
      : ptr_(inpt.ptr_)
      , count_(inpt.count_)
    {
        inpt.ptr_ = nullptr;
        inpt.count_ = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& inpt) noexcept
    {
        if (this != &inpt) {
            SharedPtr replacement(std::move(inpt));
            release_ownership();
            std::swap(ptr_, replacement.ptr_);
            std::swap(count_, replacement.count_);
        }
        return *this;
    }

    /*--------------------------------------------------------------*/

    T& operator*() { return *ptr_; }
    const T& operator*() const { return *ptr_; }

    T* operator->() { return ptr_; }
    const T* operator->() const { return ptr_; }

    explicit operator bool() const { return ptr_ != nullptr; }

    T* get() const { return ptr_; }

    std::size_t use_count() const { return count_ == nullptr ? 0 : *count_; }
};

#endif
