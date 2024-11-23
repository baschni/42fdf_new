#!python3
conv = ""
with open("matterhorn2.fdf", "r") as file:
    for line in file:
        new_line = []
        line = line.replace("\t", " ").strip()

        print(line)
        coords = line.split(" ")
        for coord in coords:
            if coord != "\n":
                new_line += [str(int(float(coord)))]
                #print(new_line)
        conv += " ".join(new_line) + "\n"


with open("cervin.fdf", "w") as file2:
    file2.write(conv)