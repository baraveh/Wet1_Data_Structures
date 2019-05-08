//
// Created by Bar The magical on 20/04/2019.
//

#ifndef WET1_SCHEDULE_H
#define WET1_SCHEDULE_H

#include "Lecture.h"
#include "List.h"
#include "Array.h"
#include "AVLTree.h"
#include "exception.h"

typedef enum {
    SCHEDULE_SUCCESS = 0,
    SCHEDULE_FAILURE = -1,
    SCHEDULE_MEMORY_ERROR = -2,
    SCHEDULE_INVALID_INPUT = -3
} ScheduleResult;

#define NO_COURSE -1

class Schedule {
private:

    class arrayEntry {
    public:
        Node<int> *roomPtr_m;
        int courseId_m;

        arrayEntry(Node<int> *ptr = nullptr, int courseId = NO_COURSE)
                : roomPtr_m(ptr), courseId_m(courseId) {}

        ~arrayEntry() = default;

        arrayEntry(const arrayEntry &anEntry) = default;

        arrayEntry &operator=(const arrayEntry &anEntry) = default;
    };

    int numOfRooms_m;
    int numOfHours_m;

    int numOfLessons_m;
    int freeHours_m;
    int freeRooms_m;

    Array<Array<arrayEntry>> lectureArr_m; // a 2d array of lesson nodes pointers
    AVLTree<int, AVLTree<Lecture, int>> courseTree_m; // a course tree of lesson trees

    Array<int> roomsArr_m; //array representing available rooms
    Array<int> hoursArr_m; //array representing available hours

    Array<List<int>> availabilityPerHour_m;

    void changeLectureCourseID(AVLNode<Lecture, int> *root, int newCourseID) {
        if (root != nullptr) {
            changeLectureCourseID(root->left_m, newCourseID);
            root->key_m.changeCourseId(newCourseID);
            lectureArr_m[root->key_m.getHour()][root->key_m.getRoom()].courseId_m = newCourseID;
            changeLectureCourseID(root->right_m, newCourseID);
        }
    }


public:

    Schedule(int hours = 1, int rooms = 1) try : numOfRooms_m(rooms),
                                                 numOfHours_m(hours),
                                                 numOfLessons_m(0),
                                                 freeHours_m(hours),
                                                 freeRooms_m(rooms),
                                                 lectureArr_m(hours,
                                                              Array<arrayEntry>(
                                                                      rooms)),

                                                 courseTree_m(),
                                                 roomsArr_m(rooms, 0),
                                                 hoursArr_m(hours, 0),
                                                 availabilityPerHour_m(hours) {
        for (int i = 0; i < hours; i++) {
            for (int j = 0; j < rooms; j++) {
                arrayEntry temp = arrayEntry(
                        availabilityPerHour_m[i].addLast(j),
                        NO_COURSE);
                lectureArr_m[i][j] = temp;
            }
        }
    }
    catch (std::bad_alloc &e) {
        throw MemError();
    }
    catch (MemError &e) {
        throw MemError();
    }

    Schedule(const Schedule &aSchedule) {
        try {
            numOfRooms_m = aSchedule.numOfRooms_m;
            numOfHours_m = aSchedule.numOfHours_m;
            numOfLessons_m = aSchedule.numOfLessons_m;
            freeRooms_m = aSchedule.freeRooms_m;
            freeHours_m = aSchedule.freeHours_m;
            courseTree_m = AVLTree<int, AVLTree<Lecture, int>>(
                    aSchedule.courseTree_m);

            availabilityPerHour_m = Array<List<int>>(numOfHours_m);
            lectureArr_m = Array<Array<arrayEntry>>(numOfHours_m,
                                                    Array<arrayEntry>(
                                                            numOfRooms_m));

            for (int i = 0; i < numOfHours_m; i++) {
                Node<int> *listIterator = aSchedule.availabilityPerHour_m[i].getHead();
                for (int j = 0; j < numOfRooms_m; j++) {
                    arrayEntry temp = arrayEntry(
                            availabilityPerHour_m[i].addLast(
                                    listIterator->data_m),
                            aSchedule.lectureArr_m[i][j].courseId_m);
                    lectureArr_m[i][j] = temp;
                    listIterator = listIterator->next_m;
                }
            }
        }
        catch (std::bad_alloc &e) {
            throw MemError();
        }
        catch (MemError &e) {
            throw MemError();
        }
    }


    ~Schedule() = default;

    Schedule &operator=(const Schedule &aSchedule) {
        if (this == &aSchedule) {
            return *this;
        }
        try {
            numOfRooms_m = aSchedule.numOfRooms_m;
            numOfHours_m = aSchedule.numOfHours_m;
            numOfLessons_m = aSchedule.numOfLessons_m;
            freeRooms_m = aSchedule.freeRooms_m;
            freeHours_m = aSchedule.freeHours_m;

            courseTree_m = AVLTree<int, AVLTree<Lecture, int>>(
                    aSchedule.courseTree_m);

            availabilityPerHour_m = Array<List<int>>(numOfHours_m);
            lectureArr_m = Array<Array<arrayEntry>>(numOfHours_m,
                                                    Array<arrayEntry>(
                                                            numOfRooms_m));

            for (int i = 0; i < numOfHours_m; i++) {
                Node<int> *listIterator = aSchedule.availabilityPerHour_m[i].getHead();
                for (int j = 0; j < numOfRooms_m; j++) {
                    arrayEntry temp = arrayEntry(
                            availabilityPerHour_m[i].addLast(
                                    listIterator->data_m),
                            aSchedule.lectureArr_m[i][j].courseId_m);
                    lectureArr_m[i][j] = temp;
                    listIterator = listIterator->next_m;
                }
            }
        }
        catch (std::bad_alloc &e) {
            throw MemError();
        }
        catch (MemError &e) {
            throw MemError();
        }
    }

