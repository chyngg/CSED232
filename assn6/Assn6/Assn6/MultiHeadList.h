#pragma once
#ifndef MULTIHEADLIST_H
#define MULTIHEADLIST_H
#include <vector>
#include <iterator>
#include <algorithm>

template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
    Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
};

template <typename T>
class MultiHeadList {
private:
    std::vector<Node<T>*> headList;
public:
    class Iterator {
    private:
        Node<T>* curr;

    public:
        Iterator(Node <T>* node) : curr(node) {} // Constructor
        Iterator operator++() // 전위 ++ overloading
        {
            if (curr != nullptr)
                curr = curr->next;
            return *this;
        }

        Iterator operator++(int) // 후위 ++ overloading
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator operator--() // 전위 -- overloading
        {
            if (curr != nullptr)
                curr = curr->prev;
            return *this;
        }

        Iterator operator--(int) // 후위 -- overloading
        {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        Iterator operator+(int n) // + overloading
        {
            for (int i = 0; i < n; ++i)
                ++(*this);
            return *this;
        }

        Iterator operator-(int n) // - overloading
        {
            for (int i = 0; i < n; i++)
                --(*this);
            return *this;
        }

        T* operator->() { return &(curr->data); } // -> overloading
        bool operator!=(const Iterator& it) const { return curr != it.curr; } // != overloading
        bool operator==(const Iterator& it) const { return curr == it.curr; } // == overloading
        T& operator*() { return curr->data; } // data 반환
        Node<T>* access_curr() { return curr; } // Iterator로부터 node에 접근할 때 사용
    };
    class ReverseIterator {
    private:
        Node<T>* curr;

    public:
        ReverseIterator(Node<T>* node) : curr(node) {}
        ReverseIterator operator++() // 전위 ++ overloading
        {
            if (curr != nullptr)
                curr = curr->prev;
            return *this;
        }
        ReverseIterator operator++(int) // 후위 ++ overloading
        {
            ReverseIterator temp = *this;
            ++(*this);
            return temp;
        }

        ReverseIterator operator--() // 전위 -- overloading
        {
            if (curr != nullptr)
                curr = curr->next;
            return *this;
        }

        ReverseIterator operator--(int) // 후위 -- overloading
        {
            ReverseIterator temp = *this;
            --(*this);
            return temp;
        }

        ReverseIterator operator+(int n) // + overloading
        {
            Iterator temp = *this;
            for (int i = 0; i < n; i++)
                ++(*temp);
            return temp;
        }

        ReverseIterator operator-(int n) // - overloading
        {
            Iterator temp = *this;
            for (int i = 0; i < n; i++)
                --(*temp);
            return temp;
        }

        bool operator!=(const ReverseIterator& reit) const { return curr != reit.curr; } // != overloading
        bool operator==(const ReverseIterator& reit) const { return curr == reit.curr; } // == overloading
        T& operator*() { return curr->data; } // data 반환
        Node<T>* access_curr() { return curr; } // Iterator로부터 node에 접근할 때 사용
        T* operator->() { return &(curr->data); } // -> overloading
    };

public:
    MultiHeadList<T>() {};
    ~MultiHeadList<T>() // Destructor
    {
        for (auto head : headList) {
            while (head != nullptr)
            {
                Node<T>* temp = head;
                head = head->next;
                delete temp; // MultiHeadList의 모든 노드 삭제
            }
        }
    }

    int headSize() { return headList.size(); }
    void push_back(const T& data, int headIdx = -1)
    {
        if (headIdx < 0 || headIdx >= headList.size()) { // 새로운 헤드 생성
            Node<T>* new_node = new Node<T>(data);
            headList.push_back(new_node);
        }
        else { // 기존 headIdx list 맨 끝에 data 추가
            Node<T>* curr = headList[headIdx];
            while (curr->next != nullptr)
                curr = curr->next;

            Node<T>* new_node = new Node<T>(data);
            curr->next = new_node;
            new_node->prev = curr;
        }

    }

