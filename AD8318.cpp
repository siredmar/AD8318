//=================================================================
//
//  Simple library to calculate dBm from the output voltage of an AD8318
//
//    Version 1.0.0
//
//  (c) Armin Schlegel, 2018 
//  based on work by Dietmar Krause, DL2SBA 2017
//
//  License see https://creativecommons.org/licenses/by/4.0/

#include "AD8318.h"

AD8318::AD8318(void)
 {
    mK0 = 2.804742194E1;
    mK1 = -3.432439417E-2;
    mK2 = 5.570579072E-6;
    mK3 = -1.015882955E-9;
    mOffset = 0.0;
}

double AD8318::Convert(int val)
{
    return (mK0 + mK1 * val + mK2 * val * val + mK3 * val * val * val) - mOffset;
}

Value AD8318::GetValue_dBm(int raw)
{
    double val = Convert(raw);
    Value ret(val, Unit::dBm);
    return ret;
}

Value AD8318::GetValue_W(int raw)
{
    double val = Convert(raw);
    return ConvertDbmToW(val);
}

Value AD8318::ConvertDbmToW(double dbm)
{
    double val = pow(10.0, dbm / 10.0);
    Unit unit = Unit::W;

    if (val < 0.000001 )
    {
        unit = Unit::pW;
        val *= 1e9;
    } 
    else if (val < 0.001 ) 
    {
        unit = Unit::nW;
        val *= 1e6;
    } 
    else if (val < 1.0) 
    {
        unit = Unit::uW;
        val *= 1e3;
    } 
    else if (val < 1000.0 ) 
    {
        unit = Unit::mW;
    } 
    else 
    {
        unit = Unit::W;
        val /= 1e3;
    }
    Value ret(val, unit);
    return ret;
}
