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
```sh
git clone my_project_git_url
cd my_project
yarn cache clean
yarn install
yarn build
yarn start
```

## Editor:
I mostly used visual studio code with the Reason extension, but you can use other editors(see Readme-Yarn).