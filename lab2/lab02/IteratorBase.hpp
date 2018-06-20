//
//  IteratorBase.hpp
//  lab02
//
//  Created by Garanya Kvasnikov on 16.05.2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#ifndef IteratorBase_hpp
#define IteratorBase_hpp

#include <stdio.h>

#include "Errors.hpp"

template <typename DataType>
class IteratorBase
{
public:
    IteratorBase(const IteratorBase<DataType>& iter);
    IteratorBase(std::shared_ptr<DataType> p){ptr = p;}
    virtual ~IteratorBase();
    IteratorBase<DataType>& operator=(const IteratorBase<DataType>& iter);
    IteratorBase<DataType>& operator++();
    IteratorBase<DataType> operator++(int);
    IteratorBase<DataType>& operator--();
    IteratorBase<DataType> operator--(int);
    
    bool operator ==(const IteratorBase& iter);
    bool operator !=(const IteratorBase& iter);
protected:
    std::weak_ptr<DataType> ptr;
    size_t position;
};

template <typename DataType>
IteratorBase<DataType>::IteratorBase(const IteratorBase<DataType>& iter) : position(iter.position)
{
    ptr = iter.ptr;
}

template <typename DataType>
IteratorBase<DataType>::~IteratorBase()
{
}

template <typename DataType>
IteratorBase<DataType>& IteratorBase<DataType>::operator=(const IteratorBase<DataType>& iter)
{
    ptr = iter.ptr;
    position = iter.position;
    return *this;
}

template <typename DataType>
IteratorBase<DataType>& IteratorBase<DataType>::operator++()
{
    ++position;
    return *this;
}

template <typename DataType>
IteratorBase<DataType> IteratorBase<DataType>::operator++(int)
{
    IteratorBase<DataType> tmp(*this);
    this->operator++();
    return tmp;
}

template <typename DataType>
IteratorBase<DataType>& IteratorBase<DataType>::operator--()
{
    --position;
    return *this;
}

template <typename DataType>
IteratorBase<DataType> IteratorBase<DataType>::operator--(int)
{
    IteratorBase<DataType> tmp(*this);
    this->operator--();
    return tmp;
}

template <typename DataType>
bool IteratorBase<DataType>::operator==(const IteratorBase &iter)
{
    auto thisPtr = ptr.lock();
    auto iterPtr = iter.ptr.lock();

    if (!(thisPtr && iterPtr)) {
        throw WeakPointerError();
    }

    return (thisPtr.get() == iterPtr.get()) && (position == iter.position);
}

template <typename DataType>
bool IteratorBase<DataType>::operator!=(const IteratorBase &iter)
{
    return !(*this == iter);
}

#endif /* IteratorBase_hpp */
