# Attribute Grammar Example
This project implements a simple attribute grammar, which converts floating point binary number into a decimal one.

The project is written in [Reason](https://facebook.github.io/reason/).

## Grammar:
 1. S -> N<sub>1</sub> . N<sub>2</sub>
 	* S.v := N<sub>1</sub>.v + N<sub>2</sub>.v
    * N<sub>1</sub>.r := 0
    * N<sub>2</sub>.r := -N<sub>2</sub>.l

2. N -> N'B
	* N.v := N'.v + B.v
	* N.l := N'.l + 1
	* N'.r := N.r + 1 (N1 case)
	* N.r := -N.l (N2 case)
    * N'.r := -N'.l (N2 case)
	* B.r := N.r

3. N -> Lambda
	* N.v := 0
	* N.l := 0

4. B -> One
	* B.v := 2 <sup>B.r</sup>

5. B -> Zero
	* B.v := 0

## How to use:
The project is sandboxed which means that it has a lot of dependecies, so the installed project size is around 3.2 GB.

```sh
git clone https://github.com/StrykerKKD/attribute-grammar-example.git
cd attribute-grammar-example
yarn cache clean
yarn install
yarn build
yarn start
```

## Editor:
I mostly used visual studio code with the Reason extension, but you can use other editors(see Readme-Yarn).	
