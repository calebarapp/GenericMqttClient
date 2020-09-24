#include <iostream>
#include <string>
#include <vector>
#include "MqttManager.h"

using namespace GenericClient;

int main() {
    std::cout << "Attempting to connect to MQTT Server..." << std::endl;
    MqttManager * mqtt;
    mqtt = new MqttManager();
    
    if(mqtt->Connect()) {
        std::cout << "Connection succesfull!" << std::endl;
    } 
    else {
        std::cout << "Connection attempt failed!" << std::endl;
    }

    delete mqtt;

    std::string out; 
    getline(std::cin, out);
    return 0;
}
