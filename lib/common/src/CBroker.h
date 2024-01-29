#pragma once
#include "globals.h"
//#include "WiFiClient.h"
#include <PubSubClient.h>

class CBroker
{
    public:
        CBroker() = delete;
        CBroker(std::string inName, std::string inURL, unsigned int inPort, 
            std::string inID, std::string inAccessToken, std::string inTopic);
        CBroker(const CBroker&) = delete;
        CBroker(CBroker&&) = default;
        virtual CBroker& operator= (const CBroker&) = delete;
        virtual CBroker& operator= (CBroker&&) = default;
        virtual ~CBroker();

        virtual const std::string& getName() const { return mName; }
        virtual const std::string& getURL() const { return mURL; }
        virtual unsigned int getPort() const { return mPort; }
        virtual const std::string& getID() const { return mID;}
        virtual const std::string& getAccessToken() const { return mAccessToken; }
        virtual const PubSubClient& getPubSubClient() const {return *mPubSubClient; }
        virtual bool isConnected() const { return mConnected; }

        virtual void connect(); // throws runtime_error
        virtual void disconnect();

        virtual void publish(std::string inTopic, std::string inMessage);

        static std::string format_value(std::string inPre, float value, 
            std::string inExt = "", int inDigits = 2);

    private:
        std::string mName;
        std::string mURL;
        unsigned int mPort;
        std::string mID;
        std::string mAccessToken;
        std::string mPassword;
        std::string mTopic;
        bool mutable mConnected = false; 
        std::unique_ptr<WiFiClient> mWifiClient;  // must be pointer! Plain object does not copy/move correctly
        std::unique_ptr<PubSubClient> mPubSubClient;  // must be pointer! Plain object does not copy/move correctly
};