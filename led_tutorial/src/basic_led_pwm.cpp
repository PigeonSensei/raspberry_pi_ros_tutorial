#include <ros/ros.h>
#include <wiringPi.h>
#include <softPwm.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "basic_led_node");
  ros::NodeHandle n("~");

  int led_pin = 0;
  uint8_t brightness = 0;

  n.param<int>("LEDPin", led_pin, 0);

  ROS_INFO("LED Pin : %d", led_pin);

  ros::Rate loop_rate(30);

  wiringPiSetupGpio();

  pinMode(led_pin, OUTPUT);
  softPwmCreate(led_pin, 0, 100);

  while(ros::ok())
  {
    softPwmWrite(led_pin, brightness);
    ROS_INFO("brightness : %d",brightness);
    brightness++;
    if(brightness > 100) brightness = 0;
    loop_rate.sleep();
    ros::spinOnce();
  }

  softPwmWrite(led_pin, 0);
  digitalWrite(led_pin,LOW);
  return 0;
}
