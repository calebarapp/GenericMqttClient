#include <string>
#include <functional>
#include <vector>
#include "MQTTClient.h"

namespace GenericClient {

    typedef std::string std_str; 
    typedef std::function<void()> void_func;
    
    class EventHandler {
    public:
        EventHandler(std_str, void_func);
        ~EventHandler();
        std_str Topic;
        void_func Action;
    };

    //Options required for connection to MQTT Server.
    // ClientID: Identification used by MQTT server for this client. Any string should do.
    // ServerURI: URI used to connect to MQTT server. mqtt[s]://[username][:password]@host.domain[:port]
    // PersitancDir: Directory for file based persistence of inbound messages. Only used if Persistence type is MQTTClient::MQTTCLIENT_PERSISTENCE_DEFAULT.
    // Persitence type: See MQTTClient.h for details.
    struct ConnectionOptions {
        char*               ClientID;
        char*               ServerURI;
        char*               PersistenceDir;
        int                 PersitanceType;
    };

    typedef std::vector<EventHandler> SubscriptionsVector;

    class MqttManager {
        public:
            struct ConnectionOptions    ConnectionOptions;
            SubscriptionsVector         Subscriptions;
            MQTTClient                  Client;

            MqttManager();
            ~MqttManager();
            int Connect();
            int Connect(MQTTClient* client, struct ConnectionOptions ConnectionOptions);
            int Subscribe(std_str const topic, EventHandler eventHandler);

        private:
            void setClientID( struct ConnectionOptions * options);
            char* buildClientID();
            MQTTClient_init_options* initClientOptions();

    };
}
