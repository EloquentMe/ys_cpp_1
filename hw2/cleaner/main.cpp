#include <iostream>
#include <istream>
#include <ostream>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;

enum COMMENT
{
    NO,
    SLINE,
    MLINE
};

COMMENT write_until_comment(istream& in, ostream& out)
{
    char current;
    char previous;
    bool isOpenedDQuotes = false;
    if (!in.get(previous))
        return NO;
    if (previous == '\"')
        isOpenedDQuotes = !isOpenedDQuotes;
    while(cin.get(current))
    {
        if(current == '\"' && previous != '\\')
            isOpenedDQuotes = !isOpenedDQuotes;
        if(previous == '/' && !isOpenedDQuotes)
        {
            switch(current)
            {
            case '*':
                return MLINE;
            case '/':
                return SLINE;
            }
        }
        out.put(previous);
        previous = current;
    }
    out.put(previous);
    return NO;
}

void skip_until_eol(istream& in)
{
    char current;
    while(in.get(current))
    {
        if (current == '\n')
        {
            in.unget();
            return;
        }
    }
}

void skip_until_comment_end(istream& in)
{
    char previous;
    char current;
    if (!in.get(previous))
    {
        return;
    }
    while(in.get(current))
    {
        if (previous == '*' && current == '/')
            return;
        previous = current;
    }
}

void cleaner(istream& in, ostream& out)
{
    do
    {
        COMMENT result = write_until_comment(in, out);
        switch(result)
        {
        case NO:
            return;
        case SLINE:
            skip_until_eol(in);
            break;
        case MLINE:
            skip_until_comment_end(in);
            break;
        }
    }
    while(true);
}

int main()
{
    cleaner(cin, cout);
    return 0;
}
