#include <zn.hpp>

using namespace std;
using namespace cv;

namespace zn {

void my_free(void *data, void *hint) { }

struct MetaData {
    int depth;
    int rows;
    int cols;
    int channels;
};

void send_image(zmq::socket_t &socket, cv::Mat &image) {

    static MetaData meta;
    static zmq::mutable_buffer mbuf(&meta, sizeof(MetaData));
    static zmq::message_t image_bytes;

    meta = {image.depth(), image.rows, image.cols, image.channels()};
    socket.send(mbuf, zmq::send_flags::sndmore);

    image_bytes.rebuild(image.data, image.total() * image.elemSize(), my_free);

    socket.send(image_bytes, zmq::send_flags::none);
}

void receive_image(zmq::socket_t &socket, cv::Mat &image) {

    static MetaData meta;
    static zmq::mutable_buffer mbuf(&meta, sizeof(MetaData));
    // 1024*768*4*1 = 3145728
    static unsigned char *image_data = new unsigned char [3145728];
    static zmq::mutable_buffer mbuf_image(image_data, 3145728);

    socket.recv(mbuf, zmq::recv_flags::none);
    socket.recv(mbuf_image, zmq::recv_flags::none);

    image = cv::Mat(meta.rows, meta.cols, CV_MAKETYPE(meta.depth, meta.channels), image_data);

}

}
