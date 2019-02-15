#!/usr/bin/env python


import os
import sys
import subprocess

#print ('Argument List:', str(sys.argv))

if len(sys.argv)<2:
	path = '.'
else:
	path=sys.argv[1]

#dumpfile=sys.argv[2]

symbolspath=os.path.join(path,'symbols')
if not os.path.exists(symbolspath):
	os.makedirs(symbolspath)
	
for file in os.listdir(path):
	current = os.path.join(path, file)
	filename, file_extension=os.path.splitext(file)
	
	if file_extension=='.sym':
		symbol_file_path=os.path.join(path,file)
		print ("Processing file:",file)
		
		symbols_str=subprocess.check_output(["head","-n1",symbol_file_path]).decode("utf-8")
		print ("Processing symbols ingo:",symbols_str)
		symbols_info=str.split(symbols_str)
		if len(symbols_info)==5:
			file_symbols_path=os.path.join(symbolspath,symbols_info[4])
			if not os.path.exists(file_symbols_path):
				os.makedirs(file_symbols_path)
			file_symbols_path_id=os.path.join(file_symbols_path,symbols_info[3])
			if not os.path.exists(file_symbols_path_id):
				os.makedirs(file_symbols_path_id)
			
			cpout=subprocess.check_output(["cp",current,file_symbols_path_id]).decode("utf-8")
			if len(cpout)>0:
				print ("error copy:",cpout)
						

#minidump_stackwalk=subprocess.check_output(["./minidump_stackwalk.exe",dumpfile+" symbols > "+dumpfile+".info 2>&1"]).decode("utf-8")
#print ("minidump_stackwalk:",minidump_stackwalk)
