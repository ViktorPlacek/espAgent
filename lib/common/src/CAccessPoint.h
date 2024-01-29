#pragma once

#include "globals.h"

/**
 * @brief Managing an access point connection.
 * 
 */
class CAccessPoint {
   public:
      CAccessPoint() = delete;
      CAccessPoint(std::string inSSID, std::string inPassword);
      CAccessPoint(const CAccessPoint&) = default;
      CAccessPoint(CAccessPoint&&) = default;
      CAccessPoint& operator=(const CAccessPoint& rhs) = delete;
      CAccessPoint& operator=(CAccessPoint&& rhs) = default;
      virtual ~CAccessPoint();

      virtual const std::string& getSSID() const { return mSSID; }
      virtual const std::string& getPassword() const { return mPassword; }
      virtual signed int getRSSI() const { return mRSSI; }


      virtual void setSSID(std::string inSSID) { mSSID = std::move(inSSID); }
      virtual void setPassword(std::string inPassword) { mPassword = std::move(inPassword); }
      virtual void setRSSI(signed int inRSSI) { mRSSI = inRSSI; }

      virtual void connect();
      virtual void disconnect();

   private:
      std::string mSSID;
      std::string mPassword;
      signed int  mRSSI;
};