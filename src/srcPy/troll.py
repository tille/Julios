import subprocess, time

comm = 'xrandr -o '
strings = ['right', 'inverted', 'left', 'normal']
count = 0

while 1:
	pop = subprocess.Popen(comm + strings[count], shell= True)
	time.sleep(2)
	if count == 3:
		count = 0
	else:
		count +=1
