from math import factorial, sqrt
import re

print("-"*13,"Wecome To my Calculator","-"*13)

# """

def GetNumber(st):
    num1 = input(st)
    ## Check if number if valid or not [dec,hec,oct,bin]
    while True:
        
        ## check dec number
        if re.match("(^[-+]?([0-9]+)(\.[0-9]+)?)$", num1):
            num1 = float(num1)
            # print (st,num1)
            break
        # check hex number 
        elif re.match("^(0[xX]){1}[0-9a-fA-F]+$", num1):
            num1 = int(num1[2:],16)
            # print (st,num1)
            break
        ## check oct number 0o15
        elif re.match("^(0[oO]){1}[0-7]+$", num1):
            num1 = int(num1[2:],8)
            # print (st,num1)
            break
        ## check bin number 0b1001
        elif re.match("^(0[bB]){1}[0-1]+$", num1):
            num1 = int(num1[2:],2)
            # print (st,num1)
            break
        else:
            print("Enter a valid Number.")
            num1 = input(st)
    return num1

CalcMode = 0
flag = 1

while 1:

    if flag:
        print("Claculator Mode:")
        print("1- Scientific Mode")
        print("2- Programming Mode")
        print("3- Exist")
        flag =0

    CalcMode = input(">> Select Mode:")
    
    ## Mode Option
    if CalcMode >= '1' and CalcMode <= '3':

        ## Scientific mode select
        if CalcMode == '1':
            print("Allowed Operation['+','-','*','/','%','x**y','n!','rt(y,x)']")
            
            num1 = GetNumber("Enter First number:")
            operation = input("Enter Operation:")
            num2 = 0

            ## Addition Operation
            if operation == "+":
                num2 = GetNumber("Enter Second number:")
                print("Result:",num1+num2)

            ## subtraction Operation
            elif operation == "-":
                num2 = GetNumber("Enter Second number:")
                print("Result:",num1-num2)

            ## Multiplication Opertion
            elif operation == "*":
                num2 = GetNumber("Enter Second number:")
                print("Result:",num1*num2)

            ## Division 
            elif operation == "/":
                num2 = GetNumber("Enter Second number:")
                if num2 == 0:
                    print("Error!!")
                else:
                    print("Result:",num1/num2)

            ## Reminder Operation
            elif operation == "%":
                num2 = GetNumber("Enter Second number:")
                print("Result:",num1%num2)
            
            ## Exponential Operation    
            elif operation == "**":
                num2 = GetNumber("Enter Second number:")
                print("Result:",pow(num1,num2))
            
            ## Square Root Operation
            elif operation == "rt":
                num2 = GetNumber("Enter Second number:")
                print("Result:",num2**(1/num1))
            
            ## Factorial Operation
            elif operation == "!":
                print("Result:",factorial(num1))
            
            else:
                print("Error Invalid Operation")

        ## Programming mode select
        elif CalcMode == '2':
            print("Allowed Operation['x','d','o','b','<<','>>','&','|','^','~]")
            
            num1 = GetNumber("Enter First number:")
            operation = input("Enter Operation:")
            num2 = 0

            ## hex Operation
            if operation == "x":
                print("Result:",hex(int(num1)))
            
            ## bin Operation
            elif operation == "b":
                print("Result:",bin(int(num1)))
            
            ## oct Operation
            elif operation == "o":
                print("Result:",oct(int(num1)))
            
            ## dec Operation
            elif operation == "d":
                print("Result:",int(num1))
            
            ## Shift left Operation
            elif operation == "<<":
                num2 = GetNumber("Enter Second number:")
                print("Result:",int(num1)<<int(num2))
            
            ## Shift Right Operation
            elif operation == ">>":
                num2 = GetNumber("Enter Second number:")
                print("Result:",int(num1)>>int(num2))
            
            ## And Operation
            elif operation == "&":
                num2 = GetNumber("Enter Second number:")
                print("Result:",int(num1)&int(num2))
            
            ## Or Operation
            elif operation == "|":
                num2 = GetNumber("Enter Second number:")
                print("Result:",int(num1)|int(num2))
            
            ## Not Operation
            elif operation == "~":
                print("Result:",~int(num1))
            
            ## Xor Operation
            elif operation == "^":
                num2 = GetNumber("Enter Second number:")
                print("Result:",int(num1)^int(num2))

        ## Exist mode select
        elif CalcMode == '3':
            exit(0)
        ## invalid mode select
        else:
            print("Plz enter a valid selection !!")
    else:
        flag = 1


# """