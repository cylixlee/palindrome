#include <stdio.h>
#include <string.h>

int palindrome(const char *s, int begin, int end) {
    int n = end - begin;
    int left=0, right = n-1;
    while(left < right){
        if(s[begin + left] != s[begin + right]){
            return 0;
        }
        ++left;
        --right;
    }
    return 1;
}

// 当字符串首尾相同时 如 `aba`
// solution("aba") = <两边不改中间改> solution("b") +
//                   <两边改中间不改>
//                      (1) 开头插入末尾字符 --> 现有字符串，除去尾部后是否为回文串
//                      (2) 末尾插入开头字符 --> 现有字符串，除去头部后是否为回文串
// *什么是两边，什么是中间：定义某字符串的开头位置（0）和末尾位置（n）为“两边”，剩余所有位置为“中间”。
//                      如`aba`中，在两边位置分别插入C，可得到`Caba`或者`abaC`字符串。
// *位置完备性：如`aba`，剩余的“中间位置”分别为`aCba`和`abCa`。这两个中间位置对于去掉首尾的子串`b`来说
//            恰好是“两边”位置，从而能将大问题转化为规模相等的小问题，进行递推。


// 当字符串首尾不相同时 如 `abc`
// solution("abc") = <两边不改中间改> 0 +
//                   <两边改中间不改>
//                      (1) 开头插入末尾字符 --> 现有字符串，除去尾部后是否为回文串
//                      (2) 末尾插入开头字符 --> 现有字符串，除去头部后是否为回文串
// *为什么两边不改中间改为0：因为即使在任意中间位置插入某个字符，由于首尾字符的不相等，新字符串一定不为
//                       回文串。

// 递推的结束条件
// solution("") --> 1 * 1 当去掉任意数量的首尾字符对后，余下的子串为空，说明原字符串为偶数字符串，
//                        在中间位置插入任意一个字母即可。
// solution("n") --> 2 * 1 当余下的子串只剩单字符时，说明原字符串为奇数字符串，在该字符左边或右边插入
//                         相同字符才能保持回文串。

int solution(const char *s, int begin, int end) {
    if (begin == end) {
        return 1;
    }
    if (begin + 1 == end) {
        return 2;
    }

    if (s[begin] == s[end - 1]) {
        return solution(s, begin + 1, end - 1)
               + palindrome(s, begin, end - 1)
               + palindrome(s, begin + 1, end);
    } else {
        return palindrome(s, begin, end - 1) + palindrome(s, begin + 1, end);
    }
}

//char buffer[1024];
//
//int main() {
//    while (scanf("%s", buffer) != EOF) {
//        int n = strlen(buffer);
//        printf("%d\n", solution(buffer, 0, n));
//    }
//    return 0;
//}