#include <ros/ros.h>
#include "unitree_legged_sdk/FaceLightClient.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "led_node");
    ros::NodeHandle nh;
    
    //ros::start();

    
   


    
    FaceLightClient client;

    // client.setAllLed(client.red);
    // client.sendCmd();
    int mode = 0;

    switch (mode){
    case 0:
        /* Same Color Test */
        while(true){
            client.setAllLed(client.red);
            client.sendCmd();
            usleep(2000000);
            client.setAllLed(client.green);
            client.sendCmd();
            usleep(2000000);
            client.setAllLed(client.blue);
            client.sendCmd();
            usleep(2000000);
            client.setAllLed(client.yellow);
            client.sendCmd();
            usleep(2000000);
            client.setAllLed(client.black);
            client.sendCmd();
            usleep(2000000);
            client.setAllLed(client.white);
            client.sendCmd();
            usleep(2000000);
        }
        break;
    case 1:
        /* Custom Setting */
        for(int i(0); i < 12; ++i){
            switch (i % 3)
            {
            case 0:
                client.setLedColor(i, client.red);
                break;
            case 1:
                client.setLedColor(i, client.green);
                break;
            case 2:
                client.setLedColor(i, client.blue);
                break;
            default:
                break;
            }
        }
        client.sendCmd();
    default:
        break;
    }
    ros::spin();
    return 0;
}