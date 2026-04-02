# Why
If you are here because a comment told you to come, then I really appreciate you reading my code that thoroughly!
# Explanations
## pixels[y * pitch + x] = circ.color
```c
//this line has a meaning
pixels[y * pitch + x] = circ.color;
```
We know that RAM is just a big one dimensional array. When storing a 2d array (our screen), we need to cleverly space each row and column so they don't interfere and corrut eachother. Pitch is the width of each row in bytes. when we wanna jump over a few rows to draw to row 10 for example, we do
```c
y * pitch
```
the little **+x** at the end is just us jumping to the right column in our row.
```c
y * pitch * x
```

## 

