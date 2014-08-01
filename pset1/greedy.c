#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float minimumAmount = 0;
    float change;
    int cents;
    
    do
    { 
        printf("How much money do I owe you: \n");
        change = GetFloat(); // receive this number by using GetFloat and place it in the variable change
        
        cents = round(change * 100); // make cents out of dollars and round it  
    }
    while(change <= minimumAmount);
    
    
    int quarters = cents / 25; // quarters is the amount in cents divided by 25 lets say 110 cents/25 = 4 (quarters = 4)
    cents = cents % 25; // updating cents using modulo which in this example was 10 so cents is now 10
 
    int dimes = cents / 10; // dimes is cents / 10, so 10/10 = 1
    cents = cents % 10; // nothing left 10 % 10 = 1.0 cents now equals 0
  
    int nickles = cents / 5;
    cents = cents % 5;

    int totalCoins = quarters + dimes + nickles + cents;
    printf("%d\n",totalCoins); //added all coins together which in this example 5 coins
 }
 
