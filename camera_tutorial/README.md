# camera_tutorial

Provide RaspberryPi Camera Module reference using Raspberry Pi and ROS

## basic_camera_node

Example of publishing a camera image to a ROS topic

### Demo

https://youtu.be/pBio6fvzaJw

### Tutorial Video

https://youtu.be/F-24LbZz9Ws

### Diagram

![basic_camera](./diagram/basic_camera.png)

### Setup

Make sure your camera unit is ready

```bash
ls -ltrh /dev/video*
```

Usually the video device number is **0**.

Below is an example of the result

```bash
crw-rw----+ 1 root video 81, 2 Sep  7 18:37 /dev/video14
crw-rw----+ 1 root video 81, 1 Sep  7 18:37 /dev/video13
crw-rw----+ 1 root video 81, 6 Sep  7 18:37 /dev/video0
crw-rw----+ 1 root video 81, 4 Sep  7 18:37 /dev/video15
crw-rw----+ 1 root video 81, 0 Sep  7 18:37 /dev/video10
crw-rw----+ 1 root video 81, 5 Sep  7 18:37 /dev/video16
crw-rw----+ 1 root video 81, 7 Sep  7 18:37 /dev/video12
crw-rw----+ 1 root video 81, 3 Sep  7 18:37 /dev/video11
```

If you do not have a camera unit, follow the procedure below.

Open the ```/boot/firmware/config.txt``` file with administrator privileges 

Below shows an example

```bash
sudo nano /boot/firmware/config.txt
```

Type the following in the bottom line, save and reboot.

```bash
start_x=1
gpu_mem=128
```

- **start_x=1** : should be specified when using the camera module **[Required]**

- **gpu_mem=128** : Set GPU memory to 128 MB **[options]**

See documentation below for details

https://www.raspberrypi.com/documentation/computers/config_txt.html


### Run

```bash
roslaunch camera_tutorial basic_camera.launch
```

### Published Topics

- **camera_image** ([sensor_msgs/Image](http://docs.ros.org/en/noetic/api/sensor_msgs/html/msg/Image.html))

  This is a video taken by the camera

### Parameters

- ~**VideoDevice** (int, default: "0")
  
  number of video device
  
  
- ~**Hz** (int, default: "30")

  frequency of the image
  
  
- ~**Resolution** (int, default: "0")

  image resolution
  
  - **1** : 640x320
  - **2** : 320x240
  - **3** : 160x120
  - **others** : Camera's defult resolution
  
