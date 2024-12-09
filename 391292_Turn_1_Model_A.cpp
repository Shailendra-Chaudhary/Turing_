// my_template.h
template <typename T>
class MyTemplate {
public:
    T add(T a, T b) {
        return a + b;
    }
};

// my_template.cpp
#include "my_template.h"

// my_test.cpp
#include "my_template.h"
#include <gtest/gtest.h>

TEST(MyTemplateTest, AddInt) {
    MyTemplate<int> templateInstance;
    EXPECT_EQ(templateInstance.add(1, 2), 3);
}

TEST(MyTemplateTest, AddDouble) {
    MyTemplate<double> templateInstance;
    EXPECT_EQ(templateInstance.add(1.0, 2.0), 3.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
