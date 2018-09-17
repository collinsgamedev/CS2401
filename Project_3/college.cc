/*******************************************************************
This is the implementation file for the College class. For more
information about the class see FBFriend.h.

Edward Collins    Ohio University        October 6 2017
Last modified: October 13 2017
******************************************************************/
#include "college.h"
#include <string>

College::College()
{
  head = NULL;    //set the head node to NULL
}

College::College(std::string& name)
{
  head = NULL;
  username = name;    //username constructor
}

College::~College()
{
  node *rmptr;   //create a node called rmptr
  while (head != NULL)    //while head is not equal to NULL
    {
      rmptr = head;    //set remove pointer to head pointer
      head = head->link();    //set head to head at link
      delete rmptr;    //delete the remove pointer
    }
}

College::College(const College& other)
{
  if (other.head == NULL)
    { head = NULL; }	//set head to NULL if other head is at NULL
  else
    {
      node *source, *dest;	//creates nodes that are pointers known as source and destination (dest for short)
      head = new node(other.head->data());	//set head to a new node and have head point at data set to other head at its data
      dest = head;	//set dest equal to head
      source = other.head->link();	//have source set to other head's link
      while (source != NULL)
	{
	  dest->set_link(new node(source->data()));	//dest will set link and create a new node
	  dest = dest->link();	//set dest to the dest at link
	  source = source->link();	//set source to the source link
	}
    }
}

void College::operator = (const College& other)
{
  if (this == &other)    //if the address of this is equal to other, return this
    { return; }
  
  
  node *remove;
  while (head != NULL)
    {
      remove = head;
      head = head->link();
      delete remove;
    }
  if (other.head == NULL)
    {
      head = NULL;
    }	//set head to NULL if other head is at NULL
  else
    {
      node *source, *dest;	//creates nodes that are pointers known as source and destination (dest for short)
      head = new node(other.head->data());	//set head to a new node and have head point at data set to other head at its data
      dest = head;	//set dest equal to head
      source = other.head->link();	//have source set to other head's link
      while (source != NULL)
	{
	  dest->set_link(new node(source->data()));	//dest will set link and create a new node
	  dest = dest->link();	//set dest to the dest at link
	  source = source->link();	//set source to the source link
	}
    }
}

void College::add(course& c)
{
  if (head == NULL)	//check to see if the head is equal to NULL, this checks to see if the list is empty
    {
      head = new node(c, NULL);	//if so, create a new node and add the course to the list
    }
  else	//if there is a list...
    {
      node *cursor = NULL, *previous = NULL;	//create two nodes know as cursor and previous. Cursor will be used to go through the list and previous is used to assign the last node that the cursor was on
      if (c < head->data())	//if the course is less than what is at the beginning of the list
	{
	  cursor = head;	//assign cursor to what head is pointing at
	  head = new node(c, cursor);		//create a new node with the course and connect it to the cursor pointer
	  while(cursor->link() != NULL)
	    {
	      cursor = head;  //set cursor to point at what head is pointing at
	      while (cursor->link() != NULL)  //while cursor link is not equal to NULL
		{
		  previous = cursor;              //set previous to point at what cursor is pointing at
		  cursor = cursor->link();        //have cursor assigned to the cursor link
		}
	      if (c > cursor->data())         //if c is greater than the course data
		{
		  node *temp;             //create a temp node
		  temp = cursor->link();  //have the temp node hold the cursor link
		  cursor->set_link(new node(c, temp));    //set the link to the temp node with the course in the data field
		}
	      else
		{
		  node *temp;             //createa a temp node
		  temp = cursor;  //have temp be equal to the cursor pointer
		  previous->set_link(new node(c, temp));  //at the previous node, set a link to a new node that will hold the course added and set a link to temp
		}
	    }
	  cursor->set_link(NULL);         //set the cursor link to NULL to avoid seg fault
	}
      else	//if the course is greater than what is at the beginning of the head of the list
	{
	  cursor = head;	//set cursor to point at what head is pointing at
	  while (cursor->link() != NULL)	//while cursor link is not equal to NULL
	    {
	      previous = cursor;		//set previous to point at what cursor is pointing at
	      cursor = cursor->link();	//have cursor assigned to the cursor link
	    }
	  if (c > cursor->data())		//if c is greater than the course data
	    {
	      node *temp;		//create a temp node
	      temp = cursor->link();	//have the temp node hold the cursor link
	      cursor->set_link(new node(c, temp));	//set the link to the temp node with the course in the data field
	    }
	  else
	    {
	      node *temp;		//createa a temp node
	      temp = cursor;	//have temp be equal to the cursor pointer
	      previous->set_link(new node(c, temp));	//at the previous node, set a link to a new node that will hold the course added and set a link to temp
	    }
	}
    }
}

