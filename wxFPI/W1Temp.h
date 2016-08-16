#ifndef W1TEMP_H
#define W1TEMP_H

#include "wx/arrstr.h"

class W1Temp
{
    public:
        W1Temp();
        virtual ~W1Temp();

        bool GetSystemAvailable(){ return m_isAvailable;}
        wxArrayString GetSensors(){ return m_Sensors; }
        int GetSensorCount();
        float ReadF(int sensorIdx);
        float ReadC(int sensorIdx);

    protected:
    private:
        bool m_isAvailable;
        wxArrayString m_Sensors;
};

#endif // W1TEMP_H
