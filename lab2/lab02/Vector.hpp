//
//  vector.hpp
//  lab02
//
//  Created by Garanya Kvasnikov on 16.04.2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <iostream>
#include <math.h>
#include <memory>

#include "VectorBase.hpp"
#include "Iterator.hpp"
#include "Errors.hpp"

template<typename DataType>
class Vector : public VectorBase
{
public:
    Vector(const std::vector<DataType> &data);
    Vector();
    Vector(DataType* data);
    Vector(std::initializer_list<DataType> data);
    Vector(const Vector<DataType> &other);
    Vector(Vector<DataType> &&other);
    Vector(size_t size);
    virtual ~Vector();
    DataType length() const;
    Vector<DataType> norm() const;
    DataType angle(const Vector<DataType> &other) const;
    Vector<DataType> vectorMult (const Vector<DataType> &other) const;

    void abstract() override {};
    
    bool ort(const Vector<DataType> &other) const;
    DataType operator * (const Vector<DataType> &other) const;

    Iterator<DataType> begin();
    Iterator<DataType> end();
    IteratorConst<DataType> begin() const;
    IteratorConst<DataType> end() const;
    
    Vector<DataType> & operator = (const Vector<DataType> &other);
    Vector<DataType> & operator = (Vector<DataType> &&other);
    Vector<DataType> & operator = (std::initializer_list<DataType> data);
    Vector<DataType> & operator += (const Vector<DataType> &other);
    Vector<DataType> & operator -= (const Vector<DataType> &other);
    Vector<DataType> & operator *= (DataType k);
    Vector<DataType> & operator /= (DataType k);
    bool operator == (const Vector<DataType> &other) const;
    bool operator != (const Vector<DataType> &other) const;
    bool operator >= (const Vector<DataType> &other) const;
    bool operator <= (const Vector<DataType> &other) const;
    
    Vector<DataType> operator * (DataType k) const;
    Vector<DataType> operator / (DataType k) const;
    Vector<DataType> operator + (const Vector<DataType> &other) const;
    Vector<DataType> operator - (const Vector<DataType> &other) const;
    Vector<DataType> operator - () const;
    Vector<DataType> operator + () const;
    Vector<DataType> operator - ();
    Vector<DataType> operator + ();
    
    DataType & operator [] (std::size_t i);
    const DataType & operator [] (std::size_t i) const;
    
private:
    std::shared_ptr<DataType> coords;
};

template<typename DataType>
Vector<DataType> Vector<DataType>::norm() const
{
    for (int i = 0; i < size(); i++)
        coords.get()[i] = coords.get()[i] / length();
    return *this;
}

template<typename DataType>
DataType Vector<DataType>::angle(const Vector<DataType> &other) const
{
    DataType angle = 1;
    if (size() != other.size()) {
        throw SizeError();
    }
    for (int i = 0; i < size(); i++)
        angle = angle + (coords.get()[i] * other.coords.get()[i]);
    return angle / (length() * other.length());
}

template<typename DataType>
Vector<DataType>::Vector(const std::vector<DataType> &data)
{
    setSize(data.size());
    coords = std::shared_ptr<DataType>((DataType *)malloc(data.size() * sizeof(DataType)), free);
    
    if (coords.get() == nullptr) {
        throw MemoryError();
    }
    
    for (size_t i = 0; i < data.size(); i++)
        coords.get()[i] = data[i];
}

template<typename DataType>
Vector<DataType>::Vector(DataType* data)
{
    setSize(data->size());
    coords = std::shared_ptr<DataType>((DataType *)malloc(data->size() * sizeof(DataType)), free);
    
    if (coords.get() == nullptr) {
        throw MemoryError();
    }
    
    for (size_t i = 0; i < data->size(); i++)
        coords.get()[i] = data[i];
}

template<typename DataType>
Vector<DataType>::Vector()
{
    setSize(0);
    coords = std::shared_ptr<DataType>((DataType *)malloc(0 * sizeof(DataType)), free);
    
    if (coords.get() == nullptr) {
        throw MemoryError();
    }
}

template<typename DataType>
Vector<DataType>::Vector(Vector<DataType> &&other)
{
    setSize(other.size());
    coords = std::shared_ptr<DataType>((DataType *)malloc(other.size() * sizeof(DataType)), free);
    
    if (coords.get() == nullptr) {
        throw MemoryError();
    }
    
    for (size_t i = 0; i < other.size(); i++)
        coords.get()[i] = other[i];
    other.coords = nullptr;
    other.resize(0);
}

