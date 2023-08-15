# borel-equidecomposition

This project is inspired by the graphic in this [quantamagazine article](https://www.quantamagazine.org/an-ancient-geometry-problem-falls-to-new-mathematical-techniques-20220208/).

Internally, it creates a bipartite graph with pixel on both images as vertices. It then picks some directions to draw a set of edges. The maximum cardinality bipartite matching yields the decomposition shown.

To use: run

```
compile.sh
```

You should be able to compile the code with pretty much any compiler. The C++ code generates bitmap images and `ffmpeg` compiles them into a video of the transformation.

## Example

![example gif](samples/square_to_circle.gif)
