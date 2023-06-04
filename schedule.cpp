#include "schedule.h"
#include <sstream>
#include <string>

using namespace std;

Schedule::Schedule()                //default constructor
{
    time_slots = 0;
    data = new string*[7];              //data points to a string pointer array
    for (unsigned int i =0; i<7; i++)
    {
        data[i] = NULL;        //each row points to a string array
    }
}

Schedule::Schedule(int c)                       //parametric constructor
{
    time_slots = c;
    data = new string*[7];
    for (unsigned int i =0; i<7; i++)       //for each row
    {
        data[i]= new string[c];
        for (unsigned int j =0; j<c; j++)           //for each column
        {
            data[i][j] = "free";                  //assigns free to each cell
        }
    }
}

Schedule::Schedule(const Schedule &copy)                //deep copy constructor
{
    time_slots = copy.time_slots;                 //assigns the same number of columns to lhs
    data = new string*[7];
    for (unsigned int i =0; i<7; i++)           //for each row
    {
        data[i] = new string[time_slots];
        for (unsigned int j =0; j<time_slots; j++)          //for each column
        {
            data[i][j] = copy.data[i][j];             //assigns ith row jth col value of copy matrix to ith row jth col of lhs matrix
        }
    }
}

Schedule::~Schedule()
{
    for (unsigned int i =0; i<7; i++)           //for each row
    {
        delete[] data[i];                //deletes each row pointer
        data[i] = nullptr;                     //good practice
    }
    delete[] data;                        //deletes the matrix
    data = nullptr;                     //good practice
}

const Schedule& Schedule::operator=(const Schedule &rhs)             //assignment overloading
{
    if (this != &rhs)                   //if it is not self assignment
    {
        deleteMatrix();                //deallocates the matrix
        data = new string*[7];          //data points a string array pointer
        time_slots = rhs.getColumns();      //declares time_slots as #columns in rhs

        for (unsigned int i =0; i<7; i++)               //for each row
        {
            data[i] = new string[time_slots];           //each row points to an array
            for (unsigned int j = 0; j<time_slots; j++)         //for each col
            {
                data[i][j] = rhs.data[i][j];               //assigns each cell
            }
        }
    }
    return *this;                       //returns lhs
}

Schedule Schedule::operator+(const Days &day) const                   //+ overloading
{
    Schedule sch (*this);           //creates a deep copy constructor
    for (unsigned int i = 0; i<7; i++)
    {
        if (i == day)           //if it is the correct day
        {
            for (unsigned int j = 0; j<sch.time_slots; j++)     //for each col
            {
                sch.data[i][j] = "busy";                //sets each col to busy
            }
            break;                                      //there can only be one correct day, it is okay to break after the operations are done
        }
    }
    return sch;
}

Schedule Schedule::operator+(const int& d) const
{
    Schedule sch (*this);           //creates a deep copy constructor
    for (unsigned int i = 0; i<7; i++)      //for each row
    {
        sch.data[i][d] = "busy";                //sets every d'th col to busy
    }
    return sch;                             //returns the newly created object
}

Schedule Schedule::operator+(const Schedule &rhs) const
{
    Schedule sch(time_slots);           //sch is created with every cell as free
    for (unsigned int i =0; i<7; i++)
    {
        for (unsigned int j =0; j<time_slots; j++)
        {
            if (data[i][j] == "busy" || rhs.data[i][j] == "busy")           //if the left matrix's cell or right matrix's cell is busy
            {
                sch.data[i][j] = "busy";                                //sets the same cell in the newly created object as busy
            }
        }
    }
    return sch;                             //returns the newly created object
}

Schedule Schedule::operator*(const Schedule &rhs) const
{
    Schedule sch(time_slots);           //sch is created with every cell as free
    for (unsigned int i =0; i<7; i++)
    {
        for (unsigned int j =0; j<time_slots; j++)
        {
            if (data[i][j] == "busy" && rhs.data[i][j] == "busy")           //if both matrices' cells are busy
            {
                sch.data[i][j] = "busy";                                //sets the same cell in the newly created object as busy
            }
        }
    }
    return sch;                             //returns the newly created object
}

string * Schedule::operator[](Days day) const
{
    for (unsigned int i =0; i<7; i++)
    {
        if (i == day)
        {
            return data[i];             //the function will end when there is a match
        }
    }
    return data[6];                 //dummy value
}

int Schedule::getColumns() const                        //returns number of columns
{
    return time_slots;
}

string** Schedule::getMatrix() const                //returns the matrix
{
    return data;
}

void Schedule::deleteMatrix()
{
    for (unsigned int i =0; i<7; i++)
    {
        delete[] data[i];                //deletes each row pointer
        data[i] = nullptr;                     //good practice
    }
    delete[] data;                        //deletes the matrix
    data = nullptr;                     //good practice
}


bool operator<(const Schedule & lhs, const Schedule & rhs)              //operator overloading as a free function
{
    int countLhs = 0;
    int countRhs = 0;
    /*for the lhs matrix*/
    for (unsigned int i =0; i<7;i++)            //for each row
    {
        for (unsigned int j =0; j< lhs.getColumns(); j++)     //for each col
        {
            if (lhs.getMatrix()[i][j] == "busy")               //if the cell is busy
            {
                countLhs++;                         //increment count
            }
        }
    }
    /*for the rhs matrix*/
    for (unsigned int i =0; i<7; i++)                   //for each row
    {
        for (unsigned int j =0; j<rhs.getColumns(); j++)      //for each col
        {
            if (rhs.getMatrix()[i][j] == "busy")               //if the cell is busy
            {
                countRhs++;                     //increment count
            }
        }
    }
    return countLhs<countRhs;
}

ostream & operator<<(ostream & os, const Schedule & sch)
{
    string str = "Mo:" + getRow(sch, 0);                                //uses getRow() function for modularity
    str += "Tu:" + getRow(sch,1);
    str += "We:" + getRow(sch,2);
    str += "Th:" + getRow(sch,3);
    str += "Fr:" + getRow(sch,4);
    str += "Sa:" + getRow(sch,5);
    str += "Su:" + getRow(sch,6);
    os << str;                                                          //puts str into os
    return os;                                                          //returns os
}

ostream & operator <<(ostream & os, const Days & day)
{
    string str;
    if (day == Monday)
    {
        str = "Monday";
    }
    else if (day == Tuesday)
    {
        str = "Tuesday";
    }
    else if (day == Wednesday)
    {
        str = "Wednesday";
    }
    else if (day == Thursday)
    {
        str = "Thursday";
    }
    else if (day == Friday)
    {
        str = "Friday";
    }
    else if (day == Saturday)
    {
        str = "Saturday";
    }
    else
    {
        str = "Sunday";
    }
    os << str;
    return os;
}


string getRow(const Schedule & rhs, const int& i)
{
    string str = "";                                //declares an empty string
    for (int j =0; j<rhs.getColumns(); j++)             //for each column
    {
        str += " " + rhs.getMatrix()[i][j];             //adds every cell in ith row
    }
    str += "\n";
    return str;
}