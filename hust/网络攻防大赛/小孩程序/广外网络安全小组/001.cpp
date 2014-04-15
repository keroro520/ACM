#include<iostream>
#include<string>
#include<math.h>
#include <stdio.h>
using namespace std;
char bit[3][5]={"","001","010"};
int findbit(int num){
	for(int i=1;i<=6;i++){
		int temp=pow(2,i);
		int temp1=pow(2,i-1);
		if(temp1<=num&&num<=temp)
			return i;
	}
}
int changed(const char *temp,int num){
	int result=0;
	for(int i=0;i<num;i++){
		int cifang=num-i;
		int bit=temp[i]-'0';
		result=result+bit*pow(2,cifang-1);
	}
	return result;
}

int main(){
  int i;
  freopen("1_out.txt","w",stdout);
	std::string data[65];
	const char *data2[65];
	std::string datarow[42];
	std::string datacol[42];
	int num=1;
	int m;int n;int m2;int n2;
	cin>>m>>n;
	m2=pow(2,m);n2=pow(2,n);
	for(int i=1;i<=2;i++){
		std::string x="";
		if(i==1)
			x=x+'0';
		else
			x=x+'1';
		for(int j=1;j<=2;j++){
			std::string temp2="";
			if(i==1)
			   temp2=x+bit[1][j];
		    else
			   temp2=x+bit[2][j];
		    for(int k=1;k<=2;k++){
			  std::string temp3="";
			  if(j==1)
			     temp3=temp2+bit[1][k];
		      else
			     temp3=temp2+bit[2][k];
			   for(int l=1;l<=2;l++){
				   std::string temp4="";
				   if(k==1)
			          temp4=temp3+bit[1][l];
		           else
			          temp4=temp3+bit[2][l];
				   for(int h=1;h<=2;h++){
					   std::string temp5="";
					   if(l==1)
			             temp5=temp4+bit[1][h];
	               	   else
			             temp5=temp4+bit[2][h];
						for(int g=1;g<=2;g++){
							std::string temp6="";
						    if(h==1)
			                  temp6=temp5+bit[1][g];
		                    else
			                  temp6=temp5+bit[2][g];
							data[num]=temp6;

							//cout<<data[num]<<endl;
							num++;
							//int a;cin>>a;
						}
				   }
			   }
		   }
		}
	}
	for(int g=1;g<=40;g++){
		data2[g]=data[g].c_str();
	}
	int bitnumrow=findbit(m2);
    int bitnumcol=findbit(n2);
	for(i=1;i<=m2;i++){
		std::string temp;
		temp=data[i].substr(6-bitnumrow,bitnumrow);
		datarow[i]=temp;
	}
	for(i=1;i<=n2;i++){
		std::string temp;
		temp=data[i].substr(6-bitnumcol,bitnumcol);
		datacol[i]=temp;
	}
	const char *result[1650];int resultint[1650];
	int sumnum=1;
	for(i=1;i<=n2;i++){
		cout<<endl;
		for(int j=1;j<=m2;j++){
			std::string temp=(datacol[i]+datarow[j]);
			result[sumnum]=temp.c_str();
			//cout<<result[sumnum]<<endl;
			resultint[sumnum]=changed(result[sumnum],bitnumrow+bitnumcol);
			cout<<resultint[sumnum]<<"\t";
		}
		//cout<<datacol[i]<<endl;
	}
}
