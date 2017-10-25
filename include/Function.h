#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <math.h>
#include <stack>
#include <set>


using namespace std;
 //* Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Function{
public:

//1. Two Sum
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> myMap;//key:the value of vector;value:the index of vector
        for(int i = 0; i != nums.size(); ++i){
            auto iter = myMap.find(target - nums[i]);
            if(iter == myMap.end()){
                //add the element which was not found in myMap;
                myMap[nums[i]] = i;
            }
            else{
                //return the two right element;
                return {iter->second, i};
            }
        }
    }

//2. Add Two Numbers
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry_bit = 0;
        ListNode l(0), *p = &l;
        while(l1 || l2 || carry_bit){ //�ڵ�ǿջ���Ҫ��λ
            int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry_bit;
            if(sum >= 10){
                carry_bit = 1;
                sum -= 10;
            }
            else carry_bit = 0;
            p->next = new ListNode(sum);
            p = p->next;
            l1 = l1 ? l1->next : l1;
            l2 = l2 ? l2->next : l2;
        }
        return l.next;
    }

//3. Longest Substring Without Repeating Characters
    int lengthOfLongestSubstring(string s){
        if(s.size() == 0) return 0;
        //i��j�ֱ��ʾ��λ��ĩλ��s[i,j] is substring without repeating characters
        int maxLen = 0, i = 0;
        vector<int> vec; //�洢��ͬ��substring�ĳ���
        map<char, int> myMap;
        for(int j = 0; j != s.size(); ++j){
            if(myMap.count(s[j]) && myMap.find(s[j])->second >= i){
                //�����Χ[i,j)���ڸ��ַ���������Ϊk
                i = myMap.find(s[j])->second + 1; //����iΪk+1
            }
            maxLen = max(maxLen, j + 1 - i); //����maxLen
            myMap[s[j]] = j;//�����Ƿ���ڣ���Ҫ����map
        }
        return maxLen;
    }

//4. Median of Two Sorted Arrays
    double findKth(vector<int>::iterator iter1, int m, vector<int>::iterator iter2, int n, int k){
        //function findKth �ҵ���kС���� ���Ӷ�O(logk)
        //m=nums1.size(), n = nums2.size()���ٶ�m<=n
        if(m > n) return findKth(iter2, n, iter1, m, k);
        if(m == 0) return *(iter2+k-1); //num1Ϊ��ʱ
        if(k == 1) return min(*iter1, *iter2); //k=1ʱ
        int pa = min(k/2, m), pb = k - pa;
        if(*(iter1+pa-1) < *(iter2+pb-1))
            //nums1ǰpa��Ԫ�ر�ȻС�ڵ�kС��Ԫ�أ�����ֱ�Ӻ���
            return findKth(iter1+pa, m-pa, iter2, n, k-pa);
        else if(*(iter1+pa-1) > *(iter2+pb-1))
            //nums2ǰpb��Ԫ�ر�ȻС�ڵ�kС��Ԫ�أ�����ֱ�Ӻ���
            return findKth(iter1, m,iter2+pb, n-pb ,k-pb);
        else
            //ֱ���ҵ���kС��Ԫ��
            return *(iter1+pa-1);
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        /*
        //STL�е�merge����,����ʱ��
        int length = nums1.size() + nums2.size();
        vector<int> merge_nums(length);
        merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), merge_nums.begin());
        if(length % 2)
            return merge_nums[length / 2];
        else
            return (merge_nums[length/2]+merge_nums[length/2-1])/2.0;
        */
        //findKth
        vector<int>::iterator iter1 = nums1.begin(), iter2= nums2.begin();
        int len1 = nums1.size(), len2 = nums2.size();
        int length = len1 + len2;
        if(length % 2)
            return findKth(iter1, len1, iter2, len2, length/2+1);
        else
            return (findKth(iter1, len1, iter2, len2, length/2+1)
                    +findKth(iter1, len1, iter2, len2, length/2))/2.0;
    }

