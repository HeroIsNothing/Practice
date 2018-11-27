#ifndef NON_COPYABLE_H_20180612_H
#define NON_COPYABLE_H_20180612_H

class noncopyable
{
protected:
	noncopyable()	{}
	~noncopyable()	{}

private:
	noncopyable(const noncopyable &rhs);
	noncopyable& operator=(const noncopyable &rhs);
};

#endif
