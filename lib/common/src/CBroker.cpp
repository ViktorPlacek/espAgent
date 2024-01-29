#include "CBroker.h"

using namespace std;

CBroker::CBroker(std::string inName, std::string inURL, unsigned int inPort, 
   std::string inID, std::string inAccessToken, std::string inTopic)
   : mName(inName), mURL(inURL), mPort(inPort), mID(inID), mAccessToken(inAccessToken), mTopic(inTopic)
{
   Log(DEBUG) << "CBroker constructor called with parameters: inName: " << mName << ", inURL: " <<
     mURL << ", inPort: " << mPort << ", inID: " << mID << ", inAccessToken: " << mAccessToken << endl;

   mWifiClient = unique_ptr<WiFiClient>(new WiFiClient);
   mPubSubClient = unique_ptr<PubSubClient>(new PubSubClient);
   mPubSubClient->setClient(*mWifiClient);
   auto url_str = new char[mURL.size() + 1]; // small memory leak
   strcpy(url_str, mURL.c_str());
   IPAddress ip_address;
   if (ip_address.fromString(url_str)) {  // if mURL is IP address
      mPubSubClient->setServer(ip_address, mPort);
   } else {
      mPubSubClient->setServer(url_str, mPort);
   }
   //mPubSubClient.setCallback(/* TODO */); //Callback functions for actuators
}

CBroker::~CBroker()
{
   Log(DEBUG) << "Call CBroker destructor." << endl;
}

void CBroker::connect() 
{
   Log(DEBUG) << "CBroker::connect() called on broker \"" << mName << "\"." << endl;

   if ( mPubSubClient->connected() ) {
      mConnected = true;
      Log(WARN) << "Trying to connect to already connected broker: " << mName << endl;
      throw runtime_error("already connected to " + mName + " !");
   }

   Log(DEBUG) << "CBroker is connecting with ID: " << mID << 
                 ", and Access Token: " << mAccessToken << "." << endl;
   Log(DEBUG) << "PubSubClient IP:" << mPubSubClient->ip.toString().c_str() << ", port: " << mPubSubClient->port << ", domain: " << mPubSubClient->domain << endl;
   auto id_string = new char[mID.length() + 1];
   auto access_token_string = new char[mAccessToken.length() + 1];
   strcpy(id_string, mID.c_str());
   strcpy(access_token_string, mAccessToken.c_str());
   bool connected = mPubSubClient->connect(id_string, access_token_string, "");
   Log(DEBUG) << "PubSubClient connection state: " << mPubSubClient->state() << endl;

   if (!connected) {
      Log(ERROR) << "Connection to broker " << mName << " failed!" << endl;
      Log(ERROR) << "PubSubClient state:" << mPubSubClient->state() << endl; 
      delete[] id_string;
      delete[] access_token_string;
      throw runtime_error("connection to " + mName + "failed!");
   } else {
      Log(INFO) << "Connected Successfully." << endl;
      mConnected = true;
   }
}

void CBroker::disconnect()
{
   Log(DEBUG) << "CBroker::disconnect() called." << endl;

   mPubSubClient->disconnect();

   if ( mPubSubClient->connected() ) {
      Log(ERROR) << "PubSubClient disconnect from " << mName << " failed!" << endl;
      Log(DEBUG) << "PubSubClient status: " << mPubSubClient->state() << endl;
      throw runtime_error("disconnection from broker " + mName + " failed!");
   }
}

std::string CBroker::format_value(std::string inPre, float value, std::string inExt, int inDigits)
{
   stringstream tempstr;

   tempstr << fixed << setprecision(inDigits) << inPre << value << inExt;

   return tempstr.str() ;
}

void CBroker::publish(std::string inTopic, std::string inMessage)
{
   Log(DEBUG) << "Publishing message \"" << inMessage << "\" to topic \"" << inTopic << "\"." << endl;
   auto topic_string = new char[inTopic.length() + 1];
   auto message_string = new char[inMessage.length() + 1];
   strcpy(topic_string, inTopic.c_str());
   strcpy(message_string, inMessage.c_str());

   bool sent = mPubSubClient->publish(topic_string, message_string);

   if (!sent) {
      Log(ERROR) << "Publishing to broker " << mName << " failed!" << endl;
      delete[] topic_string;
      delete[] message_string;
      throw runtime_error("publishing to broker " + mName + " failed!");
   }
}
