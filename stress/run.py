import os

test = 1
while True:
    os.system("python gen.py > input.txt")
    os.system(".\correct.exe < input.txt > correct.txt")
    os.system(".\solution.exe < input.txt > output.txt")
    correct = open("correct.txt").read()
    output = open("output.txt").read()
    if correct != output:
        print("Error on test", test)
        break
    print("Test", test, "is OK")
    print("-------------------")
    test += 1