//5. Longest Palindromic Substring
    string longestPalindrome(string s) {
        //ʱ�临�Ӷ�O(n^2) �ռ临�Ӷ�O(n^2)
        int len = s.size();
        if(len <= 1) return s;
        else{
            int dp[len][len]; //�洢״̬
            for(int i = 0; i < len; ++i){
                for(int j = 0; j < len; ++j){
                    dp[i][j] = 0;
                }
            }
            int Max = 0, startIndex = 0, endIndex = 0; //�洢��󳤶Ⱥ��±�
            /*״̬ʾ��ͼ
               1 0 0 0 0 0 0 ...
                 1 0 0 0 0 0 ...
                   1 2 0 0 0 ...
                     1 0 0 0 ...
                       1 2 0 ...
                         1 0 ...
                           ...
                           ...
            */
            for(int i = 0; i < len; ++i){
                dp[i][i] = 1; //�Խ���һ��Ϊ1
                if(i-1 >= 0 && s[i] == s[i-1]) dp[i-1][i] = 2; //����Ϊ2��0
            }
            for(int k = 2; k < len; ++k){ //���ŵ������Խ��߿�ʼ��б�򣩱���
                for(int i = 0; i < len; ++i){
                    int j = i + k;
                    if(s[i] == s[j] && j < len && dp[i+1][j-1]){
                        dp[i][j] = dp[i+1][j-1] + 2;//״̬ת�Ʒ���
                    }
                }
            }
            for(int i = 0; i < len; ++i){
                for(int j = i; j < len; ++j){
                    if(dp[i][j] >= Max){ //���³��Ⱥ��±�
                        startIndex = i;
                        endIndex = j;
                        Max = dp[i][j];
                    }
                }
            }
            return s.substr(startIndex, endIndex - startIndex + 1);
        }
    }

//6. ZigZag Conversion
    string convert(string s, int numRows){
        if(numRows == 1) return s; //����һ��ʱ��ֱ�����
        vector<string> vs{numRows,""};
        string S = "";
        for(int i = 0; i < s.size(); ++i){
            int re = i % (2 * numRows - 2); //ÿ(2*numRows-2)���ַ�ѭ��
            if(re >= numRows - 1) re = 2*(numRows - 1) - re; //���ַ�����
            vs[re] += s[i];
        }
        for(auto x : vs) S += x;
        return S;
    }

//7. Reverse Integer
    int reverse(int x) {
        long long res = 0;
        while(x){ //reverse����
            res = res*10 + x%10;
            x /= 10;
        }
        return (res<INT_MIN || res>INT_MAX) ? 0 : res;
    }

//8.String to Integer (atoi)
    int myAtoi(string str) {
        int index = 0; //��¼��һ���ǿո��ַ���λ��
        long sum = 0; //��¼����
        bool negetive = false; //��¼������
        for(int i = 0; i < str.size(); ++i){
            if(str[i] != ' '){
                index = i;
                break;
            }
        }
        if(str[index] == '+' || str[index] == '-' || (str[index] <= '9' && str[index] >= '0')){
            negetive = str[index] == '-' ? true : false; //�����Ŵ���
            if(str[index] == '+' || str[index] == '-') ++index; //�Ƿ��������Ŵ���
            for(int j = index; j < str.size(); ++j){
                if(str[j] <= '9' && str[j] >= '0'){
                    sum = sum * 10 + static_cast<int>(str[j] - 48);
                    if(sum > INT_MAX || sum < INT_MIN) break;
                }
                else break;
            }
            sum = negetive ? -sum : sum;
            if(sum > INT_MAX) return INT_MAX;
            if(sum < INT_MIN) return INT_MIN;
            return sum;
        }
        return 0;
    }

//9. Palindrome Number
    bool isPalindrome(int x) {
        if(x < 0) return false;
        else{
            long reverseX = 0;
            int y = x;
            while(x){ //��ת����
                reverseX = reverseX * 10 + x % 10;
                x /= 10;
            }
            return reverseX == y;
        }
    }

//10. Regular Expression Matching
    bool isMatch(string s, string p) {

    }

//11. Container With Most Water
    int maxArea(vector<int>& height) {
        auto volume = [height](int i, int j)->int{return min(height[i], height[j]) * (j - i);}; //�������
        int leftIndex = 0, rightIndex = height.size();
        int v = volume(0, height.size()-1); //��ʼ���
        //cout << v << endl;
        while(rightIndex > leftIndex){
            height[leftIndex] > height[rightIndex] ? --rightIndex : ++leftIndex; //���������м��ƶ�
            v = max(v, volume(leftIndex, rightIndex)); //�������
        }
        return v;
    }

