#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct Tourist {
    int passportCode;
    string surname;
    int days;

    void print() const {
        cout << left << setw(10) << passportCode << setw(15) << surname << setw(5) << days << endl;
    }
};

class PriorityQueue {
private:
    vector<Tourist> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].days > heap[parent].days) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int maxIndex = index;
        int size = heap.size();

        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;

            if (leftChild < size && heap[leftChild].days > heap[maxIndex].days) {
                maxIndex = leftChild;
            }
            if (rightChild < size && heap[rightChild].days > heap[maxIndex].days) {
                maxIndex = rightChild;
            }
            if (maxIndex != index) {
                swap(heap[index], heap[maxIndex]);
                index = maxIndex;
            } else {
                break;
            }
        }
    }

public:
    void push(const Tourist& t) {
        heap.push_back(t);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) {
            cout << "Черга з пріоритетом порожня!" << endl;
            return;
        }
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }

    Tourist top() const {
        if (heap.empty()) {
            cout << "Черга з пріоритетом порожня!" << endl;
            return Tourist{0, "", 0};
        }
        return heap[0];
    }

    bool empty() const {
        return heap.empty();
    }

    void print() const {
        cout << "Вміст черги з пріоритетом (відсортовано за днями, спадання):" << endl;
        cout << left << setw(10) << "Паспорт" << setw(15) << "Прізвище" << setw(5) << "Дні" << endl;
        cout << string(30, '-') << endl;
        vector<Tourist> sortedHeap = heap;
        sort(sortedHeap.begin(), sortedHeap.end(), 
             [](const Tourist& a, const Tourist& b) { return a.days > b.days; });
        for (const auto& t : sortedHeap) {
            t.print();
        }
        cout << endl;
    }
};

int main() {
    srand(time(NULL));
    PriorityQueue pq;
    const int T = 12;
    const int N = 8;  
    const int MIN_VAL = -20 * N; 
    const int MAX_VAL = 20 * N;  

    cout << "Ініціалізація 12 туристів із випадковими даними:" << endl;
    cout << left << setw(10) << "Паспорт" << setw(15) << "Прізвище" << setw(5) << "Дні" << endl;
    cout << string(30, '-') << endl;
    for (int i = 0; i < T; i++) {
        Tourist t;
        t.passportCode = MIN_VAL + rand() % (MAX_VAL - MIN_VAL + 1);
        t.surname = "Турист" + to_string(i + 1);
        t.days = MIN_VAL + rand() % (MAX_VAL - MIN_VAL + 1);
        t.print();
        pq.push(t);
    }

    cout << "\nПісля вставки всіх туристів:" << endl;
    pq.print();

    cout << "Виймання туристів за пріоритетом (спочатку найбільша кількість днів):" << endl;
    while (!pq.empty()) {
        Tourist t = pq.top();
        cout << "Вийнято: ";
        t.print();
        pq.pop();
    }

    return 0;
}
