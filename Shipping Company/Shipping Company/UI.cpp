#include "UI.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; 

string UI::askmode()
{
    string inputfilename;
    cout << "Hello Please enter the name of the input file ";
    cin >> inputfilename;
    cout << endl << "Please enter the output file name ";
    cin >> outputfile;

    cout<<endl<< "Please select the mode you prefer by entering the corrosponding number:" << endl << "1)interactive" << endl << "2)step-by-step" << endl << "3)silent mode" << endl;
    int x;
    cin >> x;
    while (x != 1 && x != 2 && x != 3)
    {
        cout << "the number you entered is invalid,please choose a valid number ";
        cin >> x;
        cout << endl;
    }
    mode = x;
    return inputfilename;
}

void UI::modeffect(Company*cmpnyptr,int hour, int day)
{
    if (mode == 1)
    {
        while (1)
        {
            if (cin.get() == '\n')
             break;
             else
                cout << "please press enter to continue" << endl;
        }
        cout << "Current Time (Day:Hour) " << day << ":" << hour<<endl;
        print(cmpnyptr);
    }
    
    if (mode == 2)
    {
        sleep_until(system_clock::now() + seconds(1));
        cout << "Current Time (Day:Hour) " << day << ":" << hour << endl;
        print(cmpnyptr);
        cout << endl;
    }
    if (mode == 3&&cmpnyptr->isfinished())
    {
        cout << " Silent Mode" << endl << "Simulation Starts..." << endl << "Simulation Ends, output file created" << endl;
    }
}

void UI::print(Company*cmpnyptr)
{
    cout << cmpnyptr->getwaitingnormal()->count() + cmpnyptr->getwaitingspecial()->count() + cmpnyptr->getwaitingvip()->count();
    cout << " " << "Waiting Cargos: " << "[";
    cmpnyptr->getwaitingnormal()->print();
    cout << "]";
    cout << " (";
    cmpnyptr->getwaitingspecial()->print();
    cout << ")";
    cout << " {";
    cmpnyptr->getwaitingvip()->print();
    cout << "}" << endl;
    cout << "--------------------------" << endl;
    cout << cmpnyptr->getdeliverednormal()->count() + cmpnyptr->getdeliveredspecial()->count() + cmpnyptr->getdeliveredvip()->count();
    cout << " Delivered Cargos:";
    cout << " [";
    cmpnyptr->getdeliverednormal()->print();
    cout << "]";
    cout << " (";
    cmpnyptr->getdeliveredspecial()->print();
    cout << ")";
    cout << " {";
    cmpnyptr->getdeliveredvip()->print();
    cout << "}" << endl;
    cout << "--------------------------" << endl;
    cout << cmpnyptr->getcountloading();
    cout << " " << "Loading Trucks: ";
    if (cmpnyptr->getnormalloadingtruck())
    {
        cout << cmpnyptr->getnormalloadingtruck()->getid() << " [";
cmpnyptr->getnormalloadingtruck()->getcargoqueue()->print();
        cout << "] ";
    }

    if (cmpnyptr->getspecialloadingtruck())
    {
        cout << cmpnyptr->getspecialloadingtruck()->getid() << " (";
        cmpnyptr->getspecialloadingtruck()->getcargoqueue()->print();
        cout << ") ";
    }

    if (cmpnyptr->getviploadingtruck())
    {
        cout << cmpnyptr->getviploadingtruck()->getid() << " {";
        cmpnyptr->getviploadingtruck()->getcargoqueue()->print();
        cout << "} ";
    }
    cout << endl << "--------------------------" << endl;
    cout << cmpnyptr->getmovingtrucks()->count(); //this is not fl output bs im putting it 34an n4oofha
    cout << " Moving Cargos:";
    cmpnyptr->getmovingtrucks()->print();
    cout << endl << "--------------------------" << endl;
    cout << cmpnyptr->getCheckupnormal()->count() + cmpnyptr->getCheckupspecial()->count() + cmpnyptr->getCheckupvip()->count();
    cout << "In-Checkup Trucks:";
    cout << " [";
    cmpnyptr->getCheckupnormal()->print();
    cout << "]";
    cout << " (";
    cmpnyptr->getCheckupspecial()->print();
    cout << ")";
    cout << " {";
    cmpnyptr->getCheckupvip()->print();
    cout << "}" << endl;
    cout << "--------------------------" << endl;
    cout << cmpnyptr->getwaitingnormaltruck()->count() + cmpnyptr->getwaitingspecialtruck()->count() + cmpnyptr->getwaitingviptruck()->count();
    cout << " " << "Empty Trucks: " << "[";
    cmpnyptr->getwaitingnormaltruck()->print();
    cout << "]";
    cout << " (";
    cmpnyptr->getwaitingspecialtruck()->print();
    cout << ")";
    cout << " {";
    cmpnyptr->getwaitingviptruck()->print();
    cout << "}" << endl;
    cout << "--------------------------" << endl<<endl;
}

string UI::getoutput() const
{
    return outputfile;
}

void UI::printfail()
{
    if(mode!=3)
        cout << "Failure of Truck has occured (bonus)" << endl;
}