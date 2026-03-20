#!/usr/bin/env python3
import numpy as np
import cv2
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point
from pathlib import Path

# Found using colorzilla the browser extension
lower = np.array([20, 80, 80], dtype=np.uint8)
upper = np.array([35, 255, 255], dtype=np.uint8)
path = Path.home() / "Desktop" / "02_mustard.png"

# choose which version to display
# options: "original", "hsv", "mask", "output"
display_mode = "original"

# dictionary for the state of the bounding box coords
state = {
    "left_upper": (0, 0),
    "right_upper": (0, 0),
    "left_lower": (0, 0),
    "right_lower": (0, 0),
    "corner_count": 0
}


class CenterPointPublisher(Node):
    def __init__(self):
        super().__init__('center_point_publisher')
        self.publisher_ = self.create_publisher(Point, '/center_point', 10)

    def publish_center(self, u, v):
        msg = Point()
        msg.x = float(u)
        msg.y = float(v)
        msg.z = 0.0
        self.publisher_.publish(msg)
        self.get_logger().info(f'Published pixel center: ({u}, {v})')


def main():
    rclpy.init()
    node = CenterPointPublisher()

    resize_amount = 1
    img = cv2.imread(str(path))
    resized = cv2.resize(img, None, fx=resize_amount, fy=resize_amount, interpolation=cv2.INTER_AREA)

    hsv = cv2.cvtColor(resized, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, lower, upper)
    output = cv2.bitwise_and(resized, resized, mask=mask)

    if display_mode == "original":
        display_img = resized.copy()
    elif display_mode == "hsv":
        display_img = cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR)
    elif display_mode == "mask":
        display_img = cv2.cvtColor(mask, cv2.COLOR_GRAY2BGR)
    elif display_mode == "output":
        display_img = output.copy()
    else:
        raise ValueError("display_mode must be one of: original, hsv, mask, output")

    def draw_circle(event, x, y, flags, param):
        nonlocal display_img

        if event == cv2.EVENT_LBUTTONDBLCLK:
            cv2.circle(display_img, (x, y), 5, (0, 0, 255), -1)

            if param["corner_count"] == 0:
                param["left_upper"] = (x, y)
                print(f'Left_Upper Pixel = {param["left_upper"]}')
            elif param["corner_count"] == 1:
                param["right_upper"] = (x, y)
                print(f'Right_Upper Pixel = {param["right_upper"]}')
            elif param["corner_count"] == 2:
                param["left_lower"] = (x, y)
                print(f'Left_Lower Pixel = {param["left_lower"]}')
            elif param["corner_count"] == 3:
                param["right_lower"] = (x, y)
                print(f'Right_Lower Pixel = {param["right_lower"]}')

            param["corner_count"] += 1

    cv2.namedWindow('image')
    cv2.setMouseCallback('image', draw_circle, state)

    box_drawn = False
    published = False

    while True:
        cv2.imshow('image', display_img)

        if box_drawn is False and state["corner_count"] >= 4:
            cv2.line(display_img, state["left_upper"], state["right_upper"], (255, 0, 0), 5)
            cv2.line(display_img, state["right_upper"], state["right_lower"], (255, 0, 0), 5)
            cv2.line(display_img, state["right_lower"], state["left_lower"], (255, 0, 0), 5)
            cv2.line(display_img, state["left_lower"], state["left_upper"], (255, 0, 0), 5)

            x_center = (state["left_upper"][0] + state["right_upper"][0]) // 2
            y_center = (state["left_upper"][1] + state["left_lower"][1]) // 2
            center = (x_center, y_center)
            print(f'Center = {center}')

            true_center = (
                int(center[0] / resize_amount),
                int(center[1] / resize_amount)
            )
            print(f'True Center = {true_center}')

            cv2.circle(display_img, center, 10, (200, 40, 200), -1)
            box_drawn = True

            if not published:
                node.publish_center(true_center[0], true_center[1])
                published = True

        rclpy.spin_once(node, timeout_sec=0.0)

        if cv2.waitKey(20) & 0xFF == 27:
            break

    cv2.destroyAllWindows()
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()