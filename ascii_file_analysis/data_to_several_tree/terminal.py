import os
#import numpy as np

# using terminal in order to delete some lines and saving the file
for i in range(10):
    command = "sed 1,5d C2acbd0000%d.txt > A_C2_%d.txt" % (i, i)
    os.system(command)

for i in range(90):
    command = "sed 1,5d C2acbd000%d.txt > A_C2_%d.txt" % (i+10, i+10)
    os.system(command)
    
for i in range(900):
    command = "sed 1,5d C2acbd00%d.txt > A_C2_%d.txt" % (i+100, i+100)
    os.system(command)

for i in range(6281):
    command = "sed 1,5d C2acbd0%d.txt > A_C2_%d.txt" % (i+1000, i+1000)
    os.system(command)

