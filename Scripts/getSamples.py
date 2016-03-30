#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
import local_variables as lv
from urllib2 import urlopen

def getIdNumber():
    return str(len(os.listdir(lv.samples_path)))

def checkFolder(id):
    d = os.path.dirname(id)
    if not os.path.exists(d):
        os.mkdir(id)

def main():
    id = raw_input("Insira o id do usuário: ")
    folder_name = lv.samples_path + str(id) + "/"
    print folder_name
    checkFolder(folder_name)
    os.system(lv.getSamples_path + " " + folder_name)
    command = lv.trainer_bin + " " + lv.samples_path + " " + lv.target_path + " " + str(lv.samples_number) + " " + getIdNumber()
    os.system(command)
    urlopen("http://127.0.0.1:82/galileo.php?update")

if __name__ == '__main__':
    main()
