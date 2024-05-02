class VectorBasis {
public:
    static const int LG = 20;
    int basis[LG];  // basis[i] keeps the mask of the vector whose f value is i
    int csz;         // Current size of the basis
    VectorBasis() : csz(0) {
        for (int i = 0; i < LG; ++i) {
            basis[i] = 0;
        }
    }

    // Method to insert a vector into the basis
    void ins(int mask) {
      if (csz == LG) return;
      while (mask) {
        int i = __lg(mask);
        if (basis[i]) mask ^= basis[i];
        else {
          basis[i] = mask;
          break;
        }
      }
    }

    void insb(VectorBasis &vb) {
        for (int i = 0; i < LG; i++) {
          if (vb.basis[i] == 0) continue;
          ins(vb.basis[i]);
        }
    }

    int has(int mask) {
      int ans = 0;
      for (int i = LG - 1; i >= 0; i--) {
        if (!basis[i]) continue;


        if ((ans & 1 << i) == (mask & 1 << i)) continue;

        ans ^= basis[i];
      }

      return ans == mask;
    }

    // Getter for size
    int size() const {
        return csz;
    }

    int getMax() {
      int ans = 0;
      for (int i = LG - 1; i >= 0; i--) {
        if (!basis[i]) continue;

        if (ans & 1 << i) continue;

        ans ^= basis[i];
      }
      return ans;
    }

    void print() {
      cout << csz << "\n";
      FOR(i, LG) {
        if (!basis[i]) continue;
        cout << basis[i] << " ";
      }
      cout << "\n";
    }
};