//12. Integer to Roman
    /*
    I(1), X(10), C(100), M(1000), V(5), L(50), D(500)
    1.��ͬ��������д,����ʾ����������Щ������ӵõ�����,�� ��=3;
    2.С�������ڴ�����ֵ��ұ�,����ʾ����������Щ������ӵõ�����,�� ��=8����=12;
    3.С������(���� ��X �� C)�ڴ�����ֵ���ߣ�����ʾ�������ڴ�����С���õ�����,�� ��=4����=9��
    */
    int power(int p, int n){
        int k = 1;
        while(n--)
            k *= p;
        return k;
    }

    string intToRoman(int num) {
        map<int, string> myMap{{0, ""}, {1, "I"}, {10, "X"}, {100, "C"}, {1000, "M"},
            {2000, "MM"}, {3000, "MMM"}, {4, "IV"},{6, "VI"},{9, "IX"}, {90, "XC"},
            {900, "CM"}, {40, "XL"},{60, "LX"},{400, "CD"},{600, "DC"}};
        vector<int> nums{2,3,5,7,8};
        for(auto num : nums){
            if(num < 4){
                myMap[num] = string(num, 'I');
                myMap[num * 10] = string(num, 'X');
                myMap[num * 100] = string(num, 'C');
            }
            else{
                myMap[num] = "V" + string(num - 5, 'I');
                myMap[num * 10] = "L" + string(num - 5, 'X');
                myMap[num * 100] = "D" + string(num - 5, 'C');

            }
        } //���Ͻ���
        string s = "";
        for(int i = 3; i >= 0; --i){
            int a = num / power(10, i);
            s += myMap[a * power(10, i)];
            num -= a * power(10, i);
        }
        return s;
    }

//13. Roman to Integer
    int romanToInt(string s) {
        map<int, string> myMap{{0, " "}, {1, "I"}, {10, "X"}, {100, "C"}, {1000, "M"},
            {2000, "MM"}, {3000, "MMM"}, {4, "IV"},{6, "VI"},{9, "IX"}, {90, "XC"},
            {900, "CM"}, {40, "XL"},{60, "LX"},{400, "CD"},{600, "DC"}};
        vector<int> nums{2,3,5,7,8}; //С�ı䶯{0, ""}->{0, " "}
        for(auto num : nums){
            if(num < 4){
                myMap[num] = string(num, 'I');
                myMap[num * 10] = string(num, 'X');
                myMap[num * 100] = string(num, 'C');
            }
            else{
                myMap[num] = "V" + string(num - 5, 'I');
                myMap[num * 10] = "L" + string(num - 5, 'X');
                myMap[num * 100] = "D" + string(num - 5, 'C');

            }
        } //���Ͻ���
        map<string, int> Map;
        for(auto iter = myMap.begin(); iter != myMap.end(); ++iter)
            Map[iter->second] = iter->first; //key, value������
        s += " "; //β������
        int sum = 0, dis = 0;
        if(s.size() <= 2) return Map[s];
        for(int i = 2; i < s.size();){
            //�����ַ�����������Map������3,2,1���ַ�
            dis = static_cast<int>(s.size() - i);
            if(Map.count(s.substr(i-2, 3))){
                sum += Map[s.substr(i-2, 3)];
                dis = min(3, dis);
            }
            else if(Map.count(s.substr(i-2, 2))){
                sum += Map[s.substr(i-2, 2)];
                dis = min(2, dis);
            }
            else{
                sum += Map[s.substr(i-2, 1)];
                dis = min(1, dis);
            }
            i += dis;
        }
        return sum;
    }

//14. Longest Common Prefix
    string common_string(string &s1, string &s2){
        //�������ַ��������������ǰ׺
        string s = "";
        for(int i = 0; i < min(s1.size(), s2.size()); ++i){
            if(s1[i] == s2[i]) s += string(1, s1[i]);
            else break;
        }
        return s;
    }

    string longestCommonPrefix(vector<string>& strs) {
        //LCP(s1,s2,...,sn) = LCP(LCP((s1,s2),s3)...,Sn)
        string s = "";
        if(strs.size() == 0) return s;
        s = strs[0];
        for(int i = 1; i != strs.size(); ++i){
            s = common_string(s, strs[i]);
        }
        return s;
    }

