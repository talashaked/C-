//
// Created by talas on 1/18/2020.
//

#ifndef CPPEX3_HASHMAP_HPP
#define CPPEX3_HASHMAP_HPP
#define  UPPERLF 0.75f
#define  LOWERLF 0.25f
#define ERROR1 "Error: Key not in map\n"
#define ERROR2 "Error: The key vector and value vector don't match\n"
#define MULTIPLYBY 2

#include <vector>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <iostream>


/**
 * @brief - a derived from exception class, descriping an exception that would be thrown from a
 * function when refering to a non existing key in a map
 */
class NoKeyFoundException : public std::exception
{
public:
    /**
     * @brief the message error that the exception would print
     * @return
     */
    const char *what() const noexcept override
    {
        return ERROR1;
    }
};

/**
 * @brief - a derived from exception class, describing an exception that would be thrown from a
 * function when giving two unmatched by size two arrays of keys and values
 */
class VectorDontMatchException : public std::exception
{
public:
    /**
     * @brief the message error that the exception would print
     * @return
     */
    const char *what() const noexcept override
    {
        return ERROR2;
    }
};

/**
 * @brief a hashmap container, containing generic keys and values
 * @tparam ValueT - the values in the map
 * @tparam KeyT - the keys in the map
 */
template<class KeyT, class ValueT>
class HashMap
{
private:
    int _capacity{};
    int _curItems{};
    float const _upperLoadFactor = (float) UPPERLF;
    float const _lowerLoadFactor = (float) LOWERLF;
    std::vector<std::pair<KeyT, ValueT>> *_table;

    /**
     * @brief this func finds the index of key in a specific bucket of the hashmap
     * @param k -the key to find in the bucket
     * @return the index of the key in the bucket. in case not found an error would be thrown but
     * the program won't crash
     */
    int _indexInBucket(const KeyT &k) const
    {
        if (containsKey(k))
        {
            int bIndex = bucketIndex(k);
            int index = 0;
            for (auto p : _table[bIndex])
            {
                if (p.first == k)
                {
                    return index;
                }
                index++;
            }
        }
        return -1;
    }

    /**
     * @brief resizes the table of the hashmap, according to the newsize given. copies all the
     * previous item in the map to the new table.
     * @param newSize - the new size that the table should be
     */
    void _resizeTable(int newSize);

    /**
     * @brief this function checks whether to resize the table.
     * @return true if resizing happened, false otherwise
     */
    void _checkIfToResize(int flag);

public:
    /**
     * @brief the default constructor of the map
     */
    HashMap() : _capacity(16), _curItems(0)
    {
        using namespace std;
        _table = new vector<pair<KeyT, ValueT>>[16];
    }

    /**
     * @brief a constructor of the hashmap, when initializing it by 2 vectors, one of keys and
     * one of values. the arrays must match by length
     * @param vKeys - the key vector
     * @param vValues - the value vector
     */
    HashMap(const std::vector<KeyT> &vKeys, const std::vector<ValueT> &vValues) :
            HashMap()
    {
        using namespace std;
        if (vKeys.size() != vValues.size())
        {
            throw VectorDontMatchException{};
        }
        int size = vKeys.size();
        for (int i = 0; i < size; i++)
        {
            (*this)[vKeys[i]] = vValues[i];
        }
    }

    /**
     * @brief the copy constructor of the hashmap.
     * @param hm - a hashmap to copy
     */
    HashMap(HashMap &hm)
    {
        _table = new std::vector<std::pair<KeyT, ValueT>>[hm.capacity()];
        _curItems = hm._curItems;
        _capacity = hm.capacity();
        for (int i = 0; i < _capacity; i++)
        {
            _table[i] = hm._table[i];
        }
    }

    /**
     * default constructor
     */
    ~HashMap()
    {
        delete[](_table);
    }

    /**
     * @brief returning the size (how many items) are in the hashmap currently
     * @return by int
     */
    int size() const
    {
        return _curItems;
    }

    /**
     * @brief returning the current capacity of the hashmap
     * @return as int
     */
    int capacity() const
    {
        return _capacity;
    }

    /**
     * @brief checks if the hashmap is empty
     * @return true if so, else false
     */
    bool empty() const
    {
        return _curItems == 0;
    }

