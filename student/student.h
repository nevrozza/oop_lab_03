#pragma once

#include <iosfwd>

class Student {
public:
    Student() = default;
    Student(const char *name, int id);
    Student(const Student &other);
    Student(Student &&other) noexcept;
    Student &operator=(const Student &other);
    Student &operator=(Student &&other) noexcept;
    ~Student();

    const char *name() const;
    int id() const;
    bool operator==(const Student &other) const;
    friend std::ostream &operator<<(std::ostream &out, const Student &student);

private:
    char *name_ = nullptr;
    int id_ = 0;

    void swap(Student &other) noexcept;
};
