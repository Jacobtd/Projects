/*
Jacob Doerr's Programming Assignment 5

This program checks all odd integers from 3 to 1001, and checks to see which of these 
odd numbers, i, have values to where both i^2 +2 and i^2 -2 are prime. In this code, we 
use several int variables, including oddNum, which stores the current odd number that we 
are checking, oddNumSquared, which is that value squared, as well as squaredPlusTwo and 
squaredMinusTwo, which each hold i^2 +2 and i^2 -2 respectively. Finally, the variable
divisor is used when checking to see if a value is prime, and is iterated from 2 to that
value -1. 

In assembly, the program starts by initializing oddNum to 3. It enters a loop to iterate 
through odd numbers up to 1001, squaring the current odd number and calculating both i^2 +2
and i^2 -2. First, the program squares oddNum and stores the result in oddNumSquared. It then 
calculates i^2 +2 and stores it in squaredPlusTwo, followed by calculating i^2 -2 and storing 
it in squaredMinusTwo. Next, the program checks if i^2 +2 is prime. It initializes divisor to 
2 and begins dividing squaredPlusTwo by each integer starting from 2 up to one less than 
squaredPlusTwo. If any division results in a remainder of 0, the program concludes that 
squaredPlusTwo  is not prime and moves to the next odd number. If no divisors are found, the 
program determines that squaredPlusTwo is prime and proceeds to check squaredMinusTwo. This 
process is identical to the primality test for squaredPlusTwo.  If both values are found to
be prime, the program outputs the current odd number, increments to the next odd number, and 
restarts the loop. The loop continues until oddNum exceeds 1001, at which point the program 
terminates. By the end of execution, the program outputs all odd numbers the program outputs 
all odd numbers within the specified range that meet the given criteria.
*/

#include <stdio.h>
#define CRT_SECURE_NO_WARNINGS

void main() {
    int oddNum; //Stores the current odd number we are checking
    int oddNumSquared; //Stores the value of that odd number squared
    int squaredPlusTwo; //Stores the odd number's squared value, plus two
    int squaredMinusTwo; // Stores the odd number's squared value, minus two
    int divisor; //Stores our current divisor while iterating to see if a value is prime

    printf("Numbers where i^2 + 2 and i^2 - 2 are prime:\n");

    __asm {
        mov oddNum, 3 //Set our first number to 3
        top: cmp oddNum, 1001 // Loop through odd numbers from 3 to 1001
        jg finish // If oddNum > 1001, exit the loop
        mov eax, oddNum // Prepare to square oddNum
        mul eax // oddNumSquared = oddNum * oddNum
        mov oddNumSquared, eax // Store squared value in oddNumSquared
        mov eax, oddNumSquared // Prepare to add 2 to the square
        add eax, 2 // squaredPlusTwo = oddNumSquared + 2
        mov squaredPlusTwo, eax // Store result in squaredPlusTwo
        mov eax, oddNumSquared // Prepare to subtract 2 from the square
        sub eax, 2 // squaredMinusTwo = oddNumSquared - 2
        mov squaredMinusTwo, eax // Store result in squaredMinusTwo
        mov divisor, 2 // Initialize divisor to 2

        plusTwoPrime: mov eax, squaredPlusTwo // Load squaredPlusTwo for primality check
        cmp divisor, eax // Compare divisor with squaredPlusTwo
        jge checkMinusTwo // If divisor >= squaredPlusTwo, move to checkMinusTwo
        mov edx, 0 // Clear edx for division
        div divisor // Divide squaredPlusTwo by divisor
        cmp edx, 0 // Check if divisible
        je notPrime // If divisible, squaredPlusTwo is not prime
        add divisor, 1 // Increment divisor
        jmp plusTwoPrime // Continue checking primality of squaredPlusTwo

        checkMinusTwo : mov divisor, 2 // Reset divisor to 2
        minusTwoPrime : mov eax, squaredMinusTwo // Load squaredMinusTwo for primality check
        cmp divisor, eax // Compare divisor with squaredMinusTwo
        jge isPrime // If divisor >= squaredMinusTwo, both numbers are prime
        mov edx, 0 // Clear edx for division
        div divisor // Divide squaredMinusTwo by divisor
        cmp edx, 0 // Check if divisible
        je notPrime // If divisible, squaredMinusTwo is not prime
        add divisor, 1 // Increment divisor
        jmp minusTwoPrime // Continue checking primality of squaredMinusTwo

        notPrime : add oddNum, 2 // Move to the next odd number
        jmp top // Restart loop at top

        isPrime : nop // Both squaredPlusTwo and squaredMinusTwo are prime
    }
    printf("%d\n", oddNum); // Output the number that meets the criteria

    __asm {
        add oddNum, 2 // Increment oddNum
        jmp top // Restart loop at top
        finish : nop // End of program
    }
}

/*
Program Output: 
Numbers where i^2 + 2 and i^2 - 2 are prime:
3
9
15
21
33
117
237
273
303
309
387
429
441
447
513
561
573
609
807
897
*/