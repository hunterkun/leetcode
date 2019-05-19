#include "SalarySystem.h"

SalarySystem::SalarySystem(void)
{
    m_nCount = 0;
}
SalarySystem::~SalarySystem(void)
{
    for (int i = 0; i < m_nCount; i++)
    {
        Emplyee *p = m_arrEmplyee[i];
        delete p;
        m_arrEmplyee[i] = NULL;
    }
}

void SalarySystem::InputEmplyee(void)
{
    cout << "please input info about emplyee: \n";
    string name = "";
    int years = 0;
    bool isManager = false;
    int index = 0;
    while (index < MAX_COUNT)
    {
        cin.clear();
        cin >> name >> years >> isManager;
        if ("end" == name)
            break;
        Emplyee *p = NULL;
        if (isManager)
        {
            p = new Manager(years, name);
        }
        else
        {
            p = new Worker(years, name);
        }
        m_arrEmplyee[index] = p;
        index++;
    }
    m_nCount = index;
}

void SalarySystem::DisplaySalary(void)
{
    cout << "Salary System:\n";
    cout << "number of emplyee is" << m_nCount << "\n Average Salary is" << GetAverSalary() << endl;
    cout << "info of emplyee is " << endl;
    for (int i = 0; i < m_nCount; i++)
    {
        Emplyee *p = m_arrEmplyee[i];
        cout << p->GetName() << '\t' << p->GetSalary() << endl;
    }
}

float SalarySystem::GetAverSalary()
{
    int total = 0;
    for (int i = 0; i < m_nCount; i++)
    {
        Emplyee *p = m_arrEmplyee[i];
        total += p->GetSalary();
    }
    return total / m_nCount;
}

int main(int argc, char const *argv[])
{
    SalarySystem SalarySys;
    SalarySys.InputEmplyee();
    SalarySys.DisplaySalary();
    return 0;
}
