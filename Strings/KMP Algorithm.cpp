struct KMP {
    string p; int psz; // 0-indexed
    vector<int> lps;

    KMP() {}
    // builds the longest proper prefix array of pattern p
    // where lps[i]=longest proper prefix which is also suffix of p[0...i]
    KMP(string _p) : p(_p), psz(p.size()){
        lps.resize(psz + 1);
        int j = 0;
        lps[0] = 0;
        for(int i = 1; i < psz; i++) {
            while(j >= 0 && p[i] != p[j]) {
                if(j >= 1) j = lps[j - 1];
                else j = -1;
            }
            j++;
            lps[i] = j;
        }
    }
    // aka, kmp. returns matches of p in s. 0-indexed
    vector<int> find_matches(const string& s) {
        int sz = s.size();
        int j = 0;
        vector<int> ans;
        for(int i = 0; i < sz; i++) {
            while(j >= 0 && p[j] != s[i]) {
                if(j >= 1) j = lps[j - 1];
                else j = -1;
            }
            j++;
            if(j == psz) {
                j = lps[j - 1];
                ans.push_back(i - psz + 1); // pattern found in string s at position i-psz+1
            }
            // after each loop we have j=longest common suffix of s[0..i] which is also prefix of p
        }
        return ans;
    }  
};