#include <ros/ros.h>
#include <wiringPi.h>

#include "echo_tutorial/EchoDistance.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "basic_echo_node");
  ros::NodeHandle n;
  ros::NodeHandle pn("~");

  ros::Rate loop_rate(5);

  ros::Publisher publisher_echo_distance = n.advertise<echo_tutorial::EchoDistance>("echo_distance", 1000);

  echo_tutorial::EchoDistance echo_distance;

  ros::Time start_time,end_time;

  double distance;

  int trig = -1;
  int echo = -1;
  int max_distance = 10;

  pn.param<int>("Trig", trig, -1);
  pn.param<int>("Echo", echo, -1);
  pn.param<int>("MaxDistance", max_distance, 10);

  wiringPiSetupGpio();

  pinMode(trig, OUTPUT) ;
  pinMode(echo , INPUT) ;

  while(ros::ok())
  {
    digitalWrite(trig, LOW) ;
    delay(10);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    while (digitalRead(echo) == 0)
    {
      start_time = ros::Time::now();
    }
    while (digitalRead(echo) == 1)
    {
      end_time = ros::Time::now();
    }

    double delta_time, delta_sec, delta_nsec;

    delta_sec = end_time.sec - start_time.sec;
    delta_nsec = (end_time.nsec - start_time.nsec) * 0.000000001;
    delta_time = delta_sec + delta_nsec;

    distance = delta_time * (340/2) * 100;
    distance = round(distance* 10) / 10;

    if(distance > max_distance) distance = -1;

    echo_distance.Stamp = ros::Time::now();
    echo_distance.Distance = distance;
    ROS_INFO("Distance : %f cm", distance);

    publisher_echo_distance.publish(echo_distance);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0 ;

}
