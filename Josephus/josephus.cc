#include <iostream>
#include <list>
#include <string>

using namespace std;

struct Man {
  string name{};
  int id{};
  string gender{};
  int age{};
  string classNum{};
  string healthStatus{};
  friend ostream &operator<<(ostream &out, const Man &man) {
    out << man.name << " " << man.id << " " << man.gender << " " << man.age
        << " " << man.classNum << " " << man.healthStatus << "\n";
    return out;
  }
};

int main() {
  int numStudents, numStep;
  cin >> numStudents >> numStep;
  list<Man> students;

  for (int i = 0; i < numStudents; i++) {
    Man man;
    cin >> man.name >> man.id >> man.gender >> man.age >> man.classNum >>
        man.healthStatus;
    students.push_back(man);
  }
  auto iter = students.begin();
  while (not students.empty()) {
    for (int i = 1; i < numStep; i++) {
      if ((++iter) == students.end())
        iter = students.begin();
    }
    cout << *iter;
    iter = students.erase(iter);
    if (iter == students.end())
      iter = students.begin();
  }
}