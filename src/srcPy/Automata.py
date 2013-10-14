import select, os, Parsers, yaml, time
from multiprocessing import Process, Pipe
        
class Automata:

	def __init__(self, name, descrip, states, alpha, final, delta, start):
		self.name = name
		self.descrip = descrip
		self.states = states
		self.alpha = alpha
		self.final = final
		self.delta = delta
		self.start = start

		self.currentStat = self.start
		self.nodeList = []

		self.__createPipes()
		self.__createNodes()
		
	def __createPipes (self):
		pipes = {}

		for nodes in self.delta:
			pipes[nodes['node']] = {}
 
		for nodes in self.delta:
			pipes[nodes['node']]['in'] = []
			pipes[nodes['node']]['out'] = []
			
		for nodes in self.delta:
			try:
				for changes in nodes['trans']:
					output, input = Pipe()
					pipes[nodes['node']]['out'].append((output, changes['next']))
					pipes[changes['next']]['in'].append((input, nodes['node']))
			except:
				pass
 	
		self.pipes = pipes

	def __createNodes (self):
		
		for nodeNam in self.states:
			start = False
			final = False
			inputPipes  = self.pipes[nodeNam]['in']
			outpurPipes = self.pipes[nodeNam]['out']
			if nodeNam == self.start:
				start = True
			elif nodeNam in self.final:
				final = True
			self.nodeList.append(Node(nodeNam, self.name, outpurPipes, inputPipes, self.delta, start, final))

	def automInfo(self):
		info = []
		info.append({'automata': self.name,  'ppid': os.getpgid(os.getpid())})
		
		for nodes in self.nodeList:
			 info.append({'node': nodes.name, 'pid': nodes.pid})

		return info

	def run (self):
		for node in self.nodeList:
			node.start()

class Node (Process):

	def __init__ (self, name, autom, outputPipes, inputPipes, delta, isStart, isFinal):
		super(Node, self).__init__()	
		self.name = name	
		self.autom = autom
		self.input = inputPipes
		self.output = outputPipes
		self.isStart = isStart
		self.isFinal = isFinal	
		self.delta = delta
		self.lastSend = {}
	
	def run (self):
		running = True

		while running:
			pipes = []
			for items in self.input:
				pipes.append(items[0])

			if self.isStart:
				pipes.append(self.scrtPipeIn)

			inputready, outputready, exceptready = select.select(pipes , [], [])

			for s in inputready: 				
				if s == self.scrtPipeIn:
					data = s.recv()
					self.comData = Parsers.parseStateCom(data)
					cadena = self.comData['rest']
					nextNode = self.makeTransition(cadena)
					self.sendData(nextNode, yaml.dump(self.comData))
				for ins in self.input:
					if s == ins[0]:
						data = s.recv()
						self.comData = Parsers.parseStateCom(data)
						cadena = self.comData['rest']
						nextNode = self.makeTransition(cadena)
						if nextNode == "reject" :
							send = {'codterm':1,'reccog':self.comData['recog'],'rest':self.comData['rest'], 'autom':self.autom}
							if send == self.lastSend:
								pass
							else:
								self.lastSend = send
								self.scrtPipeOut.send(yaml.dump(send))
						elif nextNode == "accept":
							send = {'codterm':0,'reccog':self.comData['recog'],'rest':self.comData['rest'], 'autom':self.autom}
							if send == self.lastSend:
								pass
							else:
								self.lastSend = send
								self.scrtPipeOut.send(yaml.dump(send))
						else:						
							self.sendData(nextNode, yaml.dump(self.comData))
				
						
		
	def sendData(self, node, data):
		for nodes in self.output:
			if nodes[1] == node:
				nodes[0].send(data)

	def deltaFun(self, state, input):
		if input == "" and self.isFinal:
			return "accept"
		elif input == "" and not self.isFinal:
			return "reject" 

		for nodes in self.delta:
 			if nodes['node'] == state:
				if not nodes['trans']:
					return "reject"
				for changes in nodes['trans']:
					chain = changes ['in']
					if chain == input[:len(chain)]:
						self.comData['recog'] = self.comData['recog'] + input[:len(chain)]
						self.currentStat = changes['next']
						self.data = input[len(chain):]
						self.comData['rest'] = input[len(chain):]
						return changes['next']
		return "reject" 
 
	def makeTransition(self, input):
		return self.deltaFun(self.name, input)

	def addScrtPipe(self, input, output):
		self.scrtPipeIn = input
		self.scrtPipeOut = output
