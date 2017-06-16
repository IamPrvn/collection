/*
   following are the opertaions :-

   Add: Add a given string to the collection.
   Ask: Ask if there exists a group of k strings such that they have a common
      suffix of length l .
   Removei: Remove the string that was added in the ith operation (if the string
      is not already removed). It is guaranteed that ith operation was an Add
      operation.


   Input
   First line of input contains an integer q denoting the total number of
      operations Harsh does. q lines follow in the following format.

   1 s Add the string s(all lowercase characters) to Aniket's collection of
      strings.
   2 k l Ask if there exists a group of k strings such that they have a common
      suffix of length l.
   3 x Remove the string added in the xth operation (if not already removed).

   Output
   Print the answer to all the Ask operations in different lines. Print "YES" if
      it exists else print "NO".

   Constraints
   1 ≤ q ≤ 105
   1 ≤ |s| (sum of lengths of all strings added to the collection) ≤ 105
   1 ≤ k,l ≤ 105
   1 ≤ x ≤ number of operations done yet

   Example
   Input 1:
   9
   1 aba
   1 accba
   2 2 2
   2 2 3
   1 aaaa
   1 ababa
   2 3 2
   3 1
   2 3 2


   Output 1:
   YES
   NO
   YES
   NO

   EXPLANATION:
   The collection of strings can be maintained effectively in a Trie. Since the
      queries are about the suffix of the strings, the strings need to be
      processed in reverse order. Here onwards, I will assume that all the
      strings have been reversed just after taking their input.
   The addition and removal operation can hence be performed in O(string
      length). As we know, that all the strings having same prefix converge at
      the same node in a Trie, we can keep a prefix counter in every node of the
      Trie denoting the number of strings having the same prefix (suffix in our
      case, as we have reversed the strings). Hence, if there exists a node in
      Trie at depth L having prefix counter >=K the answer to the query is Yes
      else the answer it No.
   To answer the queries efficiently, we can maintain a data structure, an array
      of maps for instance. Such that M[L][K] maintains the count of number of
      nodes at depth L having prefix counter K. This data structure is updated
      each time the prefix counters of Trie change on Add and Remove queries.
      Since, in any map K can range from 1 to N (the number of strings having
      upper bound |S|), the updation can be done in O(log(|S|). This updation
      occurs on every addition and removal operation. Thus the complexity of
      maintaining the data structure is O(|S|log(|S|)) . The queries can be
      answer by just looking up the values in the map. Hence all queries can are
      answered in O(Qlog(|S|)).
   Total complexity: O((Q+|S|)log(|S|))
 */

 #include <bits/stdc++.h>
#define pb push_back
#define pii pair < int, int >
#define mp make_pair
#define F first
#define S second
#define ll long long
#define iosbase ios_base::sync_with_stdio(false)
#define sc scanf
#define pr printf
#define null NULL
#define getcx getchar_unlocked
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define pll pair < ll, ll >
#define vi vector < int >
#define vll vector < ll >

#define maxs 100005
#define logmaxs 35

#define MOD 1000000007
#define eps 1e-9
#define llmax 1e15 + 5
#define intmax 1e9 + 5
#define intmin -intmax

#define pi 3.14159265358979

using namespace std;

map<int, int> ans[maxs];

string s;
vector<string> v;
int mrk[maxs];

struct trie {
  int edge[26];
  int prefix;
};

trie tree[maxs];
int  cnt;

void insert(int node, int idx) {
  if (idx == s.size()) {
    tree[node].prefix++;
    ans[idx][tree[node].prefix]++;
    return;
  }
  int x = s[idx] - 'a';
  tree[node].prefix++;
  ans[idx][tree[node].prefix]++;

  if (tree[node].edge[x] != 0) {
    insert(tree[node].edge[x], idx + 1);
  }
  else {
    ++cnt;
    tree[node].edge[x] = cnt;
    insert(tree[node].edge[x], idx + 1);
  }
}

void remove(int node, int idx) {
  if (idx == s.size()) {
    ans[idx][tree[node].prefix]--;
    tree[node].prefix--;
    return;
  }
  remove(tree[node].edge[s[idx] - 'a'], idx + 1);
  ans[idx][tree[node].prefix]--;
  tree[node].prefix--;
  int x = tree[node].edge[s[idx] - 'a'];

  if (tree[x].prefix == 0) tree[node].edge[s[idx] - 'a'] = 0;
}

int main() {
  iosbase;
  int q, t, k, l, x;
  cin >> q;

  for (int i = 0; i < q; i++) {
    cin >> t;

    if (t == 1) {
      cin >> s;
      reverse(s.begin(), s.end());
      v.pb(s);
      mrk[v.size()] = 1;
      insert(0, 0);
    }
    else if (t == 2) {
      v.pb("");
      cin >> k >> l;

      if (ans[l][k]) cout << "YES" << endl;
      else cout << "NO" << endl;
    }
    else {
      v.pb("");
      cin >> x;

      if (!mrk[x]) continue;
      s      = v[x - 1];
      mrk[x] = 0;
      remove(0, 0);
    }
  }
  return 0;
}
