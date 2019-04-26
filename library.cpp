//
// Created by Bar The magical on 20/04/2019.
//

#include "library.h"
#include "Schedule.h"
void*Init(int hours, int rooms) {
    auto * DS = new Schedule(hours, rooms);
    return (void*)DS;
}
StatusType AddLecture(void *DS, int hour, int roomID, int courseID) {
    if(!DS){
        return INVALID_INPUT;
    }
    return StatusType(((Schedule *)DS)-> addLecture(hour, roomID, courseID));
}

StatusType GetCourseID(void *DS, int hour, int roomID, int *courseID) {
    if(!DS){
        return INVALID_INPUT;
    }
    return StatusType(((Schedule*)DS)->getCourseId(hour, roomID, courseID));
}

StatusType DeleteLecture(void *DS, int hour, int roomID) {
    if(!DS){
        return INVALID_INPUT;
    }
    return StatusType(((Schedule*)DS)->deleteLecture(hour, roomID));
}

StatusType ChangeCourseID(void *DS, int oldCourseID, int newCourseID) {
    if(!DS){
        return INVALID_INPUT;
    }
    return StatusType(((Schedule*)DS)->changeCourseId(oldCourseID, newCourseID));
}

StatusType CalculateScheduleEfficiency(void *DS, float *efficiency) {
    if(!DS){
        return INVALID_INPUT;
    }
    return StatusType(((Schedule*)DS)->calculateScheduleEfficiency(efficiency));
}

StatusType
GetAllFreeRoomsByHour(void *DS, int hour, int **rooms, int *numOfRooms) {
    if(!DS){
        return INVALID_INPUT;
    }
    return StatusType(((Schedule*)DS)->getAllFreeRoomsByHour(hour, rooms, numOfRooms));
}

StatusType
GetAllLecturesByCourse(void *DS, int courseID, int **hours, int **rooms,
                       int *numOfLectures) {
    if(!DS){
        return INVALID_INPUT;
    }
    return StatusType(((Schedule*)DS)->getAllLecturesByCourse(courseID, hours, rooms, numOfLectures));
}

void Quit(void **DS) {
    DS = nullptr;
}



