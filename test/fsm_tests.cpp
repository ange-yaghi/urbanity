#include "pch.h"

#include "fsm_test.h"

TEST(FsmTests, FsmSanityCheck) {
    urb::FsmTest test;
    test.initialize();

    EXPECT_EQ(test.id<urb::FsmTestState<0>>(), 0);
    EXPECT_EQ(test.id<urb::FsmTestState<1>>(), 1);
    EXPECT_EQ(test.id<urb::FsmTestState<2>>(), 2);
}
