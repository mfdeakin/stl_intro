
template <typename Key, typename Value> class map {
  RedBlackTree<std::pair<Key, Value>> data;

public:
  map();
  size_t size() const noexcept;
  Value &at(const Key &) const;
  Value &operator[](const Key &) noexcept;
};
