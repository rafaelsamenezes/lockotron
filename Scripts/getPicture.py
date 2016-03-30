#!/usr/bin/python
import os
import local_variables as lv

def main():
    command = lv.getPicture_path + " " + lv.target_path
    os.system(command)

if __name__ == '__main__':
    main()
