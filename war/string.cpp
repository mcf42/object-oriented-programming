// a value-semantic string class that supports the following syntaxes:

// default contstruct
string s0;

// construct and assign from a literal value
string s1 = "hello";
s1 = "foo";

// copy construct and assign
string s2 = s1;
s2 = s1; // s2 == s1

// move construction and assignment (optional)
//string s3 = std::move(s2);
//s3 = std::move(s1);

// compare
s1 == s1;

// order
s1 < s1; //lexographical comparison

// object independence
s2 = "bar"; //does not change the value of s1

#include <cstring>

class String
{
public:
  String(const char* s) 
    : len(std::strlen(s)), str(new char[len])
  {
    std::strncpy(str, s, len);
  }

  String(const String& s)
    : str(s.str), len(s.len)
  { }

  ~String()
  {
    delete[] str;
  }

  String operator=(const String& s)
  {
    std::strncpy(str,s.str,s.len);
    return *this;
  }

  bool operator==(const String& s)
  {
    if(std::strncmp(str,s.str) == 0)
      return true;
    else
      return false;
  }

  bool operator>(const String& s)
  {
    if(std::strncmp(str,s.str) > 0)
      return true;
    else
      return false;
  }

  bool operator<(const String& s)
  {
    if(std::strncmp(str,s.str) < 0)
      return true;
    else
      return false;
  }

private:
  int len;
  char* str;
};
