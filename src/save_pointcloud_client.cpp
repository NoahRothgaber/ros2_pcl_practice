#include <chrono>
#include <cstdlib>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/empty.hpp"

class SavePointCloudClient : public rclcpp::Node
{
public:
  SavePointCloudClient() : Node("save_pointcloud_client")
  {
    client_ = this->create_client<std_srvs::srv::Empty>("save_pointcloud");
    while (!client_->wait_for_service(std::chrono::seconds(1))) {
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
        return;
      }
      RCLCPP_INFO(this->get_logger(), "Service not available, waiting again...");
    }
    auto request = std::make_shared<std_srvs::srv::Empty::Request>();
    auto result_future = client_->async_send_request(request);
    if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result_future) == rclcpp::FutureReturnCode::SUCCESS) {
      RCLCPP_INFO(this->get_logger(), "Pointcloud saved successfully.");
    } else {
      RCLCPP_ERROR(this->get_logger(), "Failed to call service save_pointcloud");
    }
  }
private:
  rclcpp::Client<std_srvs::srv::Empty>::SharedPtr client_;
};  


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<SavePointCloudClient>();

  // No need to spin here if constructor handles everything
  rclcpp::shutdown();
  return 0;
}
