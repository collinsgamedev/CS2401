/*****************************************************
   This class is a container class that holds courses of the
   class course. The container is created through a linked
   list.
     Edward Collins       Fall 2017     Ohio University
*********************************************************/

#ifndef COLLEGE
#define COLLEGE
#include <iostream>
#include <string>
#include "course.h"
#include "node.h"
class College
{
public:
	College();
	College(std::string& name);
	~College();
	College(const College& other);
	void operator = (const College& other);
	void add(course& c);
	void display(std::ostream& outs)const;
	void remove(std::string& course);
	double hours();
	double gpa();
	void save(std::ostream& outs);
	void load(std::istream& ins);

private:
	node *head;
	std::string username = "VOID";
};

#endif
