#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <algorithm>
#include <stdexcept>

template<typename T, size_t N>
struct DynamicArray {
  using value_type = T;
  using pointer = value_type *;
  using iterator = pointer;
  using const_iterator = const pointer;
  using reference = value_type &;
  using const_reference = const value_type &;

  //========== elements region ==========//
  value_type elements[N];

  //========== get iterator ==========//
  iterator begin() noexcept { return iterator(elements[0]); }
  iterator end() noexcept { return iterator(elements[N]); }

  const_iterator cbegin() const noexcept { return const_iterator(elements[0]); }
  const_iterator cend() const noexcept { return const_iterator(elements[N]); }

  // TODO:
  // iterator rbegin() noexcept;
  // iterator rend() noexcept;
  // const_iterator crbegin() const noexcept;
  // const_iterator crend() const noexcept;

  //========== visit element ==========//
  reference at(size_t index) noexcept {
    if (index >= N) {
      std::__throw_out_of_range("DynamicArray::at");
    }
    return elements[index];
  }

  const_reference at(size_t index) const noexcept {
    if (index >= N) {
      std::__throw_out_of_range("DynamicArray::at");
    }
    return elements[index];
  }

  reference operator[](size_t index) noexcept { return elements[index]; }
  const_reference operator[](size_t index) const noexcept { return elements[index]; }

  reference front() noexcept { return *begin(); }
  const_reference front() const noexcept { return *begin(); }

  reference back() noexcept { return *end(); }
  const_reference back() const noexcept { return *end(); }


  //========== array size ==========//
  [[nodiscard]] bool empty() const noexcept { return N == 0; }

  [[nodiscard]] size_t size() const noexcept { return N; }

  [[nodiscard]] size_t max_size() const noexcept { return N; }

  //========== write elements ==========//
  void fill(const_reference value) { std::fill_n(begin(), N, value); }

  void swap(reference other) noexcept { std::swap(elements(), other); }

  //========== get array pointer ==========//
  pointer data() noexcept { return elements; }
};

//========== operator== and operator!= ==========//
template<typename T, size_t N>
bool operator==(const DynamicArray<T, N> &lhs, const DynamicArray<T, N> &rhs) {
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, size_t N>
bool operator!=(const DynamicArray<T, N> &lhs, const DynamicArray<T, N> &rhs) {
  return !(lhs == rhs);
}

//========== operator> and operator< ==========//
template<typename T, size_t N>
bool operator<(const DynamicArray<T, N> &lhs, const DynamicArray<T, N> &rhs) {
  return std::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
}

template<typename T, size_t N>
bool operator>(const DynamicArray<T, N> &lhs, const DynamicArray<T, N> &rhs) {
  return !(rhs < lhs);
}

//========== operator<= and operator>= ==========//
template<typename T, size_t N>
bool operator>=(const DynamicArray<T, N> &lhs, const DynamicArray<T, N> &rhs) {
  return !(lhs < rhs);
}

template<typename T, size_t N>
bool operator<=(const DynamicArray<T, N> &lhs, const DynamicArray<T, N> &rhs) {
  return !(lhs > rhs);
}

//========== to_array ==========//
template<typename T, size_t N>
constexpr DynamicArray<std::remove_cv_t<T>, N> to_array(T (&value)[N]) {
  using U = std::remove_cv_t<T>;
  DynamicArray<U, N> result;
  std::copy(value, value + N, result.data());
  return result;
}

template<typename T, size_t N>
constexpr DynamicArray<std::remove_cv_t<T>, N> to_array(T (&&value)[N]) {
  using U = std::remove_cv_t<T>;
  DynamicArray<U, N> result;
  std::move(value, value + N, result.data());
  // std::copy(std::make_move_iterator(std::begin(value)), std::make_move_iterator(value + N), result.data());
  return result;
}

#endif
