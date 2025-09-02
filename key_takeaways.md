- linmath mat4x4_mul_vec4 function modifies the result vector passed in while reading from the input vector.
    - so, don't pass in the same vector for the result and the input, it will corrupt the data.

- 