template<typename DataType>
Vector<DataType>::Vector(size_t size)
{
    setSize(size);
    coords = std::shared_ptr<DataType>((DataType *)malloc(size * sizeof(DataType)), free);
    
    if (coords.get() == nullptr) {
        throw MemoryError();
    }
    
    for (size_t i = 0; i < size; i++)
        coords.get()[i] = 0;
}

template<typename DataType>
Vector<DataType>::Vector(std::initializer_list<DataType> data)
{
    setSize(data.size());
    coords = std::shared_ptr<DataType>((DataType *)malloc(data.size() * sizeof(DataType)), free);
    
    if (coords.get() == nullptr) {
        throw MemoryError();
    }
    
    size_t i = 0;
    for(auto& coord : data)
    {
        coords.get()[i] = coord;
        i++;
    }
}

template<typename DataType>
Vector<DataType>::Vector(const Vector<DataType> &other)
{
    setSize(other.size());
    coords =  std::shared_ptr<DataType>((DataType *)malloc(other.size() * sizeof(DataType)), [=](DataType *rawCoords)
                                        {
                                            free(rawCoords);
                                        });
    
    if (coords.get() == nullptr) {
        throw MemoryError();
    }
    
    for (size_t i = 0; i < other.size(); i++)
        coords.get()[i] = other[i];
}

template<typename DataType>
Vector<DataType>::~Vector()
{
}

//template<typename DataType>
//void Vector<DataType>::resize(size_t newSize)
//{
//    VectorBase::resize(newSize);
//    coords = (DataType *)realloc(coords, newSize * sizeof(DataType));
//
//    if (coords == NULL) {
//        throw MemoryError();
//    }
//}

template<typename DataType>
Vector<DataType> & Vector<DataType>::operator += (const Vector<DataType> &other)
{
    if (size() != other.size()) {
        throw SizeError();
    }
    
    for (size_t i = 0; i < size(); i++)
        coords.get()[i] += other.coords.get()[i];
    return *this;
}

template<typename DataType>
Vector<DataType> & Vector<DataType>::operator -= (const Vector<DataType> &other)
{
    if (size() != other.size()) {
        throw SizeError();
    }
    
    for (size_t i = 0; i < size(); i++)
        coords.get()[i] -= other.coords.get()[i];
    return *this;
}

template<typename DataType>
Vector<DataType> & Vector<DataType>::operator *= (DataType k)
{
    for (size_t i = 0; i < size(); i++)
        coords.get()[i] *= k;
    return *this;
}

template<typename DataType>
Vector<DataType> Vector<DataType>::vectorMult (const Vector<DataType> &other) const
{
    if (size() != other.size()) {
        throw SizeError();
    }

    for (size_t i = 0; i < size(); i++)
        coords.get()[i] *= other.coords.get()[i];
    return *this;
}

template<typename DataType>
Vector<DataType> & Vector<DataType>::operator /= (DataType k)
{
    if (k == 0.) {
        throw DivisionByZeroError();
    }
    
    for (size_t i = 0; i < size(); i++)
        coords.get()[i] /= k;
    return *this;
}

template<typename DataType>
bool Vector<DataType>::operator == (const Vector<DataType> &other) const
{
    if (size() != other.size()) {
        throw SizeError();
    }
    
    bool equal = true;
    for (size_t i = 0; i < size(); i++) {
        if (coords.get()[i] != other.coords.get()[i]) {
            equal = false;
            break;
        }
    }
    
    return equal;
}

template<typename DataType>
bool Vector<DataType>::operator != (const Vector<DataType> &other) const
{
    if (size() != other.size()) {
        throw SizeError();
    }
    
    return ! (*this == other);
}

template<typename DataType>
bool Vector<DataType>::operator >= (const Vector<DataType> &other) const
{
    if (size() != other.size()) {
        throw SizeError();
    }
    
    return length() >= other.length();
}

template<typename DataType>
bool Vector<DataType>::ort(const Vector<DataType> &other) const
{
    if (size() != other.size()) {
        throw SizeError();
    }
    DataType sum = 0;
    for (size_t i = 0; i < size(); i++)
        sum += this->coords.get()[i]*other.coords.get()[i];
    return (sum == 0);
}

template<typename DataType>
DataType Vector<DataType>::operator * (const Vector<DataType> &other) const
{
    if (size() != other.size()) {
        throw SizeError();
    }
    DataType sum = 0;
    for (size_t i = 0; i < size(); i++)
        sum += coords.get()[i] * other.coords.get()[i];
    return sum;
}

