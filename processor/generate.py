#
#	Process cdc160 definition
#
import re
#
#	Read and preprocess.
#
src = [x.replace("\t"," ") for x in open("cdc160.def").readlines()]
src = [x if x.find("//") < 0 else x[:x.find("//")] for x in src]
src = [x.strip() for x in src if x.strip() != ""]
#
#	Rip out functions 
#
functions = "\n".join([x[1:] for x in src if x[0] == ':'])
src = [x for x in src if x[0] != ':']
#
#	Get code and mnemonics for every opcode
#
codes = [ None ] * 64
mnemonics = [ None ] * 64

for l in src:
	m = re.match("^([0-7\-\,]+)\s*(\d+)\s*\"(.*?)\"\s*(.*)$",l)
	assert m is not None,"Bad line "+l
	if len(m.group(1)) == 5 and m.group(1)[2] == "-":
		opRange = range(int(m.group(1)[:2],8),int(m.group(1)[-2:],8)+1)
	else:
		opRange = [ int(x,8) for x in m.group(1).split(",")] 

	for opc in opRange:
		assert mnemonics[opc] is None,"Duplicate "+l
		atyp = opc % 4
		if opc >= 0o60 and opc < 0o70:
			atyp = 2 if opc < 0o64 else 3
		mnemonics[opc] = m.group(3).replace("@m","difb"[atyp])
		mnemonics[opc] = mnemonics[opc].replace("@n",["%d","(%d)","%f","%b"][atyp])
		cycles = int(m.group(2))
		code = m.group(4)
		if opc >= 0o10 and opc < 0o60 and opc % 4 == 1:
			cycles = cycles + 1
		if opc >= 0o01 and opc < 0o60:
			code = code + ";rni()"
		code = code + ";$cycles = $cycles + {0}".format(cycles)
		code = code.replace("@m","difb"[atyp])
		codes[opc] = code
#
#	Generate mnemonics
#
open("_cdc160_mnemonics_old.h","w").write("{ "+",".join(['"'+x.split("/")[0]+'"' for x in mnemonics]) + "};")
open("_cdc160_mnemonics.h","w").write("{ "+",".join(['"'+x.split("/")[1]+'"' for x in mnemonics]) + "};")
#
#	Generate case include
#
h = open("_cdc160_case.h","w")
for i in range(0,64):
	h.write("case 0x{0:02o}: /** {1} **/\n".format(i,mnemonics[i]))
	xcode = codes[i].replace("$","")+";break;"
	h.write("   "+xcode+"\n")
h.close()
#
#	Generate support include
#
h = open("_cdc160_support.h","w")
xcode = functions.replace("function","static void").replace("$","")
h.write(xcode)
h.close()
#
#	Generate cdc160 Class
#
h = open("_cdc160_class.ts","w")
h.write("abstract class CDC160Generated extends CDC160Base {\n")
#
#	Support functions
#
xcode = functions.replace("$","this.").replace("inline","").split("\n")
for i in range(0,len(xcode)):
	if xcode[i][:8] == "function":
		xcode[i] = "private "+xcode[i][8:-1].strip()+" : void {"
h.write("\n".join(xcode))
#
#	Each opcode functions
#
for i in range(0,64):
	xcode = codes[i].replace("$","this.")+";"
	h.write("private opcode_{0:02x}(): void ".format(i))
	h.write("{ "+xcode+" };\n")
	h.write("\n")
#
#	Get list of methods for each opcode.
#	
h.write("protected getOpcodeList():Function() {\n return [")
h.write(",".join(["opcode_{0:02x}".format(x) for x in range(0,256)]))
h.write("];\n}\n")
h.close()
#
#	Build mnemonic groups for assembler
#
instructions = {}
for i in range(0,64):
	for c in mnemonics[i].split("/"):
		asm = [x.strip() for x in c.split(" ")]
		if asm[0] not in instructions:
			instructions[asm[0]] = {}
		mode = asm[1].replace("#%d","#").replace("(%d)","i").replace("(%f)","g").replace("%d","d")
		mode = mode.replace("%i","i").replace("%f","f").replace("%b","b")
		defn = "{0}={1:02x}".format(mode,i)
		if mode not in instructions[asm[0]]:
			instructions[asm[0]][mode] = defn
		else:
			assert instructions[asm[0]][mode] == defn,defn+" "+instructions[asm[0]][mode]+" "+asm[0]
k = [x for x in instructions.keys()]
k.sort()
info = {}
for opcode in k:
	keys = [x for x in instructions[opcode].keys()]
	info[opcode] = ":".join([instructions[opcode][x] for x in keys])
h = open("_cdc160_asminfo.txt","w")
h.write('"""\n')
for opcode in k:
	h.write("{0} {1}\n".format(opcode,info[opcode]))
h.write('"""\n')
h.close()