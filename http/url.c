int url_decode(const char *source, char *dest)
{
    char * start = dest;
    while (*source)
    {
        switch (*source)
        {
        case '+':
            *(dest++) = ' ';
            break;
        case '%':
            if (source[1] && source[2])
            {
                int value = hex_pair_value(source + 1);
                if (value >= 0)
                {
                    *(dest++) = value;
                    source += 2;
                }
                else
                {
                    *dest++ = '?';
                }
            }
            else
            {
                *dest++ = '?';
            }
            break;
        default:
            *dest++ = *source;
            break;
        }
        source++;
    }
    *dest = 0;
    return dest - start;
}
int url_encode(const char *source, char *dest, unsigned max)
{
    static const char *digits = "0123456789ABCDEF";
    unsigned char ch;
    unsigned len = 0;
    char *start = dest;

    while (len < max - 4 && *source)
    {
        ch = (unsigned char)*source;
        if (*source == ' ')
        {
            *dest++ = '+';
        }
        else if (isalnum(ch) || strchr("-_.!~*'()", ch))
        {
            *dest++ = *source;
        }
        else
        {
            *dest++ = '%';
            *dest++ = digits[(ch >> 4) & 0x0F];
            *dest++ = digits[       ch & 0x0F];
        }
        source++;
    }
    *dest = 0;
    return start - dest;
}