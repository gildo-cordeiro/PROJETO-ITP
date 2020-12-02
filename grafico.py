import numpy as np
import matplotlib.pyplot as plot

content = [line.split(',') for line in open("saida.csv", "r").readlines()]

t = [float(line.pop()[:-1]) for line in content]
s = [float(line[0]) for line in content]
i = [float(line[1]) for line in content]
r = [float(line[2]) for line in content]

plot.figure(figsize=(6, 4))
plot.plot(s, color='#17a589', label='Sucetiveis')
plot.plot(i, color='red', label='Infectados')
plot.plot(r, color='#f4d03f', label='Recuperados')

plot.plot(s, 'g')
plot.plot(i, 'r')
plot.plot(r, 'y')

plot.grid(True)
plot.title('MODELO SIR')
plot.legend()
plot.show()
#plot.savefig("SIR.png")