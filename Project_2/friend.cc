#include <iostream>
#include "friend.h"
#include "date.h"
using namespace std;

Friend::Friend()
{
  name = "Void";
  bday = Date(1, 1, 1900);
}

std::string Friend::get_name()const
{
  return name;
}

Date Friend::get_bday()const
{
  return bday;
}

bool Friend::operator == (const Friend& other)const
{
  if(name == other.name && bday == other.bday)
    {
      return true;
    }
  else
    return false;
}

bool Friend::operator != (const Friend& other)const
{
    if(name != other.name && bday != other.bday)
    {
      return true;
    }
  else
    return false;
}

void Friend::input(std::istream& ins)
{
  while(ins.peek() == '\n' || ins.peek() == '\r') {ins.ignore();}
  std::getline(ins, name);
  ins >> bday;
}

void Friend::output(std::ostream& outs)const
{
  if(&outs == &cout)
    {
      outs << "This friend is :" << name << std::endl;
      outs << "Their birthday is :" << bday << std::endl;
    }
  else
    {
      outs << name << std::endl << bday << std::endl;
    }
}

std::istream& operator >> (std::istream& ins, Friend& f)
{
  f.input(ins);
  return ins;
}

std::ostream& operator << (std::ostream& outs, const Friend& f)
{
  f.output(outs);
  return outs;
}
