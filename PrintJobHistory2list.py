#!/usr/bin/env python3

import sqlite3
import cgitb

DBconn = sqlite3.connect('/ssd/octoprint/.octoprint/data/PrintJobHistory/printJobHistory.db')
DBcurs  = DBconn.cursor()

#This script is used to read the sql database and offer it's data  as a generated webpage as a list


result=DBcurs.execute("SELECT printStartDateTime,printEndDateTime,printStatusResult,fileName,slicerSettingsAsText,databaseId FROM pjh_printjobmodel ORDER B$

cgitb.enable()

print("Content-Type: text/html;charset=utf-8")
print("Content-type:text/html\r\n")

print("<table border=1>")
print("<tr><th>File name</th><th>Status</th><th>Started</th><th>Finished</th><th>Filament length</th><th>Filament type</th><th>id</th></tr>")

PLAfilamentcount=0
PETGfilament=0
FLEXfilament=0
filamentcount=0

for row in result:
    print("<tr>")
    name=row[3]
    for toremove in ["PLA","PETG",".gcode","0.2mm","0.4mm","0.3mm","FLEX","MINI","0.15mm"]:
        name=name.replace(toremove,'').strip()
    print("<td>"+name.replace("_"," ").strip()+"</td>")
    print("<td>"+row[2]+"</td>")
    print("<td>"+row[0]+"</td>")
    print("<td>"+row[1]+"</td>")
    for i in  row[4].split("\n") :
        if i.startswith("; filament used [mm] = "):
            xstring=(i.replace("; filament used [mm] = "," ")).strip()
            print("<td align='right'>"+xstring.split('.')[0]+"</td>")
            filamentcount+=int(float(xstring))
    for i in  row[4].split("\n") :
        if i.startswith("; filament_type ="):
            xstring=(i.replace("; filament_type = "," ")).strip()
            print("<td>"+xstring+"</td>")
    print("<td>"+str(row[5])+"</td>")
    print("</tr>")

print("</table>")
print((filamentcount / 1000) )

DBconn.close()
