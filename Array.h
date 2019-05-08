//
// Created by Bar on 26-Apr-19.
//

#ifndef WET1_DATA_STRUCTURES_ARRAY_H
#define WET1_DATA_STRUCTURES_ARRAY_H

#include "exception.h"
template <typename T>
class Array {
    T* array_m;
    int size_m;
public:

    Array(const int& size = 1, const T& defVal = T()){
        size_m = size;
        array_m = new T[size_m];
        for(int i = 0; i < size; i++){
            array_m[i] = defVal;
        }
    }


    Array(const Array& aArray){
        size_m = aArray.size_m;
        array_m = new  T[size_m];
        for(int i =0; i < size_m; i++){
            array_m[i] = aArray[i];
        }
    }
    ~Array(){
        delete [] array_m;
    }

    Array& operator=(const Array& aArray){
        if(this == &aArray){
            return *this;
        }
        T* temp = array_m;
        array_m = new T[aArray.size_m];
        delete [] temp;
        size_m = aArray.size_m;
        for(int i =0; i < aArray.size_m; i++){
            array_m[i] = aArray.array_m[i];
        }
        return *this;
    }

    T& operator[](const int& index){
        if(index >= size_m){
            throw IllegalIndex();
        }
       return array_m[index];
    }

    const T& operator[] (const int& index) const{
        if(index >= size_m){
            throw IllegalIndex();
        }
        return array_m[index];
    }

    int& getSize(){
        return size_m;
    }

};


#endif //WET1_DATA_STRUCTURES_ARRAY_H
