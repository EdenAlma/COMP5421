#include <iostream>
#ifndef TEXT_H
#define TEXT_H



class Text
{

private:
  char *text;
  int strLen(const char*) const;        //function for returning length
  void strCopy(const char* ,char*);     //copies one char* to another

public:
  Text();
  virtual ~Text();
  Text(const Text&);
  Text(const char *);
  void set(const char *);
  void set(const Text&);
  Text& operator=(const Text&);
  friend std::ostream& operator<<(std::ostream&, const Text&); //overloaded <<
  void append(const char *);
  void append(const Text&);
  int length() const;
  bool isEmpty() const;
};
#endif /* end of include guard: TEXT_H */
