#!/usr/bin/env bash

# Launch publisher and subscriber nodes with cleanup handling

PUBLISHER_PID=""
SUBSCRIBER_PID=""

cleanup() {
    echo ""
    echo "Stopping publisher and subscriber..."

    if [ -n "$PUBLISHER_PID" ]; then
        kill "$PUBLISHER_PID" 2>/dev/null
    fi

    if [ -n "$SUBSCRIBER_PID" ]; then
        kill "$SUBSCRIBER_PID" 2>/dev/null
    fi

    wait "$PUBLISHER_PID" 2>/dev/null
    wait "$SUBSCRIBER_PID" 2>/dev/null

    echo "All ROS 2 processes stopped."
    exit 0
}

trap cleanup SIGINT SIGTERM

# Launch subscriber first
ros2 run ros2_fundamentals_examples py_minimal_subscriber.py &
SUBSCRIBER_PID=$!

sleep 2

# Launch publisher second
ros2 run ros2_fundamentals_examples py_minimal_publisher.py &
PUBLISHER_PID=$!

# Keep script alive until Ctrl+C
wait