    /**
     * @brief insert a key and a value to the map. if the key already exists an error is thrown
     * @param k - the key
     * @param v - the value
     * @return -true if success
     */
    bool insert(const KeyT &k, const ValueT &v)
    {
        using namespace std;
        if (containsKey(k))
        {
            return false;
        }
        int index = std::hash<KeyT>{}(k) & (_capacity - 1);
        _table[index].push_back({k, v});
        _curItems++;
        _checkIfToResize(0);
        return true;
    }

    /**
     * @brief this function checks whether the key is in the map.
     * @param k - a given key
     * @return - true if so, else false
     */
    bool containsKey(const KeyT &k) const
    {
        using namespace std;
        int index = std::hash<KeyT>{}(k) & (_capacity - 1);
        for (auto item:_table[index])
        {
            if (item.first == k)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief this function returns the value of the given key in the map. if the key doesn't
     * exist throws an error
     * @param k - a key given
     * @return - the value of the key as reference
     */
    ValueT &at(const KeyT &k)
    {
        using namespace std;
        int index = _indexInBucket(k);
        if (index != -1)
        {
            return (_table[bucketIndex(k)][index].second);
        }
        throw NoKeyFoundException{};
    }

    const ValueT &at(const KeyT &k) const
    {
        using namespace std;
        int index = _indexInBucket(k);
        if (index != -1)
        {
            return (_table[bucketIndex(k)][index].second);
        }
        throw NoKeyFoundException{};
    }

    /**
     * @brief this function get a key and erases it from the map
     * @param k - the key to erase
     * @return - true if erasing proccess ended successfully
     */
    bool erase(const KeyT &k)
    {
        using namespace std;
        int index = std::hash<KeyT>{}(k) & (_capacity - 1);
        int indexInV = _indexInBucket(k);
        if (indexInV != -1)
        {
            _table[bucketIndex(k)].erase(_table[bucketIndex(k)].begin() + indexInV);
            _curItems--;
            _checkIfToResize(1);
            return true;
        }
        return false;
    }

    /**
     * @return returns the current load factor of the hash map
     */
    double getLoadFactor() const
    {
        return (double) _curItems / _capacity;
    }

    /**
     * @param k -a given key
     * @return returns the bucket size of the bucket containing the key k. if k doesn't exist is
     * error is printed
     */
    int bucketSize(const KeyT &k) const
    {
        if (containsKey(k))
        {
            int index = std::hash<KeyT>{}(k) & (_capacity - 1);
            return _table[index].size();
        }
        throw NoKeyFoundException{};
    }

    /**
     * @param k -a given key
     * @return returns the bucket size of the bucket containing the key k. if k doesn't exist is
     * error is printed
     */
    int bucketIndex(const KeyT &k) const
    {
        if (containsKey(k))
        {
            return std::hash<KeyT>{}(k) & (_capacity - 1);
        }
        throw NoKeyFoundException{};
    }

    /**
     * @brief erases all the items inside the hashmap
     */
    void clear()
    {
        using namespace std;
        for (int i = 0; i < _capacity; i++)
        {
            _table[i].clear();
        }
        _curItems = 0;
    }

    /**
     * @brief overrides the [] operator
     * @param k - a given key in the map. if k isnt in the map an error is printed
     * @return - the value of the key as reference
     */
    const ValueT &operator[](const KeyT &k) const
    {
        int bIndex = bucketIndex(k);
        int index = _indexInBucket(k);
        if (index == -1)
        {
            return ValueT();
        }
        else
        {
            return (_table[bIndex][index].second);
        }

    }

    /**
    * @brief overrides the [] operator
    * @param k - a given key in the map. if k isnt in the map an error is printed
    * @return - the value of the key as reference
    */
    ValueT &operator[](const KeyT &k)
    {
        if (containsKey(k))
        {
            return at(k);
        }
        insert(k, ValueT());
        return at(k);
    }

    /**
     * @brief ovveride of operator =.
     * @param hm - the hashmap that is inserted
     * @return - a reference to a new hashmap which is equal to hm
     */
    HashMap &operator=(const HashMap &hm)
    {
        if (*this != hm)
        {
            _curItems = hm.size();
            _capacity = hm.capacity();
            delete[] (_table);
            _table = new std::vector<std::pair<KeyT, ValueT>>[hm.capacity()];
            for (int i = 0; i < _capacity; i++)
            {
                _table[i] = hm._table[i];
            }
        }
        return *this;
    }

    /**
     * @brief overriding operator ==
     * @param hm - a hashmap to check equality to
     * @return - if the hashmaps are equal
     */
    bool operator==(const HashMap &hm) const
    {
        if (_curItems != hm._curItems)
        {
            return false;
        }
        for (auto p: hm)
        {
            if (!containsKey(p.first) || (p.second != at(p.first)))
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const HashMap &hm) const
    {
        return !((*this) == (hm));
    }

    /**
     * @brief an iterator class for out hashmap
     */
    class iterator
    {
        typedef int difference_type;
        typedef std::pair<KeyT, ValueT> value_type;
        typedef std::pair<KeyT, ValueT> *pointer;
        typedef std::pair<KeyT, ValueT> &reference;
        typedef std::forward_iterator_tag iterator_category;
    private:
        pointer _pointer;
        std::vector<std::pair<KeyT, ValueT>> *_hmTable;
        int _curBucket;
        int _size;
        int _curIndexInVec;

        /**
         * @brief find the next item in the map to iterate over
         */
        void _moveToNextItem()
        {
            if (_hmTable == nullptr)
            {
                return;
            }
            while (_curBucket < _size)
            {
                if ((int) _hmTable[_curBucket].size() <= _curIndexInVec)
                {
                    _curBucket++;
                    _curIndexInVec = 0;
                }
                else
                {

                    break;
                }
            }
            if (_curBucket >= _size)
            {
                _pointer = nullptr;
            }
            else
            {
                _pointer = &(_hmTable[_curBucket][_curIndexInVec]);
            }
        }

    public:
        /**
         * @brief constructor of the iterator, musrt get hashmap table as input
         * @param hmTable
         */
        iterator(std::vector<std::pair<KeyT, ValueT>> *hmTable = nullptr, pointer point = nullptr,
                 int
                 size = 0) :
                _pointer(point), _hmTable(hmTable), _curBucket(0), _size(size), _curIndexInVec(0)
        {
            _moveToNextItem();
        }

        /**
         * @brief returns the pointer
         * @return
         */
        reference operator*() const
        {
            return *_pointer;
        }

        pointer operator->() const
        {
            return _pointer;
        }

        iterator operator++()
        {
            _curIndexInVec++;
            _moveToNextItem();
            iterator i = *this;
            return i;
        }

        iterator operator++(difference_type)
        {
            _curIndexInVec++;
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(iterator const &rhs) const
        {
            return _pointer == rhs._pointer;
        }

        bool operator!=(iterator const &rhs) const
        {
            return _pointer != rhs._pointer;
        }
    };

    /**
     * @brief returns an iterator ponting to the end of the hashmap
     */
    iterator end() const
    {
        return iterator(nullptr);
    }

    /**
     * @brief returns an iterator that points to the start of the hashmap
     */
    iterator begin() const
    {
        return iterator(_table, nullptr, capacity());
    }

    /**
     * @brief returns an iterator that points to the start of the hashmap
     */
    iterator cbegin() const
    {
        return iterator(_table, nullptr, capacity());
    }

    /**
    * @brief returns an iterator ponting to the end of the hashmap
    */
    iterator cend() const
    {
        return iterator(nullptr);
    }
};


template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::_checkIfToResize(int flag)
{
    double lf = getLoadFactor();
    if (lf >= UPPERLF && flag == 0)
    {
        _resizeTable(_capacity * MULTIPLYBY);
        return;
    }
    while (lf < LOWERLF && flag == 1)
    {
        _resizeTable(_capacity / MULTIPLYBY);
        lf = getLoadFactor();
    }
}

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::_resizeTable(int newSize)
{
    using namespace std;
    auto *newTable = new vector<pair<KeyT, ValueT>>[newSize];
    for (int vIndex = 0; vIndex < _capacity; vIndex++)
    {
        for (int pairIndex = 0; pairIndex < (int) _table[vIndex].size(); pairIndex++)
        {
            int index = std::hash<KeyT>{}(_table[vIndex][pairIndex].first) & (newSize - 1);
            newTable[index].push_back(_table[vIndex][pairIndex]);
        }
    }
    _capacity = newSize;
    delete[] _table;
    _table = newTable;
}


#endif //CPPEX3_HASHMAP_HPP
