#pragma once

#include "globals.h"

class CActuatorAdapter
{
	public:
		CActuatorAdapter();
		CActuatorAdapter(const CActuatorAdapter& rhs) = delete;
		CActuatorAdapter(CActuatorAdapter&& rhs) = default;
		CActuatorAdapter& operator= (const CActuatorAdapter& rhs) = delete;
		CActuatorAdapter& operator= (CActuatorAdapter&& rhs) = default;
		virtual ~CActuatorAdapter();

		virtual void setON() = 0;
		virtual void setOFF() = 0;
		virtual bool getState() const = 0;
		virtual ActuatorType getType() const;
		virtual void setValue(float inValue) = 0;
		virtual int getValue() const = 0;

	protected:
		ActuatorType mType;
		bool mState = false;
		int mValue = 0;
};