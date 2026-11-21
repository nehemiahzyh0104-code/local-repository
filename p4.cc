#ifndef SMART_POINTERS_HPP
#define SMART_POINTERS_HPP 1

#include <cstddef>
#include <utility>

// Problem 4 (Smart Pointers): implement UniquePtr<T> and SharedPtr<T>.
// See the handout for the full requirements:
//
// UniquePtr<T>: exclusive ownership.
//   - default ctor (owns nothing), ctor from T*, destructor deletes
//   - copy ctor/assignment = delete; move ctor/assignment noexcept,
//     self-assignment safe, source becomes "null"
//   - *p, *cp (const), p->, explicit operator bool, get()
//   - reset(T* = nullptr), release()
//
// SharedPtr<T>: shared ownership via reference counting.
//   - default ctor (owns nothing), ctor from T* (count starts at 1)
//   - copy ctor/assignment increment the counter; copy-assignment must be
//     self-assignment safe (increment before decrement!)
//   - move ctor/assignment steal the pointer (noexcept), source becomes empty
//   - destructor decrements; destroys the object exactly once at zero
//   - *p, p->, explicit operator bool, get(), use_count()
//
// Do NOT include <memory>.

template <typename T>
class UniquePtr {
  // TODO: implement (see the handout).
};

template <typename T>
class SharedPtr {
  // TODO: implement (see the handout).
  // Hint: a control block holding { T *ptr; std::size_t count; } works well.
};

#endif // SMART_POINTERS_HPP
