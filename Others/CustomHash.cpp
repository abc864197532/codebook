struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    // need to change the type
    size_t operator()(vector <int> c) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        uint64_t res = 0;
        for (int i : c)
            res = (res ^ (res >> 26)) ^ splitmix64(i + FIXED_RANDOM);
        return res;
    }
};

unordered_map <vector <int>, int, custom_hash> m1;
gp_hash_table <vector <int>, int, custom_hash> m2;