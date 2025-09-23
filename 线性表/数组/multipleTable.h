//
// Created by Ko-chieh Yin on 9/23/25.
//

#ifndef STUDYALGORITHMS_MULTIPLETABLE_H
#define STUDYALGORITHMS_MULTIPLETABLE_H

#include <vector>
#include <optional>
#include <stdexcept>
#include <algorithm>
#include <iostream>

// 多重表的实现 （一个连续空间，多个线性表）
template<class T>
class multipleTable {
public:
    explicit multipleTable(size_t initialCapacity = 100, float loadFactor = 0.5, size_t tableCount = 1);
    multipleTable(const multipleTable<T>& list);

    [[nodiscard]] bool empty(size_t index) const { return tableLengths[index] == 0; }
    [[nodiscard]] size_t size(size_t index) const { return tableLengths[index]; }
    const T& get(size_t index, size_t indexInTable) const;
    std::optional<size_t> indexOf(size_t index, const T& element) const;
    void erase(size_t index, size_t indexInTable);
    void insert(size_t index, size_t indexInTable, const T& element);

    [[nodiscard]] size_t tableCapacity() const { return storage.capacity(); }

private:
    void expandStorage(size_t index, size_t indexInTable, size_t& pos);

    std::vector<T> storage;
    float loadFactor;
    size_t tableCount;
    std::vector<size_t> tableStartSets; // 每张表的起始位置
    std::vector<size_t> tableLengths;   // 每张表的当前大小
};

// 构造
template<class T>
multipleTable<T>::multipleTable(size_t initialCapacity, float loadFactor, size_t tableCount)
        : storage(),
          loadFactor(loadFactor),
          tableCount(tableCount),
          tableStartSets(tableCount, 0),
          tableLengths(tableCount, 0) {
    storage.reserve(initialCapacity); // 预留容量
    if (tableCount > 0) {
        size_t block = initialCapacity / tableCount;
        for (size_t i = 0; i < tableCount; i++) {
            tableStartSets[i] = i * block;
        }
    }
}

// 拷贝构造
template<class T>
multipleTable<T>::multipleTable(const multipleTable<T>& list)
        : storage(list.storage),
          loadFactor(list.loadFactor),
          tableCount(list.tableCount),
          tableStartSets(list.tableStartSets),
          tableLengths(list.tableLengths) {}

// 扩容
template<class T>
void multipleTable<T>::expandStorage(size_t index, size_t indexInTable, size_t& pos) {
    size_t newCap = std::max(static_cast<size_t>(storage.capacity() * (1 + loadFactor)), size_t(1));
    std::vector<T> newStorage;
    newStorage.reserve(newCap);

    auto oldStarts = tableStartSets;
    size_t startSet = 0;

    for (size_t i = 0; i < tableCount; i++) {
        tableStartSets[i] = startSet;
        for (size_t j = 0; j < tableLengths[i]; j++) {
            newStorage.push_back(storage[oldStarts[i] + j]);
        }
        startSet += tableLengths[i];
    }

    storage.swap(newStorage);
    pos = tableStartSets[index] + indexInTable;
}

// 插入
template<class T>
void multipleTable<T>::insert(size_t index, size_t indexInTable, const T& element) {
    if (index >= tableCount) throw std::out_of_range("不存在这个表");
    if (indexInTable > tableLengths[index]) throw std::out_of_range("插入位置非法");

    size_t pos = tableStartSets[index] + indexInTable;
    if (storage.size() >= storage.capacity()) {
        expandStorage(index, indexInTable, pos);
    }

    //自动填充
    if (pos>storage.size()) {
        while (storage.size() < pos) {
            storage.push_back(T());
        }
    }

    storage.insert(storage.begin() + pos, element);
    tableLengths[index]++;

    for (size_t j = index + 1; j < tableCount; j++) {
        tableStartSets[j]++;
    }
}

// 获取
template<class T>
const T& multipleTable<T>::get(size_t index, size_t indexInTable) const {
    return storage.at(tableStartSets[index] + indexInTable);
}

// 查找
template<class T>
std::optional<size_t> multipleTable<T>::indexOf(size_t index, const T& element) const {
    for (size_t i = 0; i < tableLengths[index]; i++) {
        if (storage[tableStartSets[index] + i] == element) {
            return i; // 返回表内下标
        }
    }
    return {};
}

// 删除
template<class T>
void multipleTable<T>::erase(size_t index, size_t indexInTable) {
    storage.erase(storage.begin() + tableStartSets[index] + indexInTable);
    tableLengths[index]--;
    for (size_t j = index + 1; j < tableCount; j++) {
        tableStartSets[j]--;
    }
}

#endif //STUDYALGORITHMS_MULTIPLETABLE_H