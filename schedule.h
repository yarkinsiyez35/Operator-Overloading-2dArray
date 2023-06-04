#include <string>
#include <sstream>

using namespace std;
#ifndef CS_204_HW4_SCHEDULE_H
#define CS_204_HW4_SCHEDULE_H




enum Days {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

class Schedule{
private:
    int time_slots;
    string** data;
public:
    Schedule();                                                        //default constructor
    Schedule(int c);                                                   //parametric constructor
    Schedule(const Schedule & copy);                                   //deep copy constructor
    ~Schedule();                                                       //destructor
    const Schedule& operator =(const Schedule & rhs);                  //operator overload for =
    Schedule operator+(const Days& day) const ;                        //operator overload for +
    Schedule operator+(const int& d) const;                            //operator overload for +
    Schedule operator+(const Schedule &rhs) const;                     //operator overload for +
    Schedule operator*(const Schedule &rhs) const ;                    //operator overload for *
    string * operator[](Days day) const;                               //operator overload for []
    int getColumns() const;                                            //accessor function to get number of columns
    string** getMatrix() const;                                        //accessor function to get the matrix
    void deleteMatrix();                                               //used for deallocating

};
    bool operator<(const Schedule & lhs, const Schedule & rhs);         //operator overload as free function
    ostream & operator<<(ostream & os, const Schedule & sch);           //operator overload for <<
    ostream & operator <<(ostream & os, const Days & day);              //operator overload for <<
    string getRow(const Schedule & sch, const int& i);                   //gets a row as a string value

#endif //CS_204_HW4_SCHEDULE_H
