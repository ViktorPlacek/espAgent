#pragma once

#include "globals.h"
#include "CActuatorAdapter.h"

class CActuatorRelay : public CActuatorAdapter
{
   public:
      CActuatorRelay() {std::cout << "CActuatorRelay 0-param constructor called" << std::endl;}
      CActuatorRelay(unsigned char inPin);
      virtual ~CActuatorRelay();

		virtual void setON() override;
		virtual void setOFF() override;
		virtual bool getState() const override;
		virtual void setValue(float inValue) override;
		virtual int getValue() const override;

   private:

};