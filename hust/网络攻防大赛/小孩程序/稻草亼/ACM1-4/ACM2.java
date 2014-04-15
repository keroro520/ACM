import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

/*
 小球排列
现有R个红球，B个蓝球，G个绿球。我们来把这所有的小球排成一排。我们定义“浩神排列”是满足条件“每连续的3个小球颜色都不一样”的排列。问有多少种浩神排列。
两种排列A和B，只要有color(Ai) != color(Bi), (1 <= i <= n)，我们就说A和B排列不一样。

input : 一个整数T(T < 100)，表示有多少组测试数据
		接下来T行，每行3个整数R, G, B (1 <= R+G+B <= 10^6)，代表红球、绿球、蓝球的个数
output :
		T行，每行一个整数ans，代表不同排列的方案数

sample input :
	4
	5 5 5
	3 3 2 
	0 0 1
	3 4 5
sample output :
	6
	2
	1
	0
 
*/

/*
 R3G3B2
 RGBRGBRG
 GRBGRBGR
 1.当小球数目一致的时候，就是用3个颜色的小球做排列组合 最多6种
 2.当小球数目不一致的时候
 	1.当3种小球数目都不一致，则为0种，因为总会有颜色一样的出现。
 	2.当有两种小球个数一样，并且另外一种至少一个，则就是2种颜色做排列组合，只有2种。
 	3.当只有一个或两个颜色不一样小球时，只有1种
 */
public class ACM2 {
	public static void main(String[] args) throws IOException {
		int T;
		String tmpStr = null;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		if(T>100||T<0){
			System.out.println("T不正确");
			System.exit(0);
		}	
		int[] R = new int[T];
		int[] G = new int[T];
		int[] B = new int[T];
		for (int i = 0; i < T; i++) {
			tmpStr = br.readLine();
			String[] tmp = tmpStr.split(" ");
			R[i] = Integer.parseInt(tmp[0]);
			G[i] = Integer.parseInt(tmp[1]);
			B[i] = Integer.parseInt(tmp[2]);
		}
		for (int i = 0; i < T; i++) {
			// System.out.print(R[i]+","+G[i]+","+B[i]+"=");
			if (R[i] == G[i] && G[i] == B[i])
				System.out.println("6");
			else {
				if ((R[i] == 1 && G[i] == 0 && B[i] == 0)
						|| (R[i] == 0 && G[i] == 1 && B[i] == 0)
						|| (R[i] == 0 && G[i] == 0 && B[i] == 1)) {
					System.out.println("1");
				} else if ((R[i] == 1 && G[i] == 1 && B[i] == 0)
						|| (R[i] == 1 && G[i] == 0 && B[i] == 1)
						|| (R[i] == 0 && G[i] == 1 && B[i] == 1)) {
					System.out.println("1");
				} else if ((R[i] == G[i] && R[i] - B[i] == 1)
						|| (R[i] == B[i] && R[i] - G[i] == 1)
						|| (B[i] == G[i] && B[i] - R[i] == 1)) {
					System.out.println("2");
				} else
					System.out.println("0");
			}
		}
	}
}
