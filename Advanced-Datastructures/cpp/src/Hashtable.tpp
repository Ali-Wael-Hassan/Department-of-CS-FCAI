#include "DuckHashtable.h"
#include "DuckHash.h"

#include <cstdlib>
#include <new>
#include <utility>
#include <vector>

namespace duck {

    template <class T>
    DuckHashtable<T>::DuckHashtable(size_t capacity) {
        capacity_ = static_cast<size_t>(capacity * 1.2 + 1);
        data_ = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));
        occupied_ = static_cast<bool*>(calloc(capacity_, sizeof(bool)));
        size_ = 0;
    }

    template <class T>
    DuckHashtable<T>::~DuckHashtable() {
        for (size_t i = 0; i < capacity_; ++i)
            if (occupied_[i])
                data_[i].~T();

        free(occupied_);
        free(data_);
    }

    template <class T>
    DuckHashtable<T>::DuckHashtable(const DuckHashtable& other) {
        capacity_ = other.capacity_;
        size_ = 0;

        data_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));
        occupied_ = static_cast<bool*>(calloc(capacity_, sizeof(bool)));

        for (size_t i = 0; i < other.capacity_; ++i) {
            if (!other.occupied_[i])
                continue;

            size_t idx = duck_hash(other.data_[i], capacity_);
            while (occupied_[idx])
                idx = (idx + 1) % capacity_;

            new (&data_[idx]) T(other.data_[i]);
            occupied_[idx] = true;
            ++size_;
        }
    }

    template <class T>
    DuckHashtable<T>& DuckHashtable<T>::operator=(const DuckHashtable& other) {
        if (this == &other)
            return *this;

        DuckHashtable tmp(other);
        std::swap(data_, tmp.data_);
        std::swap(occupied_, tmp.occupied_);
        std::swap(capacity_, tmp.capacity_);
        std::swap(size_, tmp.size_);
        return *this;
    }

    template <class T>
    DuckHashtable<T>::DuckHashtable(DuckHashtable&& other) noexcept {
        data_ = other.data_;
        occupied_ = other.occupied_;
        capacity_ = other.capacity_;
        size_ = other.size_;

        other.data_ = nullptr;
        other.occupied_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    template <class T>
    DuckHashtable<T>& DuckHashtable<T>::operator=(DuckHashtable&& other) noexcept {
        if (this == &other)
            return *this;

        for (size_t i = 0; i < capacity_; ++i)
            if (occupied_[i])
                data_[i].~T();

        std::free(occupied_);
        std::free(data_);

        data_ = other.data_;
        occupied_ = other.occupied_;
        capacity_ = other.capacity_;
        size_ = other.size_;

        other.data_ = nullptr;
        other.occupied_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;

        return *this;
    }

    template <class T>
    size_t DuckHashtable<T>::find_index(const T& element) const {
        size_t idx = duck_hash(element, capacity_);

        for (size_t n = 0; n < capacity_; ++n) {
            if (!occupied_[idx])
                return capacity_;
            if (data_[idx] == element)
                return idx;
            idx = (idx + 1) % capacity_;
        }

        return capacity_;
    }

    template <class T>
    void DuckHashtable<T>::grow() {
        size_t new_capacity = capacity_ * 2 + 1;

        T* new_data = static_cast<T*>(std::malloc(new_capacity * sizeof(T)));
        bool* new_occupied = static_cast<bool*>(std::calloc(new_capacity, sizeof(bool)));

        size_t new_size = 0;
        for (size_t i = 0; i < capacity_; ++i) {
            if (!occupied_[i])
                continue;

            size_t idx = duck_hash(data_[i], new_capacity);
            while (new_occupied[idx])
                idx = (idx + 1) % new_capacity;

            new (&new_data[idx]) T(data_[i]);
            new_occupied[idx] = true;
            ++new_size;
        }

        for (size_t i = 0; i < capacity_; ++i)
            if (occupied_[i])
                data_[i].~T();

        std::free(occupied_);
        std::free(data_);

        data_ = new_data;
        occupied_ = new_occupied;
        capacity_ = new_capacity;
        size_ = new_size;
    }

    template <class T>
    void DuckHashtable<T>::insert(const T& element) {
        if ((size_ + 1) * 100 > capacity_ * 80)
            grow();

        size_t idx = duck_hash(element, capacity_);
        while (occupied_[idx]) {
            if (data_[idx] == element)
                return;
            idx = (idx + 1) % capacity_;
        }

        new (&data_[idx]) T(element);
        occupied_[idx] = true;
        ++size_;
    }

    template <class T>
    bool DuckHashtable<T>::remove(const T& element) {
        size_t idx = find_index(element);
        if (idx >= capacity_)
            return false;

        occupied_[idx] = false;
        data_[idx].~T();
        --size_;

        std::vector<T> displaced;
        displaced.reserve(size_);

        size_t j = (idx + 1) % capacity_;
        while (occupied_[j]) {
            displaced.push_back(data_[j]);
            data_[j].~T();
            occupied_[j] = false;
            --size_;
            j = (j + 1) % capacity_;
        }

        for (const T& e : displaced)
            insert(e);

        return true;
    }

    template <class T>
    T* DuckHashtable<T>::get(const T& element) {
        size_t idx = find_index(element);
        return (idx < capacity_) ? &data_[idx] : nullptr;
    }

    template <class T>
    const T* DuckHashtable<T>::get(const T& element) const {
        size_t idx = find_index(element);
        return (idx < capacity_) ? &data_[idx] : nullptr;
    }

    template <class T>
    bool DuckHashtable<T>::contains(const T& element) const {
        return find_index(element) < capacity_;
    }

    template <class T>
    void DuckHashtable<T>::clear() {
        for (size_t i = 0; i < capacity_; ++i)
            if (occupied_[i])
                data_[i].~T();

        for (size_t i = 0; i < capacity_; ++i)
            occupied_[i] = false;

        size_ = 0;
    }

    template <class T>
    size_t DuckHashtable<T>::size() {
        return size_;
    }

    template <class T>
    size_t DuckHashtable<T>::size() const {
        return size_;
    }

    template <class T>
    size_t DuckHashtable<T>::capacity() {
        return capacity_;
    }

    template <class T>
    size_t DuckHashtable<T>::capacity() const {
        return capacity_;
    }

    template <class T>
    bool DuckHashtable<T>::empty() const {
        return size_ == 0;
    }

}