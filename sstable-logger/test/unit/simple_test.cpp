//
// Created by strahinja on 7/23/22.
//

#include <data-structures/sstable-logger/ss_table_logger.hpp>

#include <gtest/gtest.h>

#include <string>
#include <vector>

TEST(SSTableLoggerTest, RetrieveFromEmptyLogReturnsNull)
{
    SSTableLogger<int, std::string> logger;
    EXPECT_FALSE(logger.Retrieve(1));
}

TEST(SSTableLoggerTest, LogAndRetrieve)
{
    SSTableLogger<int, std::string, std::vector<int>> logger;

    const auto value1 = 34;
    const std::string value2 = "thirty four";
    const std::vector<int> value3 = {45, 56, 67};
    logger.Log(1, value1, value2, value3);

    auto result = logger.Retrieve(1);
    ASSERT_TRUE(result);
    EXPECT_EQ(std::tie(value1, value2, value3), result);
}

TEST(SSTableLoggerTest, RetrieveUnknownReturnsNull)
{
    SSTableLogger<int, std::string> logger;
    logger.Log(1, 22, "twenty two");
    EXPECT_FALSE(logger.Retrieve(0));
}
