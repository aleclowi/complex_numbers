#ifndef _COMPLEX
#define _COMPLEX_

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

class Complex
{
public:
	/**
	Constructor: constexpr constructor through the use of default arguments, behaves
	as a default constructor that sets both the real and imaginary parts to 0;
	when given a single double as a parameter, the real part is set to this value and the imaginary
	part is set to 0; and when given two double inputs, it sets the real and imaginary
	parts to these values in respective order

	@param either a single double or two double inputs, setting values in respective order
	*/

	constexpr Complex(double real = 0, double im = 0);

	/**
	Constructor: accepts a string input, containing no spaces, for simplicity, that
	can parse a string containing addition/subtraction of complex numbers, given an invalid
	input it will throw an std::logic_error

	@param string input containing no spaces to be parsed
	*/
	Complex(const std::string& numbers)
	{
		//this constructor we will parse the input string into a complex number
		auto s = numbers; //declare an auto variable to be able to use as reference to the string
		//condition if the string entered is empty, throw the logic error
		if (s.length() == 0)
		{
			throw std::logic_error("bad input string: " + numbers);
		}
		//Below is the code to change the format of the complex number to its 
		//correct format after being modified
		//If the first element of the string is an "i", replace it with 1i of type string
		//after it has been modified
		if (s.front() == 'i')
		{
			s.replace(0, 1, "1i");
		}
		//find the string +i, and set it to a variable of type size_t, since the .find
		//function outputs in terms of string index number
		size_t iPos = s.find("+i");
		//while loop to read through the string until it's finished, replacing +i with
		//+1i similar to above
		while (iPos != -1)
		{
			//we will replace the second position with +1i
			s.replace(iPos, 2, "+1i");
		}
		//create a variable of size_t that finds -i in the string and sets it to iNeg
		size_t iNeg = s.find("-i");
		//While loop to do the same thing we did for +1i
		while (iNeg != -1)
		{
			s.replace(iNeg, 2, "-1i");
			iNeg = s.find("-i");
		}
		//create another variable to find the i char and  
		size_t iChar = s.find("i");
		//use another while loop to read through the string until its finished,
		//replacing the first index with any arbitrary char just for string parsing
		while (iChar != -1)
		{
			s.replace(iChar, 1, "X");
			iChar = s.find("i");
		}
		//declare temporary doubles, which we will set equal to our private member variables
		//after the while loop creates the tempVariable values with correct decimal format initialized to zero
		double tempReal = 0.0;
		double tempIm = 0.0;
		//this variable we will use as the input variable to the stringstream
		double temp = 0.0;
		//so input the initial auto variable into the string
		std::istringstream is(s);
		//while condition to look for -1 elements in the string, which is impossible
		//and will tell the string to stop
		while (is.peek() != std::string::npos)
		{
			//input the temp varaible into the stream, which is what we will use to modify
			//the other values
			is >> temp;
			//if the stream fails, we will throw the logic error saying what the user input was
			//wrong
			if (is.fail() == true)
			{
				throw std::logic_error("bad input string: " + numbers);
			}
			//if the next char in the input stream is at the end of the file,
			//add that to tempReal
			if (is.peek() == EOF)
			{
				tempReal += temp;
			}
			//if the next char is either x or - in the input stream, add it to the 
			//tempReal variable, in otherworse, insert it
			else if (is.peek() == '+' || is.peek() == '-')
			{
				tempReal += temp;
			}
			//if the next char is this arbitrary char that we used for parsing the im values,
			//then add it to the tempIm variable.
			else if (is.peek() == 'X')
			{
				tempIm += temp;
				is.get();
			}
		}
		//after the temporary real and imaginary numbers have been created, set them
		//to the private member variables.
		real = tempReal;
		im = tempIm;
	}

	/*THE FOLLOWING ARE OVERLOAD OPERATORS WITHIN THE CLASS*/

	/**
	binary operator += to add two complex numbers on two different sides of =,
	changing the left-hand side

	@param Complex num from the right hand side which is added to the left-hand side
	@return solution as a complex number
	*/

	constexpr Complex& operator+=(const Complex& num); //use reference as demostrated in the notes

