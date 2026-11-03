#include "student/student_set.h"
#include <gtest/gtest.h>

TEST(StudentTest, CopyName) {
    char name[] = "Masha";
    Student a(name, 7);
    name[0] = 'D';
    Student b(a);
    EXPECT_NE(a.name(), b.name());
    EXPECT_STREQ(b.name(), "Masha");
    a = Student("Anya", 8);
    EXPECT_EQ(b.id(), 7);
    EXPECT_STREQ(b.name(), "Masha");
}

TEST(StudentTest, Assignments) {
    Student a("Masha", 7);
    Student b;
    b = a;
    EXPECT_NE(a.name(), b.name());
    Student c(std::move(a));
    EXPECT_STREQ(c.name(), "Masha");
    EXPECT_STREQ(a.name(), "");
    a = std::move(c);
    EXPECT_EQ(a.id(), 7);
    EXPECT_STREQ(c.name(), "");
}

TEST(StudentSetTest, Empty) {
    StudentSet set;
    EXPECT_TRUE(set.empty());
    EXPECT_EQ(set.size(), 0u);
    EXPECT_FALSE(set.contains(Student("Masha", 1)));
}

TEST(StudentSetTest, DuplicateId) {
    StudentSet set;
    EXPECT_TRUE(set.add(Student("Masha", 1)));
    EXPECT_FALSE(set.add(Student("Anya", 1)));
    EXPECT_EQ(set.size(), 1u);
}

TEST(StudentSetTest, Remove) {
    StudentSet set;
    set += Student("Masha", 1);
    EXPECT_TRUE(set.remove(Student("", 1)));
    EXPECT_FALSE(set.remove(Student("", 1)));
    EXPECT_TRUE(set.empty());
}

TEST(StudentSetTest, Membership) {
    StudentSet set;
    Student a("Masha", 1);
    Student b("Dima", 2);
    (set += a) += b;
    EXPECT_EQ(set(a), set.contains(a));
    EXPECT_TRUE(set(b));
    (set -= b) -= a;
    EXPECT_FALSE(set(a));
    EXPECT_FALSE(set(b));
}

TEST(StudentSetTest, Copy) {
    StudentSet original;
    original += Student("Masha", 1);

    StudentSet copy(original);
    StudentSet assigned;
    assigned += Student("Anya", 2);
    assigned = original;
    copy -= Student("", 1);
    assigned += Student("Dima", 3);
    EXPECT_TRUE(copy.empty());
    EXPECT_EQ(assigned.size(), 2u);
    EXPECT_EQ(original.size(), 1u);
    EXPECT_TRUE(original(Student("", 1)));
}

TEST(StudentSetTest, Move) {
    StudentSet source;
    source += Student("Masha", 1);
    StudentSet dest(std::move(source));
    EXPECT_TRUE(source.empty());
    EXPECT_TRUE(dest(Student("", 1)));
    source += Student("Dima", 2);
    dest = std::move(source);
    EXPECT_TRUE(source.empty());
    EXPECT_FALSE(dest(Student("", 1)));
    EXPECT_TRUE(dest(Student("", 2)));
}

TEST(StudentSetTest, SelfAssignment) {
    StudentSet set;
    set += Student("Masha", 1);
    StudentSet &alias = set;
    set = alias;
    set = std::move(alias);
    EXPECT_EQ(set.size(), 1u);
    EXPECT_TRUE(set(Student("", 1)));
}

TEST(StudentSetTest, SetOperations) {
    StudentSet a;
    (a += Student("Masha", 1)) += Student("Dima", 2);
    StudentSet b;
    (b += Student("Another name", 2)) += Student("Anya", 3);

    StudentSet intersection;
    intersection += Student("", 2);
    StudentSet difference;
    difference += Student("", 1);
    StudentSet joined(a);
    joined += Student("", 3);

    EXPECT_EQ(a | b, joined);
    EXPECT_EQ(a & b, intersection);
    EXPECT_EQ(a - b, difference);
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 2u);
}

TEST(StudentSetTest, Equality) {
    StudentSet a;
    (a += Student("A", 1)) += Student("B", 2);
    StudentSet b;
    (b += Student("C", 2)) += Student("D", 1);
    EXPECT_EQ(a, b);
    EXPECT_FALSE(a != b);
    b -= Student("", 1);
    EXPECT_NE(a, b);
}

TEST(StudentSetTest, PrintOrder) {
    StudentSet set;
    set += Student("Masha", 1);
    set += Student("Dima", 2);
    set += Student("Anya", 3);
    set += Student("Oleg", 4);
    set -= Student("", 2);

    std::ostringstream out;
    out << set;
    EXPECT_EQ(out.str(), "{ (Masha, 1), (Anya, 3), (Oleg, 4) }");
}

TEST(StudentSetTest, Stress) {
    StudentSet set;
    for (int id = 0; id < 1000; ++id) {
        ASSERT_TRUE(set.add(Student("Student", id)));
    }
    for (int id = 0; id < 1000; ++id) {
        ASSERT_TRUE(set.contains(Student("", id)));
        ASSERT_FALSE(set.add(Student("Duplicate", id)));
    }
    EXPECT_EQ(set.size(), 1000u);
}
