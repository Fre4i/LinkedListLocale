#include <iostream>
#include <exception>

using namespace std;

//Исключения
struct FindElementException : public std::exception {
    const char* what() const throw() {
        return "Element doesn't find";
    }
};


//Элемент списка
struct Node {
    float val;
    Node* next;
    Node(float _val) : val(_val), next(nullptr) {}
};
//Список
struct list {
    Node* first;
    Node* last;
    list() : first(nullptr), last(nullptr) {}

    //Данные методы
    bool is_empty() {
        return first == nullptr;
    }
    void push_back(float val) {
        Node* p = new Node(val);
        //Инициализация списка 1 элементом
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }
    void print() {
        if (is_empty())
            return;

        Node* p = first;
        while (p) {
            cout << p->val << ' ';
            p = p->next;
        }
        cout << endl;
    }
    Node* find(float _val) {
        Node* p = first;
        while (p && p->val != _val) 
            p = p->next;
        return (p && p->val == _val) ? p : nullptr;
    }
    void remove(float _val) {
        if (is_empty())
            return;
        if (first->val == _val) {
            remove_first();
            return;
        }
        else if (last->val == _val) {
            remove_last();
            return;
        }

        Node* slow = first;
        Node* fast = first->next;
        while (fast && fast->val != _val) {
            fast = fast->next;
            slow = slow->next;
        }

        if (!fast) {
            cout << "This element does not exist" << endl;
            return;
        }

        slow->next = fast->next;
        delete fast;
    }
    
    //Свои методы
    void remove_first() {
        if (is_empty()) 
            throw FindElementException();
        if (first == last) {
            delete first;
            first = nullptr;
            last = nullptr;
            return;
        }

        Node* new_first = first->next;
        delete first;
        first = new_first;
    }
    void remove_last() {
        if (is_empty())
            throw FindElementException();
        if (first == last) {
            delete last;
            first = nullptr;
            last = nullptr;
            return;
        }

        Node* slow = first;
        Node* fast = first->next;
        while (fast != last) {
            slow = slow->next;
            fast = fast->next;
        }
        delete fast;
        last = slow;
        last->next = nullptr;
    }
    //Сливание двух списков в одно множество
    list set_list(list& L2) {
        if (is_empty() && L2.is_empty()) 
            return list();
        if (is_empty())
            return L2;
        if (L2.is_empty())
            return *this;

        list L;
        set();
        L2.set();
        Node* iter_L1 = first;
        while (iter_L1 != nullptr) {
            L.push_back(iter_L1->val);
            iter_L1 = iter_L1->next;
        }
        Node* iter_L2 = L2.first;
        while (iter_L2 != nullptr) {
            L.push_back(iter_L2->val);
            iter_L2 = iter_L2->next;
        }
        L.set();
        
        return L;
    }
    void remove_all(float _val) {
        Node* iter = first;
        int count = 0;
        while (iter != nullptr) {
            if (iter->val == _val)
                count++;
            iter = iter->next;
        }

        for (unsigned i = 0; i < count; i++)
            remove(_val);
    }
    void remove_prev_negative() {
        if (first == last)
            return;

        Node* slow = first;
        Node* fast = first->next;
        while (fast != nullptr) {
            //if (fast)

            slow = slow->next;
            fast = fast->next;
        }
    }
private:
    void insert_prev_first(float _val) {
        if (is_empty())
            throw FindElementException();
        if (first == last) {
            Node* t = first;
            Node* insert_element = new Node(_val);
            first = insert_element;
            insert_element->next = t;
        }
    }
    //Превращение списка в множество
    void set() {
        if (is_empty() || (first == last && first != nullptr))
            return;

        list res;
        Node* fast = first;
        while (fast != nullptr) {
            res.push_back(fast->val);
            remove_all(fast->val);
            fast = first;
        }
        *this = res;
    }
};


int main()
{
    list l1;

    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(30);

    l1.print();

    return 0;
}