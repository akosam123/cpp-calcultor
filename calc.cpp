/******************************************************************************

Self Made Calculator

*******************************************************************************/
#include <iostream>
#include <cmath>
using namespace std;

void displayOptions();
float multiplication(float a, float b);
float addition(float a, float b);
float subtraction(float a, float b);
float divison(float a, float b);
float squareroot(float a);
float power(float a);

char options;


int main()
{
    
    cout << "This is a calculator that calculates:\n" << "*, +, -, /, squares, powers\n";
    cout << "-----------------------------------\n";
   
    
     
    
     
    while(options == 'N' || options == 'n' || options == '*', '+', '-', '/', '&', '^') 
    {
        
        displayOptions();
        cin >> options;
        
        
        if (options == 'N' || options == 'n')
        {
            cout << "\nSee you soon" << endl;
            break;
        }
        
        switch (options)
        {
            float num1, num2;
            case '*':
                multiplication(num1, num2);
                break;
            case '+':
                addition(num1, num2);
                break;
            case '-':
                subtraction(num1, num2);
                break;
            case '/':
                divison(num1, num2);
                break;
            case '&':
                squareroot(num1);
                break;
            case '^':
                power(num1);
                break;
            default:
            cout << "Try again!\n";
                continue;   
        }
        
    }
        
        
        

    return 0;
}
void displayOptions()
{
    cout << "Please input your arithmetic equation\n";
    cout << "'*' - Multiplication" << endl;
    cout << "'+' - Addition" << endl;
    cout << "'-' - Subtraction" << endl;
    cout << "'/' - Divison" << endl;
    cout << "'&' - Square root" << endl;
    cout << "'^' - Power" << endl; // will allow for power of 2 or 3
    cout << "N or n - Exits loop\n";
   
}
float multiplication(float a, float b)
{
    float total;
    cout << "Enter a number value: " << endl;
    cin >> a;
    cout << "Enter a number value: " << endl;
    cin >> b;
    total = a * b;
    cout << "The product is: " << total << endl << endl;
    return 0;
}
float addition(float a, float b)
{
    float total;
    cout << "Enter a number value: " << endl;
    cin >> a;
    cout << "Enter a number value: " << endl;
    cin >> b;
    total = a + b;
    cout << "The product is: " << total << endl << endl;
    return 0;
}
float subtraction(float a, float b)
{
    float total;
    cout << "Enter a number value: " << endl;
    cin >> a;
    cout << "Enter a number value: " << endl;
    cin >> b;
    total = a - b;
    cout << "The product is: " << total << endl << endl;
    return 0;
}
float divison(float a, float b)
{
    float total;
    cout << "Enter a number value: " << endl;
    cin >> a;
    cout << "Enter a number value: " << endl;
    cin >> b;
    total = a / b;
    cout << "The product is: " << total << endl << endl;
    return 0;
}
float power(float a)
{
    float total;
    int  exponent;
    
   // do
   // {
      //  cout << "Enter 2 for power of 2 and 3 for power of 3" << endl;
       // cin >> choice;
    
       // if(choice == 2)
       // {
            cout << "--------------------------------------" << endl;
            cout << "Enter a number value: " << endl;
            cin >> a;
            cout << "Enter a exponent value: " << endl;
            cin >> exponent;
            total = pow(a, exponent);
            cout << "The product is: " << total << endl << endl;
          //  break;
       // }
        /*else if(choice == 3)
        {
            cout << "--------------------------------------" << endl;
            cout << "Enter a number value: " << endl;
            cin >> a;
            total = pow(a, 3);
            cout << "The product is: " << total << endl << endl;
            break;
        }
        else if(choice != 3 || choice != 2)
        {
            cout << "Invalid selection. Please try again.\n";
            continue;
        }
        
    }while(choice == 2 || choice == 3);*/
    return 0;
}
float squareroot(float a)
{
    float total;
    cout << "Enter a number value: " << endl;
    cin >> a;
    total = sqrt(a);
    cout << "The product is: " << total << endl << endl;
    return 0;
}
