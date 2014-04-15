#include <math.h>
#include <algorithm>
#include <stdio.h>
using namespace std;

int r, g, b;
float h, s, l, v;

void HSV_RGB(int H, float S, float V)
{
	float C  = V * S;
	int H1 = H/60;
	float X = C * (1 - abs(H1 % 2 - 1));
	float R1, G1, B1;
	switch (H1) {
		case 0 : R1 = C, G1 = X, B1 = 0; break;
		case 1 : R1 = X, G1 = C, B1 = 0; break;
		case 2 : R1 = 0, G1 = C, B1 = X; break;
		case 3 : R1 = 0, G1 = X, B1 = C; break;
		case 4 : R1 = X, G1 = 0, B1 = C; break;
		case 5 : R1 = C, G1 = 0, B1 = X; break;
		default : R1 = G1 = B1 = 0; break;
	}
	float m = V - C;
	int R = (int)(R1 + m), G = (int)(G1+m), B = (int)(B1+m);
	r = R, g = G, b = B;
	//printf("RGB %d %d %d\n", R, G, B);
}
void HSL_RGB(int H, float S, float L)
{
	float C = (1 - fabs(2*L - 1)) * S;
	int H1 = H/60;
	float X = C * (1 - abs(H1 % 2 - 1));
	float R1, G1, B1;
	switch (H1) {
		case 0 : R1 = C, G1 = X, B1 = 0; break;
		case 1 : R1 = X, G1 = C, B1 = 0; break;
		case 2 : R1 = 0, G1 = C, B1 = X; break;
		case 3 : R1 = 0, G1 = X, B1 = C; break;
		case 4 : R1 = X, G1 = 0, B1 = C; break;
		case 5 : R1 = C, G1 = 0, B1 = X; break;
		default : R1 = G1 = B1 = 0; break;
	}
	float m = L - 0.5 * C;
	int R = (int)(R1 + m), G = (int)(G1+m), B = (int)(B1 + m);
	r = R, g = G, b = B;
	//printf("RGB %d %d %d\n", R, G, B);
}
void RGB_HSL(int R, int G, int B)
{
	float H;
	int max_ = max(R, max(G, B)), min_ = min(R, min(G, B));
	if(max_ == min_) H = 0;
	else if(max_ == R && G >= B) H = 60 * ((G-B)*1.0/(max_-min_)) ;
	else if(max_ == R && G < B ) H = 60 * ((G-B)*1.0/(max_-min_)) + 360;
	else if(max_ == G)           H = 60 * ((B-R)*1.0/(max_-min_)) + 120;
	else if(max_ == B)		     H = 60 * ((R-G)*1.0/(max_-min_)) + 240;
	float L = 0.5 * (max_ + min_);
	float S ;
	if(L == 0 || max_ == min_) 	S = 0;
	else if(0 < L && L <= 0.5) 	S = (max_ - min_) * 1.0 / (2*L);
	else if(L > 0.5) 			S = (max_ - min_) * 1.0 / (2 - (2*L));

	h = H, s = S*100, l = L*100;
}
void RGB_HSV(int R_, int G_, int B_)
{
	float H;
	float R = (R_ * 1.0)/256;
	float G = (R_ * 1.0)/256;
	float B = (R_ * 1.0)/256;

	float max_ = max(R, max(G, B)), min_ = min(R, min(G, B));
	if(equal(max_ , min_)) H = 0;
	else if(equal(max_ , R) && G >= B) H = 60 * ((G-B)*1.0/(max_-min_)) ;
	else if(equal(max_ , R) && G < B ) H = 60 * ((G-B)*1.0/(max_-min_)) + 360;
	else if(max_ == G)           H = 60 * ((B-R)*1.0/(max_-min_)) + 120;
	else if(max_ == B)		     H = 60 * ((R-G)*1.0/(max_-min_)) + 240;
	float S ;
	if(max_ == 0) S = 0;
	else		  S = 1 - min_*1.0/(max_*1.0);
	float V = (float)max_;

	h = H, s = S*100, v = V*100;
	//printf("HSV %d %d\% %d\%\n", (int)H, (int)(S * 100), (int)(V*100));
}
void HSV_HSL(int H, float S, float V)
{
	HSV_RGB(H, S, V);
	RGB_HSL(r, g, b);
}
void HSL_HSV(int H, float S, float L)
{
	HSL_RGB(H, S, L);
	RGB_HSV(r, g, b);
}
int main()
{
	int R, G, B, H, S, L, V;
	char A[100], s2[100];
	while(scanf("%s", A) != EOF) {
		scanf("%s", s2);
		if(s2[0] == 'R') {
			scanf("%d%d%d", &R, &G, &B);
			if(A[2] == 'L') {
				RGB_HSL(R,G,B);
				printf("HSL %d %d%% %d%%\n", (int)h, (int)s, (int)l);
			} else if(A[2] == 'V') {
				RGB_HSV(R, G, B);
				printf("HSV %d %d%% %d%%\n", (int)h, (int)s, (int)v);
			} else {
				printf("RGB %d %d %d\n", R, G, B);
			}
		} else if(s2[2] == 'L') {
			scanf("%d%d%%%d%%", &H, &S, &L);
			if(A[0] == 'R') {
				HSL_RGB(H, S*0.01, L*0.01);
				printf("RGB %d %d %d\n", r, g, b);
			} else if(A[2] == 'V') {
				HSL_HSV(H, S*0.01, L*0.01);
				printf("HSV %d %d%% %d%%\n", (int)h ,(int)s, (int)v);
			}
			else printf("HSL %d %d%% %d%%\n", H, S, L);
		} else if(s2[2] == 'V') {
			scanf("%d%d%%%d%%", &H, &S, &V);
			if(A[0] == 'R') {
				HSV_RGB(H, S*0.01, V*0.01);
 				printf("RGB %d %d %d\n", r, g, b);
			} else if(A[2] == 'L') {
				HSV_HSL(H, S*0.01, V*0.01);
				printf("HSL %d %d%% %d%%\n", (int)h, (int)s, (int)l);
			} else printf("HSV %d %d%% %d%%\n", H, S, V);
		}
	}
	return 0;
}
