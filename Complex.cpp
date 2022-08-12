#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Complex.h"

const double& Complex::operator[](std::string num) const
{
	//DEFINE IN .CPP NON INLINE
	//if the string says "real", return private variable real.
	//if the string says "imag", return private variable im.
	//These conditions are taken from the source file given
	if (num == "real")
	{
		return real;
	}
	else if (num == "imag")
	{
		return im;
	}
	//this is the 
	else
	{
		throw std::out_of_range("invalid index: " + num);
	}
}

double& Complex::operator[](std::string num)
{
	//DEFINE IN .CPP NON INLINE
	//this operator is overloaded on const, so we perform the exact same thing
	//for the case that a variable is not const in the main
	if (num == "real")
	{
		return real;
	}
	else if (num == "imag")
	{
		return im;
	}
	else
	{
		throw std::out_of_range("invalid index: " + num);
	}
}

Complex::operator std::string() const
{
	//DEFINE IN .CPP NON INLINE
	//conversion operator from type Complex to a string, simply use the ostreamstring
	std::ostringstream os;
	os << *this;
	//return the output stream of type string. THis will not compile unless
	//we tell it to output as a type string and not type STREAM
	return os.str();
}
std::ostream& operator<<(std::ostream& os, const Complex& cNum)
{
	//DEFINE IN .CPP NON INLINE
	//create real and imag strings to avoid magic strings/variables
	std::string R = "real";
	std::string I = "imag";
	//for the outstream, we have a variety of conditions we have to obide by for the output
	//if the real number of Complex is not zero and the imaginary number IS zero, return "real"
	if (cNum[R] != 0 || cNum[I] == 0)
	{
		os << cNum[R];
	}
	//if real number of complex is not zero and the imaginary number is greated than zero
	//then we wil have a plus in between the two numbers
	if (cNum[R] != 0 && cNum[I] > 0)
	{
		os << "+" << cNum[I] << "i";
	}
	//if the imaginary number is anything but 1, -1, or 0
	else if (cNum[I] != -1 && cNum[I] !=0 && cNum[I] != 1)
	{
		os << cNum[I] << "i";
	}
	//if the imaginary number is equal to one, then output the i next to it
	if (cNum[I] == 1)
	{
		os << "i";
	}
	//if the imaginary number is equal to -1, then output -i to it
	else if (cNum[I] == -1)
	{
		os << "-i";
	}

	return os;
}
std::istream& operator>>(std::istream& is, Complex& cNum)
{
	//DEFINE IN .CPP NON INLINE
	//Even though this function was defined as friend in the Time class,
	//input stream for both "real" and "imag" passing them as type Complex
	is >> cNum["real"];
	is >> cNum["imag"];
	if (is.fail() == true)
	{
		throw std::runtime_error("bad inputs for reading");
	}
	return is;
}