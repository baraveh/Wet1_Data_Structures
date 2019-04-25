//
// Created by Bar The magical on 20/04/2019.
//

#ifndef WET1_SCHEDULE_H
#define WET1_SCHEDULE_H

#include "AVL.h"
#include "List.h"

class Schedule {
private:
    int numOfRooms_m;
    int numOfHours_m;
    Lesson*** array_m; // an array of lesson pointers
    AvlTree<int, List<Lesson>> courseTree_m;

public:

    Schedule(int hours = 0, int rooms = 0): numOfHours_m(hours), numOfRooms_m(rooms){
        array_m = new Lesson**[rooms];
        for(int i = 0; i <rooms; i++){
            array_m[i] = new Lesson*[hours];
        }
        courseTree_m = AvlTree<int, List<Lesson>>();
    }

    Schedule(const Schedule& toCopy): numOfRooms_m(toCopy.numOfRooms_m), numOfHours_m(toCopy.numOfHours_m){
        array_m = new Lesson**[numOfRooms_m];
        for(int i = 0; i < numOfRooms_m; i++){
            array_m[i] = new Lesson*[numOfHours_m];
        }
        for(int i = 0; i < numOfRooms_m; i++){
            for(int j = 0; j < numOfHours_m; j++){
                array_m[i][j] = toCopy.array_m[i][j];
            }
        }
        courseTree_m = AvlTree<int, List<Lesson>>(toCopy.courseTree_m);
    }

    ~Schedule(){
        for(int j = 0; j < numOfHours_m; j++){
            delete array_m[j];
        }
        delete array_m;
    }

};


#endif //WET1_SCHEDULE_H
