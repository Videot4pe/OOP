//
//  Errors.hpp
//  lab02
//
//  Created by Garanya Kvasnikov on 16.05.2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#ifndef Errors_hpp
#define Errors_hpp

#include <stdio.h>
#include <exception>

class CommonError : public std::exception
{
public:
    virtual const char *what() const throw()
    {
        return "Undefined error";
    }
};

class SizeError : public CommonError
{
public:
    virtual const char *what() const throw()
    {
        return "Sizes mismatch";
    }
};

class DivisionByZeroError : public CommonError
{
public:
    virtual const char *what() const throw()
    {
        return "Division by zero";
    }
};

class BoundariesError : public CommonError
{
public:
    virtual const char *what() const throw()
    {
        return "Index is out of boundaries";
    }
};

class MemoryError : public CommonError
{
public:
    virtual const char *what() const throw()
    {
        return "Memory couldn't be allocated";
    }
};

class WeakPointerError : public CommonError
{
public:
    virtual const char *what() const throw()
    {
        return "Weak pointer is invalid";
    }
};

#endif /* Errors_hpp */
