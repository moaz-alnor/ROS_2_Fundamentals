/**
 * @file cpp_minimal_publisher.cpp
 * @author Moaz Alnor (moazalnor@my.uopeople.edu)
 * @brief ROS 2 C++ publisher 
 * @version 0.1
 * @date 2026-05-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "rclcpp/rclcpp.hpp"    // ROS 2 C++ client library
#include "std_msgs/msg/string.hpp"  // Standard message type for strings


using namespace std::chrono_literals;  //Handles time duration

class MinimalCppPublisher : public rclcpp::Node
{
    // Grant test class access to private members to enable unit testing
    // of timer_callback() without exposing it publicly.
    // Friend name format: {TestSuiteName}_{TestName}_Test
    friend class TestMinimalPublisher_TestMessageContent_Test;

public:
    MinimalCppPublisher() 
      : Node("minimal_cpp_publisher"), 
      count_(0)
    {
        publisher_ = create_publisher<std_msgs::msg::String>(
            "/cpp_example_topic",
            rclcpp::QoS(10));

        timer_ =create_wall_timer(
            500ms,
            std::bind(&MinimalCppPublisher::timer_callback, this));

        RCLCPP_INFO(get_logger(), "publishing at 2Hz");
    }

private:
    void timer_callback()
    {
        auto message = std_msgs::msg::String();

        message.data = 
            "Hello World! " + std::to_string(count_++);
        
        publisher_-> publish(message);

        RCLCPP_INFO(
            get_logger(),
            "publishing: '%s'",
            message.data.c_str());
    }


    size_t count_;  // keeps track of the number of messages published
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_; // The publisher object
    rclcpp::TimerBase::SharedPtr timer_;    
};

#ifndef TESTING_EXCLUDE_MAIN
int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node = 
        std::make_shared<MinimalCppPublisher>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}
#endif