//15. 3Sum
    set<vector<int>> twoSum(vector<int>::iterator iter1, vector<int>::iterator iter2, int target){
        //twosum:����target, ����{target,a,b}��vector��ɵ�set,����a+b=target
        //����HashMap,���Ӷ�O(n);
        set<vector<int>> svi{};
        if(iter2 - iter1 < 2) return svi;
        else{
            set<int> mySet{};
            for(auto iter = iter1; iter != iter2; ++iter){
                auto it = mySet.find(target - *iter);
                if(it == mySet.end()) mySet.insert(*iter);
                else svi.insert({-target, target - *iter, *iter});
            }
            return svi;
        }
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        //3sum ���Ӷ�O(n^2)
        sort(nums.begin(), nums.end()); //����
        vector<vector<int>> vvi{};
        set<vector<int>> svi{};
        if(nums.size() < 3) return vvi;
        else{
            for(auto iter = nums.begin(); iter != nums.end();){
                auto vi = twoSum(iter + 1, nums.end(), -(*iter));
                for(auto it = vi.begin(); it != vi.end(); ++it){
                    svi.insert(*it);
                }
                //�ظ�Ԫ��ֻ�迼�ǵ�һ��
                auto it = find(nums.rbegin(), nums.rend(), *iter); //�������һ����ͬ��Ԫ��
                if(it == nums.rend()) ++iter;
                else iter = it.base(); //���µ�����
            }
            copy(svi.begin(), svi.end(), back_inserter(vvi));
            return vvi;
        }
    }

//16. 3Sum Closest
    int closest(vector<int>::iterator iter1, vector<int>::iterator iter2, int target){
        //closest �ҵ�3�����ĺ���target�ľ�����С
        //�������������δ�ͷ����β�����м��ƶ�
        auto iter = iter1; //��ʼ������
        int posi_error = INT_MAX, nege_error = INT_MIN, sum;//sum��target�Ĳ�ֵ
        ++iter1; //ͷ��������
        --iter2; //β��������
        while(iter2 > iter1){
            sum = *iter + *iter1 + *iter2;
            if(sum == target) return sum;
            else if(sum > target){
                --iter2;//β����������ǰ��
                if(sum - target <= posi_error) posi_error = sum - target;//���²�ֵ
            }
            else{
                ++iter1;//ͷ�������������
                if(sum - target >= nege_error) nege_error = sum - target;//���²�ֵ
            }
        }
        //cout << posi_error << ends << nege_error << ends << sum << endl;
        if(posi_error == INT_MAX) return target + nege_error;
        else if(nege_error == INT_MIN) return target + posi_error;
        else{
            return abs(nege_error) <= abs(posi_error) ? target + nege_error : target + posi_error;
        }
    }

    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int m = INT_MAX, t; //m:��ֵ
        for(auto iter = nums.begin(); iter != nums.end() - 2; ++iter){
            int sum = closest(iter, nums.end(), target);
            //cout << sum << endl;
            if(sum == target) return target;
            if(abs(sum - target) <= m){
                t = sum;
                m = abs(sum - target);
            }
        }
        return t;
    }

