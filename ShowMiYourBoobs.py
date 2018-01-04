from vpython import *

scene=canvas(width=748, height=748)
f=open('output.txt','r')

pom=f.readline()[:-1].split(" ")
graniciVselennoy=float(pom[0])
N=int(pom[1])
print(pom)
Obyom=4/3*6.66E-9**3*pi

gray=color.gray(0.7)
d=graniciVselennoy
r=0.005
boxbottom=curve(color=gray)
boxbottom.append([vector(-d,-d,-d), vector(-d,-d,d), vector(d,-d,d), vector(d,-d,-d), vector(-d,-d,-d)])
boxtop=curve(color=gray)
boxtop.append([vector(-d,d,-d), vector(-d,d,d), vector(d,d,d), vector(d,d,-d), vector(-d,d,-d)])
vert1=curve(color=gray)
vert2=curve(color=gray)
vert3=curve(color=gray)
vert4=curve(color=gray)
vert1.append([vector(-d,-d,-d), vector(-d,d,-d)])
vert2.append([vector(-d,-d,d), vector(-d,d,d)])
vert3.append([vector(d,-d,d), vector(d,d,d)])
vert4.append([vector(d,-d,-d), vector(d,d,-d)])

a=[]
for i in range(N):
	a.append(f.readline()[:-1].split(' $ ')[:-1])
	for j in range(len(a[-1])):
		a[-1][j]=a[-1][j].split(" | ")
		for k in range(len(a[-1][j])):
			a[-1][j][k]=a[-1][j][k].split(" ")
			for n in range(len(a[-1][j][k])):
				a[-1][j][k][n]=float(a[-1][j][k][n])

d=[]
for x in a[0]:
	buf=vector(x[1][0], x[1][1], x[1][2])
	d.append([sphere(radius=6.66e-9, pos=vector(x[0][0], x[0][1], x[0][2]), color=vector(1, .5, 0)), arrow(pos=vector(x[0][0], x[0][1], x[0][2]), color=vector(1, 1, 0), axis=norm(buf)*10E-9)])

print("Obyomnaya Koncentraciya ", N*Obyom/graniciVselennoy**3)

A=0
print(len(a))
pom=d[0][0].pos
while True:
	for x in range(len(d)):
		d[x][0].pos=vector(a[A][x][0][0], a[A][x][0][1], a[A][x][0][2])
		d[x][1].pos=vector(a[A][x][0][0], a[A][x][0][1], a[A][x][0][2])
		buf=vector(a[A][x][1][0], a[A][x][1][1], a[A][x][1][2])
		d[x][1].axis=norm(buf)*10E-9

	A+=1
	if A>=len(a)-1: 
		A=0
		# print("pognali s nachala")