void College::display(std::ostream& outs)const
{
  if (head == NULL)	//head is equal to NULL, tell them that they have no course registered
    {
      std::cout << "You currently have no courses registered.\n";
    }
  else
    {
      for (node *temp = head; temp != NULL; temp = temp->link())	//create a temp node, have temp be set to temp at link, and check to see if temp is not equal to NULL
	{
	  std::cout << temp->data();		//go through the list and show the courses in the list
	}
    }
}


void College::remove(std::string& course)
{
  node *remove = NULL, *previous = NULL;	//create two node called remove and previous
  if (head->data().get_course_number() == course)		//if the course that is wanting to be removed is at the head of the list
    {
      remove = head;		//set remove pointer to the head pointer
      head = head->link();		//have head be set to head at link
      delete remove;	//delete the remove pointer
    }
  else
    {
      remove = head;	//set remove pointer to the head pointer
      while (remove != NULL && remove->data().get_course_number() != course)	//check to see if remove is not equal to NULL and if the data in remove is
	//not equal to the course that is wanting to be removed
	{
	  previous = remove;	//set previous to remove
	  remove = remove->link();	//set remove to the remove at link
	}
      if (remove != NULL)		//remove is not equal to NULL
	{
	  previous->set_link(remove->link());		//set previous at link to the remove at link
	  delete remove;	//delete remove
	}
      else	//else, tell them that the course is not in the list
	{
	  std::cout << "That course is not in your list.\n";
	}
    }
}

double College::hours()
{
  double total_hours = 0;		//used to store the total number of hours
  for (node *temp = head; temp != NULL; temp = temp->link())	//create a temp node, have temp be set to temp at link, and check to see if temp is not equal to NULL
    {
      total_hours += temp->data().get_hours();	//go through the list and get the sum of all the hours taken
    }
  return total_hours;		//return the total amount of hours
}

double College::gpa()
{
  //used to set the GPA to two (2) decimal points
  std::cout.setf(std::ios::fixed);
  std::cout.setf(std::ios::showpoint);
  std::cout.precision(2);
  double current_gpa = 0;		//used to store the current gpa
  double num_grade = 0;		//used to store the number grade times the hours
  double total_hours = 0;		//used to store the total hours
  for (node *temp = head; temp != NULL; temp = temp->link())	//create a temp node, have temp be set to temp at link, and check to see if temp is not equal to NULL
    {
      num_grade += (temp->data().get_number_grade() * temp->data().get_hours());	//go through the list and get the number grade and get the hours of the course
      //then get the sum of all of them
      total_hours += temp->data().get_hours();		//go through the list and get the total hours that has be entered
    }
  current_gpa = num_grade/total_hours;	//calculate the current gpa by dividing the num_grade by the total_hours
  return current_gpa;		//return the current_gpa
}

void College::save(std::ostream& outs)
{
  for(node *temp = head; temp != NULL; temp = temp->link())
    {
      outs << temp->data();
    }
}

void College::load(std::istream& ins)
{
  course c;
  c.input(ins);
  while(!ins.eof())
    {
      add(c);
      c.input(ins);
    }
}

