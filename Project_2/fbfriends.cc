#include <iostream>
#include "friend.h"
#include "fbfriends.h"
#include <algorithm>
#include <string>

using namespace std;

FBFriends::FBFriends()
{
  capacity = 5;
  used = 0;
  current_index = 0;
  data = new Friend[capacity];
}

FBFriends::~FBFriends()
{
  delete[] data;
}

FBFriends::FBFriends(const FBFriends& other)
{
  used = other.used;
  capacity = other.capacity;
  data = new Friend[capacity];
  copy(other.data, other.data + used, data);
}

void FBFriends::operator = (const FBFriends& other)
{
  if(this == &other)
    {
    return;
    }
  if(capacity != other.capacity)
    {
      delete []data;
      capacity = other.capacity;
      data = new Friend[capacity];
    }
  used = other.used;
  std::copy(other.data, other.data + used, data);
}

void FBFriends::start()
{
  current_index = 0;
}

bool FBFriends::is_item()
{
  return current_index < used;
}

Friend FBFriends::current()
{
  return data[current_index];
}

void FBFriends::advance()
{
  if (is_item())
    {
      ++current_index;
    }
}

void FBFriends::insert(const Friend& f)
{
  if(used == capacity)
    {
      resize();
    }
  if(!is_item())
    {
      current_index = 0;
      data[0] = f;
    }
  else
    {
    for(int i = used-1; i >= current_index; --i)
      {
	data[i+1] = data [i];
      }
    }
  data[current_index] = f;
  ++used;
}

void FBFriends::resize()
{
  Friend *temp;
  temp = new Friend[capacity+5];
  std::copy(data, data + used, temp);
  delete[]data;
  data = temp;
  capacity += 5;
}

void FBFriends::show_all(std::ostream& outs)const
{
  if(used == 0)
    {
      cout << "You currently have no friends registered.\n";
    }
  for(int i = 0; i < used; ++i)
    {
      cout << data[i];
    }
}

void FBFriends::attach(const Friend& f)
{
  if(used == capacity)
    {
      resize();
    }
  if(!is_item())
    {
      data[used]=f;
      ++used;
    }
  for(int i = used-1; i >= current_index; --i)
    {
      
      data[i+1] = data [i];
    }
  data[current_index+1] = f;
  ++used;
}

void FBFriends::remove_current()
{
  if(is_item())
    {
      for(int i = current_index; i < used; ++i)
	{
	  data[i] = data[i+1];
	}
      --used;
    }
}

void FBFriends::bday_sort()
{
  	Date sort_date1, sort_date2;
	bool done = false;
	size_t i = 0;
	Friend temp;
	while (!done)
	{
		done = true;
		for (i = 0; i < used - 1; ++i)
		{
			//finds the date of the array
		  sort_date1 = data[i].get_bday();
		  sort_date2 = data[i + 1].get_bday();

			if (sort_date1 > sort_date2)
			{
				//if so, sort the checks in the array through a bubble sort
				temp = data[i];
				data[i] = data[i + 1];
				data[i + 1] = temp;
				done = false;
			}
			//if not, do not change the array
			else
				done = true;
		}
	}
}

bool FBFriends::is_friend(const Friend& f) const
{
  string name1, name2;
  Date bday_check1, bday_check2;
  for(int i = 0; i < used; ++i)
    {
      name1 = data[i].get_name();
      name2 = data[i+1].get_name();
      bday_check1 = data[i].get_bday();
      bday_check2 = data[i+1].get_bday();
    }
  if(name1 == name2 && bday_check1 == bday_check2)
  {
    return true;
  }
  else
    return false;
}

void FBFriends::load(istream& ins)
{  
  string names;
  Date bdays;
  if(ins.peek() == '\n' || ins.peek() == '\r') {ins.ignore();}
  getline(ins, names);
  //if(ins.peek() == '\n' || ins.peek() == '\r') {ins.ignore();}
  ins >> bdays;
  ins.clear();
  while(!ins.eof())
    {
      if(used == capacity)
	{
	  resize();
	}
      data[used].input(ins);
      ins.clear();
      ++used;
      if(ins.peek() == '\n' || ins.peek() == '\r') {ins.ignore();}
    }
}

void FBFriends::save(ostream& outs)
{
  for (int i = 0; i < used; ++i)
    {
      outs << data[i];
    }
}

Friend FBFriends::find_friend(const std::string& name)const
{
  string find_name;
  Date bday_found;
  for(int i = 0; i < used; ++i)
    {
      find_name = data[i].get_name();
      bday_found = data[i].get_bday();
    }
  if(find_name == name)
    {
      cout << "Their birthday is: " << bday_found << std::endl;
    }
}
