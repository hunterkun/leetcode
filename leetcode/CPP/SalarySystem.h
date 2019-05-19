#include <iostream>
#include <string>
using namespace std;

class Emplyee
{
public:
  Emplyee(int years, string name) : m_nYears(years), m_strName(name){};
  string GetName()
  {
    return m_strName;
  };
  virtual float GetSalary() = 0;

protected:
  int m_nYears;
  string m_strName;
};

class Worker : public Emplyee
{
public:
  Worker(int years, string name) : Emplyee(years, name){};
  virtual float GetSalary()
  {
    return m_nYears * 200 + 2000;
  };
};

class Manager : public Emplyee
{
public:
  Manager(int years, string name) : Emplyee(years, name){};
  virtual float GetSalary()
  {
    return m_nYears * 5000 + 10000;
  };
};

const int MAX_COUNT = 100;
class SalarySystem
{
private:
  int m_nCount;
  Emplyee *m_arrEmplyee[MAX_COUNT];

public:
  SalarySystem(void);
  ~SalarySystem(void);
  void DisplaySalary(void);
  float GetAverSalary();
  void InputEmplyee(void);
};