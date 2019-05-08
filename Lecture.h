//
// Created by Bar on 26-Apr-19.
//

#ifndef WET1_DATA_STRUCTURES_LESSON_H
#define WET1_DATA_STRUCTURES_LESSON_H


class Lecture {
    int hour_m;
    int room_m;
    int courseId_m;

public:
    Lecture(const int& hour= 0, const int& room = 0, const int& courseId = -1);
    Lecture(const Lecture& aLesson){
        hour_m = aLesson.hour_m;
        room_m = aLesson.room_m;
        courseId_m = aLesson.courseId_m;
    }
    ~Lecture() = default;

    Lecture& operator=(const Lecture& aLesson);

    void changeCourseId(int newCourseId);

    int getRoom();
    int getHour();

    bool operator==(const Lecture& aLesson);
    bool operator < (const Lecture& aLesson);
    bool operator <= (const Lecture& aLesson);
    bool operator > (const Lecture& aLesson);
    bool operator >= (const Lecture& aLesson);

    friend bool operator < (const Lecture& a, const Lecture& b);
    friend bool operator > (const Lecture& a, const Lecture& b);
    friend bool operator <= (const Lecture& a, const Lecture& b);
    friend bool operator >= (const Lecture& a, const Lecture& b);
    friend bool operator == (const Lecture& a, const Lecture& b);
};



#endif //WET1_DATA_STRUCTURES_LESSON_H
