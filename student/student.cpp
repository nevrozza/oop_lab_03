#include "student.h"

#include <ostream>

Student::Student(const char *name, int id) : id_(id) {
    if (name && *name) {
        name_ = new char[std::strlen(name) + 1];
        std::strcpy(name_, name);
    }
}

Student::Student(const Student &other) : Student(other.name_, other.id_) {}

Student::Student(Student &&other) noexcept {
    swap(other);
}

Student &Student::operator=(const Student &other) {
    if (this != &other) {
        Student copy(other);
        swap(copy);
    }
    return *this;
}

Student &Student::operator=(Student &&other) noexcept {
    if (this != &other) {
        Student moved(std::move(other));
        swap(moved);
    }
    return *this;
}

Student::~Student() {
    delete[] name_;
}

void Student::swap(Student &other) noexcept {
    std::swap(name_, other.name_);
    std::swap(id_, other.id_);
}

const char *Student::name() const {
    return name_ ? name_ : "";
}

int Student::id() const {
    return id_;
}

bool Student::operator==(const Student &other) const {
    return id_ == other.id_;
}

std::ostream &operator<<(std::ostream &out, const Student &student) {
    return out << '(' << student.name() << ", " << student.id() << ')';
}
