gdb.execute("start 1 12 >/dev/null")

gdb.execute(f"watch I.count")
wp = gdb.breakpoints()[0].number
gdb.breakpoints()[0].silent=True
gdb.execute(f"condition {wp} I.count % 5 == 0")

conv = {}
while True:
    gdb.execute("c")
    if len(gdb.breakpoints()) == 0:
        break
    
    gdb.execute("up")
    for var in ["I.start", "I.stop", "I.step", "I.count"]:
        conv[var] = var + " = " + str(int(gdb.parse_and_eval(var)))
    
    print("@@@" + ", ".join(conv.values()))
