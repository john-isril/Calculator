# Calculator

Hello! This is a basic calculator console application that helps the user solve expressions. I created this application to better understand the stack data structure, it's applications, and how to properly implement my own stack. I also learned a lot about input validation throughout this projects development.

### Features:
#### 1. Floating point values: Can solve expressions with floating point values (ex: 6.8 * 4.2).
#### 2. Negative numbers: Can solve expressions with negative numbers (ex: -6 * 4, 6 -- 4).
#### 3. Chained expressions: In addition to simple expressions (ex: 5 * 2), it can also solve longer chained expressions (ex: 5 + 5 * 2).
#### 4. Input validation. Validates the users input and displays the error type. 
                       1. Rejects expressions that have binary operators without operands on both sides (ex: 6 *).
                       2. Rejects expressions with unbalanced parenthesis (ex: ((6 * 2))))). 
                       3. Rejects a divide by zero expression. Will reject unknown symbols (ex: user types in 'a').
                       4. Rejects a floating point value that does not have values on both sides of the decimal point (ex: 7.).

### Example:
![image](https://user-images.githubusercontent.com/74218894/158117328-9d83ab2a-13ed-4098-aff7-f20e9b4798f7.png)

