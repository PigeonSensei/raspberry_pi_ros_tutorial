#include <ros/ros.h>
#include <wiringPi.h>
#include <softTone.h>

#include "buzzer_tutorial/note.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "buzzer_melody_node");
  ros::NodeHandle n("~");

  ros::Rate loop_rate(3);

  int buzzer_pin = 0;
  int scale[8] = {C3, D3, E3, F3, G3, A3, B3, C4};
  int i = 0;
  bool buzzer_turn = false;

  n.param<int>("BuzzerPin", buzzer_pin, 0);

  ROS_INFO("LED Pin : %d", buzzer_pin);

  wiringPiSetupGpio();

  softToneCreate(buzzer_pin);

  while(ros::ok())
  {
    if(buzzer_turn == false)
    {
      softToneWrite(buzzer_pin,0);
      ROS_INFO("Buzzer OFF");
      buzzer_turn = true;
    }
    else
    {
      softToneWrite(buzzer_pin,scale[i]);
      ROS_INFO("Buzzer %d", scale[i]);
      buzzer_turn = false;
      i++;
      if(i>7) i = 0;
    }
    loop_rate.sleep();
    ros::spinOnce();
  }

  softToneWrite(buzzer_pin,0);
  return 0;

}
