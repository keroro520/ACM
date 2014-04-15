

void get_prime()
{
	
	for(int i = 2, oo = sqrt(1000000000); i <= oo; i++) 
		if(!boo[i]) {
			int j = i+i;
			while(j <= oo) boo[j] = true, j += i;
		}
}
int main()
{
	get_prime();
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		
}