template<typename DataType>
bool Vector<DataType>::operator <= (const Vector<DataType> &other) const
{
    if (size() != other.size()) {
        throw SizeError();
    }
    return length() <= other.length();
}

template<typename DataType>
DataType Vector<DataType>::length() const
{
    DataType sum = 0;
    for (size_t i = 0; i < size(); i++)
        sum += coords.get()[i] * coords.get()[i];
    sum = sqrt(sum);
    return sum;
}

template<typename DataType>
Vector<DataType> & Vector<DataType>::operator = (const Vector<DataType> &other)
{
    if (size() != other.size()) {
        throw SizeError();
    }
    
    for (size_t i = 0; i < size(); i++)
        this->coords.get()[i] = other.coords.get()[i];
    
    return *this;
}

template<typename DataType>
Vector<DataType> & Vector<DataType>::operator = (Vector<DataType> &&other)
{
    if (size() != other.size()) {
        throw SizeError();
    }
    
    for (size_t i = 0; i < size(); i++)
        this->coords.get()[i] = other.coords.get()[i];
    
    other.coords = nullptr;
    other.resize(0);
    return *this;
}

template<typename DataType>
Vector<DataType> & Vector<DataType>::operator = (std::initializer_list<DataType> data)
{
    if (size() != data.size()) {
        throw SizeError();
    }
    
    int i = 0;
    for(auto& coord : data)
    {
        coords.get()[i] = coord;
        i++;
    }
    
    return *this;
}

template<typename DataType>
Vector<DataType> Vector<DataType>::operator + (const Vector<DataType> &other) const
{
    if (size() != other.size()) {
        throw SizeError();
    }
    
    Vector<DataType> tmp(*this);
    
    for (size_t i = 0; i < size(); i++)
        tmp.coords.get()[i] += other.coords.get()[i];
    
    return tmp;
}

template<typename DataType>
Vector<DataType> Vector<DataType>::operator - (const Vector<DataType> &other) const
{
    if (size() != other.size()) {
        throw SizeError();
    }
    Vector<DataType> tmp(*this);
    
    for (size_t i = 0; i < size(); i++)
        tmp.coords.get()[i] -= other.coords.get()[i];
    
    return tmp;
}

template<typename DataType>
Vector<DataType> Vector<DataType>::operator / (DataType k) const
{
    if (k == 0.) {
        throw DivisionByZeroError();
    }
    
    Vector<DataType> tmp(*this);
    return tmp /= k;
}

template<typename DataType>
Vector<DataType> Vector<DataType>::operator * (DataType k) const
{
    Vector<DataType> tmp(*this);
    return tmp *= k;
}

template<typename DataType>
Vector<DataType> Vector<DataType>::operator - ()
{
    Vector<DataType> tmp(*this);
    return tmp *= -1;
}

template<typename DataType>
Vector<DataType> Vector<DataType>::operator + ()
{
    Vector<DataType> tmp(*this);
    return tmp *= 1;
}

template<typename DataType>
DataType & Vector<DataType>::operator [] (std::size_t i)
{
    if ((i < 0) || (i >= size())) {
        throw BoundariesError();
    }
    return coords.get()[i];
}

template<typename DataType>
const DataType & Vector<DataType>::operator [] (std::size_t i) const
{
    if ((i < 0) || (i >= size())) {
        throw BoundariesError();
    }
    return coords.get()[i];
}

template<class DataType>
std::ostream & operator << (std::ostream &os, const Vector<DataType> &vector)
{
    os << "\n" << "Vector<" << typeid(DataType).name() << "> { ";
    for (size_t i = 0; i < vector.size(); i++)
    {
        os << vector[i];
        if (i != vector.size() - 1) {
            os << ", ";
        }
    }
    os << " }" << std::endl;
    return os;
}

template <typename DataType>
Iterator<DataType> Vector<DataType>::begin()
{
    Iterator<DataType> it(coords);
    return it;
}

template <typename DataType>
Iterator<DataType> Vector<DataType>::end()
{
    return Iterator<DataType>(coords, size());
}

template <typename DataType>
IteratorConst<DataType> Vector<DataType>::begin() const
{
    return IteratorConst<DataType>(coords.get());
}

template <typename DataType>
IteratorConst<DataType> Vector<DataType>::end() const
{
    return IteratorConst<DataType>(coords + size());
}

#endif /* Vector_hpp */

