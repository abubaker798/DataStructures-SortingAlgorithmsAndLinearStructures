#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

class Student {
public:
    string name;
    int id;
    float gpa;

    Student(string n, int i, float g) : name(std::move(n)), id(i), gpa(g) {}

    bool operator<(const Student& other) const {
        return name < other.name;
    }

    void print() const {
        cout << name << " " << id << " " << gpa << endl;
    }
};

vector<Student> readStudents(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        exit(1);
    }

    int numStudents;
    file >> numStudents;

    vector<Student> students;
    string name;
    int id;
    float gpa;
    for (int i = 0; i < numStudents; ++i) {
        file.ignore();
        getline(file, name);
        file >> id >> gpa;
        students.emplace_back(name, id, gpa);
    }

    file.close();
    return students;
}

void printStudents(const vector<Student>& students) {
    for (const auto& student : students) {
        student.print();
    }
}

void writeToFile(const char * str, const vector<Student> & vector, system_clock::time_point start, system_clock::time_point end, const char * text) {
    ofstream file(text);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    file << "Algorithm: " << str << endl;
    file << "Running Time: " << duration_cast<milliseconds>(end - start).count() << " milliseconds" << endl;

    file << "Sorted Student Elements:" << endl;
    for (const auto& student : vector) {
        file << student.name << endl;
        file << student.id << endl;
        file << student.gpa << endl;
    }

    file.close();
}

void insertionSortByName(vector<Student>& arr) {
    const int n = arr.size();
    for (int i = 1; i < n; ++i) {
        Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSortByGPA(vector<Student>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].gpa < arr[minIndex].gpa) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}


//=====================< 2 >>>>>>>>>>>>>>>>>>>
// Single Linked List (SLL)
class SLLNode {
public:
    int data;
    SLLNode* next;

    explicit SLLNode(int element);
};


SLLNode::SLLNode(const int element): data(element), next(nullptr) {}

class SLL {
private:
    SLLNode* head;
    int size;

public:
    SLL() : head(nullptr), size(0) {}

    void insertAtHead(int element);

