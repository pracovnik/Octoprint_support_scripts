#!/usr/bin/python3

import time
import urllib.request
import os
import sys
import glob
import os.path
from pathlib import Path


timestring = time.strftime("%Y%m%d-%H%M%S")

#ESP take picture
imgURL = "http://192.168.1.198/capture"
fileESP32="/ssd/octoprint/timelapse/.collect1/ESP32/"+timestring+".jpg"
urllib.request.urlretrieve(imgURL,fileESP32)

#Below this is only part, where I add ESP picture to the timelapse's picture. 
#First rotate and add to the picture (extend timelapse's and add to empty space the ESP ones)

