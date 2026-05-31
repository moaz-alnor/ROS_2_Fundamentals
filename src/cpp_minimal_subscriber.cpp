/**
 * @file cpp_minimal_subscriber.cpp
 * @author Moaz Alnor (moazalnor@my.uopeople.edu)
 * @brief  Demonstrate ROS 2 C++ subscriber
 * @version 0.1
 * @date 2026-05-31
 *
 * @copyright Copyright (c) 2026
 * --------
 * Subscription Topics:
 *  String message
 *  /cpp_example_topic - std_msgs/String
 * --------
 * Publishing Topic:
 *  None
 */

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;  

class MinimalCppSubscriber : public rclcpp::Node
{
public:
    MinimalCppSubscriber() : Node("minimal_cpp_subscriber")
    {
        subscriber_ = create_subscription<std_msgs::msg::String>(  
            "/cpp_example_topic",
            10,
            std::bind(
                &MinimalCppSubscriber::topicCallback,
                this,
                _1
            )
        );

        subscriber_2_ = create_subscription<std_msgs::msg::String>(
            "/py_example_topic",
            10,
            std::bind(
                &MinimalCppSubscriber::pyTopicCallback,
                this,
                _1
            )
        );
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_2_;

    void topicCallback(const std_msgs::msg::String & msg) const  
    {
        RCLCPP_INFO_STREAM(get_logger(), "I heard: " << msg.data);  
    }

    void pyTopicCallback(const std_msgs::msg::String & msg) const
    {
        RCLCPP_INFO_STREAM(get_logger(), "I heard from Python: " << msg.data);
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MinimalCppSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;  
}