
template <typename T, size_t n_> class array {
  T data[n];
  constexpr size_t num_elems = n_;

public:
  array() {
    for (size_t i = 0; i < num_elems; ++i) {
      data[i] = T();
    }
  }

  T &operator[](size_t i) { return data[i]; }

  T &at(size_t i) {
    if (i > num_elems) {
      throw std::out_of_range("");
    }
    return data[i];
  }

  T *begin() { return data; }
  T *end() { return data + num_elems; }
};
