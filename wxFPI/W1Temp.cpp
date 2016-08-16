#include "W1Temp.h"
#include "wx/dir.h"

#define W1_TEMP_DIR  wxT("/sys/bus/w1/devices")

W1Temp::W1Temp()
{
    wxDir dir(W1_TEMP_DIR);

    m_isAvailable = dir.IsOpened();

    if(m_isAvailable == FALSE)
        return;

    wxString filename;
    bool cont = dir.GetFirst(&filename);
    while ( cont )
    {
        if(filename.StartsWith("28"))
            m_Sensors.Add(filename);
        cont = dir.GetNext(&filename);
    }
}

W1Temp::~W1Temp()
{
    //dtor
}

int W1Temp::GetSensorCount()
{
    if(m_Sensors == NULL)
        return 0;
    return m_Sensors.GetCount();
}

float W1Temp::ReadF(int sensorIdx)
{


}

float W1Temp::ReadC(int sensorIdx)
{
    if(m_isAvailable == FALSE)
        return 255.0;

     wxString dirPath(W1_TEMP_DIR);

    wxFile file(dirPath.Append(wxString::Format(wxT("%s/w1_slave"),m_Sensors.Item(sensorIdx))),wxFile::read);

    if(file.IsOpened()==FALSE)
        return -1;

    wxFileOffset nSize = file.Length();

    wxUint8* data = new wxUint8[nSize];

    file.Read(data,(size_t)nSize);

    file.Close();
}
