template <typename T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = m / a;
        m -= t * a; swap(a, m);
        u -= t * v; swap(u, v);
    }
    assert(m == 1);
    return u;
}

template <const int32_t MOD>
class Modular {
  public:
    using Type = int32_t;

    Modular() : value(0) {}
    template <typename U>
    Modular(const U& x) { value = normalize(x); }

    template <typename U>
    static Type normalize(const U& x) {
        Type v;
        if(-mod() <= x && x < mod()) v = static_cast<Type>(x);
        else v = static_cast<Type>(x % mod());
        if(v < 0) v += mod();
        return v;
    }

    const Type& operator()() const { return value; }
    template <typename U> operator U() const { return value; }
    constexpr static Type mod() { return MOD; }

    Modular &operator+=(const Modular &other) { value += other.value; value -= (value >= mod()) * mod(); return *this; }
    Modular &operator-=(const Modular &other) { value -= other.value; value += (value < 0) * mod(); return *this; }
    template <typename U> Modular &operator+=(const U &other) { return *this += Modular(other); }
    template <typename U> Modular &operator-=(const U &other) { return *this -= Modular(other); }
    Modular& operator++() { return *this += 1; }
    Modular& operator--() { return *this -= 1; }
    Modular operator++(int32_t) { Modular result(*this); *this += 1; return result; }
    Modular operator--(int32_t) { Modular result(*this); *this -= 1; return result; }
    Modular operator-() const { return Modular(-value); }
    
    Modular &operator*=(const Modular &rhs) {
        value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
        return *this;
    }
    template <typename U> Modular &operator*=(const U &other) { return *this *= Modular(other); }

    Modular &operator/=(const Modular &other) { return *this *= Modular(inverse(other.value, mod())); }

    friend const Type& abs(const Modular& x) { return x.value; }

    bool operator==(const Modular &other) { return value == other.value; }
    bool operator!=(const Modular &other) { return value != other.value; }
    template <typename U> bool operator==(const U &other) { return *this == Modular(other); }
    template <typename U> bool operator!=(const U &other) { return *this != Modular(other); }
    
    bool operator<(const Modular &other) { return value < other.value; }
    bool operator>(const Modular &other) { return value > other.value; }

    template <typename V> friend V& operator>>(V& stream, Modular<MOD>& number);

  private:
    Type value;
};

template <int32_t MOD> Modular<MOD> operator+(const Modular<MOD>& lhs, const Modular<MOD>& rhs) { return Modular<MOD>(lhs) += rhs; }
template <int32_t MOD, typename U> Modular<MOD> operator+(const Modular<MOD>& lhs, U rhs) { return Modular<MOD>(lhs) += rhs; }
template <int32_t MOD, typename U> Modular<MOD> operator+(U lhs, const Modular<MOD>& rhs) { return Modular<MOD>(lhs) += rhs; }

template <int32_t MOD> Modular<MOD> operator-(const Modular<MOD>& lhs, const Modular<MOD>& rhs) { return Modular<MOD>(lhs) -= rhs; }
template <int32_t MOD, typename U> Modular<MOD> operator-(const Modular<MOD>& lhs, U rhs) { return Modular<MOD>(lhs) -= rhs; }
template <int32_t MOD, typename U> Modular<MOD> operator-(U lhs, const Modular<MOD>& rhs) { return Modular<MOD>(lhs) -= rhs; }

template <int32_t MOD> Modular<MOD> operator*(const Modular<MOD>& lhs, const Modular<MOD>& rhs) { return Modular<MOD>(lhs) *= rhs; }
template <int32_t MOD, typename U> Modular<MOD> operator*(const Modular<MOD>& lhs, U rhs) { return Modular<MOD>(lhs) *= rhs; }
template <int32_t MOD, typename U> Modular<MOD> operator*(U lhs, const Modular<MOD>& rhs) { return Modular<MOD>(lhs) *= rhs; }

template <int32_t MOD> Modular<MOD> operator/(const Modular<MOD>& lhs, const Modular<MOD>& rhs) { return Modular<MOD>(lhs) /= rhs; }
template <int32_t MOD, typename U> Modular<MOD> operator/(const Modular<MOD>& lhs, U rhs) { return Modular<MOD>(lhs) /= rhs; }
template <int32_t MOD, typename U> Modular<MOD> operator/(U lhs, const Modular<MOD>& rhs) { return Modular<MOD>(lhs) /= rhs; }

const int md = 998244353;
using Mint = Modular<md>;

template<typename U>
Mint power(const Mint& a, const U& b) {
    assert(b >= 0);
    Mint x = a, res = 1;
    U p = b;
    while (p > 0) {
        if (p & 1) res *= x;
        x *= x;
        p >>= 1;
    }
    return res;
}

bool IsZero(const Mint& number) {
    return number() == 0;
}

string to_string(const Mint& number) {
  return to_string(number());
}

template <typename U>
U& operator<<(U& stream, const Mint& number) {
  return stream << number();
}

template <typename U>
U& operator>>(U& stream, Mint& number) {
    int64_t x;
    stream >> x;
    number.value = Mint::normalize(x);
    return stream;
}