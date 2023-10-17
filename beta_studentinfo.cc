#include <array>
#include <iomanip>
#include <iostream>

using namespace std;

struct Student {
  int id{0};
  string name{};
  array<double, 3> score{0, 0, 0};
  double average{0};

  friend ostream &operator<<(ostream &os, const Student &student) {
    os << student.id << " " << student.name << " " << setprecision(2)
       << student.score[0] << " " << student.score[1] << " " << student.score[2]
       << " " << student.average << '\n';

    return os;
  }
};

struct Node {
  Student student{};
  Node *next{nullptr};
};

class List {
public:
  List() : first{new Node}, last{first} {}

  List(const List &src) : first{new Node}, last{first} { copyFrom(src); }
  List &operator=(const List &rhs) {
    if (this != &rhs) {
      clear();
      first = new Node;
      copyFrom(rhs);
    }
    return *this;
  }
  ~List() { clear(); }

  bool empty() const { return (first == last); }

  void push_back(const Student &student) {
    push_after(student, last);
    if (last == first)
      first->next = last->next;
    last = last->next;
  }

  void push_front(const Student &student) {
    Node *temp = first->next;
    first->next = new Node;
    first->next->next = temp;
    first->next->student = student;
  }
  void decreOrderInsert(const Student &student) {
    Node *temp = first;
    while ((temp->next) != nullptr) {
      if (student.average > temp->next->student.average) {
        push_after(student, temp);
      }
      temp = temp->next;
    }
    if (temp->next == nullptr) {
      push_back(student);
    }
  }

  friend ostream &operator<<(ostream &os, const List &list) {
    Node *temp = list.first;
    while ((temp = temp->next) != nullptr) {
      os << temp->student;
    }
    return os;
  }

protected:
  void clear() {
    while (not empty()) {
      Node *temp = first->next;
      first->next = temp->next;
      delete temp;
    }
    delete first;
  }

  void copyFrom(const List &src) {
    Node *srcTemp = src.first;
    Node *desTemp = first;
    while ((srcTemp = srcTemp->next) != nullptr) {
      desTemp->next = new Node;
      desTemp->student = srcTemp->student;
    }
    last = desTemp;
  }

  void push_after(const Student &student, Node *after) {
    Node *temp = after->next;
    after->next = new Node;
    after->next->student = student;
    after->next->next = temp;
  }

private:
  Node *first{nullptr};
  Node *last{nullptr};
};

int main() {

  int numStudents{};
  cin >> numStudents;
  List students;

  for (int i = 0; i < numStudents; i++) {
    Student student{};
    cin >> student.id >> student.name >> student.score[0] >> student.score[1] >>
        student.score[2];
    for (const auto &score : student.score) {
      student.average += score;
    }
    student.average /= 3;

    students.decreOrderInsert(student);
  }

  cout << students;
}