    void print() const {
        const SLLNode* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

auto SLL::insertAtHead(const int element) -> void {
    auto* newNode = new SLLNode(element);
    newNode->next = head;
    head = newNode;
    size++;
}


class DLLNode {
public:
    int data;
    DLLNode* prev;
    DLLNode* next;

    explicit DLLNode(const int element) : data(element), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DLLNode* head;
    DLLNode* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void insertAtHead(int element) {
        const auto newNode = new DLLNode(element);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void insertAtTail(const int element) {
        auto* newNode = new DLLNode(element);
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void print() const {
        const DLLNode *current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

};

class CLLNode {
public:
    int data;
    CLLNode* next;

    explicit CLLNode(const int element) : data(element), next(nullptr) {}
};


// Circular Linked List
class CircularLinkedList {
private:
    CLLNode* head;
    int size;

public:
    CircularLinkedList() : head(nullptr), size(0) {}

    void insertAtHead(const int element) {
        auto* newNode = new CLLNode(element);
        if (head == nullptr) {
            head = newNode;
            head->next = head;
        } else {
            CLLNode* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            newNode->next = head;
            head = newNode;
            temp->next = head;
        }
        size++;
    }

    void insertAtTail(int element);

    void print() const {
        if (head == nullptr) {
            cout << "Circular Linked List is empty." << endl;
            return;
        }
        CLLNode *current = head;
        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != head);
        cout << endl;
    }
};

void CircularLinkedList::insertAtTail(const int element) {
    auto* newNode = new CLLNode(element);
    if (head == nullptr) {
        head = newNode;
        head->next = head;
    } else {
        CLLNode* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }
    size++;
}


// stack
class Stack {
private:
    vector<int> elements;

public:
    auto push(int element) -> void ;

    void pop() {
        if (!isEmpty()) {
            elements.pop_back();
        }
    }

    [[nodiscard]] int top() const {
        if (!isEmpty()) {
            return elements.back();
        }
        return NULL;
    }

    [[nodiscard]] bool isEmpty() const{
        return elements.empty();
    }

    [[nodiscard]] int stackSize() const {
        return elements.size();
    }

    void clear() {
        elements.clear();
    }

    void print() const {
        for (int i = elements.size() - 1; i >= 0; --i) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }

};


void Stack::push(int const element) {
    elements.push_back(element);
}

// Queue
class Queue {
private:
    vector<int> elements;

public:
    void enqueue(const int element) {
        elements.push_back(element);
    }

    void dequeue() {
        if (!isEmpty()) {
            elements.erase(elements.begin());
        }
    }

    [[nodiscard]] int first() const {
        if (!isEmpty()) {
            return elements.front();
        }
        return NULL;
    }

    [[nodiscard]] bool isEmpty() const {
        return elements.empty();
    }

    [[nodiscard]] auto queueSize() const -> int {
        return elements.size();
    }

    void clear() {
        elements.clear();
    }

    void print() const {
        for (const int element : elements) {
            cout << element << " ";
        }
        cout << endl;
    }
};


int main() {
    vector<Student> students = readStudents("students.txt");

    vector<Student> studentsByName = students;

    system_clock::time_point start = system_clock::now();
    insertionSortByName(studentsByName);
    auto end = high_resolution_clock::now();
    writeToFile("Insertion Sort", studentsByName, start, end, "SortedByName.txt");

    vector<Student> studentsByGPA = students;
    start = high_resolution_clock::now();
    selectionSortByGPA(studentsByGPA);
    end = high_resolution_clock::now();
    writeToFile("Selection Sort", studentsByGPA, start, end, "SortedByGPA.txt");


    //==================< Single Linked List >================
    SLL sll;
    cout << "\n=================< Single Linked List >=========\n";
    sll.insertAtHead(5);
    sll.insertAtHead(10);
    sll.insertAtHead(2);
    sll.insertAtHead(23);
    sll.insertAtHead(15);
    sll.insertAtHead(55);
    sll.print();


 //=================< Doubly Linked List >===========
    cout << "\n================< Double Linked List <====================\n";
    DoublyLinkedList dll;
    dll.insertAtHead(5);
    dll.insertAtHead(10);
    dll.insertAtTail(15);
    cout << "Doubly Linked List contents: ";
    dll.print();

    //=================< Circular Linked List >=============="
    cout << "\n=================< Circular Linked List >==============\n";
    CircularLinkedList cll;
    cll.insertAtHead(68);
    cll.insertAtHead(16);
    cll.insertAtTail(25);
    cll.insertAtHead(52);
    cll.insertAtHead(100);
    cll.insertAtTail(75);
    cout << "Circular Linked List contents: ";
    cll.print();


  //=================< Stack >================;
    cout << "\n==================< Stack >=================\n";
    Stack stack;
    cout << "Stack operations:" << endl;
    stack.push(32);
    stack.push(45);
    stack.push(21);
    stack.push(81);
    stack.push(63);
    stack.push(14);
    stack.print();
    cout << "Stack size: " << stack.stackSize() << endl;
    cout << "Popping elements from the stack: ";
    while (!stack.isEmpty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << endl;
    cout << "Stack size after popping: " << stack.stackSize() << endl << endl;


    //=================< Queue >================;
    cout << "\n==================< Queue >=================\n";
    Queue queue;
    cout << "Queue operations:" << endl;
    cout << "Enqueueing elements into the queue: ";
    queue.enqueue(25);
    queue.enqueue(13);
    queue.enqueue(11);
    queue.enqueue(51);
    queue.enqueue(18);
    queue.enqueue(19);
    queue.print();

    cout << "Queue size: " << queue.queueSize() << endl;
    cout << "Dequeuing elements from the queue: ";
    while (!queue.isEmpty()) {
        cout << queue.first() << " ";
        queue.dequeue();
    }
    cout << endl;

    cout << "Queue size after dequeuing: " << queue.queueSize() << endl;

    return 0;
}