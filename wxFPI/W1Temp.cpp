#include "W1Temp.h"
#include "wx/dir.h"
#include "wx/file.h"

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
        if(filename.StartsWith(wxT("28")))
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
    return m_Sensors.GetCount();
}

float W1Temp::ReadF(int sensorIdx)
{
    float val = ReadC(sensorIdx);
    if(val == 255.0)
        return val;
    return val * 9.0 / 5.0 * 32.0;

}

float W1Temp::ReadC(int sensorIdx)
{

    if(m_isAvailable == FALSE)
        return 255.0;

    wxString dirPath(W1_TEMP_DIR);
    dirPath = dirPath.Append(m_Sensors.Item(sensorIdx));
    dirPath = dirPath.Append(wxT("/w1_slave"));
    wxFile file(dirPath,wxFile::read);

    if(file.IsOpened()==FALSE)
        return -1;

    wxFileOffset nSize = file.Length();

    wxUint8* data = new wxUint8[nSize];

    file.Read(data,(size_t)nSize);

    file.Close();

    wxString buf = wxString::From8BitData((const char *)data);

    int idx = buf.Find(wxT("t="));

    if(idx == wxNOT_FOUND)
        return 255.0;

    double val;

    if(buf.SubString(idx + 2, idx + 2 + 5).ToDouble(&val) == FALSE)
       return 255.0;
    else
       return (float)(val / 1000.0);
}
