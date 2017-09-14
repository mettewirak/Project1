import matplotlib.pyplot as plt

filnames=['build-Project1-Desktop-Debug/resultat10.txt','build-Project1-Desktop-Debug/resultat100.txt','build-Project1-Desktop-Debug/resultat1000.txt','build-Project1-Desktop-Debug/andre_tall_10_6.txt']

#'build-Project1-Desktop-Debug/resultat10.txt','build-Project1-Desktop-Debug/resultat100.txt','build-Project1-Desktop-Debug/resultat1000.txt','build-Project1-Desktop-Debug/andre_tall_10_6.txt'

def leser(filename):
	with open(filename) as f:
	    lines = f.readlines()
	    x = [line.split()[0] for line in lines]
	    error = [line.split()[2] for line in lines]
	    v = [line.split()[4] for line in lines]
	    u = [line.split()[6] for line in lines]
	for i in range(len(error)):
		if error[i]=="inf":
			error[i]=0
	return x, error,v,u
x_10,e_10,v_10,u_10=leser(filnames[0])
x_100,e_100,v_100,u_100=leser(filnames[1])
x_1000,e_1000,v_1000,u_1000=leser(filnames[2])



plt.plot(x_10,v_10, 'b', label= 'n=10')
plt.plot(x_100,v_100, 'g', label= 'n=100')
plt.plot(x_1000,v_1000, 'c', label= 'n=1000')
plt.plot(x_1000,u_1000, 'r', label= "anlalytic")

plt.plot(x_10,e_10, '+b', label= 'error, n=10')
plt.plot(x_100,e_100, '+g', label= 'error, n=100')
plt.plot(x_1000,e_1000, '+c', label= 'error, n=1000')

plt.xlabel('x',fontsize=20)
plt.ylabel('v(x)',fontsize=20)
plt.title(" v(x), and rellative error using the general algorithm for 3 different n's",fontsize=20)
plt.legend(loc=0)


plt.show()

"""
x10,error10,v10,u10=leser(filnames[0])
x100,error100,v100,u100=leser(filnames[1])
x1000,error1000,v1000,u1000=leser(filnames[2])


plt.plot(x10,u10,'g', label="n=10")
plt.plot(x100,u100,'b', label="n=100")
plt.plot(x1000,u1000,'m', label="n=1000")
plt.plot(x1000, v1000,'r')
plt.legend(loc='upper right')

plt.show()
plt.plot(x10,error10,'g')
plt.plot(x100,error100,'b')
plt.plot(x1000,error1000,'m')
plt.show()
"""

