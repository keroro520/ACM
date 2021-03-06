E. Keroro侵略地球

Keroro来侵略地球之前，曾跟Giroro伍长打赌：“我一个人灭掉整个地球给你看！”.
于是Keroro同学真的自己一个人来到地球开始他的侵略行动了。从K隆星出发之前，Keroro从Kururu曹长那儿拿了若干台左手武器{Li}和若干台右手武器{Ri}，Keroro需要从{Li}里选一台左手武器，从{Ri}里选一台右手武器，用来组合成可用的恐怖武器。
左右手武器组合的规则很简单，假设从{Li}选出来攻击力为p的武器，从{Ri}选出来攻击力为q的武器，组合起来的攻击力就是p XOR q.

Keroro想知道，他能组合成的最强武器攻击力为多少？

Hint：必须左右手武器都选出来一个，才能组合成可用武器

      XOR表二进制里的“异或”操作，pascal语言里是"xor", C/C++/Java里是"^".


Input :
    第一行两个整数n, m (1 <= n,m <= 100000), 表有n件左手武器，m件右手武器。
    第二行n个正整数{L},li表第i件左手武器的攻击力，0 <= li <= 10^12
    第三行m个正整数{R},ri表第i件右手武器的攻击力，0 <= ri <= 10^12
Output :
    最强组合武器的最大值。
