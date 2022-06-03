#!/usr/bin/python3

from urllib.request import urlopen

try:
        url = "http://192.168.1.198/control?var=flash&val=0"
        page = urlopen(url)
        Light="off"
except:
        Light="error"
