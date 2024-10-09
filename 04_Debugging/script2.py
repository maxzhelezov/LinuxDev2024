gdb.execute("start -100 100 3 >/dev/null")

gdb.execute(f"watch I.count")
brk = gdb.breakpoints()[0]
brk.silent=True


conv = {}
i = 0
while True:
    gdb.execute("c")
    if len(gdb.breakpoints()) == 0:
        break
    
    if 27 < i and i < 36:
        gdb.execute("up")
        for var in ["I.start", "I.stop", "I.step", "I.count"]:
            conv[var] = var + " = " + str(int(gdb.parse_and_eval(var)))
        print("@@@" + ", ".join(conv.values()))
    
    i += 1
