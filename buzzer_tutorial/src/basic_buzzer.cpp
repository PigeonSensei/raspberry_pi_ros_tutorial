#include <ros/ros.h>
#include <wiringPi.h>
#include <softTone.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "basic_buzzer_node");
  ros::NodeHandle n("~");

  ros::Rate loop_rate(1);

  int buzzer_pin = 0;
  bool led_turn = false;

  n.param<int>("BuzzerPin", buzzer_pin, 0);

  ROS_INFO("LED Pin : %d", buzzer_pin);

  wiringPiSetupGpio();

  softToneCreate(buzzer_pin);

  while(ros::ok())
  {
    if(led_turn == false)
    {
      softToneWrite(buzzer_pin,262);
      ROS_INFO("Buzzer ON");
      led_turn = true;
    }
    else
    {
      softToneWrite(buzzer_pin,0);
      ROS_INFO("Buzzer OFF");
      led_turn = false;
    }
    loop_rate.sleep();
    ros::spinOnce();
  }

  softToneWrite(buzzer_pin,0);
  return 0;

}
