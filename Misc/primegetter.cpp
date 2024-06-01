
// Function to check if a number is prime
bool isPrime(long long num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;

    for (long long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

// Function to print the first X prime numbers after Y as a C++ array
void printPrimesAfterY(long long X, long long Y) {
    long long count = 0;
    long long num = Y + 1;  // Start checking from Y + 1
    std::cout << "long long primes[] = {";

    while (count < X) {
        if (isPrime(num)) {
            if (count > 0) {
                std::cout << ", ";
            }
            std::cout << num;
            count++;
        }
        num++;
    }

    std::cout << "};" << std::endl;
}

vi pr = {1000000007, 1000000009, 1000000021, 1000000033, 1000000087, 1000000093, 1000000097, 1000000103, 1000000123, 1000000181, 1000000207, 1000000223, 1000000241, 1000000271, 1000000289, 1000000297, 1000000321, 1000000349, 1000000363, 1000000403, 1000000409, 1000000411, 1000000427, 1000000433, 1000000439, 1000000447, 1000000453, 1000000459, 1000000483, 1000000513, 1000000531, 1000000579, 1000000607, 1000000613, 1000000637, 1000000663, 1000000711, 1000000753, 1000000787, 1000000801, 1000000829, 1000000861, 1000000871, 1000000891, 1000000901, 1000000919, 1000000931, 1000000933, 1000000993, 1000001011};

pii getRand() {
    std::mt19937 rng(time(nullptr)); // Seed with current time
    std::uniform_int_distribution<int> dist(0, pr.size() - 1); // Distribution range

    // Select two random indices
    int index1 = dist(rng);
    int index2 = dist(rng);

    // Ensure index1 and index2 are not the same
    while (index1 == index2) {
        index2 = dist(rng);
    }
    return {pr[index1], pr[index2]};
}
