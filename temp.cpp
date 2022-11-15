#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;


/*
Operator Overloading:
                    The Operator Overloading, is a compile time Polymorphism, which is translated, at the Compile time itself.
                    
                    The Operator Overloading can be performed, with respect to particular Scopes.
                            
                    
                    Types of Operator:
                                        Athematic operations: + – * / %
                                        Logical operations:  && and ||
                                        Relational operations: == != >= <=
                                        Pointer operators: & and *
                                        Memory management operator: new, delete []
                                        
                            In Class Scope:
                                        Overloading Methodologies: 
                                                            1. Inside Class Scope (either using Scope resolution Operator or not).
                                                            2. using Member Function.
                
            Features:
                        1. The Operator is given a different Meaning, other than it's default,
                                hence   Returning values is not Compulsory
                                        No restriction in Process to be given.
                                
                                The above mentioned Features are restricted, to the Situation, in which the Operator is used.
Reference:
    1. https://stackoverflow.com/questions/58010917/scope-operator-in-operator-overloading#:~:text=If%20you%20define%20the%20operator,)%20%7B%20%2F%2F%20...%20%7D
*/



class temp
{
    public:
    int a,b,c;
    temp(int a,int b,int c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    temp(){}
    void operator ++()
    {
        cout<<"++ - Unary Operator Overloaded \n";
        this->a++;
        this->b++;
        this->c++;
    }
    temp operator +(temp& t)                                                            // Operator Overloaded inside CLASS SCOPE.
    {
        cout<<"+ - Binary Operator Overloaded in 'temp' Scope to add Data Members of two Objects"<<'\n';
        temp t1;
        t1.a = this->a+t.a;
        t1.b = this->b+t.b;
        t1.c = this->c+t.c;
        return t1;
    }
    void operator +(int a)
    {
        cout<<"+ - Binary Operator Overloaded 'temp' Scope to display :"<<a<<'\n';
    }
    //int operator +()                                                              // Invalid, Since '+' is a Binary Operator.
    void print()
    {
        cout<<"a : "<<this->a<<" b : "<<this->b<<" c : "<<this->c<<'\n';
    }
};

class temp1
{
    public:
    int t[4];
    temp1(int a,int b,int c)
    {
        this->t[0] = a;
        this->t[1] = b;
        this->t[2] = c;
    }
    temp1(){}                                                                                // Default Constructor, if not Declared, nomral Object Declaration is not allowed.
    void print()
    {
        cout<<"t[0] : "<<this->t[0]<<" t[1] : "<<this->t[1]<<" t[2] : "<<this->t[2]<<'\n';
    }
    void operator +=(int a)
    {
        cout<<" += Operator Overloaded\n";
        for(int i=0;i<3;i++)
            this->t[i]+=a;
    }
    /*
    void* operator new (size_t size)
    {
        return (void*)::new long int(10);                                           // Memory Management, NEW SCENARIO 
    }*/
    
    void* operator new(size_t size)
    {
        cout<<"New Operator Overloaded with respect to Class 'temp1'\n";
        return ::operator new(size);
        //  Here the Point is, we are returning only the ADDRESS of the MEMORY allocated, no type is specified, inside the function, Since the return type is 'VOID*'.
        //  return (void*)::operator new(size);                                           // Valid
        //  return (void*):: new int(10);                                                 // Valid
        //  return new temp1;                                                             // Invalid, Calls the Same Overloaded new Operator in the Class, resulting in Recursive Call.
        //  return (::new temp1);                                                         // Valid Since, it calls Global(Actual) new Operator.
        //  return *(:: new temp1) or return temp1()                                     // ERROR, since, there is only provision to return a Void pointer, in the Operator Overloading Function, hence cannot return a Solid Object. 
    }
    
    void operator delete(void* p)
    {
        cout<<"Delete Operator Overloaded with respect to Class 'temp1'\n";
        free(p);
        //delete p;
    }
    temp1 operator-(temp1&);
    friend temp1 operator +(temp1&,temp1&);
};

temp1 operator +(temp1 &t1,temp1 &t2)                                               // Operator overloaded using, friend function, takes one argument extra.
{
    cout<<" + Operator overloaded in class 'temp1' Scope\n";
    temp1 te;
    for(int i=0;i<3;i++)    
        te.t[i] = t1.t[i]+t2.t[i];
    return te;
}

temp1 temp1::operator -(temp1 &t1)                                                  // access the Class Scope, without proper Provision is Unauthorized. // It also takes one argument less than friend Function method.
{
    cout<<" - Operator overloaded in class 'temp1' Scope\n";
    temp1 te;
    for(int i=0;i<3;i++)    
        te.t[i] = this->t[i]-t1.t[i];
    return te;
}

// Global Operator Overloading:
/*
                                    The Global Operator Overloading inside a Namespace, is allowed, only if the Overloading Function is associated with a User-Defined Datatypes such as Class,Enum etc.
*/

void operator +(temp t)
{
    cout<<" '+' Operator Overloaded in the Global Scope "<<'\n';    
}
/*
void operator +(int t)              // _ERROR, since it is not associated with a user defined Datatype.
{
    cout<<" '+' Operator Overloaded in the Global Scope "<<'\n';    
}*/

void* operator new(size_t size)
{
    cout<<"New Operator is overloaded Globally\n";
    return (void*)malloc(size);
    //return new(size);
}

int main()
{
    
    temp t1(10,100,1000),t2(1,2,3);
    temp t3 = t1+t2;
    t1.print();
    t2.print();
    t3.print();
    +t2;
    +3;
    t1+3;
    ++t3;
    //t3+;                                                                          // Invalid Syntax.
    t1.print();
    t2.print();
    t3.print();
    //printf("[%d]",t3);
    
    // Overloading Methodologies:
    temp1 t11(9,8,7),t12(6,5,4);
    t11.print();
    t12.print();
    temp1 t13 = t11-t12;
    temp1 t14 = t11+t12;
    t13.print();
    t14.print();
    t13+=100;
    t13.print();
    temp1 *t15 = new temp1();
    t15->print();
    *(t15)+=4;
    t15->print();
    delete(t15);
    int* a = (int*)new temp1();
    char* a1 = (char*)new temp1();
    char* a2 = (char*)new temp1();
    //printf("[%d]",sizeof(a));
    /*
    for(int i=0;i<50;i++)
    {
        a[i] = i;
        a1[i] = i+48;
        a2[i] = i+65;
        cout<<i<<' '<<a[i]<<' '<<a1[i]<<' '<<a2[i]<<'\n';
    }
      */  
    /*
    for(int i=0;i<240;i++)                                                        // Entire ASCII System
            printf("| %d %c|",i,i);
    printf("\n%d",'\n');*/
}
