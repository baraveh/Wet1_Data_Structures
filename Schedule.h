//
// Created by Bar The magical on 20/04/2019.
//

#ifndef WET1_SCHEDULE_H
#define WET1_SCHEDULE_H

#include "Lecture.h"
#include "List.h"
#include "Array.h"

typedef enum {
    SCHEDULE_SUCCESS = 0,
    SCHEDULE_FAILURE = -1,
    SCHEDULE_MEMORY_ERROR = -2,
    SCHEDULE_INVALID_INPUT = -3
} ScheduleResult;

#define NO_COURSE -1

class Schedule {
private:

    struct arrayEntry {
        Node<int> *roomPtr_m;
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
        for (int i = 0; i < numOfHours_m; i++) {
            for (int j = 0; j < numOfRooms_m; j++) {
                arrayEntry temp = {availabilityPerHour_m[i].addLast(j),
                                   NO_COURSE};
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
        courseTree_m = AvlTree<int, AvlTree<Lecture, int>>(
                aSchedule.courseTree_m);

        availabilityPerHour_m = Array<List<int>>(numOfHours_m);
        lectureArr_m = Array<Array<arrayEntry>>(numOfHours_m, Array<arrayEntry>(
                numOfRooms_m));

        for (int i = 0; i < numOfHours_m; i++) {
            Node<int> *listIterator = aSchedule.availabilityPerHour_m[i].getHead();
            for (int j = 0; j < numOfRooms_m; j++) {
                arrayEntry temp = {
                        availabilityPerHour_m[i].addLast(listIterator->data_m),
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

        courseTree_m = AvlTree<int, AvlTree<Lecture, int>>(
                aSchedule.courseTree_m);

        availabilityPerHour_m = Array<List<int>>(numOfHours_m);
        lectureArr_m = Array<Array<arrayEntry>>(numOfHours_m, Array<arrayEntry>(
                numOfRooms_m));

        for (int i = 0; i < numOfHours_m; i++) {
            Node<int> *listIterator = aSchedule.availabilityPerHour_m[i].getHead();
            for (int j = 0; j < numOfRooms_m; j++) {
                arrayEntry temp = {
                        availabilityPerHour_m[i].addLast(listIterator->data_m),
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
        if (lectureArr_m[room][hour].courseId_m != NO_COURSE) {
            return SCHEDULE_FAILURE;
        }

        roomsArr_m[room]++;
        hoursArr_m[hour]++;
        numOfLessons_m++;
        if (roomsArr_m[room] == 1) {
            //first lesson in this room
            freeRooms_m--;
        }
        if (hoursArr_m[hour] == 1) {
            //first lesson in this hour
            freeHours_m--;
        }

        availabilityPerHour_m[hour].moveNodeToEnd(
                lectureArr_m[hour][room].roomPtr_m);

        lectureArr_m[hour][room].courseId_m = courseId;
        Lecture newLecture = Lecture(hour, room, courseId);
        //TODO - add lecture to tree
    }

    ScheduleResult
    getCourseId(const int &hour, const int &room, int *courseId) {
        if (room < 0 || hour < 0 || courseId == nullptr ||
            room >= numOfRooms_m ||
            hour >= numOfHours_m) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (lectureArr_m[room][hour].courseId_m == NO_COURSE) {
            return SCHEDULE_FAILURE;
        }

        *courseId = lectureArr_m[room][hour].courseId_m;
        return SCHEDULE_SUCCESS;
    }

    ScheduleResult deleteLecture(const int &hour, const int &roomId) {
        if (roomId < 0 || hour < 0 || roomId >= numOfRooms_m ||
            hour >= numOfHours_m) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (lectureArr_m[roomId][hour].courseId_m == NO_COURSE) {
            return SCHEDULE_FAILURE;

        }

        roomsArr_m[roomId]--;
        hoursArr_m[hour]--;
        numOfLessons_m--;
        if (roomsArr_m[roomId] == 0) {
            //last lesson in this room
            freeRooms_m++;
        }
        if (hoursArr_m[hour] == 0) {
            //last lesson in this hour
            freeHours_m++;
        }

        availabilityPerHour_m[hour].moveNodeToStart(
                lectureArr_m[hour][roomId].roomPtr_m);
        lectureArr_m[hour][roomId].courseId_m = NO_COURSE;

        //TODO - remove lecture from tree
    }

    ScheduleResult changeCourseId(const int &oldCourse, const int &newCourse) {

    }

    ScheduleResult calculateScheduleEfficiency(float *efficiency) {
        if (efficiency == nullptr) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (numOfLessons_m == 0) {
            return SCHEDULE_FAILURE;
        }
        *efficiency = (numOfLessons_m / ((numOfRooms_m - freeRooms_m) *
                                         (numOfHours_m - freeHours_m)));
        return SCHEDULE_SUCCESS;
    }

    ScheduleResult
    getAllFreeRoomsByHour(int hour, int **rooms, int *numOfRooms) {
        if (hour < 0 || hour >= numOfHours_m || numOfRooms == nullptr ||
            rooms == nullptr) {
            return SCHEDULE_INVALID_INPUT;
        }

        *numOfRooms = numOfRooms_m - hoursArr_m[hour];
        int* freeRooms = (int*)malloc(sizeof(*freeRooms)*(*numOfRooms));
        if(!freeRooms){
            return SCHEDULE_MEMORY_ERROR;
        }

        Node<int>* listIterator = availabilityPerHour_m[hour].getHead();
        for(int i = 0; i < *numOfRooms; i++){
            freeRooms[i] = listIterator->data_m;
            listIterator = listIterator->next_m;
        }

        *rooms = freeRooms;
        return SCHEDULE_SUCCESS;
    }

    ScheduleResult getAllLecturesByCourse(int courseId, int** hours, int** rooms, int* numOfLectures){
        if(courseId <= 0 || hours == nullptr || rooms == nullptr || numOfLectures ==
                                                                            nullptr){
            return SCHEDULE_INVALID_INPUT;
        }
        //TODO
    }

};


#endif //WET1_SCHEDULE_H
