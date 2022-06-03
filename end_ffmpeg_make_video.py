#!/usr/bin/python3

import os
import time


timestring = time.strftime("%Y%m%d-%H%M%S")
timeframx="25"

import os, os.path

# path joining version for other paths
DIR = '/ssd/octoprint/timelapse/.collect/ESP32/'
if ( len([name for name in os.listdir(DIR) if os.path.isfile(os.path.join(DIR, name))]) < 500 ) :
        timeframex="6"
else:
        timeframex="25"

os.system("/usr/bin/ffmpeg -framerate "+timeframex+" -pattern_type glob -i \' "+DIR+"*.jpg\' -c:v libx264 -pix_fmt yuv420p /ssd/octoprint/timelapse/ESP_"+timestring+".mp4"

