import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/*
无限小数
给你一个N和一个K，一个整数数列D[0..N-1]，其中0 <= D[i] <= 9
让我们来看看这么样一个实数数列{A}，Ai的整数部分为0，小数部分是无限的十进制数D[(i + 0 * k) mod N], D[(i + 2*K) mod N]等等下去。
举个例子：N = 3, K = 2, D = {1, 9, 4}
A1 = 0.1491491491... 
A2 = 0.9149149149... 
A3 = 0.4914914914... 

找出最大的Ai，并且输出Ai的前N位小数

input : 第一行2个整数N, K(1 <= N <= 150000; 0 <= K <= 10^9)
		第二行有N个正整数Di, 0 <= Di <= 9
output : 根据上述要求输出N个数字

Input
Test #1 
3 2 
194 

Test #2 
2 1 
57 

Test #3 
4 1 
0000

Output
Test #1 
914 

Test #2 
75 

Test #3 
0000

 */
public class ACM3 {
	public static void main(String[] args) throws IOException {
		int N;
		double K;
		String tmpD;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String tmpStr = br.readLine();
		String[] tmp = tmpStr.split(" ");
		N = Integer.parseInt(tmp[0]);
		K = Double.parseDouble(tmp[1]);
		if (N < 1 || N > 150000 || K < 0 || K > Math.pow(10, 9)) {
			System.out.println("N,K不正确");
			System.exit(0);
		}
		tmpD = br.readLine();
		int D[] = new int[tmpD.length()];
		for (int i = 0; i < tmpD.length(); i++) {
			D[i] = tmpD.charAt(i) - 48;
			if (D[i] < 0 || D[i] > 9)
				System.exit(0);
		}
		// 开始计算
		int MAX = 0;
		int tmpA[][] = new int[N][N];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int t = (int) ((i + j * K) % N);
				tmpA[i][j] = D[t];
			}
			// 比大小
			for (int j = 0; j < N; j++) {
				if (tmpA[MAX][j] < tmpA[i][j])
					MAX = i;
				if (tmpA[MAX][j] > tmpA[i][j])
					break;
			}
		}
		for (int i = 0; i < tmpD.length(); i++) {
			System.out.print(tmpA[MAX][i]);
		}
		
	}
}
