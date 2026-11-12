
#include <gtest/gtest.h>
#include <stdexcept>
#include <utility>

#include "polygon_collection.hpp"
#include "triangle.hpp"
#include "square.hpp"
#include "pentagon.hpp"

TEST(CollectionTest, DefaultConstructor) {
    PolygonCollection collection;
    EXPECT_EQ(collection.size(), 0u);
    EXPECT_DOUBLE_EQ(collection.totalMetric(), 0.0);
}

TEST(CollectionTest, AddAndTotalMetric) {
    PolygonCollection collection;
    collection.add(Triangle({0, 0}, {4, 0}, {2, 3}));
    collection.add(Square({0, 0}, {2, 0}, {2, 2}, {0, 2}));
    collection.add(Pentagon());
    EXPECT_EQ(collection.size(), 3u);
    EXPECT_DOUBLE_EQ(collection.totalMetric(), 12.5);
}

TEST(CollectionTest, RemoveMiddleElement) {
    PolygonCollection collection;
    collection.add(Triangle());
    collection.add(Square());
    collection.add(Pentagon());
    collection.remove(1);
    EXPECT_EQ(collection.size(), 2u);
    EXPECT_NE(dynamic_cast<Pentagon*>(&collection.at(1)), nullptr);
}

TEST(CollectionTest, RemoveLastElement) {
    PolygonCollection collection;
    collection.add(Triangle());
    collection.add(Square());
    collection.remove(1);
    EXPECT_EQ(collection.size(), 1u);
    EXPECT_NE(dynamic_cast<Triangle*>(&collection.at(0)), nullptr);
}

TEST(CollectionTest, InvalidIndex) {
    PolygonCollection collection;
    EXPECT_THROW(collection.at(0), std::out_of_range);
    EXPECT_THROW(collection.remove(0), std::out_of_range);
    collection.add(Triangle());
    EXPECT_THROW(collection.at(1), std::out_of_range);
    EXPECT_THROW(collection.remove(1), std::out_of_range);
}

TEST(CollectionTest, ConstAccess) {
    PolygonCollection collection;
    collection.add(Triangle());
    const PolygonCollection& ref = collection;
    EXPECT_DOUBLE_EQ(ref.at(0).metric(), 0.5);
}

TEST(CollectionTest, DeepCopyConstructor) {
    PolygonCollection original;
    original.add(Triangle());
    original.add(Square());
    PolygonCollection copy(original);
    ASSERT_EQ(copy.size(), 2u);
    EXPECT_NE(&original.at(0), &copy.at(0));
    EXPECT_NE(&original.at(1), &copy.at(1));
    copy.remove(0);
    EXPECT_EQ(copy.size(), 1u);
    EXPECT_EQ(original.size(), 2u);
}

TEST(CollectionTest, CopyAssignment) {
    PolygonCollection original;
    original.add(Triangle());
    original.add(Square());
    PolygonCollection copy;
    copy.add(Pentagon());
    copy = original;
    ASSERT_EQ(copy.size(), 2u);
    EXPECT_NE(&copy.at(0), &original.at(0));
    original.remove(0);
    EXPECT_EQ(original.size(), 1u);
    EXPECT_EQ(copy.size(), 2u);
}

TEST(CollectionTest, MoveConstructor) {
    PolygonCollection original;
    original.add(Triangle());
    original.add(Square());
    PolygonCollection moved(std::move(original));
    EXPECT_EQ(moved.size(), 2u);
    EXPECT_EQ(original.size(), 0u);
    EXPECT_DOUBLE_EQ(moved.totalMetric(), 1.5);
}

TEST(CollectionTest, MoveAssignment) {
    PolygonCollection original;
    original.add(Triangle());
    PolygonCollection target;
    target.add(Square());
    target = std::move(original);
    EXPECT_EQ(target.size(), 1u);
    EXPECT_EQ(original.size(), 0u);
    EXPECT_NE(dynamic_cast<Triangle*>(&target.at(0)), nullptr);
}

TEST(CollectionTest, SelfAssignment) {
    PolygonCollection collection;
    collection.add(Triangle());
    PolygonCollection& same = collection;
    collection = same;
    EXPECT_EQ(collection.size(), 1u);
    EXPECT_DOUBLE_EQ(collection.totalMetric(), 0.5);
}

TEST(CollectionTest, ClearAndReuse) {
    PolygonCollection collection;
    collection.add(Triangle());
    collection.add(Square());
    collection.clear();
    EXPECT_EQ(collection.size(), 0u);
    EXPECT_DOUBLE_EQ(collection.totalMetric(), 0.0);
    collection.add(Pentagon());
    EXPECT_EQ(collection.size(), 1u);
    EXPECT_DOUBLE_EQ(collection.totalMetric(), 2.5);
}
