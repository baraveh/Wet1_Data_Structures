//
// Created by Bar The magical on 20/04/2019.
//

#include "library.h"
#include "Schedule.h"
void *Init(int hours, int rooms) {
    Schedule *DS = new Schedule(hours, rooms);
    return (void*)DS;
}
StatusType AddLecture(void *DS, int hour, int roomID, int courseID) {
    return ((Schedule *)DS)-> AddLecture(hour, roomID, courseID);
}


