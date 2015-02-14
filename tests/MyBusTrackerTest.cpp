#include "buslib/MyBusTracker.h"
#include "gtest/gtest.h"

TEST(MyBusTrackerTest, TestApiKeyHash) {
    // Using the example given in the MyBusTracker documentation
    const std::string api_key = "ABCDEFGHIJKLMNOPQRSTUVWXY";
    const QDateTime datetime(QDate(2011, 4, 27), QTime(18, 34));
    const std::string expected_result = "149e15ab76beb9cf3cb195468e0c75ae";

    ASSERT_EQ(expected_result, Buslib::MyBusTracker::GetHashedKey(api_key, datetime));
}
