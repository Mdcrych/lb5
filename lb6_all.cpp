#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    void insert(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void remove(int data) {
        if (head == nullptr) {
            return;
        }
        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* temp = head;
        Node* prev = nullptr;
        while (temp != nullptr && temp->data != data) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            return;
        }

        prev->next = temp->next;
        delete temp;
    }

    void insertAfter(int key, int data) {
        Node* newNode = new Node(data);
        Node* temp = head;
        while (temp != nullptr && temp->data != key) {
            temp = temp->next;
        }

        if (temp != nullptr) {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    void insertAfterFirst(int key, int data) {
        Node* temp = head;
        while (temp != nullptr && temp->data != key) {
            temp = temp->next;
        }

        if (temp != nullptr) {
            Node* newNode = new Node(data);
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    LinkedList list;

    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(2);
    list.insert(4);

    cout << "List before insertion: ";
    list.display();

    list.insertAfterFirst(2, 5);

    cout << "List after insertion: ";
    list.display();

    return 0;
}
#include <iostream>

template <class T>
class Node {
public:
    T data;
    Node* prev;
    Node* next;

    Node(T data) {
        this->data = data;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

template <class T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void addFront(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void addBack(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (!tail) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void remove(Node<T>* node) {
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
        delete node;
    }

    void printList() {
        Node<T>* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    DoublyLinkedList<int> list;
    int E;
    std::cout<< "Введите E, которое нужно вставить" << std::endl;
    std::cin>> E;
    
    list.addFront(1);
    list.addBack(2);
    list.addBack(3);
    list.addBack(4);
    list.addBack(5);
    list.addBack(7);
    list.addBack(E);
    list.addFront(E);
    

    list.printList();

    return 0;
}

