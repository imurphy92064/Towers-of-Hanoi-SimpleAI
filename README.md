# Towers-of-Hanoi-SimpleAI
This program solves the towers of hanoi problem using an augmented depth first search. The augmentation I made was to give scores to states, and depending on which state has
the lowest score, is the next state we move too. This can be given as an equation f=g+h, where f is the score, g is the number of moves so far, & h is an custom equation I came
up with. With trial and error I was able to tweak it so that it not only finds the correct path, but doesn't take to many wrong paths, and if does corrects quick. 
Some symbolism: S=small disk; M=meduim disk; L=large disk. 
SumPeg2(disk(s) NOT on peg 2), 
ProductPeg3(disk(s) on Peg 3) Where S=.5, M=.25, L=.125,
h = SumPeg2 * ProductPeg3. Where if either SumPeg2 or ProductPeg3 is 0 return the other that isn't 0.
