#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int maximumHeight = 23;
    int minimumHeight = 0;
    int height;
    

    do
    {
        printf("Fill in a non-negative number between %d and %d:\n", minimumHeight, maximumHeight); //%d asks for integer
        height = GetInt();
    }
    /*
     *state a maximumheight, later on its easier to change your code and give maximumheight a different number
      GetInt gets the information from the user and attaches it to height, whenever height is used in the code now it 
      uses the number that was given.
     */
    while (height <= minimumHeight || height > maximumHeight);
    /*
     * do the loop while height >= maximumHeight (23) when the given integer is lower than 23 it will continue with the 
       rest of the code.
     */
 
 
    int count; // line
    int count2; // spaces #
   
    for(count = 0; count < height; count++) // begins with count 0 = smaller than height; count++ -> count 1 (loop starts over)
    {
         for(count2 = 0; count2 < height - (count + 1); count2++) // to retrieve lower height with count(spaces are dependent on height)  
        {
            printf(" "); // when count = 0  and height is 20 spaces are 20-1=19
        }
        for(count2 = 0; count2 < count + 2; count2++) // begint met count 0 = kleiner dan count (dit geval 0+1); count2++ -> count2 1 
        {
            printf("#"); // with count = 0 # printed twice
        }
        printf("\n"); // new line
    } /*
       * and loop starts over, count=1; count<height; count++ -> count 2 (loop starts again next round 
       * and tells the second loop to start) count2=1;
       * count2(=1) < count+1(1+2=3);count2++->2
       * and so on untill count is not smaller than height any longer. The loops will stop and the pyramid is ready
       */
    

}
