# Recursively create directories and subdirectories with the same struct
# Example: >app c:/python spo0kyee/manysubs 4 

import os
import sys
import customtkinter

def main():
    if len(sys.argv) < 3:
        print("usage: {app} parent_folder folder_path amount_of_copies")
        return
    
    for i in range(int(sys.argv[3])):
        if not os.path.exists(sys.argv[2]):
            splited = str(sys.argv[2]).split('/')
            splited[0] = splited[0] + str(i + 1)
            path = sys.argv[1] + '/'
            path += "/".join(splited)
            os.makedirs(path, exist_ok=True)

main()