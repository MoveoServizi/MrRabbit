
#include <ros/ros.h>
#include "unitree_legged_sdk/unitree_legged_sdk.h"
#include <unitree_legged_msgs/HighCmd.h>
#include <unitree_legged_msgs/HighState.h>
#include "unitree_legged_sdk/convert.h"
#include "unitree_legged_sdk/FaceLightClient.h"

using namespace UNITREE_LEGGED_SDK;
FaceLightClient led_client;
class Custom
{
public:
    UDP high_udp;

    HighCmd high_cmd = {0};
    
    HighState high_state = {0};
    

public:
    Custom()
        : 
        high_udp(8090, "192.168.123.161", 8082, sizeof(HighCmd), sizeof(HighState))
    {
        high_udp.InitCmdData(high_cmd);
    }

    void highUdpSend()
    {

        high_udp.SetSend(high_cmd);
        high_udp.Send();
    }



    void highUdpRecv()
    {

        high_udp.Recv();
        high_udp.GetRecv(high_state);
        //printf(high_state);
    }

   

    
};

Custom custom;

ros::Subscriber sub_high;
ros::Subscriber sub_led;

ros::Publisher pub_high;


long high_count = 0;
//long low_count = 0;

void highCmdCallback(const unitree_legged_msgs::HighCmd::ConstPtr &msg)
{
    printf("highCmdCallback is running !\t%ld\n", ::high_count);

    custom.high_cmd = rosMsg2Cmd(msg);

    unitree_legged_msgs::HighState high_state_ros;
    

    high_state_ros = state2rosMsg(custom.high_state);

    pub_high.publish(high_state_ros);

    printf("highCmdCallback ending !\t%ld\n\n", ::high_count++);
}

void ledCallback(const unitree_legged_msgs::LEDConstPtr &msg) {
    uint8_t rgb[3];
    rgb[0] = msg->r;
    rgb[1] = msg->g;
    rgb[2] = msg->b;
    led_client.setAllLed(rgb);
    led_client.sendCmd();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ros_udp");

    ros::NodeHandle nh;

    if (strcasecmp(argv[1], "HIGHLEVEL") == 0)
    {
        sub_high = nh.subscribe("high_cmd", 1, highCmdCallback);
        sub_led = nh.subscribe("led_topic",1, ledCallback);
        pub_high = nh.advertise<unitree_legged_msgs::HighState>("high_state", 1);
        

        LoopFunc loop_udpSend("high_udp_send", 0.002, 3, boost::bind(&Custom::highUdpSend, &custom));
        LoopFunc loop_udpRecv("high_udp_recv", 0.002, 3, boost::bind(&Custom::highUdpRecv, &custom));

        loop_udpSend.start();
        loop_udpRecv.start();

        ros::spin();

    }
    else
    {
        std::cout << "Control level name error! Can only be highlevel or lowlevel(not case sensitive)" << std::endl;
        exit(-1);
    }

    return 0;
}

