#pragma once


/*
 * FunctionList.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

/// List of functions that share the same signature - can be used to call all of them easily
template<typename Signature>
class CFunctionList
{
public:
	std::vector<std::function<Signature> > funcs;

	CFunctionList(int){};
	CFunctionList(){};
	template <typename Functor> 
	CFunctionList(const Functor &f)
	{
		funcs.push_back(std::function<Signature>(f));
	}
	CFunctionList(const std::function<Signature> &first)
	{
		if (first)
			funcs.push_back(first);
	}
	CFunctionList(std::nullptr_t)
	{}
	CFunctionList & operator+=(const std::function<Signature> &first)
	{
		funcs.push_back(first);
		return *this;
	}
	void add(const CFunctionList<Signature> &first)
	{
		for (size_t i = 0; i < first.funcs.size(); i++)
		{
			funcs.push_back(first.funcs[i]);
		}
	}
	void clear()
	{
		funcs.clear();
	}
	operator bool() const
	{
		return funcs.size();
	}
	void operator()() const
	{
		std::vector<std::function<Signature> > funcs2 = funcs; //backup
		for(size_t i=0;i<funcs2.size(); ++i) 
		{
			if (funcs2[i])
				funcs2[i]();
		}
	}
	template <typename Arg> 
	void operator()(const Arg & a) const
	{
		std::vector<std::function<Signature> > funcs2 = funcs; //backup
		for(int i=0;i<funcs2.size(); i++) 
		{
			if (funcs2[i])
				funcs2[i](a);
		}
	}
	// Me wants variadic templates :(
	template <typename Arg1, typename Arg2>
	void operator()(Arg1 & a, Arg2 & b) const
	{
		std::vector<std::function<Signature> > funcs2 = funcs; //backup
		for(int i=0;i<funcs2.size(); i++)
		{
			if (funcs2[i])
				funcs2[i](a, b);
		}
	}
};
