//
// Created by Bar The magical on 20/04/2019.
//

#ifndef WET1_SCHEDULE_H
#define WET1_SCHEDULE_H

#include "AVL.h"
#include "Lecture.h"
#include "List.h"
#include "Array.h"

typedef enum {
    SCHEDULE_SUCCESS = 0,
    SCHEDULE_FAILURE = -1,
    SCHEDULE_INVALID_INPUT = -3
} ScheduleResult;

class Schedule {
private:

    struct arrayEntry{
        Node<int>* roomPtr_m;
        int courseId_m;
    };
    
    int numOfRooms_m;
    int numOfHours_m;

    int numOfLessons_m;
    int freeHours_m;
    int freeRooms_m;

    Array<Array<arrayEntry>> lectureArr_m; // a 2d array of lesson nodes pointers
    AvlTree<int, AvlTree<Lecture, int>> courseTree_m; // a course tree of lesson trees

    Array<int> roomsArr_m; //array representing available rooms
    Array<int> hoursArr_m; //array representing available hours

    Array<List<int>> availabilityPerHour_m;


public:

    Schedule(int hours = 0, int rooms = 0) : numOfRooms_m(rooms),
                                             numOfHours_m(hours),
                                             freeHours_m(hours),
                                             freeRooms_m(rooms),
                                             numOfLessons_m(0),
                                             roomsArr_m(rooms, 0),
                                             hoursArr_m(hours, 0) {
        
        availabilityPerHour_m = Array<List<int>>(numOfHours_m);
        lectureArr_m = Array<Array<arrayEntry>>(numOfHours_m);
        for(int i =0; i < numOfHours_m; i++){
            for(int j = 0; j < numOfRooms_m; j++){
                arrayEntry temp = {availabilityPerHour_m[i].addLast(j),
                                   -1};
                lectureArr_m[i][j] = temp;
            }
        }
        courseTree_m = AvlTree<int, AvlTree<Lecture, int>>();
    }

    Schedule(const Schedule &aSchedule) {
        numOfRooms_m = aSchedule.numOfRooms_m;
        numOfHours_m = aSchedule.numOfHours_m;
        numOfLessons_m = aSchedule.numOfLessons_m;
        freeRooms_m = aSchedule.freeRooms_m;
        freeHours_m = aSchedule.freeHours_m;
        courseTree_m = AvlTree<int, AvlTree<Lecture, int>>(aSchedule.courseTree_m);

        availabilityPerHour_m = Array<List<int>>(numOfHours_m);
        lectureArr_m = Array<Array<arrayEntry>>(numOfHours_m, Array<arrayEntry>(numOfRooms_m));

        for(int i =0 ; i < numOfHours_m; i++){
            Node<int>* listIterator = aSchedule.availabilityPerHour_m[i].getHead();
            for(int j = 0; j < numOfRooms_m; j++){
                arrayEntry temp = {availabilityPerHour_m[i].addLast(listIterator->data_m),
                                   aSchedule.lectureArr_m[i][j].courseId_m};
                lectureArr_m[i][j] = temp;
                listIterator = listIterator->next_m;
            }
        }

    }

    ~Schedule() = default; //TODO there might be an issue here since freeing the array with the list references in it will cause double free

    Schedule &operator=(const Schedule &aSchedule) {

        numOfRooms_m = aSchedule.numOfRooms_m;
        numOfHours_m = aSchedule.numOfHours_m;
        numOfLessons_m = aSchedule.numOfLessons_m;
        freeRooms_m = aSchedule.freeRooms_m;
        freeHours_m = aSchedule.freeHours_m;

        courseTree_m = AvlTree<int, AvlTree<Lecture, int>>(aSchedule.courseTree_m);

        availabilityPerHour_m = Array<List<int>>(numOfHours_m);
        lectureArr_m = Array<Array<arrayEntry>>(numOfHours_m, Array<arrayEntry>(numOfRooms_m));

        for(int i =0 ; i < numOfHours_m; i++){
            Node<int>* listIterator = aSchedule.availabilityPerHour_m[i].getHead();
            for(int j = 0; j < numOfRooms_m; j++){
                arrayEntry temp = {availabilityPerHour_m[i].addLast(listIterator->data_m),
                                   aSchedule.lectureArr_m[i][j].courseId_m};
                lectureArr_m[i][j] = temp;
                listIterator = listIterator->next_m;
            }
        }


    }

    ScheduleResult
    addLecture(const int &hour, const int &room, const int &courseId) {
        if (room < 0 || hour < 0 || courseId <= 0 || room >= numOfRooms_m ||
            hour >= numOfHours_m) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (array_m[room][hour] != nullptr) {
            return SCHEDULE_FAILURE;
        }

    }

    ScheduleResult
    getCourseId(const int &hour, const int &room, int *courseId) {
        if (room < 0 || hour < 0 || courseId == nullptr ||
            room >= numOfRooms_m ||
            hour >= numOfHours_m) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (array_m[room][hour] == nullptr) {
            return SCHEDULE_FAILURE;
        }

        *courseId = (array_m[room][hour])->key;
        return SCHEDULE_SUCCESS;
    }

    ScheduleResult deleteLecture(const int &hour, const int &roomId) {
        if (roomId < 0 || hour < 0 || roomId >= numOfRooms_m ||
            hour >= numOfHours_m) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (array_m[roomId][hour] == nullptr) {
            return SCHEDULE_FAILURE;

        }
    }

    ScheduleResult changeCourseId(const int &oldCourse, const int &newCourse) {

    }

};


#endif //WET1_SCHEDULE_H
