#pragma once
#include <algorithm>

using namespace std;

// Template class MyBag for dynamic array 
template <typename T>
class MyBagTemplate 
{
private:
    T* data;
    int size;
    int capacity;

public:

    //**************************** Constructor ***************************//

    // default constructor
    MyBagTemplate() : data(nullptr), size(0), capacity(0) {}

    // argument construcor
    MyBagTemplate(int initialCapacity) : data(new T[initialCapacity]), size(0), capacity(initialCapacity) {}

    // destructor
    ~MyBagTemplate() 
    {
        delete[] data;
    }

    //**************************** Accessor *********************************//
    int getSize() const
    {
        return size;
    }

    //**************************** Mutator *********************************//
    void setSize(int newSize)
    {
        size = newSize;
    }

    //*************************** Member Functions ***************************//
    void clear() 
    {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    void insert(const T& item) 
    {
        if (size >= capacity) 
        {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[newCapacity];

            for (int i = 0; i < size; ++i) 
            {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        data[size++] = item;
    }

    bool search(const T& item) const 
    {
        for (int i = 0; i < size; ++i) 
        {
            if (data[i] == item) {
                return true;
            }
        }
        return false;
    }

    bool remove(const T& item) 
    {
        int index = -1;
        for (int i = 0; i < size; ++i) 
        {
            if (data[i] == item) 
            {
                index = i;
                break;
            }
        }
        if (index != -1) 
        {
            for (int i = index; i < size - 1; ++i) 
            {
                data[i] = data[i + 1];
            }
            size--;
            return true;
        }
        return false;
    }

    void sort() 
    {
        sort(data, data + size);
    }

    //************************** Overloading Operator ***********************//
    bool operator<(const MyBagTemplate<T>& other) const 
    {
        return size < other.size;
    }

    T& operator[](int index) 
    {
        if (index < 0 || index >= size) 
        {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const 
    {
        if (index >= 0 && index < size) 
        {
            return data[index];
        }

        // Handle out-of-bounds access
        throw out_of_range("Index out of bounds");
    }

    friend ostream& operator<<(ostream& out, const MyBagTemplate<T>& bag) 
    {
        for (int i = 0; i < bag.size; ++i) 
        {
            out << bag.data[i] << " ";
        }
        return out;
    }
};