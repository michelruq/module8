#pragma once
#include "../module8/stringcontainer/stringcontainer.h"
#include "../module8/exception/derivedexception.h"

//The original IntArray comes from https://www.learncpp.com/cpp-tutorial/container-classes/
//This class has been modified for addition "bool getIndexOfElement(int value, int& index);"

template <typename T>
class IntArray
{
private:
    int m_length{};
    T* m_data{};

    void erase();
    void reallocate(int newLength);

public:
    IntArray() = default;
    //create container
    IntArray(int length);
    IntArray(const IntArray& a);

    //copy container
    IntArray& operator=(const IntArray& a);

    //get access to any element of container
    T& operator[](int index);

    //change container's size
    void resize(int newLength);

    //add element into container
    void insertBefore(T value, int index);

    //remove element into container
    void remove(int index);

    //insert at the end
    void insertAtEnd(T value);

    //insert at the beginning
    void insertAtBeginning(T value);

    //find out index of value in container
    bool getIndexOfElement(T value, int& index);

    //very useful for doing with object
    int getLength() const;

    //destroy object
    ~IntArray();

};

template <typename T>
IntArray<T>::IntArray(int length) : m_length{ length }
{
    BaseException e(es_ctor, length);
    if (!(length >= 0))
    {
        throw e;
    }
    if (length > 0)
    {
        m_data = new T[length] {};
    }
}

template <typename T>
IntArray<T>::IntArray<T>(const IntArray<T>& a)
{
    // Set the size of the new array appropriately
    reallocate(a.getLength());

    // Then copy the elements
    for (int index{ 0 }; index < m_length; ++index)
    {
        m_data[index] = a.m_data[index];
    }
}

template <typename T>
IntArray<T>::~IntArray()
{
    delete[] m_data;
    // we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
}

template <typename T>
void IntArray<T>::erase()
{
    delete[] m_data;
    // We need to make sure we set m_data to nullptr here, otherwise it will
    // be left pointing at deallocated memory!
    m_data = nullptr;
    m_length = 0;
}

template <typename T>
T& IntArray<T>::operator[](int index)
{
    DerivedException e(es_getter, m_length, index);
    if (!(index >= 0 && index < m_length))
    {
        throw e;
    }
    return m_data[index];
}

// reallocate resizes the array.  Any existing elements will be destroyed.  This function operates quickly.
template <typename T>
void IntArray<T>::reallocate(int newLength)
{
    // First we delete any existing elements
    erase();

    // If our array is going to be empty now, return here
    if (newLength <= 0)
    {
        return;
    }

    // Then we have to allocate new elements
    m_data = new int[newLength];
    m_length = newLength;
}

// resize resizes the array.  Any existing elements will be kept.  This function operates slowly.
template <typename T>
void IntArray<T>::resize(int newLength)
{
    // if the array is already the right length, we're done
    if (newLength == m_length)
    {
        return;
    }


    // If we are resizing to an empty array, do that and return
    if (newLength <= 0)
    {
        erase();
        return;
    }

    // Now we can assume newLength is at least 1 element.  This algorithm
    // works as follows: First we are going to allocate a new array.  Then we
    // are going to copy elements from the existing array to the new array.
    // Once that is done, we can destroy the old array, and make m_data
    // point to the new array.

    // First we have to allocate a new array
    int* data{ new int[newLength] };

    // Then we have to figure out how many elements to copy from the existing
    // array to the new array.  We want to copy as many elements as there are
    // in the smaller of the two arrays.
    if (m_length > 0)
    {
        int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

        // Now copy the elements one by one
        for (int index{ 0 }; index < elementsToCopy; ++index)
        {
            data[index] = m_data[index];
        }
    }

    // Now we can delete the old array because we don't need it any more
    delete[] m_data;

    // And use the new array instead!  Note that this simply makes m_data point
    // to the same address as the new array we dynamically allocated.  Because
    // data was dynamically allocated, it won't be destroyed when it goes out of scope.
    m_data = data;
    m_length = newLength;
}

template <typename T>
IntArray<T>& IntArray<T>::operator=(const IntArray<T>& a)
{
    // Self-assignment check
    if (&a == this)
    {
        return *this;
    }

    // Set the size of the new array appropriately
    // !!!We don't need to check length here because all objects are created correctly
    reallocate(a.getLength());

    // Then copy the elements
    for (int index{ 0 }; index < m_length; ++index)
    {
        m_data[index] = a.m_data[index];
    }

    return *this;
}

template <typename T>
void IntArray<T>::insertBefore(T value, int index)
{
    // Sanity check our index value
    DerivedException e(es_insertBefore, m_length, index);
    if (!(index >= 0 && index <= m_length))
    {
        throw e;
    }

    // First create a new array one element larger than the old array
    int* data{ new int[m_length + 1] };

    // Copy all of the elements up to the index
    for (int before{ 0 }; before < index; ++before)
    {
        data[before] = m_data[before];
    }

    // Insert our new element into the new array
    data[index] = value;

    // Copy all of the values after the inserted element
    for (int after{ index }; after < m_length; ++after)
    {
        data[after + 1] = m_data[after];
    }

    // Finally, delete the old array, and use the new array instead
    delete[] m_data;
    m_data = data;
    ++m_length;
}

template <typename T>
void IntArray<T>::remove(int index)
{
    // Sanity check our index value
    DerivedException e(es_remove, m_length, index);
    if (!(index >= 0 && index <= m_length))
    {
        throw e;
    }

    // If we're removing the last element in the array, we can just erase the array and return early
    if (m_length == 1)
    {
        erase();
        return;
    }

    // First create a new array one element smaller than the old array
    int* data{ new T[m_length - 1] };

    // Copy all of the elements up to the index
    for (int before{ 0 }; before < index; ++before)
    {
        data[before] = m_data[before];
    }


    // Copy all of the values after the removed element
    for (int after{ index + 1 }; after < m_length; ++after)
    {
        data[after - 1] = m_data[after];
    }


    // Finally, delete the old array, and use the new array instead
    delete[] m_data;
    m_data = data;
    --m_length;
}

template <typename T>
void IntArray<T>::insertAtBeginning(T value)
{
    insertBefore(value, 0);
}

template <typename T>
void IntArray<T>::insertAtEnd(T value)
{
    insertBefore(value, m_length);
}

template <typename T>
int IntArray<T>::getLength() const
{
    return m_length;
}

template <typename T>
bool IntArray<T>::getIndexOfElement(T value, int& outgoingIndex)
{
    bool returnValue = false;
    for (int index{ 0 }; index < getLength(); ++index)
    {
        if (m_data[index] == value)
        {
            returnValue = true;
            outgoingIndex = index;
        }
    }
    return returnValue;
}
