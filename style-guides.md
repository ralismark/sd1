# Coding Style Guidelines

These are the guidelines on how to make good code.

## Indentation

One indent is a single tab character. This should be the size of 8 spaces, but
should never be a series of spaces. Indentation should not be present on empty
lines.

Refer to individual sections for specific indenting for each code structure.

## Functions

Functions have the whole definition on the same line. This excludes templates,
which you should refer to the templates section for.

The brace for the beginning of the function should be on the next line by
itself, and be at the same indent level as the function declaration. The closing
brace should be at the same level as the opening one, and be on its own line.

The content of the function should be one level greater than the declaration. It
should never be empty, even for constructors - use a single semicolon instead.
This is the only exception to the brace rule, as braces should both be on the
same line. Refer to the class section for details on constructors.

These are examples of correct function declarations:

``` cpp
int main(int argc, char** argv)
{
	// Do stuff at this level
	...
}

typename std::map<int, std::string>::key_type foo::bar::baz(int abc, const char* const * str) const
{
	...
}

type_xyz::type_xyz() // constructor
{ ; }
```

These are examples of incorrect declarations:

``` cpp
typename std::map<int, std::string>::key_type
foo::bar::baz(int abc,
	      const char* const * str) const
	      // Single line only
{
	...
}

int add(int a, int b) { return a + b; } // Must be split
```
