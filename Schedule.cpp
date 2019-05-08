//
// Created by Bar The magical on 20/04/2019.
//

/*#include "Schedule.h"

int main(){
    ScheduleResult res;
    Schedule s1 = Schedule(2,2);
    res =s1.addLecture(0,0, 234218);
    assert(res == SCHEDULE_SUCCESS);
    s1.addLecture(1,1, 234218);
    assert(res == SCHEDULE_SUCCESS);
    int courseId = 0;
    s1.getCourseId(0,0, &courseId);
    assert(courseId == 234218);
    s1.getCourseId(1,1, &courseId);
    assert(courseId == 234218);
    float efficiency = 0;
    s1.calculateScheduleEfficiency(&efficiency);
    assert(efficiency == 0.5);
    int numOfRooms;
    int* rooms;
    res = s1.getAllFreeRoomsByHour(1, &rooms, &numOfRooms);
    assert(res == SCHEDULE_SUCCESS);
    assert(numOfRooms == 1);
    assert(room[0] == 0);
    res = s1.changeCourseId(234218, 234219);
    free(rooms);
    assert(res == SCHEDULE_SUCCESS);
    int* hoursLectures;
    int* roomsLectures;
    int numOfLectures;
    res = s1.getAllLecturesByCourse(234219, &hoursLectures, &roomsLectures, &numOfLectures);
    assert(res == SCHEDULE_SUCCESS);
    assert(hoursLectures[0] == 0);
    assert(hoursLectures[1] == 1);
    assert(roomsLectures[0] == 0);
    assert(roomsLectures[1] == 1);
    assert(numOfLectures == 2);
    free(hoursLectures);
    free(roomsLectures);
    res = s1.deleteLecture(0,0);
    assert(res == SCHEDULE_SUCCESS);
    float efficiency2 = 0;
    res = s1.calculateScheduleEfficiency(&efficiency2);
    assert(res == SCHEDULE_SUCCESS && efficiency2 == 0.5);
} */