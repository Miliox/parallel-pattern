# Pipeline

A Pipeline split a task in stages, stages are connected, the output of one
stage is the input of the next one, each stage execute in parallel.

## Linear Pipeline

A linear sequence of pipeline stages without branch.

```
input -> [stage1] -> [stage2] -> ... -> [stageN] -> -> output
```
<p align="center">Figure 1. Linear Pipeline</p>

## Nonlinear Pipeline

A sequence of pipeline stages with at least one branch.

```
                    -> [stage2a]
input -> [stage1] <              -> ... -> [stageN] -> -> output
                    -> [stage2b]
```
<p align="center">Figure 2. Nonlinear Pipeline</p>

# Execution Time

Each stage of pipeline can execute in parallel, but because the output
of one stage is the input of the next one, there is no guarantee
that at any time all stages will be busy.

The optimal implementation of pipeline, all stage will take almost
the same time to execute.

```
                  time
        ------------------------------->
stage1  [C1] [C2] [C3] [C4]
stage2       [C1] [C2] [C3] [C4]
stage3            [C1] [C2] [C3] [C4]
```
<p align="center">Figure 3. Pipeline [OPL Berkeley Pipeline]</p>

# Pipeline stage

```
Initialize
while (more data)
{
    receive data element from previous stage
    perform operation on data element
    send data elmeent to next stage
}
finalize
```
<p align="center">Figure 3. Pseudocode of pipeline stage [OPL Berkeley Pipeline]</p>

# Reference
[OPL Pipeline Pattern](http://parlab.eecs.berkeley.edu/wiki/_media/patterns/pipeline-v1.pdf)
