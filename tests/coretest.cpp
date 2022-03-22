#include "core.h"
#include "helper.h"
#include <gtest/gtest.h>

TEST(st,st1){
    ASSERT_EQ(10, sum(1,9));
}

int main(int argc, char* argv[]){
     ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