	/**
	unary operator + to simply return a copy of the complex number

	@param none
	@return copy of the complex number
	*/

	constexpr Complex operator+() const;

	/**
	PREFIX (unary) operator ++ to increment the real part by 1

	@param none
	@return incremented number
	*/

	constexpr Complex& operator++(); //use reference as demonstrated in the notes

	/**
	POSTFIX (binary) operator ++ to increment the real part by 1

	@param integer that has been unused
	@return incremented number
	*/

	constexpr Complex operator++(int post);

	/**
	binary operator -= to subtract two complex numbers on two different sides of =,
	changing the left-hand side

	@param Complex num from the right hand side which is subtracted from the left hand side
	@return solution as a complex number that's been subtracted
	*/

	constexpr Complex& operator-=(const Complex& num);

	/**
	unary operator - to return a complex number negated (real and imaginary parts)

	@param none
	@return copy of the number but negated
	*/

	constexpr Complex operator-() const;

	/**
	PREFIX (unary) operator -- to decrement the real part by 1

	@param none
	@return decremented number
	*/

	constexpr Complex operator--();

	/**
	POSTFIX (binary) operator -- to decrement the real part by 1

	@param unused int
	@return decremented number
	*/

	constexpr Complex operator--(int post);

	/**
	binary operator *- to multiply two complex numbers changing the left hand side

	@param number on the right hand side
	@return complex number updated after multiplying to the left hand side
	*/
	constexpr Complex& operator*=(const Complex& num);

	/**
	binary operator /- to divide two complex numbers changing the left hand side

	@param number on the right hand side
	@return complex number updated after dividing to the left hand side
	*/

	constexpr Complex& operator/=(const Complex& num);

	/**
	unary operator ~ for the conjugate of a number

	@param none
	@return the conjugate of the complex number
	*/
	constexpr Complex operator~() const;

	/**
	call operator

	@param none
	@return sets complex number to zero
	*/
	constexpr void operator()();

	/**
	subscript operator assigning the real and/or imaginary numbers to their numbers respectively

	@param number in the form of a string
	@return type double of the number
	*/
	double& operator[](std::string num); //DEFINE IN .CPP NON INLINE

	/**
	subscript operator OVERLOADED ON CONST
	assigning the real and/or imaginary numbers to their numbers respectively

	@param number in the form of a string
	@return type double of the number, overloaded const
	*/

	const double& operator[](std::string num) const; //DEFINE IN .CPP NON INLINE

	/**
	comparison operator < such that a+bi are compared lexicographically
	declared as friend to be able to access the private member variabls of the class

	@param left number and right number to be compared
	@return type bool, true if leftNum is less than rightNum, false otherwise
	*/

	friend constexpr bool operator<(const Complex& leftNum, const Complex& rightNum);
	/**
	comparison operator == such that a+bi are compared lexicographically

	@param left number and right number to be compared
	@return type bool, true if leftNum is equal to rightNum, false otherwise
	*/

	friend constexpr bool operator==(const Complex& leftNum, const Complex& rightNum);

	/**
		comparison operator > such that a+bi are compared lexicographically

		@param left number and right number to be compared
		@return type bool, true if leftNum is greater than rightNum, false otherwise
		*/

	friend constexpr bool operator>(const Complex& leftNum, const Complex& rightNum);

	/**
		comparison operator <= such that a+bi are compared lexicographically

		@param left number and right number to be compared
		@return type bool, true if leftNum is less than or equal to rightNum, false otherwise
		*/

	friend constexpr bool operator<=(const Complex& leftNum, const Complex& rightNum);

	/**
		comparison operator >= such that a+bi are compared lexicographically

		@param left number and right number to be compared
		@return type bool, true if leftNum isless than rightNum, false otherwise
		*/

	friend constexpr bool operator>=(const Complex& leftNum, const Complex& rightNum);

	/**
		comparison operator != such that a+bi are compared lexicographically

		@param left number and right number to be compared
		@return type bool, true if leftNum is not equal to rightNum, false otherwise
		*/

	friend constexpr bool operator!=(const Complex& leftNum, const Complex& rightNum);
	/**
	Conversion operator from class Complex to string

	@param none
	@return type string
	*/
	operator std::string() const; //DEFINE IN .CPP NON INLINE


private:
	double real;
	double im;

};

