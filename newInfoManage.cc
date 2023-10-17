#include <array>
#include <iomanip>
#include <iostream>

using namespace std;

struct Student {
  int id{};
  string name{};
  array<double, 3> score{};
  double average{};

  friend ostream &operator<<(ostream &os, const Student &student) {
    os << student.id << " " << student.name << " " << fixed << setprecision(2)
       << student.score[0] << " " << student.score[1] << " " << student.score[2]
       << " " << student.average;

    return os;
  }
};

struct Node {
  Student student{};
  Node *next{};
};

class List {
public:
  using Link = Node *;
  List() : first{new Node} {}

  List(const List &src) : first{new Node} { copyFrom(src); }
  List &operator=(const List &rhs) {
    if (this != &rhs) {
      clearStudent();
      copyFrom(rhs);
    }
    return *this;
  }
  ~List() {
    clearStudent();
    delete first;
  }

  bool empty() const { return (first->next == nullptr); }

  void decreOrderInsert(const Student &student) {
    Link current_front = first;
    // first
    if (current_front->next == nullptr) {
      Link newNode = new Node;
      newNode->student = student;
      newNode->next = nullptr;
      first->next = newNode;
      return;
    }
    // middle
    while ((current_front->next) != nullptr) {
      if (student.average >= (current_front->next->student).average) {
        Link current = current_front->next;
        Link newNode = new Node;
        newNode->student = student;
        current_front->next = newNode;
        newNode->next = current;
        return;
      }
      current_front = current_front->next;
    }
    // last
    Link newNode = new Node;
    newNode->student = student;
    newNode->next = nullptr;
    current_front->next = newNode;
  }

  friend ostream &operator<<(ostream &os, const List &list) {
    Link temp = list.first;
    int i = 1;
    while ((temp = temp->next) != nullptr) {
      os << temp->student << " " << i++ << '\n';
    }
    return os;
  }

protected:
  void clearStudent() {
    while (first->next != nullptr) {
      Link temp = first->next;
      first->next = temp->next;
      delete temp;
    }
  }

  void copyFrom(const List &src) {
    Link srcTemp = src.first;
    Link desTemp = first;
    while ((srcTemp = srcTemp->next) != nullptr) {
      desTemp->next = new Node;
      desTemp = desTemp->next;
      desTemp->student = srcTemp->student;
    }
    desTemp->next = nullptr;
  }

private:
  Link first{};
};

int main() {
  int numStudents{};
  cin >> numStudents;
  List students{};

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
