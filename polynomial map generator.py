#12 Aug 2024
'''
Generates a Lagrange polynomial that interpolates an x and y vector

Polynomial is encoded into x86 assembly



This creates a direct mapping of the inputs to the output - f(key) = value, for all keys and value
'''
import sys;
import math;

#Vectors to fit
sourceCodePneumonics = {

    #NOTE: Could technically have multi-char pneumonics here - but makes it much harder to not go over 64 bit integer limit


    #Pneumonic : Machine code
    "A" : "0", "L" : "1", "J" : "2",

    #Registers
    "X" : "0", "Y" : "1",


    #"R0" : "0", "R1" : "1", "R2" : "2", "R3" : "3",

};


#Check for overflows
MAX_BYTES = 4;
BITS_PER_BYTE = 8;
BYTES_PER_CHAR = 1;





#Preprocess pneumonics to put them into binary form
def preprocess_pneumonics(sourceCodePneumonicsInput):

    keys = [];
    values = [];

    for key, value in sourceCodePneumonicsInput.items():

        if(len(key) > MAX_BYTES * BYTES_PER_CHAR or len(value) > MAX_BYTES * BYTES_PER_CHAR): #String cannot be longer than 8 bytes (must fit in reg)
            print("ERROR: key: '" + str(key) + "' or value: '" + str(value) + "' overflows set byte limit, max char limit is: " + str(int(MAX_BYTES * BYTES_PER_CHAR)));
            return keys, values, 1;



        newKey = "";
        newValue = "";

        for char in key:
            newKey += str(ord(char));
        
        for char in value:
            newValue += str(ord(char));

        keys.append(int(newKey));
        values.append(int(newValue));

    return keys, values, 0;



#Generate the map and assembly
def generate_Lagrange_map(keys, values):

    if(len(keys) != len(values)):
        print("ERROR: Keys and values vectors are not the same length || keys = " + str(len(keys)) + " values = " + str(len(values)));
        return 1;

    #NOTE: For now this just prints text to the console - make it output to a .asm file later
    for i in range(0, len(keys)):

        leadingCoefficient = values[i];
        print(str(leadingCoefficient) + " * (", end = '');


        print("(", end = '');
        for j in range(0, len(keys)): #Numerator
            
            if keys[j] != keys[i]:
                print("(x - " + str(keys[j]) + ") ", end = '');

        print(" / ", end = '');


        denominator = 1;
        for j in range(0, len(keys)): #Denominator

            if keys[j] != keys[i]:
                #Denominator
                denominator *= keys[i]- keys[j];



        print(str(denominator) + ")", end = '');
                
        print(") + ");
    
        if(denominator > pow(2, BITS_PER_BYTE * MAX_BYTES)):
            print("ERROR: denominator '" + str(denominator) + "' exceeds " + str(MAX_BYTES) + " byte signed limit (" + str(pow(2, BITS_PER_BYTE * MAX_BYTES)) + ")");
            print("Overflow factor: " + str(denominator/ pow(2, BITS_PER_BYTE * MAX_BYTES)));
            return 1;

    return 0;








def main():

    keys = [];
    values = [];
    sourceCodePneumonicsInput = sourceCodePneumonics;

    keys, values, returnCode = preprocess_pneumonics(sourceCodePneumonicsInput);
    if(returnCode != 0):
        return 1;

    if(generate_Lagrange_map(keys, values) != 0):
        return 1;

    return 0;


if __name__ == "__main__":
    sys.exit(main());