    void push_front(const T& data, int headIdx = -1)
    {
        if (headIdx < 0 || headIdx >= headList.size()) { // 새로운 head 생성
            Node<T>* new_node = new Node<T>(data);
            headList.push_back(new_node);
        }
        else { // 기존 headIdx list 맨 앞에 data 추가
            Node<T>* curr = headList[headIdx];
            Node<T>* new_node = new Node<T>(data);
            new_node->next = curr;
            if (curr != nullptr)
                curr->prev = new_node;

            headList[headIdx] = new_node;
        }

    }

    void insert(Iterator pos, const T& data)  // pos가 가리키는 곳 이전에 data 삽입
    {
        Node<T>* curr = pos.access_curr(); // pos가 가리키는 노드 접근
        Node<T>* new_node = new Node<T>(data);

        if (curr != nullptr) {
            new_node->next = curr;
            new_node->prev = curr->prev;

            if (curr->prev != nullptr) {
                curr->prev->next = new_node;
            }
            else { // curr이 헤드 노드인 경우
                for (int i = 0; i < headList.size(); ++i) {
                    if (headList[i] == curr) {
                        headList[i] = new_node;
                        break;
                    }
                }
            }

            curr->prev = new_node;
        }
        else { // pos가 end()를 가리키는 경우, 새로운 헤드 추가
            headList.push_back(new_node);
        }

    }

    void pop_back(int headIdx) // headIdx번째 list 맨 끝 data 삭제
    {
        int headlist_size = headList.size();
        if (headIdx >= 0 && headIdx < headList.size())
        {
            Node<T>* curr = headList[headIdx]; // 삭제할 headIdx번째 list
            if (curr == nullptr) // headIdx번째 list가 이미 비어있는 경우
                return;

            while (curr->next != nullptr)
                curr = curr->next; // 맨 끝 노드로 이동
            if (curr->prev != nullptr) // current가 헤드가 아닌 경우
                curr->prev->next = nullptr;

            else // 삭제 후 headIdx번째 list가 빈 리스트가 되는 경우
            {
                headList[headIdx] = nullptr;
                

                if (headlist_size - 1 == headIdx) {
                    for (int i = headIdx; i < headList.size() - 1; ++i) {
                        headList[i] = headList[i + 1];
                    }
                    headList.pop_back();
                }
            }
            headList.erase(std::remove(headList.begin(), headList.end(), nullptr), headList.end());
            delete curr;
        }
    }

    void pop_front(int headIdx) // headIdx번째 list 맨 앞 data 삭제
    {
        int headlist_size = headList.size();
        if (headIdx >= 0 && headIdx < headList.size()) {
            Node<T>* head = headList[headIdx];
            if (head != nullptr) {
                headList[headIdx] = head->next;
                if (head->next) {
                    head->next->prev = nullptr;
                }
                delete head;
            }
            if (headList[headIdx] == nullptr && headIdx != headlist_size-1) { // headIdx번째 리스트가 빈 리스트가 될 경우
                headList.erase(headList.begin() + headIdx);

                for (int i = headIdx; i < headList.size() - 1; ++i) {
                    headList[i] = headList[i + 1];
                }
                headList.pop_back();
                
            }
            headList.erase(std::remove(headList.begin(), headList.end(), nullptr), headList.end());
        }
    }

    void merge(int frontHeadIdx, int backHeadIdx) // frontHeadIdx번째 리스트 뒤에 backHeadIdx번째 list 붙이기
    {
        if (frontHeadIdx >= 0 && frontHeadIdx < headList.size() && backHeadIdx >= 0 && backHeadIdx < headList.size())
        {
            Node<T>* front = headList[frontHeadIdx];
            Node<T>* back = headList[backHeadIdx];
            if (front == nullptr || back == nullptr) return;
            while (front->next != nullptr)
                front = front->next; // frontHeadIdx 리스트의 맨 끝 노드로 이동

            front->next = back;
            back->prev = front;
            headList.erase(headList.begin() + backHeadIdx); // backHeadIdx가 가리키는 곳 삭제
        }
    }