//17. Letter Combinations of a Phone Number
    void backTrack(vector<string> &vs, string s, int index, string digits){
        //���ݷ�
        map<char, string> myMap{{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
            {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
        if(index == digits.size()){
            vs.push_back(s);
        }
        else{
            string S = myMap[digits[index]];
            for(int i = 0; i != S.size(); ++i){
                string s_replace = s;
                s_replace += S[i];
                backTrack(vs, s_replace, index + 1, digits);
            }
        }
    }

    vector<string> letterCombinations(string digits) {
        vector<string> sv{};
        if(digits.size() == 0) return sv;
        string s{};
        int index = 0;
        backTrack(sv, s, index, digits);
        return sv;
    }

//18. 4sum
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

    }

//19. Remove Nth Node From End of List
    int length(ListNode* head){
        //the length of ListNode
        int len = 1;
        while(head = head->next) ++len;
        return len;
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int len = length(head), c = 0;
        ListNode l(0), *p = &l;
        while(head){
            if(c == len - n){
                head = head->next;
                if(head){
                    p->next = new ListNode(head->val);
                    p = p->next;
                }
            }
            else{
                p->next = new ListNode(head->val);
                p = p->next;
                head = head->next;
                ++c;
            }
        }
        return l.next;
    }

//20. Valid Parentheses
    bool isValid(string s) {
        stack<char> cs;
        for(auto x : s){
            if(x == ')' && (cs.size() == 0 || cs.top() != '(')) return false;
            if(x == ']' && (cs.size() == 0 || cs.top() != '[')) return false;
            if(x == '}' && (cs.size() == 0 || cs.top() != '{')) return false;
            if(x == '(' || x == '[' || x == '{') cs.push(x);
            if(x == ')' || x == ']' || x == '}') cs.pop();
            cout << cs.size() << ends;
        }
        cout << endl;
        return cs.empty();
    }

//21. Merge Two Sorted Lists
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode l(0), *p = &l;
        while(l1 && l2){
            if(l1->val <= l2->val){
                p->next = l1;
                l1 = l1->next;
            }
            else{
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        if(l1) p->next = l1;
        if(l2) p->next = l2;
        return l.next;
    }

//22. Generate Parentheses
    void genbackTrack(vector<string> &vs, string s, int left, int right){
        if(!left && !right){
            vs.push_back(s);
        }
        else{
            if(left <= right && left) genbackTrack(vs, s + "(", left - 1, right);
            if(left <= right && right) genbackTrack(vs, s + ")", left, right - 1);
        }

    }

    vector<string> generateParenthesis(int n) {
        //(2n)!/(n!*(n+1)!)
        string s = "";
        vector<string> vs{};
        int left = n, right = n;
        genbackTrack(vs, s, left, right);
        return vs;
    }

//23. Merge k Sorted Lists
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *l = nullptr;
        for(int i = 0; i != lists.size(); ++i){
            l = mergeTwoLists(l, lists[i]);
        }
        return l;
    }

//24. Swap Nodes in Pairs
    ListNode* swapPairs(ListNode* head) {
        int len = length(head);
        if(len < 2) return head;
        else{

        }

    }

//26. Remove Duplicates from Sorted Array
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        int i = 0, j = 0;
        while(++j < nums.size())
            if(nums[j] != nums[i]) nums[++i] = nums[j];
        return i+1;
    }

//27. Remove Element
    int removeElement(vector<int>& nums, int val) {
        int index = 0;
        for(int i = 0; i != nums.size(); ++i){
            if(nums[i] != val){
                nums[index] = nums[i];
                ++index;
            }
        }
        return index;
    }

//28. Implement strStr()
/*/KMP
    int next(string needle){
        int len = needle.size();
        vector<int> iv(len - 1, 0);
        for(int i = 1; i != len; ++i){
            string s1(needle, 0, i), s2(needle, len - i,i);
            iv[i] = s1 == s2 ? i : 0;
        }
        return *max_element(iv.begin(), iv.end());
    }

    int match(string s1, string s2){
        int i = 0;
        for(; i != s2.size(); ++i){
            if(s2[i] != s1[i]) break;
        }
        return i;
    }

    int strStr(string haystack, string needle) {
        int len = needle.size();
        if(len > haystack.size()) return -1;
        if(len == 0) return 0;
        for(int i = 0; i < haystack.size();){
            string s = haystack.substr(i, min(len, haystack.size()));
            int j = match(s, needle);

        }
        return -1;
    }
*/

//29. Divide Two Integers
    long long abs(long long x){
        return x < 0 ? -x : x;
    }

    int divide(int dividend, int divisor) {
        if(divisor == 0 || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
        int sign = (dividend ^ divisor) < 0 ? -1 : 1;
        long long dd = abs(dividend);
        long long dr = abs(divisor);
        if(dd < dr) return 0;
        int quoient = 0;
        while(dd >= dr){
            int p = 1;
            long long temp = dr;
            while(dd >= (temp << 1)){
                temp <<= 1;
                p <<= 1;
            }
            dd -=temp;
            quoient += p;
        }
        return sign == -1 ? -quoient : quoient;
    }

//30. Substring with Concatenation of All Words
    vector<int> findSubstring(string s, vector<string>& words) {

    }

//31. Next Permutation
    void nextPermutation(vector<int>& nums) {
        //next_permutation(nums.begin(), nums.end()); //library function in STL
        int len = nums.size();
        int i = len - 2, j = len - 1, k = len;
        while(i >= 0 && nums[i] >= nums[i + 1]) --i;
        if(i == -1){
            while(j >= ++i){
                swap(nums[i], nums[j]);
                --j;
            }
        }
        else{
            for(; j > i; --j) if(nums[j] > nums[i]) break;
            for(; j > i; --j) if(nums[j] < nums[j - 1]) break;
            j == i ? swap(nums[i], nums[i + 1]) : swap(nums[i], nums[j]);
            sort(nums.begin() + i + 1, nums.end());
            //for(auto x : nums) cout << x << ends;
        }
    }

//35. Search Insert Position
    int binary_search(vector<int>& nums, int lo, int hi, int target){
        if(hi == lo + 1) return target <= nums[lo] ? lo : hi;
        int mi = (lo + hi) / 2;
        return target >= nums[mi] ? binary_search(nums, mi, hi, target) : binary_search(nums, lo, mi, target);
    }

    int searchInsert(vector<int>& nums, int target) {
        return binary_search(nums, 0, nums.size(), target);
    }
};
