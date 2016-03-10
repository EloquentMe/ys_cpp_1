void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int gcdex(int a, int b, int & x, int & y)
{
    int q, last_x = 1, last_y = 0;
    bool isSwapped = false;
    bool a_pos = true;
    bool b_pos = true;
    if (a < 0)
    {
        a_pos = false;
        a *= -1;
    }
    if (b < 0)
    {
        b_pos = false;
        b *= -1;
    }
    if (b > a)
    {
        swap(a, b);
        isSwapped = true;
    }
    x = 0;
    y = 1;
    while (b != 0)
    {
        q = a / b;
        a = a % b;
        swap(a, b);

        last_x -= q * x;
        swap(last_x, x);
        last_y -= q * y;
        swap(last_y, y);
    }
    x = isSwapped ? last_y : last_x;
    y = isSwapped ? last_x : last_y;
    if (!a_pos) x *= -1;
    if (!b_pos) y *= -1;
    return a;
}

bool invert(int a, int n, int &k)
{
    int x, y;
    int gcd = gcdex(a, n, x, y);
    if(gcd != 1)
        return false;
    else
    {
        if (n < 0)
            n *= -1;
        k = (x % n + n) % n;
        return true;
    }
}

