#include <vector>
#include <ostream>

using std::vector;

namespace NPolynom
{
inline int max(int a, int b)
{
    return a > b ? a : b;
}

template <class T> class TPolynom
{
    vector<T> coeff;
public:
    class iterator
    {
        friend class TPolynom;
    private:
        int position;
        int sizeAtInstantiation;
        TPolynom<T>* parent;
        iterator(int start,TPolynom<T>* p)
        {
            this->parent = p;
            position = start;
            sizeAtInstantiation = parent->Degree();
        }
    public:
        iterator& operator+=(int offset)
        {
            position += offset;
            return *this;
        }
        iterator& operator++()
        {
            ++position;
            return *this;
        }
        T& operator*() const
        {
            return parent->operator[](position);
        }
    };

    TPolynom(const T& scalar = 0)
        : coeff()
    {
        coeff.assign(1, scalar);
    }

    T& operator[] (std::size_t index)
    {
        if (index > this->coeff.size() - 1)
            this->coeff.resize(index + 1, 0);
        return this->coeff[index];
    }

    const T& operator[] (std::size_t index) const
    {
        return this->coeff[index];
    }

    int Degree() const
    {
        int degree = this->coeff.size() - 1;
        while(degree >= 0 && this->coeff[degree] == 0)
            --degree;
        return degree;
    }

    bool operator == (const TPolynom<T>& other)
    {
        auto it1 = this->coeff.begin();

        auto it2 = other.coeff.begin();

        while( it1 != coeff.end() && it2 != other.coeff.end() && *it1 == *it2)
        {
            ++it1;
            ++it2;
        }

        if(it1 == this->coeff.end())
        {
            if(it2 == other.coeff.end())
                return true;
            else
            {
                while(it2 != other.coeff.end() && *it2 == 0)
                    ++it2;
                if (it2 == other.coeff.end())
                    return true;
                else
                    return false;
            }
        }
        else
        {
            if(it2 != other.coeff.end())
                return false;
            else
            {
                while (it1 != this->coeff.end() && *it1 == 0)
                    ++it1;
                if (it1 == this->coeff.end())
                    return true;
                else
                    return false;
            }
        }
    }

    bool operator != (const TPolynom& other)
    {
        return !(*this == other);
    }

    TPolynom& operator += (const T& scalar)
    {
        this->operator[](0) += scalar;
        return *this;
    }

    TPolynom& operator -= (const T& scalar)
    {
        this->coeff[0] -= scalar;
        return *this;
    }

    TPolynom& operator *= (const T& scalar)
    {
        for (int i = 0; i <= this->Degree(); ++i)
            this->coeff[i] *= scalar;
        return *this;
    }

    TPolynom& operator += (const TPolynom<T>& other)
    {
        int size = other.Degree();
        for (int i = size; i >= 0 ; --i)
            this->operator[](i) += other[i];
        return *this;
    }

    TPolynom& operator -= (const TPolynom<T>& other)
    {
        int size = other.Degree();
        for (int i = size; i >= 0 ; --i)
            this->operator[](i) -= other[i];
        return *this;
    }

    TPolynom& operator *= (const TPolynom& other)
    {
        int hisSize = other.Degree();
        int ourSize = Degree();
        TPolynom result(0);
        for (int n = 0; n <= hisSize + ourSize; ++n)
            for (int i = ourSize; i >= 0; --i)
            {
                int j = n - i;
                if (j <= hisSize && j >= 0)
                    result[n] += this->operator[](i) * other[j];
            }
        *this = result;
        return *this;
    }

    TPolynom operator + (const T& scalar)
    {
        TPolynom result = *this;
        result[0] += scalar;
        return result;
    }

    TPolynom operator - (const T& scalar)
    {
        TPolynom result = *this;
        result[0] -= scalar;
        return result;
    }

    TPolynom operator * (const T& scalar)
    {
        TPolynom result = *this;
        result *= scalar;
        return result;
    }

    TPolynom operator + (const TPolynom& other)
    {
        TPolynom result = *this;
        result += other;
        return result;
    }

    TPolynom operator - (const TPolynom& other)
    {
        TPolynom result = *this;
        result -= other;
        return result;
    }

    TPolynom operator * (const TPolynom& other)
    {
        TPolynom result(*this);
        result *= other;
        return result;
    }

    TPolynom& operator /= (const T& scalar)
    {
        for (int i = 0; i <= this->Degree(); ++i)
            this->coeff[i] /= scalar;
        return *this;
    }

    TPolynom& operator %= (const T& scalar)
    {
        for (int i = 0; i <= this->Degree(); ++i)
            this->coeff[i] %= scalar;
        return *this;
    }

    TPolynom operator / (const T& scalar)
    {
        TPolynom result = *this;
        result /= scalar;
        return result;
    }

    TPolynom operator % (const T& scalar)
    {
        TPolynom result = *this;
        result %= scalar;
        return result;
    }

    TPolynom operator / (const TPolynom& other)
    {
        TPolynom q;
        TPolynom r = *this;
        int d = other.Degree();
        T c = other[d];
        int rd;
        while((rd = r.Degree()) >= d)
        {
            TPolynom s;
            s[rd - d] = r[rd] / c;
            q += s;
            r -= s * other;
        }
        return q;
    }

    TPolynom operator % (const TPolynom& other)
    {
        TPolynom r = *this;
        T c = other[other.Degree()];
        int d = other.Degree();
        while(r.Degree() >= d)
        {
            TPolynom s;
            s[r.Degree() - d] = r[r.Degree()] / c;
            r -= s * other;
        }
        return r;
    }

    TPolynom& operator /= (TPolynom other)
    {
        *this = *this / other;
        return *this;
    }

    TPolynom& operator %= (const TPolynom& other)
    {
        *this = *this % other;
        return *this;
    }

    T operator() (const T& at)
    {
        T x = at;
        T result = this->operator[](0);
        int size = this->Degree();
        for (int i = 1; i <= size; ++i)
        {
            result += this->coeff[i] * x;
            x *= at;
        }
        return result;
    }

    template <class S> friend std::ostream& operator<<(std::ostream& os, const TPolynom& obj);

    template <class S> friend TPolynom<S> operator,(TPolynom<S> const & obj1, TPolynom<S> const & obj2);

    typename TPolynom<T>::iterator begin()
    {
        return iterator(0,this);
    }
};

template <class S> std::ostream& operator<<(std::ostream& os, const TPolynom<S>& obj)
{
    for (int i = obj.Degree(); i > 0; --i)
    {
        if (obj[i] != 0)
        {
            if (obj[i] != 1)
                os << obj[i];
            if (i == 1)
                os << "x";
            else
                os << "x^" << i;
            os << " + ";
        }
    }
    os << obj[0];
    return os;
}

template <class S> TPolynom<S> operator,(TPolynom<S>& obj1, TPolynom<S>& obj2)
{
    TPolynom<S> r_last = obj1;
    TPolynom<S> r = obj2;
    while(r.Degree() > 0)
    {
        TPolynom<S> temp = r_last % r;
        r_last = r;
        r = temp;
    }
    return r_last;
}
}
