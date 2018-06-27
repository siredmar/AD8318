//=================================================================
//
//  Simple library to calculate dBm from the output voltage of an AD8318
//
//	Version 1.0.0
//
//  (c) Armin Schlegel, 2018 
//  based on work by Dietmar Krause, DL2SBA 2017
//
//  License see https://creativecommons.org/licenses/by/4.0/
#pragma once
#include <Arduino.h>

class enum UnitType
{
	dBm,
	pW,
	nW,
	uW,
	mW,
	W
};

class Value
{
  public:
	Value(double value, UnitType unit);

	Unit()
	{
		return unit;
	}

	Value()
	{
		return value;
	}
  private:
	UnitType unit;
	double value;
};

class AD8318 
{
  public:
    AD8318();
	Value GetValue_dBm();
	Value GetValue_W();
  private:
	double Convert(uint16_t val);
	Value ConvertDbmToW(double val);
    double mK0;
    double mK1;
    double mK2;
    double mK3;
	double mOffset;
};
#endif
