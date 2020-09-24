#include <unistd.h>
#include <limits.h>
#include "MqttManager.h"


namespace GenericClient {

//===================================================================
// Event Handler Class
//===================================================================

std_str Topic;
void_func Action;

EventHandler::EventHandler(std_str topic, void_func action) {
    this->Topic = topic;
        this->Action = action;
    }

    EventHandler::~EventHandler() {
        //May need to free func?
    }

//===================================================================
//  Public members
//===================================================================
    SubscriptionsVector         Subscriptions;
    MQTTClient                  Client;
    struct ConnectionOptions    ConnectionOptions;

//===================================================================
//  Ctor
//===================================================================
    MqttManager::MqttManager() {

    };
    
    MqttManager::~MqttManager() {
        //Deallocate subscriptions list.
        if(this->Subscriptions.empty()) {
            this->Subscriptions.clear();
            SubscriptionsVector().swap(this->Subscriptions);
        }
    }

//===================================================================
//  public methods:
//  - Instantiates connection to MQTT server with class members.
//===================================================================
    int MqttManager::Connect() {
        return Connect(&this->Client, this->ConnectionOptions);
    };

    //If successful, client will be the actiev server connection.
    int MqttManager::Connect(MQTTClient* client, struct ConnectionOptions ConnectionOptions) {
        if( !ConnectionOptions.ServerURI ) return 0;

        try {
            MQTTClient_init_options* options = initClientOptions();
            MQTTClient_global_init(options);

            int hr = MQTTClient_create(  
                            client
                            ,ConnectionOptions.ServerURI
                            ,ConnectionOptions.ClientID
                            ,ConnectionOptions.PersitanceType
                            ,ConnectionOptions.PersistenceDir);

            if( hr == MQTTCLIENT_SUCCESS ) return 0;
            //Trace.Log("Connection to ${ServerURI} succesful!");
            //

        } 
        catch(int e) {

        }
        return 1;
    };

    int MqttManager::Subscribe(std_str topic, EventHandler eventHandler ) 
    {
        return -1;
    }

//===================================================================
//  private methods
//===================================================================
    
    //Struct version MUST be 1.
    //We initialize SSL on connect.
    MQTTClient_init_options* MqttManager::initClientOptions() {
        MQTTClient_init_options* options = new MQTTClient_init_options();
        options->do_openssl_init = 1;
        options->struct_version = 1;
        return options;
    }
    
    char* MqttManager::buildClientID() {
        char* ret;
        char hostname[HOST_NAME_MAX];

        int hr = gethostname(hostname, HOST_NAME_MAX);
        if(hr > 0)
        {
            ret = hostname;
        }
        return ret;
    }

    void MqttManager::setClientID( struct ConnectionOptions* options) {
        options->ClientID = buildClientID();
    }
}