/**AS DEMOSTRATED IN THE NOTES FROM THE TIME CLASS, THE FOLLOWING OPERATORS ARE NON MEMBER FUNCTIONS**/

	/**
	binary operator + to add two complex numbers, simply returning the sum

	@param two complex nums to be added
	@return sum of two complex nums
	*/

constexpr Complex operator+(Complex leftNum, const Complex& rightNum);

/**
binary operator - to add two complex numbers, simply returning the difference

@param two complex numbers to be taken difference
@return difference between two numbers
*/

constexpr Complex operator-(Complex leftNum, const Complex& rightNum);

/**
	binary operator * to multiply two complex numbers, simply returning the product

	@param two complex numbers to be taken product
	@return product between two numbers
	*/

constexpr Complex operator*(Complex leftNum, const Complex& rightNum);

/**
	binary operator / to multiply two complex numbers, simply returning the quotient

	@param two complex numbers to be taken quotient
	@return quotient between two numbers
	*/

constexpr Complex operator/(Complex leftNum, const Complex& rightNum);

/**
	stream operator << to print or display the complex number

	@param an output stream and complex number reference
	@return print/display of the complex numbers using an ostream
	*/

std::ostream& operator<<(std::ostream& os, const Complex& cNum); //DEFINE IN .CPP NON INLINE

/**
	stream operator << to print or display the complex number

	@param an output stream and complex number reference
	@return print/display of the complex numbers using an ostream
	*/

std::istream& operator>>(std::istream& is, Complex& cNum); //DEFINE IN .CPP NON INLINE

/**
	user-defined literal expression: code expressions such as 3.3i will be converted
	into the complex number 0+3.3i

	@param the number in the form of long double(user defined literal only takes long double)
	@return complex number in correct form
	*/

constexpr Complex operator""_i(long double cNum);



/////////////////////////////////////////////////////////////////////////////////////////////////////
//////**THE FOLLOWING ARE FUNCTION DEFINITIONS FOR CLASS MEMBER INLINE/CONSTEXPR FUNCTIONS **////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

	//Constexpr and inline functions must be declared inside the .h file otherwise it will
		//result in a linker error

constexpr Complex::Complex(double real, double im) : real(real), im(im)
{}

constexpr Complex& Complex::operator+=(const Complex& num) //refer to similar functions from the notes
{
	//simply add both sides of the equation
	real += num.real;
	im += num.im;

	return *this; //return updated object
}

constexpr Complex Complex::operator+() const
{
	//simply return a copy of the real and imaginary number of type Complex (copy operator)
	return Complex(real, im);
}

constexpr Complex& Complex::operator++() //use reference as demonstrated in the notes
{
	//prefix unary operator 
	//simply increment the real number, then return the number of type Complex incremented by one
	++real;
	return *this;
}

constexpr Complex Complex::operator++(int post) //use similar code in the notes from Time class
{
	//postfix unary operator, call the constructor
	Complex copy(*this); //copy the current real number
	++real;
	return copy; //return the copy
}

constexpr Complex& Complex::operator-=(const Complex& num)
{
	//similar to the += operator, subtract both sides of the equation
	real -= num.real;
	im -= num.im;
	return *this; //return the updated object
}

constexpr Complex Complex::operator-() const
{
	//here we're just returning a negated copy of the real and im numbers
	return Complex(-real, -im);
}

constexpr Complex Complex::operator--()
{
	//prefix unary operator, simply decrement the real number only
	--real;
	return *this;
}

constexpr Complex Complex::operator--(int post)
{
	//postfix unary operator, copy current, decrement, return copy
	Complex copy(*this);
	--real;
	return copy;
}

constexpr Complex& Complex::operator*=(const Complex& num)
{
	//right side of equation will be the private member variable
	//call the constructor because we will need to multiply Complex by a double
	Complex copy(*this);
	//cast the double real to multiply it by the num
	//(a+bi)(c+di) = (ac - bd) + (bc + ad)
	copy.real = (real * num.real) - (im * num.im); //(ac - bd)
	im = (im * num.real) + (real * num.im); //(bc + ad)
	real = copy.real; //set the private member variable to it
	return *this;
}

