#pragma once

#include <cstddef>

namespace duck {

    template <class T>
    class DuckHashtable {

        public:
            DuckHashtable(size_t capacity = 16);
            ~DuckHashtable();

            DuckHashtable(const DuckHashtable& other);
            DuckHashtable& operator=(const DuckHashtable& other);

            DuckHashtable(DuckHashtable&& other) noexcept;
            DuckHashtable& operator=(DuckHashtable&& other) noexcept;

            void insert(const T& element);
            bool remove(const T& element);

            T* get(const T& element);
            const T* get(const T& element) const;

            bool contains(const T& element) const;

            void clear();

            size_t size();
            size_t size() const;

            size_t capacity();
            size_t capacity() const;

            bool empty() const;

        private:
            size_t find_index(const T& element) const;
            void grow();

            T* data_;
            bool* occupied_;

            size_t capacity_;
            size_t size_;
    };

}

#include "Hashtable.tpp"