#include <memory>
#include <stdexcept>

template <typename T> class vector {
  std::unique_ptr<T[]> array_;
  size_t array_size_;
  size_t inserted_;

public:
  vector() : array_(nullptr), array_size_(0), inserted_(0) {}

  explicit vector(const size_t count, const T &value = T()) : vector() {
    for (size_t i = 0; i < count; ++i) {
      push_back(value);
    }
  }

  vector(const vector &src) : vector() { *this = src; }

  ~vector() { clear(); }

  size_t size() const { return inserted_; }

  size_t capacity() const { return array_size_; }

  vector &operator=(const vector &src) {
    clear();
    array_size_ = src.array_size_;
    inserted_ = src.inserted_;
    array_ = std::make_unique<T[]>(array_size_);
    for (size_t i = 0; i < inserted_; ++i) {
      array_[i] = src[i];
    }
    return *this;
  }

  T &operator[](const size_t i) const { return array_[i]; }

  T &at(const size_t i) const {
    if (i > array_size_) {
      throw std::out_of_range("");
    }
    return array_[i];
  }

  void reserve(const size_t new_size) {
    if (new_size > array_size_) {
      auto new_array = std::make_unique<T[]>(new_size);
      for (size_t i = 0; i < array_size_; ++i) {
        new_array[i] = array_[i];
        array_[i].~T();
      }
      array_ = std::move(new_array);
      array_size_ = new_size;
    }
  }

  void push_back(const T &value) {
    if (inserted_ >= array_size_) {
      reserve(array_size_ * 2 + 1);
    }
    array_[inserted_] = value;
    inserted_++;
  }

  void clear() {
    for (size_t i = 0; i < inserted_; ++i) {
      array_[i].~T();
    }
    inserted_ = 0;
  }

  using iterator = T *;
  iterator begin() const { return array_.get(); }
  iterator end() const { return array_.get() + inserted_; }

  iterator insert(iterator pos, const T &value);

  vector &operator=(vector &&src) {
    clear();
    array_ = std::move(src.array_);
    array_size_ = src.array_size_;
    inserted_ = src.inserted_;
    src.array_size_ = 0;
    src.inserted_ = 0;
    return *this;
  }

  vector(vector &&src) : vector() { *this = std::move(src); }
};
