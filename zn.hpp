#pragma once

#include <opencv2/opencv.hpp>
#include <zmq.hpp>

namespace zn {

void send_image(zmq::socket_t &socket, cv::Mat &image);
void receive_image(zmq::socket_t &socket, cv::Mat &image);

}
