#12 Aug 2024
'''
Generates a Lagrange polynomial that interpolates an x and y vector

Polynomial is encoded into x86 assembly



This creates a direct mapping of the inputs to the output - f(key) = value, for all keys and value
'''
import sys;

#Vectors to fit
keys = [-2-1,0,4];
values = [-2,4,1,8];





def main():

    if(len(keys) != len(values)):
        print("Keys and values vectors are not the same length");
        return 1;




    #NOTE: For now this just prints text to the console - make it output to a .asm file later
    for i in range(0, len(keys)):

        leadingCoefficient = values[i];
        print(str(leadingCoefficient) + " * (", end = '');

        for j in range(0, len(keys)):
            
            if keys[j] != keys[i]:
                print("((x - " + str(keys[j]) + ") / ", end = '');
                print(str(keys[i]- keys[j]) + ") ", end = '');
                
        print(") * ", end = '');

    return 0;


if __name__ == "__main__":
    sys.exit(main());




