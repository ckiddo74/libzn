import numpy as np
import zmq
import struct

dtype_map = { 0: np.uint8, 1: np.int8,
              2: np.uint16, 3: np.int16,
              4: np.int32,  5: np.float32,
              6: np.float64
            }

depth_map = { 2:  0, # uint8
              1:  1, # int8
              4:  2, # uint16
              3:  3, # int16
              5:  4, # int32
              11: 5, # float32
              12: 6  # float64
            }

def send(sock, frame):
  shape = frame.shape
  meta=struct.pack('iiii', depth_map[frame.dtype.num], shape[0], shape[1], shape[2])
  sock.send(meta, zmq.SNDMORE)
  sock.send(frame)

def recv(sock):
  data = sock.recv()
  meta=struct.unpack('iiii', data)

  dtype = dtype_map[meta[0]]
  shape0 = meta[1]
  shape1 = meta[2]
  shape2 = meta[3]
  data = sock.recv(zmq.RCVMORE)
  frame = np.fromstring(data, dtype=dtype).reshape(shape0, shape1, shape2)
  return frame
