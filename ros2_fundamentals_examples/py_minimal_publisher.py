#!/usr/bin/env python3

""" 
Description:
    This ROS 2  node periodically publishes "Hello World" messages to a topic.

-----
Publishing Topics:
    This channel containing the "Hello World" messages
    /py_example_topic - std_msgs/String

Subscription Topics:
    None

-----
Author: Moaz Alnor
Date: May 28, 2026     
"""

import rclpy  # Import the ROS 2 client libaray for python
from rclpy.node import Node # Import the node class, used for creating nodes

from std_msgs.msg import String # Import String message type for ROS 2


class MinimalPyPublisher(Node):
    """Create a minimal publisher node.

    """
    def __init__(self):
        """ create a custom node class for publishing messages 
        """
        # Initialize the node with a name
        super().__init__('Minimal_Py_Publisher')

        #create a publisher on the topic with a queue size of 10 messages
        self.publisher_1 = self.create_publisher(String, '/py_example_topic', 10)

        # create a timer with a period of 0.5 seconds to trigger publishing of message 
        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_callback)

        # Initialize a counter veriable for message content
        self.i = 0


    def timer_callback(self):
        """Callback function executed periodically by the timer
        """
        # create a new string message object 
        msg = String()

        #set the message data with a counter
        msg.data = 'Hello World: %d ' % self.i

        #publish the message you created above to a topic 
        self.publisher_1.publish(msg)

        # Log a message indicating the message has been published 
        self.get_logger().info('publishing: "%s"' % msg.data)

        self.i = self.i + 1 

def main(args=None):
    """Main function to start the ROS 2 node
    
    Args:
        args(List, optional): Command-line arguments. default to none.
    """
    rclpy.init(args=args)

    #Create an instance of the minimal publisher node
    minimal_py_publisher = MinimalPyPublisher()

    rclpy.spin(minimal_py_publisher)

    # destroy the node explicitly
    minimal_py_publisher.destroy_node()

    #shutdown ROS 2 communication
    rclpy.shutdown()

if __name__ == '__main__':
    # Execute the main function if the script is run directly
    main()            