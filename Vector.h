#ifndef VECTOR_H
#define VECTOR_H

template <typename Object> class Vector {
public:
  explicit Vector(int size = 0){};
  Vector(const Vector &){};
  Vector(Vector &&){};
  Vector &operator=(const Vector &){};
  Vector &operator=(Vector &&){};
  ~Vector(){};

  void resize(int){};
  void reserve(int){};
  void shrink_to_fit(){};

  bool empty() const {};
  int size() const {};
  int capacity() const {};

  void insert(const Object&, int index = m_size-1){};
  void remove(){};

  using Rank = int;

protected:
  int m_size{0};
  int m_capacity{0};
  Object *m_objects{nullptr};
};

#endif // VECTOR_H
