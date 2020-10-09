#include <iostream>
#include <string>
#include <vector>
#include "MqttManager.h"

using namespace GenericClient;

int main() {
    std::cout << "Attempting to connect to MQTT Server..." << std::endl;
    
    MqttManager * mqtt;
    ConnectionOptions * options;

    mqtt = new MqttManager();    
    options = new ConnectionOptions();
    //mqtt[s]://[username][:password]@host.domain[:port]
   // const char *uri = "mqtt://@localhost:1883";
    
    //options->ServerURI = uri;

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
