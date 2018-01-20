from vpython import *
from PIL import ImageGrab, ImageDraw, ImageFont
import time, os

spisokFiles=os.listdir("D:\\pomoina")
ind=spisokFiles.index('Boobles.txt')
f=open('D:\\pomoina\\'+spisokFiles.pop(ind),'r')
pom=f.readline()[:-1].split(" ")
f.close()

scene=canvas(width=748, height=748)

graniciVselennoy=float(pom[0])
N=int(int(pom[1])/1)
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

B=[]
for x in spisokFiles:
	B.append(open('D:\\pomoina\\'+x,'r'))
print("--- --- ---")

a=[[]]
y=0
while True:
	pom=B[y].readline()[:-1]
	pom=B[y].readline()[:-1]
	if pom=='': break
	pom=pom.split(' | ')
	pom[0]=pom[0].split(' ')
	pom[1]=pom[1].split(' ')
	for x in range(len(pom[0])):
		pom[0][x]=float(pom[0][x])
		pom[1][x]=float(pom[1][x])

	a[-1].append(pom)
	y+=1
	if y>len(B)-1: 
		y=0
		a.append([])

print("opochki. teper narisuem shariki")

d=[]
for x in a[0]:
	buf=vector(x[1][0], x[1][1], x[1][2])
	d.append([sphere(radius=6.66e-9, pos=vector(x[0][0], x[0][1], x[0][2]), color=vector(1, .5, 0)), arrow(pos=vector(x[0][0], x[0][1], x[0][2]), color=vector(1, 1, 0), axis=norm(buf)*10E-9)])

print("Obyomnaya Koncentraciya ", N*Obyom/graniciVselennoy**3)

A=0
print(len(a), N)
time.sleep(2)#input()
while True:
	pom=d[0][1].axis
	if A%10==0: print("\t\t", A)
	for x in range(len(d)):
		d[x][0].pos=vector(a[A][x][0][0], a[A][x][0][1], a[A][x][0][2])
		d[x][1].pos=vector(a[A][x][0][0], a[A][x][0][1], a[A][x][0][2])
		buf=vector(a[A][x][1][0], a[A][x][1][1], a[A][x][1][2])
		d[x][1].axis=norm(buf)*10E-9

	A+=1
	if A%30==0:#
		Freame=ImageGrab.grab([10,10,748,748])#grab([0,0,300,300])
		puti='D:/filma/hot-%07d-.tiff'%(A//30)
		Freame.save(puti,'TIFF')
	if A>=N-3: 
		A=0
		input("pognali s nachala")