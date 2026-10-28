#include "memory.h"
#include "gtest/gtest.h"

class MemoryTest : public testing::Test
{
    protected:
    Memory m;

    MemoryTest()
    {
        // You can do set-up work for each test here.
        m = Memory();
    }

    ~MemoryTest() override
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
};


TEST_F(MemoryTest, store)
{
    EXPECT_THROW( m.store(-1, '1'), std::out_of_range ); // too low
    EXPECT_THROW( m.store(DEFAULT_MEMORY_SIZE, '1'), std::out_of_range ); // too high
    EXPECT_EQ( m.load(0), 0 ); // valid address
    EXPECT_EQ( m.store(0, 'H'), 0);
    EXPECT_EQ( m.load(0), 'H' ); // valid address
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
