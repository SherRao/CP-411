#include <stdio.h>
#include <GL/glut.h>

template <typename T>
class ListNode
{
public:
    T value;
    ListNode *previous;
    ListNode *next;

    ListNode(T value, ListNode *previous, ListNode *next)
    {
        this->value = value;
        this->previous = previous;
        this->next = next;
    }
};

template <typename T>
class List
{
public:
    ListNode<T> *front;
    GLint size;

    List()
    {
        this->front = NULL;
        this->size = 0;
    }

    void add(T value)
    {
        if (this->front == NULL)
        {
            this->front = ListNode<T>(value, NULL, NULL);
        }
        else
        {
            ListNode<T> *current = this->front;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = ListNode<T>(value, current, NULL);
        }

        this->size++;
    }

    void remove(int index)
    {
        if (index < 0 || index >= size)
        {
            return;
        }

        ListNode<T> *current = this->front;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        if (current->prev != NULL)
        {
            current->prev->next = current->next;
        }
        else
        {
            this->front = current->next;
        }

        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }

        delete current;
        this->size--;
    }

    int indexOf(T value)
    {
        int index = 0;
        ListNode<T> *current = this->front;
        while (current != NULL)
        {
            if (current->value == value)
            {
                return index;
            }
            current = current->next;
            this->index++;
        }
        return -1;
    }
};
