#ifndef GPIOCLASS_H
#define GPIOCLASS_H

#include <wx/string.h>

class GPIOClass
{
    public:
        GPIOClass();
        GPIOClass(wxString gpiox);
        virtual ~GPIOClass();

        int Export();
        int UnExport();
        int SetDir(wxString dirx);
        int SetVal(wxString valx);
        int GetVal(wxString &valx);
        wxString GetNum();
        bool GetSystemAvailable(){return m_isAvailable;}



    protected:
    private:
        wxString m_gpionum;
        bool m_isAvailable;
        void ValidateIOSystem();
};

#endif // GPIOCLASS_H
