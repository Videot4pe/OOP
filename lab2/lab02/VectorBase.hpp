//
//  VectorBase.hpp
//  lab02
//
//  Created by Garanya Kvasnikov on 07.05.2018.
//  Copyright © 2018 Videot4pe. All rights reserved.
//

#ifndef base_hpp
#define base_hpp

#include <stdio.h>

class VectorBase
{
private:
    size_t _size;
protected:
    void setSize(size_t newSize) { _size = newSize; };
public:
    virtual size_t size() const { return _size; };
    virtual void resize(size_t newSize) { setSize(newSize); };
    virtual void abstract() = 0;
};


#endif /* base_hpp */
