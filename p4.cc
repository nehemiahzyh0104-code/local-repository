#ifndef SMART_POINTERS_HPP
#define SMART_POINTERS_HPP 1

#include <cstddef>
#include <utility>

template <typename T> class UniquePtr {
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;
};

template <typename T> class SharedPtr {};

#endif // SMART_POINTERS_HPP
