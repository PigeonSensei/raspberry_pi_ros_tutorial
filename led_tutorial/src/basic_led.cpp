#include <ros/ros.h>
#include <wiringPi.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "basic_led_node");
  ros::NodeHandle n("~");

  int led_pin = 0;
  bool led_turn = false;

  n.param<int>("LEDPin", led_pin, 0);

  ROS_INFO("LED Pin : %d", led_pin);

  ros::Rate loop_rate(1);

  wiringPiSetupGpio();

  pinMode(led_pin, OUTPUT);

  while(ros::ok())
  {
    if(led_turn == false)
    {
      digitalWrite(led_pin,HIGH);
      ROS_INFO("LED ON");
      led_turn = true;
    }
    else
    {
      digitalWrite(led_pin,LOW);
      ROS_INFO("LED OFF");
      led_turn = false;
    }
    loop_rate.sleep();
    ros::spinOnce();
  }

  digitalWrite(led_pin,LOW);
  return 0;
}
