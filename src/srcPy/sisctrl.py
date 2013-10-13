import Parsers


while True:
	cmd = raw_input("")
	com = Parsers.parseCmd(cmd)
	print com
