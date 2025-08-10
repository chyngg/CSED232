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
        Iterator operator++() // ���� ++ overloading
        {
            if (curr != nullptr)
                curr = curr->next;
            return *this;
        }

        Iterator operator++(int) // ���� ++ overloading
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator operator--() // ���� -- overloading
        {
            if (curr != nullptr)
                curr = curr->prev;
            return *this;
        }

        Iterator operator--(int) // ���� -- overloading
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
        T& operator*() { return curr->data; } // data ��ȯ
        Node<T>* access_curr() { return curr; } // Iterator�κ��� node�� ������ �� ���
    };
    class ReverseIterator {
    private:
        Node<T>* curr;

    public:
        ReverseIterator(Node<T>* node) : curr(node) {}
        ReverseIterator operator++() // ���� ++ overloading
        {
            if (curr != nullptr)
                curr = curr->prev;
            return *this;
        }
        ReverseIterator operator++(int) // ���� ++ overloading
        {
            ReverseIterator temp = *this;
            ++(*this);
            return temp;
        }

        ReverseIterator operator--() // ���� -- overloading
        {
            if (curr != nullptr)
                curr = curr->next;
            return *this;
        }

        ReverseIterator operator--(int) // ���� -- overloading
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
        T& operator*() { return curr->data; } // data ��ȯ
        Node<T>* access_curr() { return curr; } // Iterator�κ��� node�� ������ �� ���
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
                delete temp; // MultiHeadList�� ��� ��� ����
            }
        }
    }

    int headSize() { return headList.size(); }
    void push_back(const T& data, int headIdx = -1)
    {
        if (headIdx < 0 || headIdx >= headList.size()) { // ���ο� ��� ����
            Node<T>* new_node = new Node<T>(data);
            headList.push_back(new_node);
        }
        else { // ���� headIdx list �� ���� data �߰�
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
        if (headIdx < 0 || headIdx >= headList.size()) { // ���ο� head ����
            Node<T>* new_node = new Node<T>(data);
            headList.push_back(new_node);
        }
        else { // ���� headIdx list �� �տ� data �߰�
            Node<T>* curr = headList[headIdx];
            Node<T>* new_node = new Node<T>(data);
            new_node->next = curr;
            if (curr != nullptr)
                curr->prev = new_node;

            headList[headIdx] = new_node;
        }

    }

    void insert(Iterator pos, const T& data)  // pos�� ����Ű�� �� ������ data ����
    {
        Node<T>* curr = pos.access_curr(); // pos�� ����Ű�� ��� ����
        Node<T>* new_node = new Node<T>(data);

        if (curr != nullptr) {
            new_node->next = curr;
            new_node->prev = curr->prev;

            if (curr->prev != nullptr) {
                curr->prev->next = new_node;
            }
            else { // curr�� ��� ����� ���
                for (int i = 0; i < headList.size(); ++i) {
                    if (headList[i] == curr) {
                        headList[i] = new_node;
                        break;
                    }
                }
            }

            curr->prev = new_node;
        }
        else { // pos�� end()�� ����Ű�� ���, ���ο� ��� �߰�
            headList.push_back(new_node);
        }

    }

    void pop_back(int headIdx) // headIdx��° list �� �� data ����
    {
        int headlist_size = headList.size();
        if (headIdx >= 0 && headIdx < headList.size())
        {
            Node<T>* curr = headList[headIdx]; // ������ headIdx��° list
            if (curr == nullptr) // headIdx��° list�� �̹� ����ִ� ���
                return;

            while (curr->next != nullptr)
                curr = curr->next; // �� �� ���� �̵�
            if (curr->prev != nullptr) // current�� ��尡 �ƴ� ���
                curr->prev->next = nullptr;

            else // ���� �� headIdx��° list�� �� ����Ʈ�� �Ǵ� ���
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

    void pop_front(int headIdx) // headIdx��° list �� �� data ����
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
            if (headList[headIdx] == nullptr && headIdx != headlist_size-1) { // headIdx��° ����Ʈ�� �� ����Ʈ�� �� ���
                headList.erase(headList.begin() + headIdx);

                for (int i = headIdx; i < headList.size() - 1; ++i) {
                    headList[i] = headList[i + 1];
                }
                headList.pop_back();
                
            }
            headList.erase(std::remove(headList.begin(), headList.end(), nullptr), headList.end());
        }
    }

    void merge(int frontHeadIdx, int backHeadIdx) // frontHeadIdx��° ����Ʈ �ڿ� backHeadIdx��° list ���̱�
    {
        if (frontHeadIdx >= 0 && frontHeadIdx < headList.size() && backHeadIdx >= 0 && backHeadIdx < headList.size())
        {
            Node<T>* front = headList[frontHeadIdx];
            Node<T>* back = headList[backHeadIdx];
            if (front == nullptr || back == nullptr) return;
            while (front->next != nullptr)
                front = front->next; // frontHeadIdx ����Ʈ�� �� �� ���� �̵�

            front->next = back;
            back->prev = front;
            headList.erase(headList.begin() + backHeadIdx); // backHeadIdx�� ����Ű�� �� ����
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

                    if (curr->prev != nullptr) { // curr�� ��尡 �ƴ�
                        curr->prev->next = curr->next;
                    }
                    else { // curr�� ���
                        headList[targetHeadIdx] = nullptr;
                        a = true;
                    }

                    if (curr->next != nullptr) { // current�� ������ ��尡 �ƴ�
                        curr->next->prev = curr->prev;
                    }

                    delete curr;
                    erased = true;
                    if (targetHeadIdx != headlist_size - 1 && a == true)
                        for (int i = targetHeadIdx; i < headList.size() - 1; ++i) {
                            headList[i] = headList[i + 1];
                        }
                    headList.pop_back();

                    // headList�� empty list ����
                    headList.erase(std::remove(headList.begin(), headList.end(), nullptr), headList.end());

                    if (next_node != nullptr) {
                        next_node->prev = nullptr; 
                        headList.push_back(next_node); // current ���� ������ ���ο� index�� ��� ����Ʈ�� �������
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
        if (current->prev != nullptr) { // current�� ��尡 �ƴ�
            Node<T>* next_node = current->next;
            next_node->prev = nullptr;
            current->next = nullptr;

            headList.push_back(next_node); // current ���� ������ ���ο� index�� ��� ����Ʈ�� �������
            erased = true;
            current->prev->next = nullptr;

            if(current->next != nullptr)
                current->next->prev = nullptr;

            current->prev = nullptr;
            current->next = nullptr;
            
            delete current;
            return erased;

        }
        else { // current�� ���
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

            delete current; // ��� ����

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

    Iterator begin(int headIdx) // headIdx��° list�� ��带 ����Ű�� Iterator ��ȯ
    {
        if (headIdx >= 0 && headIdx < headList.size())
            return Iterator(headList[headIdx]);
        return end();
    }
    Iterator end() { return Iterator(nullptr); } // nullptr�� ����Ű�� Iterator ��ȯ
    ReverseIterator rbegin(int headIdx) // headIdx��° list�� Tail�� ����Ű�� Iterator ��ȯ
    {
        Node<T>* lastNode = headList[headIdx];
        while (lastNode != nullptr && lastNode->next != nullptr) {
            lastNode = lastNode->next;
        }
        return ReverseIterator(lastNode);
    }
    ReverseIterator rend() { return ReverseIterator(nullptr); } // nullptr�� ����Ű�� Iterator ��ȯ
};

#endif


