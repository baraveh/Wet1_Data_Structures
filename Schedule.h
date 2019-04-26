//
// Created by Bar The magical on 20/04/2019.
//

#ifndef WET1_SCHEDULE_H
#define WET1_SCHEDULE_H

#include "AVL.h"
#include "List.h"

typedef enum {
    SCHEDULE_SUCCESS = 0,
    SCHEDULE_FAILURE = -1,
    SCHEDULE_INVALID_INPUT = -3
} ScheduleResult;

class Schedule {
private:

    struct Lesson {
        int courseId;
        int room;
        int hour;
    };

    int numOfRooms_m;
    int numOfHours_m;
    Node<Lesson> ***array_m; // a 2d array of lesson nodes pointers
    AvlTree<int, List<Lesson>> courseTree_m;

public:

    Schedule(int hours = 0, int rooms = 0) : numOfHours_m(hours),
                                             numOfRooms_m(rooms) {
        array_m = new (Node<Lesson> **)[rooms];
        for (int i = 0; i < rooms; i++) {
            array_m[i] = new Node<Lesson> *[hours];
        }
        for (int i = 0; i < numOfRooms_m; i++) {
            for (int j = 0; j < numOfHours_m; j++) {
                array_m[i][j] = nullptr;
            }
        }
        courseTree_m = AvlTree<int, List<Lesson>>();
    }

    Schedule(const Schedule &toCopy) : numOfRooms_m(toCopy.numOfRooms_m),
                                       numOfHours_m(toCopy.numOfHours_m) {
        array_m = new Node<Lesson> **[numOfRooms_m];
        for (int i = 0; i < numOfRooms_m; i++) {
            array_m[i] = new Node<Lesson> *[numOfHours_m];
        }
        for (int i = 0; i < numOfRooms_m; i++) {
            for (int j = 0; j < numOfHours_m; j++) {
                array_m[i][j] = toCopy.array_m[i][j];
            }
        }
        courseTree_m = AvlTree<int, List<Lesson>>(toCopy.courseTree_m);
    }

    ~Schedule() {
        for (int j = 0; j < numOfHours_m; j++) {
            delete array_m[j];
        }
        delete array_m;
    }

    Schedule &operator=(const Schedule &aSchedule) {

        for (int j = 0; j < numOfHours_m; j++) {
            delete array_m[j];
        }
        delete array_m;

        numOfRooms_m = aSchedule.numOfRooms_m;
        numOfHours_m = aSchedule.numOfHours_m;

        array_m = new Node<Lesson> **[numOfRooms_m];
        for (int i = 0; i < numOfRooms_m; i++) {
            array_m[i] = new Node<Lesson> *[numOfHours_m];
        }
        for (int i = 0; i < numOfRooms_m; i++) {
            for (int j = 0; j < numOfHours_m; j++) {
                array_m[i][j] = aSchedule.array_m[i][j];
            }
        }

        courseTree_m = AvlTree<int, List<Lesson>>(aSchedule.courseTree_m);
    }

    ScheduleResult addLecture(int hour, int room, int courseId) {
        if (room < 0 || hour < 0 || courseId <= 0 || room >= numOfRooms_m ||
            hour >= numOfHours_m) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (array_m[room][hour] != nullptr) {
            return SCHEDULE_FAILURE;
        }

        Lesson toAdd = {courseId, room, hour};
        array_m[room][hour] = courseTree_m[courseId].addLast(toAdd);
        //TODO: operator [] on avl should return the list, if course id doesnt exist it should create a new entry for it
        return SCHEDULE_SUCCESS;
    }

};


#endif //WET1_SCHEDULE_H
