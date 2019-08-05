# Takes a file path as input. Attempts to read a c-style struct/class from it and generate
# a restructured text sphinx docs page for that class. Has some limitations currently:
# - Can't handle functions, comments, or specifiers like const, volatile, static, etc
# - Can't handle multiple public/private/protected values. Only one right at the start of the class
# - Can't handle additional specifiers in the class declaration like declspec(align(some_number)) or whatever thing
# - Can't handle multiple inherited classes
# - Can only handle one class/struct definition per input file
# - Doesn't properly name array types. Keeps array size on variable name.
#
# Some of these limitations will be fixed in the future and some of them don't really matter for the pusposes of the RSL.
# Since most classes being bound and documented are the games classes dumped with IDA as c-style classes with no functions or constructors
# some of these limitations are minor issues. Usually only slight modifications of a class definition must be made to get a correct parse. 

from sys import argv
from os import path
from pathlib import Path
import re

class Member:
    def __init__(self, Type, Name):
        self.Type = Type
        self.Name = Name

class StructInfo:
    def __init__(self):
        self.Name = ""
        self.Parent = None
        self.Members = []
        self.Types = []
        self.ExemptTypes = [ # types who's names shouldn't be capitalized
            "unsigned int", "int", "unsigned long", "long", "float", "char",
            "unsigned char", "signed char", "short", "unsigned short",
            "string", "std::string", "unsigned int16", "int16", "bool",
            "unsigned int8", "int8", "void*", "String", "unsigned __int32",
            "char*"
        ]

    def Print(self):
        print(f"Struct.Name: {self.Name}")
        print(f"Struct.Parent: {self.Parent}")
        
        print(f"Struct.Members:")
        for i, Member in enumerate(self.Members):
            print(f"\t{i}: Type: {Member.Type}, Name: {Member.Name}")
        
        print(f"Struct.Types:")
        for i, Type in enumerate(self.Types):
            print(f"\t{i}: {Type}")

    def GenerateTypesList(self):
        for Member in self.Members:
            if Member.Type not in self.Types:
                self.Types.append(Member.Type)

    def FixNames(self):
        for Member in self.Members:
            Name = Member.Name.title() # Capitalize first letter of each word
            Member.Name = re.sub('_', '', Name) # Remove underscores

            if Member.Type not in self.ExemptTypes:
                Type = Member.Type.title()
                Member.Type = re.sub('_', '', Type)

#print("argv: ", argv)

if len(argv) < 1:
    print("Pass the path of a file with a c style class definition in it to have docs for that class/struct generated.")
else:
    StructFilePath = Path(argv[1])

with open("./TestFile.h", 'r') as StructFile:
    StructString = StructFile.read().split()

Struct = StructInfo()

Index = 0
if(StructString[Index] == "class" or StructString[Index] == "struct"):
    Index += 1
    Struct.Name = StructString[Index]
    print(f"StructName: {Struct.Name}")
    Index += 1
    
    if(StructString[Index] == ':'):
        Index += 1
        MaybeParent= StructString[Index]
        if(MaybeParent == "public" or MaybeParent == "private" or MaybeParent == "protected"):
            Index += 1
            Struct.Parent = StructString[Index]
        else:
            Struct.Parent = MaybeParent

        Index += 1
        print(f"Parent type detected as \"{Struct.Parent}\". Continuing...")
    elif(StructString[Index] == '{'):
        print("No parent type detected. Continuing...")

    if(StructString[Index] == '{'):
        Index += 1
        if(StructString[Index] == "public:" or StructString[Index] == "private:" or StructString[Index] == "protected:"):
            Index += 1
        
        i = Index
        while i < len(StructString) - 1:
            Value = StructString[i]
            NextValue = StructString[i + 1]

            if(Value != "};" and NextValue != '};'):
                if(Value == "signed" or Value == "unsigned"):
                    Type = Value + " " + NextValue
                    Struct.Members.append(Member(Type, StructString[i+2].strip(';')))
                    i += 3
                else:
                    Struct.Members.append(Member(Value, NextValue.strip(';')))
                    i += 2
            else:
                break
    else:
        print(f"Invalid string \"{StructString[Index]}\" following type name! Expected '{{' Exiting!")

print("\nDone parsing struct string. Output:")

Struct.FixNames()
Struct.GenerateTypesList() # Need to generate this once done parsing the file for later use to avoid repeat types.
#Struct.Print() # Has it's own print function for convenience

# Next we want to generate a blank documentation page for the struct using the info gathered
print(f"Generating documentation page for {Struct.Name}")

with open("./" + Struct.Name + ".rst", 'w') as Out:
    Out.write("\n.. attention:: This page is incomplete and needs better descriptions and research into the behavior of the variables.\n\n\n")
    Out.write(Struct.Name + "\n")
    Out.write("********************************************************\n")
    Out.write("Type description goes here.\n\n")
    
    if Struct.Parent is not None:
        Out.write(f"Inherits `{Struct.Parent}`_\n\n")
    
    Out.write("Variables\n")
    Out.write("========================================================\n\n")

    # Write out variables. Currently doesn't detect functions separately
    for Member in Struct.Members:
        Out.write(f"**{Member.Name}** (`{Member.Type}`_)\n")
        Out.write(f"    Unknown value.\n\n") # The default description for unknown stuff. Can be left blank or filled in.
    
    # Write out links at the bottom for type pages. Assumes page has same name as type
    for Type in Struct.Types:
        if Type not in Struct.ExemptTypes:
            Out.write(f".. _`{Type}`: ./{Type}.html\n")
        else:
            Out.write(f".. _`{Type}`: ./PrimitiveTypes.html\n")
    
    # Write parent class link if valid
    if Struct.Parent is not None:
        Out.write(f".. _`{Struct.Parent}`: ./{Struct.Parent}.html\n")

print("Done!")