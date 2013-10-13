import Parsers
automs = Parsers.parseAutomatas('automata.yaml')
autom = automs[0]
autom.run()
autom.nodeList[0].sendData('A', '{ recog: "", rest: "aaaaac"}')
