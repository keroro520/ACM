C. 社团吞并

某段时间社会上流行企业收购，而南邮也受此社会风气影响，各个社团到处想着吞并其它社团，以实现扩张势力范围且梦想着统治南邮社团，于是，凶残的“社团吞并风波”就是这样开始了...

已知每个社团有两个个属性：势力，标签。 势力代表一个社团的强大能力，任何一个社团只能吞并势力比它小的社团。标签代表该社团是属于什么类型的，一个社团可以有多个标签，如传媒科协有“技术类”，“艺术类”等标签，任意两个社团只有当他们有某一个相同的标签时才能发生吞并。

下面C天每天有一次谈判(A,B)，表示编号为A的社团和社团B谈判，谈判规则如下：
    (1)若A,B某一方满足把另一方吞并的所有条件，强大的一方s就会毫不犹豫地把弱的一方x吞并掉，并且把x吞并过的社团也全部纳入自己的麾下。
    (2)在满足(1)的条件下，若弱的一方x原本属于某个社团y，则此时x会叛变y，让自己以及自己麾下的社团全都投靠社s。
如(3, 4)表示社团编号为3 和 4谈判，若社4的势力比社3强，且他们有某一个相同的标签，则现在社3以及社3吞并的社团全部都属于社4。
之后若有(2, 3)谈判，则社团3还是以原来的势力值和标签做条件，并且若社2被3吞并了，则社2也会属于社4.
再之后若有(3, 5)谈判，社5能吞并社3，则社3会背叛社4，带领自己的小社团们投靠社5，但它的原boss社4依然不变。

问在“南邮社团吞并风波”结束后每个社团的总boss的编号，也就是最终属于那个社团。

Input :
    三个整数n,m,C(n <= MAXN, m <= 60). n表南邮的社团数，分别用编号1..n来表示（最开始时社i属于社i，这个叙述有点绰，就是自己属于自己）。m表示总的标签个数，用1~m编号。
    接下来n行，每一行首先两个整数pi, li, 分别表编号为i的社团势力值和标签个数。之后有li个整数b1,b2,...,bli(1 <= bk <= m, 1 <= k <= li)表社团i所属的标签。
    接下来C行，第i行表第i天的一个谈判Ai,Bi(1 <= Ai,Bi <= n)。

Output :
    一行有n个数，第i个数表社团i在风波结束后属于的社团编号。

Sample Input :
    
