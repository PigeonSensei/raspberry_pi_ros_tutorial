#include <ros/ros.h>
#include <wiringPi.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "switch_led_node");
  ros::NodeHandle n("~");

  int led_pin = 0;
  int switch_pin = 0;

  n.param<int>("LEDPin", led_pin, 0);
  n.param<int>("SwitchPin", switch_pin, 0);

  ROS_INFO("LED Pin : %d", led_pin);
  ROS_INFO("Switch Pin : %d", switch_pin);

  ros::Rate loop_rate(30);

  wiringPiSetupGpio();

  pinMode(led_pin, OUTPUT);
  pinMode(switch_pin, INPUT);

  while(ros::ok())
  {
    if(digitalRead(switch_pin) == HIGH)
    {
      digitalWrite(led_pin,HIGH);
      ROS_INFO("SWITCH ON");
      ROS_INFO("LED ON");
    }
    else
    {
      digitalWrite(led_pin,LOW);
      ROS_INFO("SWITCHOFF");
      ROS_INFO("LED OFF");
    }

    loop_rate.sleep();
    ros::spinOnce();
  }

  digitalWrite(led_pin,LOW);
  return 0;
}
