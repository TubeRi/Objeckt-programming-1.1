#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <utility>

template <typename T>
class Vector
{
private:
    T *data_;

    size_t size_;
    size_t capacity_;
    size_t reallocations_;

public:
    // ================= KONSTRUKTORIAI =================

    Vector() : data_(nullptr),
               size_(0),
               capacity_(0),
               reallocations_(0)
    {
    }

    // ================= DESTRUKTORIUS =================

    ~Vector()
    {
        delete[] data_;
    }

    // ================= COPY =================

    Vector(const Vector &other)
    {
        size_ = other.size_;
        capacity_ = other.capacity_;

        data_ = new T[capacity_];

        for (size_t i = 0; i < size_; i++)
        {
            data_[i] = other.data_[i];
        }
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            delete[] data_;

            size_ = other.size_;
            capacity_ = other.capacity_;

            data_ = new T[capacity_];

            for (size_t i = 0; i < size_; i++)
            {
                data_[i] = other.data_[i];
            }
        }

        return *this;
    }

    // ================= MOVE =================

    Vector(Vector &&other) noexcept
    {
        data_ = other.data_;

        size_ = other.size_;

        capacity_ = other.capacity_;

        other.data_ = nullptr;

        other.size_ = 0;

        other.capacity_ = 0;
    }

    Vector &operator=(Vector &&other) noexcept
    {
        if (this != &other)
        {
            delete[] data_;

            data_ = other.data_;

            size_ = other.size_;

            capacity_ = other.capacity_;

            other.data_ = nullptr;

            other.size_ = 0;

            other.capacity_ = 0;
        }

        return *this;
    }

    // ================= PUSH_BACK =================

    void push_back(const T &value)
    {
        if (size_ >= capacity_)
        {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        data_[size_] = value;

        size_++;
    }

    // ================= ERASE =================

    T *erase(T *pos)
    {
        if (pos < begin() || pos >= end())
        {
            return end();
        }

        for (T *it = pos; it < end() - 1; ++it)
        {
            *it = std::move(*(it + 1));
        }

        size_--;

        return pos;
    }

    // ================= ERASE RANGE =================

    T *erase(T *first, T *last)
    {
        size_t count = last - first;

        for (T *it = first; it + count < end(); ++it)
        {
            *it = std::move(*(it + count));
        }

        size_ -= count;

        return first;
    }

    // ================= INSERT =================

    template <typename Iterator>
    void insert(
        T *pos,
        Iterator first,
        Iterator last)
    {
        (void)pos;

        while (first != last)
        {
            push_back(*first);

            ++first;
        }
    }

    // ================= RESERVE =================

    void reserve(size_t new_capacity)
    {
        if (new_capacity <= capacity_)
        {
            return;
        }

        T *temp = new T[new_capacity];

        for (size_t i = 0; i < size_; i++)
        {
            temp[i] = std::move(data_[i]);
        }

        delete[] data_;

        data_ = temp;
        reallocations_++;
        capacity_ = new_capacity;
    }

    // ================= CLEAR =================

    void clear()
    {
        size_ = 0;
    }

    // ================= ACCESS =================

    T &operator[](size_t index)
    {
        return data_[index];
    }

    const T &operator[](size_t index) const
    {
        return data_[index];
    }

    // ================= INFO =================

    size_t size() const
    {
        return size_;
    }

    size_t capacity() const
    {
        return capacity_;
    }

    size_t reallocations() const
    {
        return reallocations_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    // ================= ITERATORIAI =================

    T *begin()
    {
        return data_;
    }

    T *end()
    {
        return data_ + size_;
    }

    const T *begin() const
    {
        return data_;
    }

    const T *end() const
    {
        return data_ + size_;
    }
};

#endif