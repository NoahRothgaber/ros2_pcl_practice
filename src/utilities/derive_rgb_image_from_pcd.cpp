#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

    if (pcl::io::loadPCDFile("/home/csrobot/Desktop/02_mustard.pcd", *cloud) == -1)
    {
        std::cerr << "Failed to load cloud.pcd\n";
        return -1;
    }

    if (cloud->height == 1)
    {
        std::cerr << "Cloud is unorganized; cannot directly reconstruct image layout.\n";
        return -1;
    }

    cv::Mat image(cloud->height, cloud->width, CV_8UC3);

    for (int y = 0; y < cloud->height; ++y)
    {
        for (int x = 0; x < cloud->width; ++x)
        {
            const auto& pt = cloud->at(x, y);

            // OpenCV uses BGR
            image.at<cv::Vec3b>(y, x) = cv::Vec3b(pt.b, pt.g, pt.r);
        }
    }

    cv::imshow("Recovered RGB", image);
    cv::waitKey(0);

    return 0;
}