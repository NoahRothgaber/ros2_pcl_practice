#!/usr/bin/env python3
import numpy as np
import cv2
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point
from save_pointcloud.msg import BoundingBoxCenter
from pathlib import Path

# Found using colorzilla the browser extension
lower = np.array([20, 80, 80], dtype=np.uint8)
upper = np.array([35, 255, 255], dtype=np.uint8)

source_path = Path.home() / "Desktop" / "05_cheezit_mustard_soup.png"

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
        self.publisher_ = self.create_publisher(BoundingBoxCenter, '/bbox_center', 10)

    def publish_bbox_center(self, u, v, x_min, y_min, x_max, y_max):
        msg = BoundingBoxCenter()
        msg.center.x = float(u)
        msg.center.y = float(v)
        msg.center.z = 0.0
        msg.x_min = int(x_min)
        msg.y_min = int(y_min)
        msg.x_max = int(x_max)
        msg.y_max = int(y_max)
        self.publisher_.publish(msg)
        self.get_logger().info(
            f'Published center=({u}, {v}) bbox=[{x_min}, {y_min}, {x_max}, {y_max}]'
        )


def main():
    rclpy.init()
    node = CenterPointPublisher()

    resize_amount = 1
    img = cv2.imread(str(source_path))
    if img is None:
        print(f"Failed to load image: {source_path}")
        node.destroy_node()
        rclpy.shutdown()
        return

    resized = cv2.resize(
        img, None,
        fx=resize_amount,
        fy=resize_amount,
        interpolation=cv2.INTER_AREA
    )

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
    cropped_saved = False

    while True:
        cv2.imshow('image', display_img)

        if box_drawn is False and state["corner_count"] >= 4:
            cv2.line(display_img, state["left_upper"], state["right_upper"], (255, 0, 0), 5)
            cv2.line(display_img, state["right_upper"], state["right_lower"], (255, 0, 0), 5)
            cv2.line(display_img, state["right_lower"], state["left_lower"], (255, 0, 0), 5)
            cv2.line(display_img, state["left_lower"], state["left_upper"], (255, 0, 0), 5)

            x_coords = [
                state["left_upper"][0],
                state["right_upper"][0],
                state["left_lower"][0],
                state["right_lower"][0]
            ]
            y_coords = [
                state["left_upper"][1],
                state["right_upper"][1],
                state["left_lower"][1],
                state["right_lower"][1]
            ]

            x_min = min(x_coords)
            x_max = max(x_coords)
            y_min = min(y_coords)
            y_max = max(y_coords)

            center = ((x_min + x_max) // 2, (y_min + y_max) // 2)
            print(f'Bounding Box Center (display image) = {center}')

            true_center = (
                int(center[0] / resize_amount),
                int(center[1] / resize_amount)
            )
            print(f'Bounding Box Center (original image) = {true_center}')

            cv2.circle(display_img, center, 10, (200, 40, 200), -1)

            cropped = resized[y_min:y_max, x_min:x_max]

            if cropped.size > 0:
                cropped_h, cropped_w = cropped.shape[:2]
                cropped_center_local = (cropped_w // 2, cropped_h // 2)

                # map cropped-image center back to original-image coordinates
                cropped_center_original = (
                    int((x_min + cropped_center_local[0]) / resize_amount),
                    int((y_min + cropped_center_local[1]) / resize_amount)
                )

                print(f'Cropped Center (cropped image coords) = {cropped_center_local}')
                print(f'Cropped Center (original image coords) = {cropped_center_original}')

                cv2.imshow("cropped", cropped)

                cropped_path = source_path.with_name(f"{source_path.stem}_cropped.png")
                cv2.imwrite(str(cropped_path), cropped)
                print(f"Cropped image saved to: {cropped_path}")

                if not published:
                    node.publish_bbox_center(
                        cropped_center_original[0],
                        cropped_center_original[1],
                        int(x_min / resize_amount),
                        int(y_min / resize_amount),
                        int(x_max / resize_amount),
                        int(y_max / resize_amount)
                    )
                    published = True

                cropped_saved = True
            else:
                print("Cropped image is empty; not saving or publishing.")

            box_drawn = True

        rclpy.spin_once(node, timeout_sec=0.0)

        if cv2.waitKey(20) & 0xFF == 27:
            break

    cv2.destroyAllWindows()
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()