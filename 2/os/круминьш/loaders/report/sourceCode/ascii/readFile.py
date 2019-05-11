f = open('ascii.txt', 'rU', encoding='utf8')
asciiDic = {' ':"32,", '─':"196,", '█':"219,", '▓':"178,", '░':"176,",'\n':"13,10,", '▄':"220,", '▒':"177,", '▀':"223,"}
while True:
	c = f.read(1)
	if not c:
		break
	print(asciiDic[c], end='')