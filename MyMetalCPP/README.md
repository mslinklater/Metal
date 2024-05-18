# README

## TODO

* Move the shaders out in to their own .metal files - DONE
* Get rid of the temporary pointers - why are they there ? Seems a waste of space.

## Notes

### 00

### 01

The vertex positions and colours are stored in two different buffers.
The vertex shader just passes the vertex positions straight through without transform.

### 02 - Arg Buffer

The arg buffer stores two references to the two buffers from 01

### 03 - Animation

