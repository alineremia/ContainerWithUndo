#include <iostream>
#include <list>
#include <stack>

enum Action { INSERT, DELETE };

template <typename T>
class ListWithUndo {
private:
    std::list<T> data;
    std::stack<std::pair<Action, T>> actions;

public:
    void insert(const T& value) {
        data.push_back(value);
        actions.push(std::make_pair(INSERT, value));
    }

    void remove() {
        if (!data.empty()) {
            T lastElement = data.back();
            data.pop_back();
            actions.push(std::make_pair(DELETE, lastElement));
        } else {
            std::cout << "List is empty, nothing to delete." << std::endl;
        }
    }

    void undo() {
        if (!actions.empty()) {
            auto lastAction = actions.top();
            actions.pop();
            if (lastAction.first == INSERT) {
                data.pop_back();
                std::cout << "Undoing insert of element: " << lastAction.second << std::endl;
            } else if (lastAction.first == DELETE) {
                data.push_back(lastAction.second);
                std::cout << "Undoing delete of element: " << lastAction.second << std::endl;
            }
        } else {
            std::cout << "No actions to undo." << std::endl;
        }
    }

    void display() {
        std::cout << "List Contents: ";
        for (const auto& element : data) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    ListWithUndo<int> myList;

    // Insert some elements
    myList.insert(10);
    myList.insert(20);
    myList.insert(30);
    myList.display();
    
    // Undo the last action
    myList.undo();
    myList.display();

    // Remove an element
    myList.remove();
    myList.display();

    // Undo the last action
    myList.undo();
    myList.display();

    return 0;
}
