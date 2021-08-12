#include <ros/ros.h>
#include <wiringPi.h>

#include "led_tutorial/SetRGBDigital.h"

bool R = true;
bool G = true;
bool B = true;

bool SetRGBDigitalCallBack(led_tutorial::SetRGBDigital::Request &req,
                           led_tutorial::SetRGBDigital::Response &res)
{
  R = req.R;
  G = req.G;
  B = req.B;

  res.result = "True";
  res.message = "Set R : " + std::to_string(R) + ", Set G : " + std::to_string(G) + ", Set B : " + std::to_string(B);
  res.Timestamp = ros::Time::now();
  ROS_INFO("Set R : %d, Set G : %d, Set B : %d", R,G,B);

  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rgb_led_node");
  ros::NodeHandle n("~");

  ros::Rate loop_rate(10);

  ros::ServiceServer service_server_set_rgb_digital;
  service_server_set_rgb_digital = n.advertiseService("setRGBDigital", SetRGBDigitalCallBack);

  int r_pin = 0;
  int g_pin = 0;
  int b_pin = 0;

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

  while(ros::ok())
  {
    digitalWrite(r_pin,R);
    digitalWrite(g_pin,G);
    digitalWrite(b_pin,B);
    loop_rate.sleep();
    ros::spinOnce();
  }

  digitalWrite(r_pin,LOW);
  digitalWrite(g_pin,LOW);
  digitalWrite(b_pin,LOW);

  return 0;
}
