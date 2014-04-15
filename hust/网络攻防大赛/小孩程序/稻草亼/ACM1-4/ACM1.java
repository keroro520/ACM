import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Scanner;

/**
现在我们来把0到2^(n+m)-1 这2^(n+m)个数字放到2^n * 2^m 矩阵里面。
唯一条件是矩阵里面两个相邻的格子里的数字的二进制形式必须有且仅有一位不相同。
我们定义“相邻格子”为有公共边的格子。该矩阵是环状的，
即最左边的格子和最右边的格子（当然，同一行）是相邻的，最下边的格子和最顶的格子（同一列）是相邻的。
input :
	两个整数n, m (0 < n,m;  n+m <= 20)
output :
	输出一个满足条件的2^n * 2^m矩阵
sample input :
	1 1
sample output :
	0 2 
	1 3

*/

/*
//循环格雷码
000 001 011 010 110 111 101 100
001 011 010 110 111 101 100 000
011 010 110 111 101 100 000 001
010 110 111 101 100 000 001 011
110 111 101 100 000 001 011 010
111 101 100 000 001 011 010 110
101 100 000 001 011 010 110 111
100 000 001 011 010 110 111 101
 */
public class ACM1 {
	public void grey(int n) {
		if (n <= 0)
			return;
		boolean[] codes = new boolean[n];
		grey(codes, 0);
	}

	private void out(boolean[] codes) {
		StringBuilder sb = new StringBuilder(codes.length);
		for (boolean b : codes)
			if (b)
				sb.append(1);
			else
				sb.append(0);
		tmpAl.add(sb.toString());
	}

	private void grey(boolean[] codes, int w) {
		if (w == codes.length - 1) {
			out(codes);
			codes[w] = !codes[w];
			out(codes);
		} else {
			grey(codes, w + 1);
			codes[w] = !codes[w];
			grey(codes, w + 1);
		}
	}

	static ArrayList<String> tmpAl = new ArrayList<String>();

	public static void main(String[] args) throws IOException {
		int m,n;
		ACM1 acm1 = new ACM1();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String tmpStr = br.readLine();
		String[] tmp = tmpStr.split(" ");
		m = Integer.parseInt(tmp[0]);
		n = Integer.parseInt(tmp[1]);
		if(m+n>20){
			System.out.println("m,n不正确");
			System.exit(0);
		}
		//System.out.println("m=" + m + ",n=" + n);
		int ml = (int) Math.pow(2, m);
		int nl = (int) Math.pow(2, n);
		//System.out.println("ml=" + ml + ",nl=" + nl);
		String[][] mat = new String[ml][nl];
		// 得到第一行格雷码
		acm1.grey(m);
		// 矩阵第一行写入
		for (int j = 0; j < nl; j++) {
			mat[0][j] = tmpAl.get(j);
		}
		// 清空集合
		tmpAl.clear();
		// 填写数据
		for (int i = 1; i < ml; i++) {
			for (int j = 0; j < nl; j++) {
				mat[i][j] = mat[i - 1][(j + 1) % nl];
			}
		}
		// 输出数据
		for (int i = 0; i < ml; i++) {
			for (int j = 0; j < nl; j++) {
				System.out.print(mat[i][j] + " ");
			}
			System.out.println();
		}
	}
}
