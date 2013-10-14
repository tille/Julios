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

def dumpStateCom(data):
	return yaml.dump(data)

def dumpAcpMs(data, msg):
	ans = []
	reject = {'msgtype':'reject', 'reject':[]}
	accept = {'msgtype':'accept', 'accept':[]}
	for items in data:
		if items['codterm'] == 1:
			reject['reject'].append({'automata': items['autom'], 'msg':msg})
		elif items['codterm'] == 0:
			accept['accept'].append({'automata': items['autom'], 'msg':msg})

	if not len(reject['reject']) == 0:
		ans.append(reject)
	
	if not len(accept['accept']) == 0:
		ans.append(accept)

	return yaml.dump(ans, default_flow_style=False)	
		
		
