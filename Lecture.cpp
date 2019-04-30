//
// Created by Bar on 26-Apr-19.
//

#include "Lecture.h"

bool Lecture::operator==(const Lecture &aLecture) {
    return room_m == aLecture.room_m && hour_m == aLecture.hour_m;
}

bool Lecture::operator<(const Lecture &aLecture) {
    return !(operator>(aLecture) || operator==(aLecture));
}

bool operator<(const Lecture &a, const Lecture &b) {
    return !(a > b || a == b);
}

bool Lecture::operator>=(const Lecture &aLecture) {
    return (operator>(aLecture) || operator==(aLecture));
}

bool Lecture::operator>(const Lecture &aLecture) {
    return (hour_m > aLecture.hour_m ||
            (hour_m == aLecture.hour_m && room_m > aLecture.room_m));
}

bool Lecture::operator<=(const Lecture &aLecture) {
    return !(operator>(aLecture));
}

Lecture &Lecture::operator=(const Lecture &aLecture) {
    hour_m = aLecture.hour_m;
    room_m = aLecture.room_m;
    courseId_m = aLecture.courseId_m;
}

Lecture::Lecture(const int &hour, const int &room, const int &courseId)
        : hour_m(hour), room_m(room), courseId_m(courseId) {}

bool operator>(const Lecture &a, const Lecture &b) {
    return (a.hour_m > b.hour_m ||
            (a.hour_m == b.hour_m && a.room_m > b.room_m));
}

bool operator<=(const Lecture &a, const Lecture &b) {
    return (a < b || a == b);
}

bool operator>=(const Lecture &a, const Lecture &b) {
    return (a > b || a == b);
}

bool operator==(const Lecture &a, const Lecture &b) {
    return (a.room_m == b.room_m && a.hour_m == b.hour_m);
}

void Lecture::changeCourseId(int newCourseId) {
    courseId_m = newCourseId;
}
