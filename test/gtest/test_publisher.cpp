/**
 * @file test_publisher.cpp
 * @brief Unit tests for the ROS 2 minimal publisher node.
 * 
 * This file contains test cases to verify the functionlity of our miniaml publisher.
 * We test two main things:
 * 1. That the node is created correctly with right name and topic
 * 2. That it publishes the expected "Hello World! " message
 * 
 * Testing Framework:
 *  Google Test (gtest) for C++ unit testing
 * 
 * Tests:
 *  TestNodeCreation: Verifies node name and publisher setup
 *  TestMessageContent: Verifies published message format
 * 
 * @author: Moaz Alnor
 * @date: June 1st, 2026
 * 
 */

#include <gtest/gtest.h>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MinimalCppPublisher;

#define TESTING_EXCLUDE_MAIN
#include "../../src/cpp_minimal_publisher.cpp"

class TestMinimalPublisher : public ::testing::Test
{
protected:
    void SetUp() override
    {
        rclcpp::init(0, nullptr);

        node = std::make_shared<MinimalCppPublisher>();

    }
    void TearDown() override
    {
        node.reset();
        rclcpp::shutdown();
    }
    std::shared_ptr<MinimalCppPublisher> node;
};

TEST_F(TestMinimalPublisher, TestNodeCreation)
{
    EXPECT_EQ(std::string(node->get_name()), std::string("minimal_cpp_publisher"));

    auto pub_endpoints = node-> get_publishers_info_by_topic("/cpp_example_topic");
    EXPECT_EQ(pub_endpoints.size(), 1u);
}

TEST_F(TestMinimalPublisher, TestMessageContent)
{
    std::shared_ptr<std_msgs::msg::String> recieved_msg;

    auto subscription = node->create_subscription<std_msgs::msg::String>(
        "/cpp_example_topic", 10,
        [&recieved_msg](const std_msgs::msg::String::SharedPtr _msg) {
            recieved_msg = _msg;
        });

    node->timer_callback();

    rclcpp::spin_some(node);

    ASSERT_NE(recieved_msg, nullptr) << "No message was received!";
    EXPECT_EQ(recieved_msg->data.substr(0, 12),"Hello World!");
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}