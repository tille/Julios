import Parsers

cmd = raw_input("")
automs = Parsers.parseAutomatas(cmd)

while True:
	cmd = raw_input("")
	com = Parsers.parseCmd(cmd)
	print com

	if com ['cmd'] == 'send':
		pass
	elif com ['cmd'] == 'info':
		pass
	elif com ['cmd'] == 'stop':
		pass
