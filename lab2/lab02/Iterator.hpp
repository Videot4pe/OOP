//
//  Iterator.hpp
//  lab02
//
//  Created by Garanya Kvasnikov on 16.05.2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#ifndef Iterator_hpp
#define Iterator_hpp

#include <stdio.h>
#include "IteratorBase.hpp"
#include "VectorBase.hpp"

template <typename DataType>
class Iterator : public IteratorBase<DataType>
{
public:
    Iterator(const Iterator<DataType>& iter);
    Iterator(std::shared_ptr<DataType> p, size_t position = 0);
    DataType& operator*();
    const DataType operator*() const;
    DataType *operator->();
    const DataType *operator->() const;
};

template <typename DataType>
class IteratorConst : public IteratorBase<DataType>
{
public:
    IteratorConst(const IteratorConst<DataType>& iter);
    IteratorConst(const std::shared_ptr<DataType> p, size_t position = 0);
    const DataType operator*() const;
    const DataType *operator->() const;
};

template <typename DataType>
Iterator<DataType>::Iterator(const Iterator<DataType>& iter) : IteratorBase<DataType>(std::shared_ptr<DataType>(iter.ptr))
{
    this->position = iter.position;
}

template <typename DataType>
Iterator<DataType>::Iterator(std::shared_ptr<DataType> p, size_t position) : IteratorBase<DataType>(p)
{
    this->position = position;
}

template <typename DataType>
DataType& Iterator<DataType>::operator*()
{
    auto thisPtr = this->ptr.lock();

    if (!thisPtr) {
        throw WeakPointerError();
    }

    DataType *rawData = thisPtr.get();
    DataType *pointedData = rawData + this->position;
    return *(pointedData);
}

template <typename DataType>
const DataType Iterator<DataType>::operator*() const
{
    auto thisPtr = this->ptr.lock();

    if (!thisPtr) {
        throw WeakPointerError();
    }

    DataType *rawData = thisPtr.get();
    DataType *pointedData = rawData + this->position;
    return *(pointedData);
}

template <typename DataType>
DataType *Iterator<DataType>::operator->()
{
    auto thisPtr = this->ptr.lock();

    if (!thisPtr) {
        throw WeakPointerError();
    }

    DataType *rawData = thisPtr.get();
    DataType *pointedData = rawData + this->position;
    return pointedData;
}

template <typename DataType>
const DataType *Iterator<DataType>::operator->() const
{
    auto thisPtr = this->ptr.lock();

    if (!thisPtr) {
        throw WeakPointerError();
    }

    DataType *rawData = thisPtr.get();
    DataType *pointedData = rawData + this->position;
    return pointedData;
}

template <typename DataType>
IteratorConst<DataType>::IteratorConst(const IteratorConst<DataType>& iter)
{
    this->position = iter.position;
    this->ptr = iter.ptr;
}

template <typename DataType>
IteratorConst<DataType>::IteratorConst(const std::shared_ptr<DataType> p, size_t position)
{
    this->ptr = p;
    this->position = position;
}

template <typename DataType>
const DataType IteratorConst<DataType>::operator*() const
{
    auto thisPtr = this->ptr.lock();

    if (!thisPtr) {
        throw WeakPointerError();
    }

    DataType *rawData = thisPtr.get();
    DataType *pointedData = rawData + this->position;
    return *(pointedData);
}

template <typename DataType>
const DataType *IteratorConst<DataType>::operator->() const
{
    auto thisPtr = this->ptr.lock();

    if (!thisPtr) {
        throw WeakPointerError();
    }

    DataType *rawData = thisPtr.get();
    DataType *pointedData = rawData + this->position;
    return pointedData;
}

#endif /* Iterator_hpp */
