#include "GPIOClass.h"
#include "wx/file.h"
#include "wx/textfile.h"
#include "wx/dir.h"

#define EXPORT_PATH wxT("/sys/class/gpio/export")
#define UNEXPORT_PATH wxT("/sys/class/gpio/unexport")
#define GPIO_PATH wxT("/sys/class/gpio")

GPIOClass::GPIOClass()
{
    m_gpionum = wxT("4");
    ValidateIOSystem();
}

GPIOClass::GPIOClass(wxString gpiox)
{
    m_gpionum = gpiox;
    ValidateIOSystem();
}

GPIOClass::~GPIOClass()
{
    //dtor
}

void GPIOClass::ValidateIOSystem()
{
    wxDir dir(GPIO_PATH);

    m_isAvailable = dir.IsOpened();

}

int GPIOClass::Export()
{
    if(m_isAvailable == FALSE)
        return -1;

    wxFile file(EXPORT_PATH,wxFile::write);
    if(file.IsOpened()==FALSE)
        return -1;

    if(file.Write(m_gpionum)==FALSE)
        return -1;

    file.Close();

    return 0;
}

int GPIOClass::UnExport()
{
    if(m_isAvailable == FALSE)
        return -1;

    wxFile file(UNEXPORT_PATH,wxFile::write);
    if(file.IsOpened()==FALSE)
        return -1;

    if(file.Write(m_gpionum)==FALSE)
        return -1;

    file.Close();

    return 0;
}

int GPIOClass::SetDir(wxString dirx)
{

    if(m_isAvailable == FALSE)
        return -1;

    wxString dirPath(GPIO_PATH);

    wxFile file(dirPath.Append(wxString::Format(wxT("%i/direction"))),wxFile::write);

    if(file.IsOpened()==FALSE)
        return -1;

    if(file.Write(dirx)==FALSE)
        return -1;

    file.Close();

    return 0;

}
int GPIOClass::SetVal(wxString valx)
{
    if(m_isAvailable == FALSE)
        return -1;

    wxString dirPath(GPIO_PATH);

    wxFile file(dirPath.Append(wxString::Format(wxT("%i/value"))),wxFile::write);

    if(file.IsOpened()==FALSE)
        return -1;

    if(file.Write(valx)==FALSE)
        return -1;

    file.Close();

    return 0;
}
int GPIOClass::GetVal(wxString &valx)
{

    if(m_isAvailable == FALSE)
        return -1;

    wxString dirPath(GPIO_PATH);

    wxFile file(dirPath.Append(wxString::Format(wxT("%s/value"),m_gpionum)),wxFile::read);

    if(file.IsOpened()==FALSE)
        return -1;

    wxFileOffset nSize = file.Length();

    wxUint8* data = new wxUint8[nSize];

    file.Read(data,(size_t)nSize);

    file.Close();

    if(data[0] != '0')
        valx = wxT("1");
    else
        valx = wxT("0");

    return 0;
}
wxString GPIOClass::GetNum()
{
    return m_gpionum;
}