    ScheduleResult
    addLecture(const int &hour, const int &room, const int &courseId) {
        if (room < 0 || hour < 0 || courseId <= 0 || room >= numOfRooms_m ||
            hour >= numOfHours_m) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (lectureArr_m[hour][room].courseId_m != NO_COURSE) {
            return SCHEDULE_FAILURE;
        }

        Lecture newLecture = Lecture(hour, room, courseId);
        try {
            if (!courseTree_m.searchKey(courseId)) {
                courseTree_m.insertElement(courseId);
            }
            courseTree_m[courseId].insertElement(newLecture);
        }
        catch (MemError &e) {
            return SCHEDULE_MEMORY_ERROR;
        }

        lectureArr_m[hour][room].courseId_m = courseId;
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

        return SCHEDULE_SUCCESS;
    }

    ScheduleResult
    getCourseId(const int &hour, const int &room, int *courseId) {
        if (room < 0 || hour < 0 || courseId == nullptr ||
            room >= numOfRooms_m ||
            hour >= numOfHours_m) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (lectureArr_m[hour][room].courseId_m == NO_COURSE) {
            return SCHEDULE_FAILURE;
        }

        *courseId = lectureArr_m[hour][room].courseId_m;
        return SCHEDULE_SUCCESS;
    }

    ScheduleResult deleteLecture(const int &hour, const int &roomId) {
        if (roomId < 0 || hour < 0 || roomId >= numOfRooms_m ||
            hour >= numOfHours_m) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (lectureArr_m[hour][roomId].courseId_m == NO_COURSE) {
            return SCHEDULE_FAILURE;

        }

        int courseId = lectureArr_m[hour][roomId].courseId_m;
        Lecture key = Lecture(hour, roomId, courseId);
        courseTree_m[courseId].deleteElement(key);

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
        if (courseTree_m[courseId].getRoot() == nullptr) {
            courseTree_m.deleteElement(courseId);
        }
        return SCHEDULE_SUCCESS;

    }

    ScheduleResult changeCourseId(const int &oldCourse, const int &newCourse) {
        if (oldCourse <= 0 || newCourse <= 0) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (!courseTree_m.searchKey(oldCourse)) {
            return SCHEDULE_FAILURE;
        }
        if (!courseTree_m.searchKey(newCourse)) {
            try {
                courseTree_m.insertElement(newCourse);
            }
            catch (MemError &e) {
                return SCHEDULE_MEMORY_ERROR;
            }
        }

        try {

            courseTree_m[newCourse].mergeTrees(courseTree_m[oldCourse],
                                               courseTree_m[newCourse]);
            changeLectureCourseID(courseTree_m[newCourse].getRoot(), newCourse);
            courseTree_m.deleteElement(oldCourse);
        }
        catch (MemError &e) {
            return SCHEDULE_MEMORY_ERROR;
        }

        return SCHEDULE_SUCCESS;

    }

    ScheduleResult calculateScheduleEfficiency(float *efficiency) {
        if (efficiency == nullptr) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (numOfLessons_m == 0) {
            return SCHEDULE_FAILURE;
        }
        *efficiency = (float(numOfLessons_m) / float(((numOfRooms_m) *
                                                      (numOfHours_m -
                                                       freeHours_m))));
        return SCHEDULE_SUCCESS;
    }

    ScheduleResult
    getAllFreeRoomsByHour(int hour, int **rooms, int *numOfRooms) {
        if (hour < 0 || hour >= numOfHours_m || numOfRooms == nullptr ||
            rooms == nullptr) {
            return SCHEDULE_INVALID_INPUT;
        }

        int res = numOfRooms_m - hoursArr_m[hour];
        if (res == 0) {
            return SCHEDULE_FAILURE;
        }
        *numOfRooms = res;
        int *freeRooms = (int *) malloc(sizeof(*freeRooms) * (*numOfRooms));
        if (!freeRooms) {
            return SCHEDULE_MEMORY_ERROR;
        }

        Node<int> *listIterator = availabilityPerHour_m[hour].getHead();
        for (int i = 0; i < *numOfRooms; i++) {
            freeRooms[i] = listIterator->data_m;
            listIterator = listIterator->next_m;
        }

        *rooms = freeRooms;
        return SCHEDULE_SUCCESS;
    }

    ScheduleResult
    getAllLecturesByCourse(int courseId, int **hours, int **rooms,
                           int *numOfLectures) {
        if (courseId <= 0 || hours == nullptr || rooms == nullptr ||
            numOfLectures ==
            nullptr) {
            return SCHEDULE_INVALID_INPUT;
        }
        if (!courseTree_m.searchKey(courseId)) {
            return SCHEDULE_FAILURE;
        }
        *numOfLectures = courseTree_m[courseId].countNodesInTree();

        Lecture *lectureArr = (Lecture *) malloc(
                sizeof(*lectureArr) * (*numOfLectures));
        int *garbageArr = (int *) malloc(sizeof(int) * (*numOfLectures));
        *rooms = (int *) malloc(sizeof(int) * (*numOfLectures));
        *hours = (int *) malloc(sizeof(int) * (*numOfLectures));
        if (!*rooms || !*hours || !lectureArr || !garbageArr) {
            return SCHEDULE_MEMORY_ERROR;
        }

        courseTree_m[courseId].printTree(lectureArr, garbageArr);
        free(garbageArr);
        for (int i = 0; i < *numOfLectures; i++) {
            (*rooms)[i] = lectureArr[i].getRoom();
            (*hours)[i] = lectureArr[i].getHour();
        }
        free(lectureArr);
        return SCHEDULE_SUCCESS;
    }

};


#endif //WET1_SCHEDULE_H
