#pragma once
template<typename T>
struct ListNode
{
    static void addToTail(ListNode<T>** current, T* var);

    ListNode<T>* head;
    ListNode<T>* tail;
    ListNode<T>* next;
    ListNode<T>* prev;
    T* data;

    ListNode<T>()
        : data(nullptr)
        , head(this)
        , tail(this)
        , next(nullptr)
        , prev(nullptr)
    {
    }

    void addNext(T* var);
    void addTail(T* var);
    void removeSelf();
};

template<typename T>
void ListNode<T>::removeSelf()
{
    auto next = this->next;
    if (this->next)
    {
        if (this->next->head == this)
            this->next->head = this->next;
        this->next->prev = this->prev;
    }
    if (this->prev)
    {
        if (this->prev->tail == this)
            this->next->tail = this->prev;
        this->prev->next = this->next;
    }
    delete this;
}

template<typename T>
void ListNode<T>::addToTail(ListNode<T>** current, T* var)
{
    auto node = *current;
    if (node == nullptr)
    {
        node = new ListNode<T>();
        node->data = var;
        *current = node;
    }
    else
    {
        node->addTail(var);
    }
}

template<typename T>
void ListNode<T>::addTail(T* var)
{
    this->tail->addNext(var);
}

template<typename T>
void ListNode<T>::addNext(T* var)
{
    auto node = new ListNode<T>();
    node->data = var;
    if (this->next == nullptr)
    {
        this->next = node;
        this->tail = node;
        node->prev = this;
        node->tail = node;
        node->head = this->head;
    }
    else
    {
        node->prev = this;
        node->next = this->next;
        node->tail = this->next->tail;
        node->head = this->head;
        this->next = node;
    }
}


