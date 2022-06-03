#!/usr/bin/python3

#Remove files in picture folder
import os
import glob

files = glob.glob('/ssd/octoprint/timelapse/.collect/ESP32/*')
for f in files:
    os.remove(f)
