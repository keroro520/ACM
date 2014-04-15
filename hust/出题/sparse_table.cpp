
{A}，若干询问(l.r)，回答区间[l,r]里最大和次大元素的和/乘积...
//由cf 172 D 想到

思路：sparse table
	  max = st[l,r], sec = MAX{ st[l,max-1], st[max+1,r] }
