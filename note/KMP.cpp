/*
KMP的next求循环节：http://blog.sina.com.cn/s/blog_7981299401012xl0.html
	int len = s.length();
	int rep = len - next[len];
	int times = (len%rep == 0 ? len/rep : 1);
*/

//next[] : 匹配失败时回跳的位置
void fail(string &s)
{
    int len = s.length();
    int i = 0, j = -1;
    next[0] = -1;
    while(i < len) {
        if(j == -1 || s[i] == s[j]) {
            i++, j++;
            next[i] = j;
        } else j = next[j];
    }
}

//PMT[] : 部分匹配值 
void fail(string s)
{
    int len = s.length();
    int j = 0;
    PMT[0] = 0;
    for(int i = 1; i < len; i++) {
        while(j > 0 && s[i] != s[j]) {
            j = PMT[j-1];
        }
        if(s[i] == s[j]) j ++;
        PMT[i] = j;
    }
}
int KMP(string s1, string s2)		//求s2在s1出线的次数（重叠的算两次）
{
	int sum = 0, len1 = s1.length(), len2 = s2.length();
	fail(s2);
	int i = 0, j = 0;
	while(i < len1) {
		while(i < len1 && j < len2) {
			if(s1[i] != s2[j]) j -= PMT[j];
			else j++;
			i++;
		}
		if(len2 == j) {
			sum++;
			j = 0;
			i = i - len2 + 1;
		}
	}
	return sum;
}
