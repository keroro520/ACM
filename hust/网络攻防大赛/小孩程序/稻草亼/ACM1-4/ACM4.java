import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

/*
 在YY世界里，存在着这么一个丧尸班级...该班有N个男生，为了鼓励大家好好学习，学校给这N个男生各配备了左右两个女同桌。
 为了方便喜欢YY的男同学统计出“最美女神”排行榜，我们给这2*N个女生分别打了不同的漂亮指数，
 我们记i号男同学的左右女同桌的漂亮指数为Li, Ri。
现在问题来了，对于i号男生，如果他发现存在某个男生j，有Lj < Li 但Ri < Rj，
他就会心里纠结...问会有多少男生心里纠结...?

输入：第一行一个整数N (1 <= N <= 1600).
	  第二行到第N+1行每行两个整数Li, Ri (1 <= Li,Ri <= 2000000000)，数据保证不会有每个女生的漂亮指数不同.

输出：一行：会纠结的男生数目

sample input :
	5
	0 10
	2 9
	3 8
	1 15
	6 11
sample output :
	3
 */
public class ACM4 {
	public static void main(String[] args) throws NumberFormatException, IOException {
		int N;
		int jiujieman=0;
		String tmpStr=null;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		if(N>1600||N<0){
			System.out.println("N不正确");
			System.exit(0);
		}
		int[] L = new int[N];
		int[] R = new int[N];
		for (int i = 0; i < N; i++) {
			tmpStr = br.readLine();
			String[] tmp = tmpStr.split(" ");
			L[i] = Integer.parseInt(tmp[0]);
			R[i] = Integer.parseInt(tmp[1]);
		}
		//开始计算
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(L[j]<L[i]&&R[i]<R[j]){
					jiujieman++;
					break;
				}			
			}
		}
		System.out.println(jiujieman);
	}
}
