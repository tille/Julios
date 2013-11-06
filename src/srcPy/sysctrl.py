import Parsers, select, time, sys, yaml, os
from multiprocessing import Process, Pipe

cmd = raw_input("")
automs = Parsers.parseAutomatas(cmd)
  
inputPipes  = []
outputPipes = []

respAcept = []
lastMesg = ''

for automatas in automs:
	for nodes in automatas.nodeList:
		output, input = Pipe()
		if nodes.isStart:
			out, inp = Pipe()
			nodes.addScrtPipe(output, inp)
			inputPipes.append(input)
			outputPipes.append(out)
		else:
			nodes.addScrtPipe(None, input)
			outputPipes.append(output)

for automatas in automs:
	automatas.run()

outputPipes.append(sys.stdin)

while True:

	inputready, outputready, exceptready = select.select(outputPipes , inputPipes, [])
 	for s in inputready:
		if s == sys.stdin:
			cmd = sys.stdin.readline() 
			com = Parsers.parseCmd(cmd)
			try:
				if com ['cmd'] == 'send':
					msg = com ['msg']
					lastMesg = com ['msg']
 					for pipes in inputPipes:
						pipes.send(Parsers.dumpStateCom({'recog': "", 'rest': msg}))
				elif com ['cmd'] == 'info':
					data = []
					if not com ['msg']:
						for automatas in automs:
							data = data + automatas.automInfo()
					else:
						for automata in automs:
							if automata.name == com ['msg']:
								data = automata.automInfo()
					print Parsers.dumpInfo(data)	
				elif com ['cmd'] == 'stop':
					for aut in automs:
						for nod in aut.nodeList:
							nod.close()
							del nod
				else:
					info = {'msgtype':'error', 'error':{'where': 'Pid: '+str(os.getpid()), 'cause': "broken pipe on function sndMsg"}}
					print yaml.dump(info, default_flow_style=False)
			except:
				info =  {'msgtype':'error', 'error':{'where': 'Pid: '+str(os.getpid()), 'cause': "broken pipe on function sndMsg"}}
				print yaml.dump(info, default_flow_style=False)
		else:
			data = s.recv()
			data = yaml.load(data)

			if 'codterm' in data.keys() and (data['codterm'] == 1 or data['codterm'] == 0):
				respAcept.append(data)
				if len(respAcept) == len (automs):
					print Parsers.dumpAcpMs(respAcept, lastMesg)

			if 'codterm' in data.keys() and data['codterm'] == 2:
				info = {'msgtype':'error', 'error':{'where': 'Pid: '+str(data['pid']), 'cause': data['cause']}}
				print yaml.dump(info, default_flow_style=False)
