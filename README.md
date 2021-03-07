# Variance Reduced Replica Exchange SGHMC

Despite the advantages of gradient variance reduction in near-convex problems, a natural discrepancy between theory and practice is that whether we should avoid the gradient noise in non-convex problems. To fill in the gap, we only focus on the variance reduction of **noisy energy estimators** to exploit the theoretical accelerations but no longer consider the variance reduction of the noisy gradients so that the **empirical experience** from stochastic gradient descents with momentum (M-SGD) can be naturally imported.


### Requirement
* Python 2.7
* [PyTorch = 1.1](https://pytorch.org/) or similar
* numpy
* CUDA 


<p float="left">
  <img src="output/SGLD.gif" width="200" title="SGLD"/>
  <img src="output/reSGLD_vs_VR_reSGLD.gif" width="500" alt="Made with Angular" title="Angular" /> 
</p>


## Classification: ResNet20 on CIFAR100 with batch size 256

Momentum stochastic gradient descent (M-SGD) with 500 epochs, batch size 256 and decreasing learning rates
```python
$ python bayes_cnn.py -sn 500 -chains 1 -lr 2e-6 -LRanneal 0.984 -T 1e-300  -burn 0.6 
```


Stochastic Gradient Hamiltonian Monte Carlo (SGHMC) with annealing temperatures in warm-up period and fixed temperature afterward
```python
$ python bayes_cnn.py -sn 500 -chains 1 -lr 2e-6 -LRanneal 0.984 -T 0.01 -Tanneal 1.02 -burn 0.6 
```
Standard SGHMC with cylic learning rates and 1000 epochs
```python
$ python bayes_cnn.py -sn 1000 -chains 1 -lr 2e-6 -LRanneal 1.0 -T 0.001 -cycle 5 -period 0 -burn 0.7 
```

Standard Replica Exchange SGHMC (reSGHMC) with annealing temperatures in warm-up period and fixed temperature afterward
```python
$ python bayes_cnn.py -sn 500 -chains 2 -lr 2e-6 -LRanneal 0.984 -T 0.01 -var_reduce 0 -period 2 -bias_F 1.5e5 -burn 0.6 
```

Variance-reduced Replica Exchange SGLD with control variates updated every 2 epochs and fixed temperature after the warm-up period (Algorithm 1)
```python
$ python bayes_cnn.py -sn 500 -chains 2 -lr 2e-6 -LRanneal 0.984 -T 0.01 -var_reduce 1 -period 2 -bias_F 1.5e5 -burn 0.6 -seed 85674
```

Variance-reduced Replica Exchange SGLD with adaptive control variates and fixed temperature after the warm-up period (Algorithm 2)
```python
$ python bayes_cnn.py -sn 500 -chains 2 -lr 2e-6 -LRanneal 0.984 -T 0.01 -var_reduce 1 -period 2 -bias_F 1.5e5 -burn 0.6 -adapt_c 1
```

Variance-reduced Replica Exchange SGLD with adaptive control variates and a constant temperature (Algorithm 2)
```python
$ python bayes_cnn.py -sn 500 -chains 2 -lr 2e-6 -LRanneal 0.984 -T 0.0001 -Tanneal 1 -var_reduce 1 -period 2 -bias_F 1.5e7 -burn 0.6 -adapt_c 1 
```

## Uncertainty estimation: Test ResNet on CIFAR10 (seen) and SVHN (unseen)

Apply a temperature scaling of 2 for uncertainty calibration
```python
$ python uncertainty_test.py -c VR_reSGHMC -T_scale 2
$ python uncertainty_test.py -c cSGHMC -T_scale 2
```