    bool erase(const T& data, int targetHeadIdx)
    {
        int headlist_size = headList.size(); bool a = false;
        bool erased = false;
        if (targetHeadIdx >= 0 && targetHeadIdx < headList.size()) {
            Node<T>* curr = headList[targetHeadIdx];
            while (curr != nullptr) {
                if (curr->data == data) {
                    Node<T>* next_node = curr->next;

                    if (curr->prev != nullptr) { // curr는 헤드가 아님
                        curr->prev->next = curr->next;
                    }
                    else { // curr이 헤드
                        headList[targetHeadIdx] = nullptr;
                        a = true;
                    }

                    if (curr->next != nullptr) { // current가 마지막 노드가 아님
                        curr->next->prev = curr->prev;
                    }

                    delete curr;
                    erased = true;
                    if (targetHeadIdx != headlist_size - 1 && a == true)
                        for (int i = targetHeadIdx; i < headList.size() - 1; ++i) {
                            headList[i] = headList[i + 1];
                        }
                    headList.pop_back();

                    // headList의 empty list 삭제
                    headList.erase(std::remove(headList.begin(), headList.end(), nullptr), headList.end());

                    if (next_node != nullptr) {
                        next_node->prev = nullptr; 
                        headList.push_back(next_node); // current 뒤의 노드들은 새로운 index의 헤드 리스트에 집어넣음
                    }
                    break;
                }
                curr = curr->next;
            }
        }
        return erased;
    }

    bool erase(Iterator pos)
    {
        bool erased = false;
        Node<T>* current = pos.access_curr();
        if (current->prev != nullptr) { // current가 헤드가 아님
            Node<T>* next_node = current->next;
            next_node->prev = nullptr;
            current->next = nullptr;

            headList.push_back(next_node); // current 뒤의 노드들은 새로운 index의 헤드 리스트에 집어넣음
            erased = true;
            current->prev->next = nullptr;

            if(current->next != nullptr)
                current->next->prev = nullptr;

            current->prev = nullptr;
            current->next = nullptr;
            
            delete current;
            return erased;

        }
        else { // current가 헤드
            int find_index = -1;
            int headlist_size = headList.size();
            Node<T>* find_head = headList[0];
            for (int i = 0; i < headList.size() && find_index == -1; ++i)
            {
                find_head = headList[i];
                while (find_head != nullptr) {
                    if (find_head == current) {
                        find_index = i;
                        find_head = current;
                        break;
                    }
                }
            }
            if (!current->prev)
                current->prev->next = nullptr;

            if (!current->next)
                current->next->prev = nullptr;

            current->prev = nullptr;
            current->next = nullptr;

            delete current; // 노드 삭제

            headList[find_index] = nullptr;
            if (find_index != headlist_size)
            {
                for (int i = find_index; i < headList.size() - 1; ++i) {
                    headList[i] = headList[i + 1];
                }
                headList.pop_back();
            }
            

            Node<T>* next_node = find_head->next;
            next_node->prev = nullptr;
            headList.erase(std::remove(headList.begin(), headList.end(), nullptr), headList.end());
            headList.push_back(next_node);
            
            erased = true;
        }

        return erased;
    }

    Iterator begin(int headIdx) // headIdx번째 list의 헤드를 가리키는 Iterator 반환
    {
        if (headIdx >= 0 && headIdx < headList.size())
            return Iterator(headList[headIdx]);
        return end();
    }
    Iterator end() { return Iterator(nullptr); } // nullptr을 가리키는 Iterator 반환
    ReverseIterator rbegin(int headIdx) // headIdx번째 list의 Tail을 가리키는 Iterator 반환
    {
        Node<T>* lastNode = headList[headIdx];
        while (lastNode != nullptr && lastNode->next != nullptr) {
            lastNode = lastNode->next;
        }
        return ReverseIterator(lastNode);
    }
    ReverseIterator rend() { return ReverseIterator(nullptr); } // nullptr을 가리키는 Iterator 반환
};

#endif


