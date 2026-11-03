#pragma once

#include "student.h"
#include <cstddef>

class StudentSet {
public:
    StudentSet() = default;
    StudentSet(const StudentSet &other);
    StudentSet(StudentSet &&other) noexcept;
    StudentSet &operator=(const StudentSet &other);
    StudentSet &operator=(StudentSet &&other) noexcept;
    ~StudentSet();

    bool add(const Student &student);
    bool remove(const Student &student);
    bool contains(const Student &student) const;
    bool operator()(const Student &student) const;
    std::size_t size() const;
    bool empty() const;

    StudentSet &operator+=(const Student &student);
    StudentSet &operator-=(const Student &student);
    StudentSet operator|(const StudentSet &other) const;
    StudentSet operator&(const StudentSet &other) const;
    StudentSet operator-(const StudentSet &other) const;
    bool operator==(const StudentSet &other) const;
    bool operator!=(const StudentSet &other) const;
    friend std::ostream &operator<<(std::ostream &out, const StudentSet &set);

private:
    Student *data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;

    void swap(StudentSet &other) noexcept;
    void grow();
    std::size_t find(const Student &student) const;
};
