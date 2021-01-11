#pragma once

#include <opencv2/opencv.hpp>
#include <zmq.hpp>

#define MAX_ROWS 768
#define MAX_COLS 1024
#define MAX_CHANNELS 4
#define BYTES_PER_PIXEL 1


namespace zn {

void send_image(zmq::socket_t &socket, cv::Mat &image);
void receive_image(zmq::socket_t &socket, cv::Mat &image);

}
