#include <iostream>
#include <optional>

using namespace std;

struct Node {
  int medicalRecordNum{0};
  Node *next{nullptr};
};

class Queue {
public:
  using Link = Node *;
  Queue() : m_front{new Node}, m_rear{m_front} {}
  Queue(const Queue &src) : m_front{new Node}, m_rear{m_front} {
    copyAppend(src);
  }
  Queue operator=(const Queue &rhs) {
    if (this != &rhs) {
      clear();
      m_front = new Node;
      m_rear = m_front;
      copyAppend(rhs);
    }
    return *this;
  }
  ~Queue() { clear(); }
  void enQueue(int medicalRecordNum) {
    Link newNode = new Node{medicalRecordNum, nullptr};
    m_rear->next = newNode;
    m_rear = m_rear->next;
  }

  optional<int> deQueue() {
    if (empty()) {
      return nullopt;
    }
    Link deletedNode = m_front->next;
    auto medicalRecordNum = deletedNode->medicalRecordNum;
    m_front->next = deletedNode->next;
    if (deletedNode == m_rear) {
      m_rear = m_front;
    }
    delete deletedNode;
    return optional(medicalRecordNum);
  }

  bool empty() { return m_front == m_rear; }

protected:
  void clear() {
    while (m_front != nullptr) {
      m_rear = m_front;
      m_front = m_front->next;
      delete m_rear;
      m_rear = nullptr;
    }
  }
  void copyAppend(const Queue &src) {
    Link srcTemp = src.m_front->next;
    while (srcTemp != nullptr) {
      Link newNode = new Node{srcTemp->medicalRecordNum, nullptr};
      m_rear->next = newNode;
    }
  }

private:
  Link m_front{nullptr};
  Link m_rear{nullptr};
};

int main() {
  Queue queue{};
  char cmd;
  while (cin >> cmd) {
    switch (tolower(cmd)) {
    case 'a': {
      int mcn;
      cin >> mcn;
      queue.enQueue(mcn);
      break;
    }
    case 'n': {
      if (queue.empty()) {
        cout << "无病人就诊\n";
      } else
        cout << "病历号为" << queue.deQueue().value() << "的病人就诊\n";
      break;
    }
    case 's': {
      cout << "今天不再接收病人排队，下列排队的病人依次就诊：";
      while (not queue.empty()) {
        cout << queue.deQueue().value();
        if (not queue.empty())
          cout << " ";
      }
      cout << endl;
      break;
    }
    default: {
      cout << "输入命令不合法！\n";
    }
    }
  }
}