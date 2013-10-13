import yaml
from Automata import Automata

def parseAutomatas (fileDir):
	try:
		file = open (fileDir)
	except:
		print "Invalid File"
 
	text = file.read()
	parseData = yaml.load(text) 
	
	autList = list()

	for automatas in parseData:
		autList.append(parseAutomata(automatas))
	
	return autList

def parseAutomata (parseData):
	
	states  = parseData['states']
	start   = parseData['start']
	name    = parseData['automata']
	descrip = parseData['description']
	alpha   = parseData['alpha']
	final   = parseData['final']
	delta   = parseData['delta']

	return Automata(name, descrip, states, alpha, final, delta, start)


def dumpRes(data):
	return yaml.dump(data)

def dumpInfo(infoList):
	return yaml.dump({'msgtype':'info', 'info': infoList}, default_flow_style=False)	

def parseCmd(cmd):
	return yaml.load(cmd)

def parseStateCom(data):
	return yaml.load(data)
