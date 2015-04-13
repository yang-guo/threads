## Description

Starts a threadpool and runs functions in the pool

## Documentation

All functions are under the namespace .threads

There is only one function
* _async[job;callback]_ runs the job and returns data to the callback

The parameters are
* job(_parselist_) parse list of expression to evaluate
* callback(_fn[x]_) takes in result of job

## Examples

```q
.threads.async[((*);5;3);{xx::x}] //Result is 15
```