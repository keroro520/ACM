# 超时了

# 看正解吧

p, x = map( int, input().split() )
tt = (10**p)
a = 1
while a < 10 and (( (a * tt * x - a*x)  % (10*x-1) != 0 )  or (  ((a * tt * x - a*x)  // (10*x-1)) // x < tt//10)) :
	a += 1
if a >= 10 :
	print("Impossible")
else :
	print(  (a * tt * x - a*x)  // (10*x-1)  // x)
