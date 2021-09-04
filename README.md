# SDDL
A simple tool to simulate digital circuit using a very simple sddl language.

### Instructions
Run bisim ( or built executble ) in directory where order.txt is present.

#### order.txt
    fulladder.sddl
    2bitadder.sddl
    dut.sddl

specify all the files to compile here in the order you want them to be compiled.
The first file compiles first.

#### sddl syntax

`fulladder.sddl`
```
component fulladder
signal s1,s2,s3
input a,b,cin
output s,cout
xor a,b -> s1
xor s1,cin -> s
and s1,cin -> s2
and a,b -> s3
or s2,s3 -> cout
```
general syntax here is `<cmd-name> <args>`.
#### Some Commands:
1. component command specifies name of component.
   Note there can be only one component per file.
2. signal s1,s2,s3 specifies the signals / wires that would be present.
3. input / output specify the input and out port of the component.
4. `<gate-name> <i1>,<i2>... -> <o0>,<o1>` is the way to specify gate io, here instead of gate-name component can also be used provided component is built earlier.

### Things To Note
1. Your final file in `order.txt` must contain a dut component.

```
`dut.sddl`

component dut
input a,b,c,d
output o1,o2,cout
2bitadder a,b,c,d -> o1,o2,cout
```
2. Look through the example files.
3. the executable most run in the same folder as order.txt.



