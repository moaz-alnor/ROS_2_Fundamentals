#!/usr/bin/env python3 

"""
Test suite for the ROS 2 minimal publisher node.

This script contains unit tests for verifying the functionality of a minimal ROS 2 publisher
It test the node creation, message counter increment, and message content formatting.

------
Subscription Topics:
    None

-----------
Publishing Topics:
    /py_example_topic (std_msgs/msg/String): Example messages with incrementing counter

author: Moaz Alnor
date: June 1st, 2026 

"""

import pytest
import rclpy
from std_msgs.msg import String
from ros2_fundamentals_examples.py_minimal_publisher import MinimalPyPublisher

def test_publisher_creation():
    """
    Test if the publisher node is created correctly
    This test verifies:
    1. The node name is set correctly.
    2. The publisher object exists.
    3. The topic name is correct.
    
    :raises: AssertionErorr if any of the checks fail
    """
    # Initialize ROS 2 communication
    rclpy.init()

    try:
        # Create an instance of out publisher node 
        node = MinimalPyPublisher()

        # Test 1: verify the node has the expected name 
        assert node.get_name() == "minimal_py_publisher"

        # Test 2: verify the publisher exist and has the correct topic name
        assert hasattr(node, 'publisher_1')
        assert node.publisher_1.topic_name == '/py_example_topic'
    finally:
        # Clean up ROS 2 communication
        rclpy.shutdown()


def test_message_counter():
    """
    Test if the message counter increment correctly 

    This test verifies that the counter (node.i) increases by 1 after each
    timer callback execution.

    :raises: AsserionError if the counter doesn't increment properly
    """

    rclpy.init()

    try:
        node = MinimalPyPublisher()
        initial_count = node.i
        node.timer_callback()
        assert node.i == initial_count + 1 
    finally:
        rclpy.shutdown()

def test_message_content():
    """
    Test if the message content if formatted correctly

    This test verifies that the message string is properly formatted using an f-string with 
    current counter value.

    :raises: AssertionError if the message format doesn't match the expected output
    """                

    rclpy.init()

    try:
        node = MinimalPyPublisher()

        # Set counter to a known value for testing 
        node.i = 5 
        msg = String()

        # Using f-string instead of % formatting
        msg.data = f'Hello World: {node.i}'
        assert msg.data == 'Hello World: 5'

    finally:
        rclpy.shutdown()

if __name__ == '__main__':
    pytest.main(['-v'])                