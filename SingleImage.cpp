#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "SingleImage.h"

#include <QDebug>

SingleImage::SingleImage()
{
   memset(&buffer, 0, sizeof(buffer));
   _isReady = false;
}

bool SingleImage::initialize()
{
   fd = open("/dev/video0", O_RDWR);
   if (fd >= 0)
   {
      if (setupDevice())
      {
         if (initMemoryMap())
         {
            return _isReady = true;
         }
      }
      else{ qDebug() << "CAMERA: Setup device failed."; }
   }
   else{ qDebug() << "Open /dev/video0 failed with errno = " << errno; }
   close(fd);
   return false;
}

int SingleImage::xioctl(int request, void *arg)
{
   int r;

   do
      r = ioctl(fd, request, arg);
   while (r == -1 && EINTR == errno);

   return r;
}

bool SingleImage::setupDevice()
{
   struct v4l2_capability caps;

   memset(&caps, 0, sizeof(caps));

   if (xioctl(VIDIOC_QUERYCAP, &caps) == -1) { return false; }

   printf( "Driver Caps:\n"
           "  Driver: \"%s\"\n"
           "  Card: \"%s\"\n"
           "  Bus: \"%s\"\n"
           "  Version: %d.%d\n"
           "  Capabilities: %08x\n",
           caps.driver,
           caps.card,
           caps.bus_info,
           (caps.version >> 16) && 0xff,
           (caps.version >> 24) && 0xff,
           caps.capabilities);


   struct v4l2_cropcap cropcap;

   memset(&cropcap, 0, sizeof(cropcap));
   cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   if (xioctl(VIDIOC_CROPCAP, &cropcap) == -1) { return false; }

   printf( "Camera Cropping:\n"
           "  Bounds: %dx%d+%d+%d\n"
           "  Default: %dx%d+%d+%d\n"
           "  Aspect: %d/%d\n",
           cropcap.bounds.width, cropcap.bounds.height, cropcap.bounds.left, cropcap.bounds.top,
           cropcap.defrect.width, cropcap.defrect.height, cropcap.defrect.left, cropcap.defrect.top,
           cropcap.pixelaspect.numerator, cropcap.pixelaspect.denominator);

   bool supportsYUYV = false;

   struct v4l2_fmtdesc fmtdesc;
   memset(&fmtdesc, 0, sizeof(fmtdesc));
   fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   char fourcc[5];
   char c, e;
   printf("  FMT : CE Desc\n--------------------\n");
   while (0 == xioctl(VIDIOC_ENUM_FMT, &fmtdesc))
   {
      memset(fourcc, 0, sizeof(fourcc));
      strncpy(fourcc, (char*)&fmtdesc.pixelformat, 4);
      if (fmtdesc.pixelformat == V4L2_PIX_FMT_YUYV) { supportsYUYV = true; }
      c = fmtdesc.flags & 1 ? 'C' : ' ';
      e = fmtdesc.flags & 2 ? 'E' : ' ';
      printf("  %s: %c%c %s\n", fourcc, c, e, fmtdesc.description);
      fmtdesc.index++;
   }

   if (!supportsYUYV) { return false; }

   struct v4l2_format fmt;
   memset(&fmt, 0, sizeof(fmt));
   fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   fmt.fmt.pix.width       = 320;
   fmt.fmt.pix.height      = 240;
   fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;


   if (xioctl(VIDIOC_S_FMT, &fmt) == -1) { return false; }

   strncpy(fourcc, (char*)&fmt.fmt.pix.pixelformat, 4);
   printf( "Selected Camera Mode:\n"
           "  Width: %d\n"
           "  Height: %d\n"
           "  PixFmt: %s\n"
           "  Field: %d\n",
           fmt.fmt.pix.width,
           fmt.fmt.pix.height,
           fourcc,
           fmt.fmt.pix.field);
   return true;
}

bool SingleImage::initMemoryMap()
{
   struct v4l2_requestbuffers req;

   memset(&req, 0, sizeof(req));

   req.count = SIBUFFERS;
   req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   req.memory = V4L2_MEMORY_MMAP;

   if (xioctl(VIDIOC_REQBUFS, &req) == -1) { return false; }

   for (unsigned int bufferIndex = 0; bufferIndex < req.count; bufferIndex++)
   {
      struct v4l2_buffer buf;
      memset(&buf, 0, sizeof(buf));
      buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      buf.memory = V4L2_MEMORY_MMAP;
      buf.index = bufferIndex;
      if (xioctl( VIDIOC_QUERYBUF, &buf) == 1) { return false; }

      buffer[bufferIndex] = (uint8_t*)mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);

      printf("Length: %d\nAddress: %p\n", buf.length, buffer[bufferIndex]);
      printf("Image Length: %d\n", buf.bytesused);
   }

   return true;
}

bool SingleImage::performCaptureImage(uint8_t **image, int& imageSize)
{
   struct v4l2_buffer buf;
   int bufferType = V4L2_BUF_TYPE_VIDEO_CAPTURE;

   memset(&buf, 0, sizeof(buf));
   buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   buf.memory = V4L2_MEMORY_MMAP;
   for (int x = 0; x < SIBUFFERS; x++)
   {
      buf.index = x;
      if (xioctl( VIDIOC_QBUF, &buf) == -1) { printf("REQUEUE FAILED\n"); }
   }


   struct v4l2_control control;
   control.id = V4L2_CID_VFLIP;
   control.value = 0;
   xioctl(VIDIOC_S_CTRL, &control);
   control.id = V4L2_CID_HFLIP;
   control.value = 0;
   xioctl(VIDIOC_S_CTRL, &control);

   if (xioctl(VIDIOC_STREAMON, &bufferType) == -1) { return false; }

   int frame = 2;
   struct timeval tv;
   fd_set fds;

   do
   {
      FD_ZERO(&fds);
      FD_SET(fd, &fds);
      memset(&tv, 0, sizeof(tv));
      tv.tv_sec = 2;
      int r = select(fd + 1, &fds, NULL, NULL, &tv);
      if (r == -1)
      {
         xioctl(VIDIOC_STREAMOFF, &bufferType);
         return false;
      }

      if (xioctl(VIDIOC_DQBUF, &buf) == -1) { return false; }
      if (--frame > 0) { if (xioctl(VIDIOC_QBUF, &buf) == -1) { return false; } }
   }
   while (frame);


   xioctl(VIDIOC_STREAMOFF, &bufferType);
   printf("Got image with %d bytes from buffer index %d\n", buf.bytesused, buf.index);

   imageSize = buf.bytesused;
   printf("1\n");
   *image = new uint8_t[imageSize];
   printf("1\n");
   memcpy(*image, buffer[buf.index], imageSize);

   printf("Image copied\n");

   return true;
}

bool SingleImage::captureImage(uint8_t **image, int& imageSize)
{
   if (!_isReady) { return false; }
   return performCaptureImage(image, imageSize);
}




/*

   .qc = {
                        .id = V4L2_CID_VFLIP,
                        .type = V4L2_CTRL_TYPE_BOOLEAN,
                        .name = "Vertical flip",
                        .minimum = 0,
                        .maximum = 1,
                        .step = 1,
                        .default_value = 0,
                },
                .tweak = ov7675_t_vflip,
                .query = ov7675_q_vflip,
        },
        {
                .qc = {
                        .id = V4L2_CID_HFLIP,
                        .type = V4L2_CTRL_TYPE_BOOLEAN,
                        .name = "Horizontal mirror",
                        .minimum = 0,
                        .maximum = 1,
                        .step = 1,
                        .default_value = 0,

 */
