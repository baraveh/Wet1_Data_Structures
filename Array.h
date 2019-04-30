//
// Created by Bar on 26-Apr-19.
//

#ifndef WET1_DATA_STRUCTURES_ARRAY_H
#define WET1_DATA_STRUCTURES_ARRAY_H

template <typename T>
class Array {
    T* array_m;
    int size_m;
public:

    explicit Array(const int& size = 0, const T& defVal = T()){
        size_m = size;
        array_m = new T[size_m]{defVal};
    }

    Array(const int& size = 0): size_m(size){
      array_m = new T[size_m];
    }

    Array(const Array& aArray){
        size_m = aArray.size_m;
        array_m = new  T[size_m];
        for(int i =0; i < size_m; i++){
            array_m[i] = aArray[i];
        }
    }
    ~Array(){
        delete[] array_m;
    }

    Array& operator=(const Array& aArray){
        T* temp = array_m;
        array_m = new T[aArray.size_m];
        delete temp;
        size_m = aArray.size_m;
        for(int i =0; i < aArray.size_m; i++){
            array_m[i] = aArray.array_m[i];
        }
    }

    T& operator[](const int& index){
       return array_m[index];
    }

    const T& operator[] (const int& index) const{
        return array_m[index];
    }

    int& getSize(){
        return size_m;
    }

};


#endif //WET1_DATA_STRUCTURES_ARRAY_H
