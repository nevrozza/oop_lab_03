#include "student_set.h"

#include <ostream>

StudentSet::StudentSet(const StudentSet &other)
    : size_(other.size_), capacity_(other.capacity_) {
    if (capacity_ == 0) {
        return;
    }
    data_ = new Student[capacity_];
    try {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    } catch (...) {
        delete[] data_;
        throw;
    }
}

StudentSet::StudentSet(StudentSet &&other) noexcept {
    swap(other);
}

StudentSet &StudentSet::operator=(const StudentSet &other) {
    if (this != &other) {
        StudentSet copy(other);
        swap(copy);
    }
    return *this;
}

StudentSet &StudentSet::operator=(StudentSet &&other) noexcept {
    if (this != &other) {
        StudentSet moved(std::move(other));
        swap(moved);
    }
    return *this;
}

StudentSet::~StudentSet() {
    delete[] data_;
}

void StudentSet::swap(StudentSet &other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

void StudentSet::grow() {
    std::size_t new_capacity = capacity_ ? capacity_ * 2 : 1;
    Student *bigger = new Student[new_capacity];
    for (std::size_t i = 0; i < size_; ++i) {
        bigger[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = bigger;
    capacity_ = new_capacity;
}

std::size_t StudentSet::find(const Student &student) const {
    for (std::size_t i = 0; i < size_; ++i) {
        if (data_[i] == student) {
            return i;
        }
    }
    return size_;
}

bool StudentSet::add(const Student &student) {
    if (contains(student)) {
        return false;
    }

    Student copy(student);
    if (size_ == capacity_) {
        grow();
    }
    data_[size_] = std::move(copy);
    ++size_;
    return true;
}

bool StudentSet::remove(const Student &student) {
    std::size_t pos = find(student);
    if (pos == size_) {
        return false;
    }

    for (std::size_t i = pos; i + 1 < size_; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }
    --size_;
    data_[size_] = Student();
    return true;
}

bool StudentSet::contains(const Student &student) const {
    return find(student) != size_;
}

bool StudentSet::operator()(const Student &student) const {
    return contains(student);
}

std::size_t StudentSet::size() const {
    return size_;
}

bool StudentSet::empty() const {
    return size_ == 0;
}

StudentSet &StudentSet::operator+=(const Student &student) {
    add(student);
    return *this;
}

StudentSet &StudentSet::operator-=(const Student &student) {
    remove(student);
    return *this;
}

StudentSet StudentSet::operator|(const StudentSet &other) const {
    StudentSet result(*this);
    for (std::size_t i = 0; i < other.size_; ++i) {
        result.add(other.data_[i]);
    }
    return result;
}

StudentSet StudentSet::operator&(const StudentSet &other) const {
    StudentSet result;
    for (std::size_t i = 0; i < size_; ++i) {
        if (other.contains(data_[i])) {
            result.add(data_[i]);
        }
    }
    return result;
}

StudentSet StudentSet::operator-(const StudentSet &other) const {
    StudentSet result;
    for (std::size_t i = 0; i < size_; ++i) {
        if (!other.contains(data_[i])) {
            result.add(data_[i]);
        }
    }
    return result;
}

bool StudentSet::operator==(const StudentSet &other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (std::size_t i = 0; i < size_; ++i) {
        if (!other.contains(data_[i])) {
            return false;
        }
    }
    return true;
}

bool StudentSet::operator!=(const StudentSet &other) const {
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &out, const StudentSet &set) {
    out << "{ ";
    for (std::size_t i = 0; i < set.size_; ++i) {
        if (i != 0) {
            out << ", ";
        }
        out << set.data_[i];
    }
    return out << (set.empty() ? "}" : " }");
}
