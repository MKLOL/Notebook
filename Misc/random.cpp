mt19937 rng(time(0));
uniform_int_distribution<mt19937::result_type> d(1,6); // distribution in range [1, 6]
d(rng) // gets the number
