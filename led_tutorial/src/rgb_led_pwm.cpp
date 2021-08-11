#include <ros/ros.h>
#include <wiringPi.h>
#include <softPwm.h>

#include "led_tutorial/SetRGBAnalog.h"

uint8_t R = 255;
uint8_t G = 255;
uint8_t B = 255;

bool SetRGBAnalogCallBack(led_tutorial::SetRGBAnalog::Request &req,
                           led_tutorial::SetRGBAnalog::Response &res)
{
  R = req.R;
  G = req.G;
  B = req.B;

  res.result = "True";
  res.message = "Set R : " + std::to_string(R) + ", Set G : " + std::to_string(G) + ", Set B : " + std::to_string(B);
  res.Timestamp = ros::Time::now();

  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rgb_led_pwm_node");
  ros::NodeHandle n("~");

  ros::Rate loop_rate(10);

  ros::ServiceServer service_server_set_rgb_analog;
  service_server_set_rgb_analog = n.advertiseService("setRGBAnalog", SetRGBAnalogCallBack);

  int r_pin = 0;
  int g_pin = 0;
  int b_pin = 0;
  bool led_turn = false;

  n.param<int>("RPin", r_pin, 0);
  n.param<int>("GPin", g_pin, 0);
  n.param<int>("BPin", b_pin, 0);

  ROS_INFO("R Pin : %d", r_pin);
  ROS_INFO("G Pin : %d", g_pin);
  ROS_INFO("B Pin : %d", b_pin);

  wiringPiSetupGpio();

  pinMode(r_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);

  softPwmCreate(r_pin, 0, 255);
  softPwmCreate(g_pin, 0, 255);
  softPwmCreate(b_pin, 0, 255);

  while(ros::ok())
  {
    softPwmWrite(r_pin, R);
    softPwmWrite(g_pin, G);
    softPwmWrite(b_pin, B);
    loop_rate.sleep();
    ros::spinOnce();
  }

  softPwmWrite(r_pin, 0);
  softPwmWrite(g_pin, 0);
  softPwmWrite(b_pin, 0);

  digitalWrite(r_pin,LOW);
  digitalWrite(g_pin,LOW);
  digitalWrite(b_pin,LOW);

  return 0;
}
