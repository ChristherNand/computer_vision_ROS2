#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

using std::placeholders::_1;

class ImageSubscriber : public rclcpp::Node
{
public:
  ImageSubscriber()
  : Node("image_subscriber_node")
  {
    // Create a subscription to the image topic
    // Quality of Service (QoS) is set to 'best effort' with a history depth of 1
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
      "/camera/image_raw", // Image topic name
      rclcpp::SensorDataQoS(), // Recommended QoS for sensor data
      std::bind(&ImageSubscriber::image_callback, this, _1));

    RCLCPP_INFO(this->get_logger(), "Image Subscriber Node Initialized. Waiting for images on /camera/image_raw...");
  }

private:
  void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "Received image message.");

    // Convert ROS Image message to OpenCV Mat
    try
    {
      // The bridge handles the conversion. "bgr8" is a common format for color images.
      cv::Mat cv_image = cv_bridge::toCvShare(msg, msg->encoding)->image;

      if (!cv_image.empty())
      {
        // --- OpenCV Processing Example ---
        RCLCPP_INFO(this->get_logger(),
          "Image received: Size = %dx%d, Type = %s",
          cv_image.cols,
          cv_image.rows,
          getCvType(cv_image.type()).c_str());

        // Example processing: Convert to grayscale
        cv::Mat gray_image;
        cv::cvtColor(cv_image, gray_image, cv::COLOR_BGR2GRAY);
        // --- End of Example ---
      }
      else
      {
        RCLCPP_WARN(this->get_logger(), "Received an empty image!");
      }
    }
    catch (cv_bridge::Exception& e)
    {
      RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
      return;
    }
  }

  // Helper function to get the string representation of an OpenCV Mat type
  std::string getCvType(int type) {
    std::string r;
    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);
    switch ( depth ) {
      case CV_8U:  r = "8U"; break;
      case CV_8S:  r = "8S"; break;
      case CV_16U: r = "16U"; break;
      case CV_16S: r = "16S"; break;
      case CV_32S: r = "32S"; break;
      case CV_32F: r = "32F"; break;
      case CV_64F: r = "64F"; break;
      default:     r = "UNKNOWN"; break;
    }
    r += "C";
    r += (chans+'0');
    return r;
  }

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ImageSubscriber>());
  rclcpp::shutdown();
  return 0;
}
