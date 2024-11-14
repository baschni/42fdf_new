# Class to handle the actual printing



class SplitPrinter():

	def __init__(self, val):
		self.val = val

	def to_string(self):
		i = self.val
		while (i.dereference() != 0):
			print (i.dereference())
			i = i + 1

class VectorPrinter():

	def __init__(self, val):
		self.val = val

	def to_string(self):
		v = self.val
		vals = []
		p  = v["values"]
		#return(str(p.dereference()))
		for i in range(0, v["size"]):
			vals.append(float(p.dereference()))
			p = p + 1
			i = i + 1
		#return "".join(["{:>3.2f}"]*len(vals))
		return "".join(["{:>8.2f}"]*len(vals)).format(*vals)

class EdgePrinter():

	def __init__(self, val):
		self.val = val

	def to_string(self):
		v = self.val
		start = []
		end = []
		pstart  = v["start"]
		pend = v["end"]
		ppstart = pstart["values"]
		ppend = pend["values"]
		#return(str(p.dereference()))
		for i in range(0, pstart["size"]):
			start.append(float(ppstart.dereference()))
			end.append(float(ppend.dereference()))
			ppstart = ppstart + 1
			ppend = ppend + 1
			i = i + 1
		#return "".join(["{:>3.2f}"]*len(vals))
		return "".join(["{:>8.2f}"]*len(start)).format(*start) + "     -> " + "".join(["{:>8.2f}"]*len(end)).format(*end)

def output_row_list(row_list):
	output = ""
	while(row_list != 0):
		row = row_list["content"]
		output += output_row(row)
		row_list = row_list["next"]
	return output

def output_row(row):
	line = ""
	z = row["z"]
	c = row["color"]
	for i in range(0,row["width"]):
		line += str(z.dereference()) + ", 0x" + hex(c.dereference()) +  "\t"
		z += 1
		c += 1
	return line.strip() + "\n"

class RowListPrinter():

	def __init__(self, val):
		self.val = val

	def to_string(self):
		row = self.val["content"]
		return output_row(row)
	
class RowPrinter():

	def __init__(self, val):
		self.val = val

	def to_string(self):
		row = self.val
		return output_row(row)
	
class MapPrinter():

	def __init__(self, val):
		self.val = val

	def to_string(self):
		map = self.val
		out = []
		out.append("width: " + str(map["width"]) + ", height: " + str(map["height"]))
		out.append(output_row_list(map["first_row"]))
		return "\n".join(out)

# to use it, cast the list to (t_elist *) before printing
class EdgeListPrinter():

	def __init__(self, val):
		self.val = val

	def to_string(self):
		v = self.val
		start = []
		end = []
		content = v["content"].cast(gdb.lookup_type("t_edge").pointer)
		print (content)
		#print(v.dereference())

def register_printers(val):
	if str(val.type)=="char **":
		return SplitPrinter(val)
	if str(val.type)=="t_map *":
		return MapPrinter(val.dereference())
	if str(val.type)=="t_lrow *":
		return RowListPrinter(val.dereference())
	if str(val.type)=="t_row *":
		return RowPrinter(val.dereference())
	if str(val.type)=="t_vect *":
		return VectorPrinter(val)
	if str(val.type)=="t_edge *":
		return EdgePrinter(val)
	if str(val.type)=="t_elist *":
		return EdgeListPrinter(val)

#remove older versions of the Printer
for printer in gdb.pretty_printers:
	gdb.pretty_printers = [item for item in gdb.pretty_printers \
						if not ( type(item).__name__ == "function" and item.__name__ == "register_printers" )]

# add new Printer to pretty printers
gdb.pretty_printers.append(register_printers)