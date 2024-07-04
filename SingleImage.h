#ifndef SINGLEIMAGE_H
#define SINGLEIMAGE_H

#include <stdint.h>

#define SIBUFFERS 3

class SingleImage
{
 public:
  SingleImage();
  inline bool  isReady() { return _isReady; }
  bool         initialize();
  bool         captureImage(uint8_t **image, int& imageSize);

 private:
  int          xioctl(int request, void *arg);
  bool         setupDevice();
  bool         initMemoryMap();
  bool         performCaptureImage(uint8_t **image, int& imageSize);

  bool         _isReady;
  int          fd;
  uint8_t *    buffer[SIBUFFERS];
};

#endif