constexpr Complex& Complex::operator/=(const Complex& num)
{
	//here we take in a num of type Complex, so we have to cast it
	//as the private member variable to modify it with a double
	// (a + bi)/(c + di) = (ac+bd)/(c^2+d^2) + (bc - ad)/(c^2 + d^2)
	double realNum = (real * num.real) + (im * num.im); //(ac+bd)
	double imNum = (im * num.real) - (real * num.im); //(bc - ad)
	double denominator = (num.real * num.real) + (num.im * num.im); //(c^2 + d^2)
	real = realNum / denominator; //(ac+bd)/(c^2+d^2)
	im = imNum / denominator; //(bc - ad)/(c^2 + d^2)
	return *this;
}

constexpr Complex Complex::operator~() const
{
	//simply return the conjugate of the complex number, negate the imaginary
	return Complex(real, -im); 
}

constexpr void Complex::operator()()
{
	//call operator setting both real and imaginary to zero!
	real = 0;
	im = 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
///////**THE FOLLOWING ARE FUNCTION DEFINITIONS FOR NON MEMBER INLINE/CONSTEXPR FUNCTIONS **/////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

constexpr Complex operator+(Complex leftNum, const Complex& rightNum)
{
	//here we just return the sum of the two numbers
	return leftNum += rightNum;
}

constexpr Complex operator-(Complex leftNum, const Complex& rightNum)
{
	//here we just return the result of the difference
	return leftNum -= rightNum;
}

constexpr Complex operator*(Complex leftNum, const Complex& rightNum)
{
	//here just return the result of the product of the two numbers
	return leftNum *= rightNum;
}

constexpr Complex operator/(Complex leftNum, const Complex& rightNum)
{
	//here just return the quotient of the two numbers
	return leftNum /= rightNum;
}

constexpr Complex operator""_i(long double cNum)
{
	//user defined literal expression, this will change 3.3_i to 0+3.3i
	//throw the zero in for the real slot so the imaginary number is not 
	//modified by the real number
	return Complex(0, cNum);
}

constexpr bool operator==(const Complex& leftNum, const Complex& rightNum)
{
	return (!(leftNum < rightNum) || (!(rightNum < leftNum))); //from time class in notes
}

//THE FOLLOWING ARE FRIEND OPERATORS 
constexpr bool operator<(const Complex& leftNum, const Complex& rightNum)
{
	//since function was declared as friend we have access to the private variables
	//condition for when the left real number is less than the right real number
	if (leftNum.real < rightNum.real)
	{
		return true;
	}
	//condition for when the real numbers are equal but the left imaginary number
	//is less than the right imaginary number
	else if (leftNum.real == rightNum.real && leftNum.im < rightNum.im)
	{
		return true;
	}
	//all other conditions we will return false for this operator
	else
	{
		return false;
	}
}

constexpr bool operator>(const Complex& leftNum, const Complex& rightNum)
{
	//since function was declared as friend we have access to the private member variables
	//must use (!(L < R)) format from Time class in notes when creating comparison operators
	if ((!(leftNum.real < rightNum.real) && leftNum.im != rightNum.im))
	{
		return true;
	}
	else
	{
		return false;
	}
	//this code was regurgitated from the time class
}

constexpr bool operator<=(const Complex& leftNum, const Complex& rightNum)
{
	//FUNCTION DECLARED AS FRIEND
	//basically a negation statement for "if not (>) then <="
	if (!(leftNum > rightNum))
	{
		return true;
	}
	//all other conditions return false
	else
	{
		return false;
	}
	//this code was regurgitated from the time class
}

constexpr bool operator>=(const Complex& leftNum, const Complex& rightNum)
{
	//basically a negation statement for >=
	if (!(leftNum < rightNum))
	{
		return true;
	}
	else
	{
		return false;
	}
	//this code was regurgitated from the time class
}

constexpr bool operator!=(const Complex& leftNum, const Complex& rightNum)
{
	
	if (!(leftNum == rightNum))
	{
		return true;
	}
	else
	{
		return false;
	}
	//this code was regurgitated from the time class
}

#endif

