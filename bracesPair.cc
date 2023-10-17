#include <algorithm>
#include <array>
#include <iostream>
#include <optional>
#include <string>

class Stack {
  public:
    Stack(size_t capacity = DEFAULT_CAPACITY)
        : m_stack{new char[capacity]}, m_size{0}, m_capacity{capacity} {}
    Stack(const Stack& src) : m_size{src.m_size}, m_capacity{src.m_capacity} {
        expand(m_capacity);
        for (size_t i{0}; i < m_size; i++) {
            m_stack[i] = src.m_stack[i];
        }
    }
    Stack& operator=(const Stack& rhs) {
        if (this == &rhs)
            return *this;
        m_size = rhs.m_size;
        expand(rhs.m_capacity);
        for (size_t i{0}; i < m_size; i++) {
            m_stack[i] = rhs.m_stack[i];
        }
        return *this;
    }
    ~Stack() {
        delete[] m_stack;
    }

    void push(char chr) {
        expand(m_size + 1);
        m_stack[m_size] = chr;
        m_size += 1;
    }

    std::optional<char> pop() {
        if (empty())
            return std::nullopt;
        return m_stack[m_size -= 1];
    }

    std::optional<char> top() const {
        if (empty())
            return std::nullopt;
        return m_stack[m_size - 1];
    }

    bool empty() const {
        return (m_size == 0);
    }
    friend std::ostream& operator<<(std::ostream& out, const Stack& stack) {
        for (size_t i = 0; i < stack.m_size; i++) {
            out << static_cast<char>(stack.m_stack[i]) << " ";
        }
        return out;
    }

  protected:
    void expand(size_t required_size) {
        if (required_size > m_capacity) {
            m_capacity = std::max(m_capacity >> 1, required_size);
            auto old_statck = m_stack;
            m_stack = new char[m_capacity];
            for (size_t i = 0; i < m_size; i++) {
                m_stack[i] = old_statck[i];
            }
            delete[] old_statck;
        }
    }

    constexpr static size_t DEFAULT_CAPACITY{10};

  private:
    char* m_stack{nullptr};
    size_t m_size{};
    size_t m_capacity{};
};

void getSharp(const Stack& stack) {
    if (stack.top().has_value())
        std::cout << "不匹配" << std::endl;
    else
        std::cout << "匹配" << std::endl;
}

int main() {
    Stack stack;
    constexpr std::array pairs{
        '{', '}', '(', ')', '[', ']',
    };
    std::string braces;
    std::getline(std::cin, braces);

    for (auto iter{braces.cbegin()}; iter != braces.cend(); iter++) {
        if (*iter == '#') {
            getSharp(stack);
            return 0;
        }
        for (size_t i = 1; i < pairs.size(); i += 2) {
            if (*iter == pairs[i] and (pairs[i - 1] != stack.pop().value_or(' '))) {
                std::cout << "不匹配" << std::endl;
                return 0;
            }
        }
        for (size_t i = 0; i < pairs.size(); i += 2) {
            if (*iter == pairs[i]) {
                stack.push(*iter);
                break;
            }
        }
    }
}