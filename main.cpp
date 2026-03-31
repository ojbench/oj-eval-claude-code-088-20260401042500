#include <iostream>
#include <cstdlib>

using namespace std;

// Node structure for linked list
struct Node {
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

// Linked list class for simulation
class LinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        if (head == nullptr) return;

        // Break the circular link first
        if (tail != nullptr) {
            tail->next = nullptr;
        }

        // Now delete all nodes
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
            newNode->next = newNode; // circular
        } else {
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
        }
        size++;
    }

    void moveFirstToLast() {
        if (head == nullptr || head == tail) return;
        head = head->next;
        tail = tail->next;
    }

    void removeFirst() {
        if (head == nullptr) return;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = head;
            head = head->next;
            tail->next = head;
            delete temp;
        }
        size--;
    }

    int getFirst() const {
        return head ? head->value : -1;
    }

    int getSize() const {
        return size;
    }
};

void subtask1(long long n) {
    LinkedList list;

    // Initialize the list with cards 1 to n
    for (int i = 1; i <= n; i++) {
        list.append(i);
    }

    // Simulate n-1 rounds
    for (int round = 0; round < n - 1; round++) {
        // Step 1: Move first card to last
        list.moveFirstToLast();

        // Step 2: Discard the first card
        list.removeFirst();

        // Output the first card after this round
        cout << list.getFirst() << endl;
    }
}

long long subtask2(long long n) {
    // Josephus problem with k=2
    // Find the highest power of 2 <= n
    long long powerOf2 = 1;
    while (powerOf2 * 2 <= n) {
        powerOf2 *= 2;
    }

    // If n is a power of 2, answer is 1
    if (powerOf2 == n) {
        return 1;
    }

    // Otherwise, n = powerOf2 + l, answer is 2*l + 1
    long long l = n - powerOf2;
    return 2 * l + 1;
}

int main() {
    int id;
    long long n;

    cin >> id >> n;

    if (id == 1) {
        subtask1(n);
    } else if (id == 2) {
        cout << subtask2(n) << endl;
    }

    return 0;
}
